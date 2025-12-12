package com.nokia.scripts.jenkins_local

import com.nokia.scripts.PersistentShellSession

import java.util.concurrent.ConcurrentHashMap

class NodeSessionManager implements AutoCloseable {


    private final Map<String, SshNodeSession> sshCache = new ConcurrentHashMap<>()
    private final Map<String, PersistentShellSession> shellCache = new ConcurrentHashMap<>()


    SshNodeSession getSsh(String node, Closure<SshNodeSession> builder) {
        sshCache.computeIfAbsent(node) { name ->
            def nodeSession = builder.call()
            nodeSession.open()
            return nodeSession
        }
    }

    PersistentShellSession getShell(String node, Closure<PersistentShellSession> builder) {
        shellCache.computeIfAbsent(node) { name ->
            def shellSession = builder.call()
            shellSession.open()
            return shellSession
        }
    }

    @Override
    void close() {
        sshCache.values().each { it.close() }
        shellCache.values().each { it.close() }
        sshCache.clear(); shellCache.clear()
    }
}
