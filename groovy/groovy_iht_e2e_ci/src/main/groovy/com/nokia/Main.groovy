package com.nokia

import com.nokia.scripts.Knowledge
import com.nokia.scripts.Log as log

import groovy.json.JsonSlurperClassic
import com.nokia.scripts.ArtifactTools
import com.nokia.scripts.Log

class Main {

    static void main(String[] args) {
        log.setLevel("SUCCESS")
        Knowledge knowledge_playground = new Knowledge();
        knowledge_playground.show_collections();
    }
}
