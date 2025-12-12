package com.nokia

import com.nokia.scripts.ArtifactTools
import com.nokia.scripts.Knowledge
import com.nokia.scripts.Log as log

class Main {

    static void main(String[] args) {
        log.setLevel("SUCCESS")
        Knowledge knowledge_playground = new Knowledge();
        knowledge_playground.show_collections();
        ArtifactTools artifactTools = new ArtifactTools()
        artifactTools.debugExecuteCusUtil()
        artifactTools.connectToRemoteHostAndRunCommand();
    }
}
