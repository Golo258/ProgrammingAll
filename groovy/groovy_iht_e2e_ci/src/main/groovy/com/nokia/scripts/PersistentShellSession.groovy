package com.nokia.scripts

import net.schmizz.sshj.SSHClient
import net.schmizz.sshj.connection.channel.direct.Session
import net.schmizz.sshj.transport.verification.PromiscuousVerifier

import java.nio.charset.StandardCharsets

class PersistentShellSession implements AutoCloseable {

    private final String host
    private final int port
    private final String user
    private final String password
    private final String privateKeyPath

    private SSHClient ssh
    private Session session
    private Session.Shell shell
    private OutputStream stdin
    private InputStream stdout
    private InputStream stderr
    private boolean open = false

    private String MARK = "___END__MARK___" + UUID.randomUUID().toString()

    long defaultTimeoutMs = 30000L

    PersistentShellSession(String host, int port = 22, String user,
                           String password = null, String privateKeyPath = null) {
        this.host = host
        this.port = port
        this.user = user
        this.password = password
        this.privateKeyPath = privateKeyPath
    }

    synchronized void open() {
        if (open) return
        ssh = new SSHClient()
        ssh.addHostKeyVerifier(new PromiscuousVerifier())
        ssh.connect(host, port)

        if (privateKeyPath) ssh.authPublickey(user, privateKeyPath)
        else if (password) ssh.authPassword(user, password)
        else ssh.authPublickey(user)

        session = ssh.startSession()
        session.allocateDefaultPTY()
        shell = session.startShell()
        stdin = shell.getOutputStream()
        stdout = shell.getInputStream()
        stderr = shell.getErrorStream()
        open = true

        drain()

        sendInit([
            'set -o pipefail',
            'export LC_ALL=C'
        ])
    }

    private void sendInit(List<String> lines) {
        lines.each { String l ->
            stdin.write((l + "\n").getBytes(StandardCharsets.UTF_8))
        }
        stdin.flush()
        drain()
    }

    private void drain() {
        byte[] buf = new byte[4096]
        while (stdout.available() > 0) {
            stdout.read(buf)
        }
        while (stderr.available() > 0) {
            stderr.read(buf)
        }
    }

    private void ensureOpen() {
        if (!open) open()
    }

    synchronized ShResult run(String cmd, long timeoutMs = defaultTimeoutMs, boolean collectErr = false) {
        ensureOpen()
        String payload = cmd + '\n' + 'rc=$?; printf "%s:%d\n" "' + MARK + '" "$rc"' + '\n'

        stdin.write(payload.getBytes(StandardCharsets.UTF_8))
        stdin.flush()

        long deadline = System.currentTimeMillis() + timeoutMs
        StringBuilder out = new StringBuilder()
        StringBuilder err = new StringBuilder()
        byte[] buf = new byte[4096]

        Integer exitCode = null

        while (System.currentTimeMillis() < deadline) {
            while (stdout.available() > 0) {
                int n = stdout.read(buf)
                if (n <= 0) break
                out.append(new String(buf, 0, n, StandardCharsets.UTF_8))
            }
            // stderr (opcjonalnie)
            if (collectErr) {
                while (stderr.available() > 0) {
                    int n = stderr.read(buf)
                    if (n <= 0) break
                    err.append(new String(buf, 0, n, StandardCharsets.UTF_8))
                }
            }

            int idx = out.indexOf(MARK + ":")
            if (idx >= 0) {
                int eol = out.indexOf("\n", idx)
                String tail = (eol >= 0 ? out.substring(idx, eol) : out.substring(idx))
                def m = (tail =~ /\d+/)  // znajdź sekwencję cyfr
                if (m.find()) {
                    exitCode = Integer.parseInt(m.group())
                } else {
                    exitCode = 255
                }

                if (eol >= 0) {
                    out.delete(idx, eol + 1)
                } else {
                    out.delete(idx, out.length())
                }

                String cleanOut = out.toString().replace("\r\n", "\n").trim()
                String cleanErr = err.toString().replace("\r\n", "\n").trim()

                return new ShResult(exitCode, cleanOut, cleanErr)
            }

            Thread.sleep(20)
        }

        throw new RuntimeException("Timeout (${timeoutMs} ms) waiting for command result and marker '${MARK}'")
    }

    @Override
    synchronized void close() {
        try {
            stdin?.close()
        } catch (ignored) {
        }
        try {
            shell?.close()
        } catch (ignored) {
        }
        try {
            session?.close()
        } catch (ignored) {
        }
        try {
            ssh?.disconnect()
        } catch (ignored) {
        }
        try {
            ssh?.close()
        } catch (ignored) {
        }
        open = false
    }

    static class ShResult {
        final int exitCode
        final String stdout
        final String stderr

        ShResult(int exitCode, String stdout, String stderr) {
            this.exitCode = exitCode
            this.stdout = stdout
            this.stderr = stderr
        }

        boolean isSuccess() { exitCode == 0 }

        @Override
        String toString() { "exit=${exitCode}\nSTDOUT:\n${stdout}\nSTDERR:\n${stderr}" }
    }
}
