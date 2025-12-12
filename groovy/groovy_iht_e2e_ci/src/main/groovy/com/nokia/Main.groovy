package com.nokia

import com.nokia.scripts.ArtifactTools
import com.nokia.scripts.Knowledge
import com.nokia.scripts.Log as log

class Main {

    static void main(String[] args) {
        log.setLevel("SUCCESS")

        Knowledge knowledge_playground = new Knowledge();
//        knowledge_playground.show_collections();
//        knowledge_playground.regexMatching()
        Knowledge.RegexMatching regexMatching = new Knowledge.RegexMatching(knowledge_playground)
        regexMatching.qualificators()
        regexMatching.anchors()
        regexMatching.sign_classes()
        regexMatching.greedy_lazy()
        regexMatching.flags()
        regexMatching.matching()
        
        ArtifactTools artifactTools = new ArtifactTools()

        artifactTools.debugExecuteCusUtil()
    }
}
