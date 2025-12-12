package com.nokia.scripts.jenkins_local

class NodeRegistry {
    static ShExecutor forNode(String nodeName) {
        switch (nodeName) {
            case "linux-vm":
                return new SshShExecutor(
                    "10-7-T05SK095.p05.ska-lab.nsn-rdnet.net",
                    22,
                    "ute",
                    "ute",
                    null
                )
            case "local":
                return new LocalShExecutor()
            default:
                throw new IllegalArgumentException("Unknown node ${nodeName}")
        }
    }
}
