package com.nokia.scripts.jenkins_local

import net.schmizz.sshj.SSHClient
import net.schmizz.sshj.connection.channel.direct.Session
import net.schmizz.sshj.transport.verification.PromiscuousVerifier

class SshShExecutor implements ShExecutor {

    private final String host
    private final int port
    private final String username
    private final String password
    private final String privateKeyPath

    SshShExecutor(String host, int port, String username, String password, String privateKeyPath = null) {
        this.host = host
        this.port = port
        this.username = username
        this.password = password
        this.privateKeyPath = privateKeyPath
    }

    @Override
    ShResult run(String command) {
        SSHClient sshClient = new SSHClient()
        sshClient.addHostKeyVerifier(new PromiscuousVerifier())
        sshClient.connect(host, port);
        if (privateKeyPath) {
            sshClient.authPublickey(username, privateKeyPath)
        } else if (password) {
            sshClient.authPassword(username, password)
        } else {
            throw new IllegalStateException("No auth method provided")
        }

        Session session = sshClient.startSession()
        try {
            Session.Command cmd = session.exec(command)
            String stdout = cmd.inputStream.getText("UTF-8")
            String stderr = cmd.errorStream.getText("UTF-8")
            cmd.join()
            int exit = cmd.exitStatus
            return new ShResult(exit, stdout, stderr)
        }
        finally {
            session.close()
            sshClient.disconnect()
            sshClient.close()
        }
    }
}
