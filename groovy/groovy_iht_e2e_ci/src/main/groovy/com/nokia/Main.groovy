package com.nokia

import com.nokia.scripts.ArtifactTools
import com.nokia.scripts.Knowledge
import com.nokia.scripts.Log as log

class Main {

    static Knowledge base = new Knowledge()
    // collections
    static Knowledge.CollectionsPlayground collections = new Knowledge.CollectionsPlayground(this.base)
    static Knowledge.CollectionsPlayground.ListPlayground listPlayground = new Knowledge.CollectionsPlayground.ListPlayground(this.collections)
    static Knowledge.CollectionsPlayground.MapPlayground mapPlayground = new Knowledge.CollectionsPlayground.MapPlayground(this.collections)

    static void present_collections() {
        this.listPlayground.creation();
        this.listPlayground.operations();
        this.listPlayground.accessAndSlices();
        this.listPlayground.iterationAndTransformation();
    }

    //    string operations
    static Knowledge.RegexMatching regexMatching = new Knowledge.RegexMatching(this.base)
    static Knowledge.JsonPlayground jsonPlayground = new Knowledge.JsonPlayground(this.base)


    static void show_base() {
        this.base.show_collections()
        this.regexMatching.qualificators()
        this.regexMatching.anchors()
        this.regexMatching.sign_classes()
        this.regexMatching.greedy_lazy()
        this.regexMatching.flags()
        this.regexMatching.matching()
    }

    static void debugCusUpdate() {
        String hostname = "10.84.158.242"
        ArtifactTools artifactTools = new ArtifactTools(hostname)
        List<String> ctrlBuilds = artifactTools.receiveInstalledBuildsOnCtrl()
        String targetBuild = "CUS.251126.04"
        ctrlBuilds.any { it.contains(targetBuild) }
    }

    static void debugRequiredEnvParameters() {
        def env = [
            "TESTLINE"       : null,
            "TEST_SUITE_FILE": "fas",
            "CUS_BUILD_NAME" : "CUS123",
            "ESIM_BUILD_NAME": "ESIM123"
        ]
        List<String> requiredEnvParams = ["TESTLINE", "TEST_SUITE_FILE", "CUS_BUILD_NAME", "ESIM_BUILD_NAME"]
        log.debug(env["CUS_BUILD_NAME"])
        log.debug(env.CUS_BUILD_NAME)
        def missingParams = env.findAll { key, value ->
            return (key in requiredEnvParams) && !value
        }
        if (!missingParams.isEmpty()) {
            log.debug("Missing ${missingParams.keySet()} parameters")
        } else {
            log.success("there is no missing properties")
        }
        def missingAny = env.any { key, value ->
            (key in requiredEnvParams) && !value
        }
        log.debug("any missing: ${missingAny}")

    }

    static void debugArtifactsTools() {
        ArtifactTools tools = new ArtifactTools("10.84.158.242")
//        tools.debugSshResultVersion();
        tools.debugCreatingArtifactObjects();
    }

    static void main(String[] args) {
        log.setLevel("SUCCESS")

        this.debugArtifactsTools();

    }

}
