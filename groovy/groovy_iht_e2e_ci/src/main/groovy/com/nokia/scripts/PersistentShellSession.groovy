package com.nokia.scripts

import com.nokia.scripts.jenkins_local.ShResult
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

    private final String MARK = "___END__MARK___" + UUID.randomUUID().toString()

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

        Thread.sleep(500)
        drain()

        sendInit([
            'stty -echo',
            'unset PROMPT_COMMAND',
            'PS1=',
            'set -o pipefail',
            'export LC_ALL=C'
        ])
        open = true
    }

    private void sendInit(List<String> lines) {
        lines.each { String l ->
            stdin.write((l + "\n").getBytes(StandardCharsets.UTF_8))
        }
        stdin.flush()
        Thread.sleep(200)
        drain()
    }

    private void drain() {
        byte[] buf = new byte[4096]
        while (stdout.available() > 0) stdout.read(buf)
        while (stderr.available() > 0) stderr.read(buf)
    }

    private void ensureOpen() {
        if (!open) open()
    }

    synchronized ShResult run(String cmd, long timeoutMs = defaultTimeoutMs, boolean collectErr = false) {
        ensureOpen()

        String payload = "${cmd}; rc=\$?; printf '%s:%d\\n' '${MARK}' \"\$rc\"\n"

        stdin.write(payload.getBytes(StandardCharsets.UTF_8))
        stdin.flush()

        long deadline = System.currentTimeMillis() + timeoutMs
        StringBuilder outBuilder = new StringBuilder()
        StringBuilder errBuilder = new StringBuilder()
        byte[] buf = new byte[4096]

        Integer exitCode = null

        while (System.currentTimeMillis() < deadline) {
            while (stdout.available() > 0) {
                int n = stdout.read(buf)
                if (n > 0) outBuilder.append(new String(buf, 0, n, StandardCharsets.UTF_8))
            }
            if (collectErr) {
                while (stderr.available() > 0) {
                    int n = stderr.read(buf)
                    if (n > 0) errBuilder.append(new String(buf, 0, n, StandardCharsets.UTF_8))
                }
            }

            String currentOutput = outBuilder.toString()
            int idx = currentOutput.indexOf(MARK + ":")

            if (idx >= 0) {
                int start = idx + (MARK + ":").length()
                int eol = currentOutput.indexOf("\n", start)

                String codeStr = (eol >= 0 ? currentOutput.substring(start, eol) : currentOutput.substring(start)).trim()
                def m = (codeStr =~ /^(\d+)/)
                exitCode = m.find() ? m.group(1).toInteger() : -1

                outBuilder.delete(idx, eol >= 0 ? eol + 1 : outBuilder.length())

                String cleanOut = outBuilder.toString().replace("\r\n", "\n").trim()
                String cleanErr = errBuilder.toString().replace("\r\n", "\n").trim()

                return new ShResult(exitCode, cleanOut, cleanErr)
            }

            Thread.sleep(50) // Krótka pauza, żeby nie zarżnąć CPU pętlą while
        }

        throw new RuntimeException("Timeout (${timeoutMs} ms) waiting for command result on ${host}")
    }

    @Override
    synchronized void close() {
        if (!open) return
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
}