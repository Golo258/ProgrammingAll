package com.nokia

import com.nokia.scripts.ArtifactTools
import com.nokia.scripts.Knowledge
import com.nokia.scripts.Log as log

class Main {

    static void show_base() {
        Knowledge knowledge_playground = new Knowledge();
        knowledge_playground.show_collections();

        Knowledge.RegexMatching regexMatching = new Knowledge.RegexMatching(knowledge_playground)
        regexMatching.qualificators()
        regexMatching.anchors()
        regexMatching.sign_classes()
        regexMatching.greedy_lazy()
        regexMatching.flags()
        regexMatching.matching()
    }

    static void debugCusUpdate() {
        String hostname = "192.168.1.13"
        ArtifactTools artifactTools = new ArtifactTools(hostname)
        List<String> ctrlBuilds = artifactTools.receiveInstalledBuildsOnCtrl()
        String targetBuild = "CUS.251126.04"
        ctrlBuilds.any { it.contains(targetBuild) }
    }

    static void main(String[] args) {
        log.setLevel("SUCCESS")
//        show_base();
        debugCusUpdate()


    }
}
