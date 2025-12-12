package com.nokia.scripts.jenkins_local

import net.schmizz.sshj.SSHClient
import net.schmizz.sshj.connection.channel.direct.Session
import net.schmizz.sshj.sftp.SFTPClient
import net.schmizz.sshj.transport.verification.PromiscuousVerifier

import java.util.concurrent.atomic.AtomicBoolean

class SshNodeSession implements AutoCloseable {
    private final String host;
    private final int port;
    private final String user;
    private final String password;
    private final String privateKeyPath;
    private final int connectTimeoutMs;
    private final int sessionTimeoutMs


    private SSHClient ssh;
    private final AtomicBoolean open = new AtomicBoolean(false)

    SshNodeSession(
        int port, String host,
        String privateKeyPath, String password, String user,
        int sessionTimeoutMs = 15000, int connectTimeoutMs = 600000
    ) {
        this.host = host
        this.port = port
        this.user = user
        this.password = password
        this.privateKeyPath = privateKeyPath
        this.connectTimeoutMs = connectTimeoutMs
        this.sessionTimeoutMs = sessionTimeoutMs
    }

    synchronized void open() {
        if (open.get()) {
            return
        }
        ssh = new SSHClient()
        ssh.addHostKeyVerifier(new PromiscuousVerifier())
        ssh.connect(host, port)
        ssh.getConnection().setTimeoutMs(sessionTimeoutMs)
        if (privateKeyPath) {
            ssh.authPublickey(user, privateKeyPath)
        } else if (password) {
            ssh.authPassword(user, password)
        } else {
            ssh.authPublickey(user)
        }
        ssh.getTransport().setHeartbeatInterval(30) // sec
        open.set(true)
    }


    synchronized ShResult exec(String command, boolean allocatePty = false) {
        ensureOpen()
        Session session = ssh.startSession()
        try {
            if (allocatePty) {
                session.allocateDefaultPTY()
            }
            Session.Command cmd = session.exec(command)
            String stdout = cmd.inputStream.getText("UTF-8")
            String stderr = cmd.errorStream.getText("UTF-8")
            cmd.join()
            int code = cmd.exitStatus ?: 0
            return new ShResult(code, stdout, stderr)
        } finally {
            session.close()
        }
    }

    synchronized void upload(String localPath, String remotePath) {
        ensureOpen()
        SFTPClient sftp = ssh.newSFTPClient()
        try {
            sftp.put(localPath, remotePath)
        }
        finally {
            sftp.close()
        }
    }

    private void ensureOpen() {
        if (!open.get()) {
            open()
        }
    }

    @Override
    synchronized void close() {
        if (!open.get()) {
            return
        }
        try {
            ssh.disconnect()
        }
        catch (ignored) {
        }
        try {
            ssh.close()
        }
        catch (ignored) {
        }
        open.set(false)
    }


}
