package com.nokia.scripts

import com.nokia.scripts.Log as log
import com.nokia.scripts.jenkins_local.NodeRegistry
import com.nokia.scripts.jenkins_local.NodeSessionManager
import com.nokia.scripts.jenkins_local.ShResult
import groovy.json.JsonOutput

class ArtifactTools {

    ArtifactTools() {}

    void debugExecuteCusUtil() {
        def manager = new NodeSessionManager()
        def shell = manager.getShell("linux-vm") {
            new PersistentShellSession(
                "10-7-T05SK095.p05.ska-lab.nsn-rdnet.net",
                22,
                "ute",
                "ute",
                null
            )
        }
        def cusUtilResultOutput = shell.run(
            '/opt/cus/bin/cus-util.py ver | grep -oP \"RUN = \\K[^ ]+\"'
        )
        def outputTrimed = cusUtilResultOutput.stdout.trim()
        log.debug("Cus util result version: ${outputTrimed}")

        def collectedBuildVersions = outputTrimed
            .readLines()
            .findAll { cusBuildOnCtrl ->
                log.debug("Checking cus-util output line ${cusBuildOnCtrl}")
                if (cusBuildOnCtrl ==~ /CUS[\._]?\d+\.\d+(\.REL|\.DEV)?\.\d+\.\d+(\.DEV)?|CUS\.\d+\.\d+(\.\d+)?(\.DEV)?/) {
                    log.debug("${cusBuildOnCtrl} is valida cus build")
                    return true
                }
            }
        log.debug("Collected bbuilds: ${collectedBuildVersions}")

    }

    void connectToRemoteHostAndRunCommand() {
        def executor = NodeRegistry.forNode("linux-vm")
        ShResult result = executor.run("hostname")
        log.debug(
            "Exit code: ${result.exitCode}\n" +
                "Stdout: ${result.stdout}\n" +
                "Stderr: ${result.stderr}\n"
        )
    }

    void connectToNodeAndStayOnSession() {
        def manager = new NodeSessionManager()
        try {
            def shell = manager.getShell("linux-vm") {
                new PersistentShellSession(
                    "10-7-T05SK095.p05.ska-lab.nsn-rdnet.net",
                    22,
                    "ute",
                    "ute",
                    null
                )
            }
            def pwdResult = shell.run("pwd")
            def echoResult = shell.run("echo 'siemano'")
            def lsResult = shell.run("ls -la")
            log.debug("Result pwd: ${pwdResult.stdout}")
            log.debug("Result echo: ${echoResult.stdout}")
            log.debug("Result ls: ${lsResult.stdout}")
        }
        finally {
            manager.close()
        }
    }


    static Map getjsonApiHeaders(Map headers, String WFT_TOKEN) {
        return [
            items                  : 100,
            sorting_field          : "created_at",
            sorting_direction      : "DESC",
            columns                : [
                0: [id: "version"],
                1: [id: "quicktest_status"],
                3: [id: "test_result_group", element: "1"],
                6: [id: "delivery_date"]
            ],
            projects               : ["ALL"],
            view_filters_attributes: [
                0: [column: "version", operation: "eq"],
                1: [column: headers["columnOption"], operation: "eq", value: headers["branch"]]
            ],
            access_key             : WFT_TOKEN
        ]
    }

    static Map getWftArtifacts(String wftUrl, Map headers, Closure<Boolean> condition) {
        def response;
        def expectedArtifact = null;
        String wftToken = (headers?.branch == "RTG")
            ? "abcd456"
            : "efgf123"
        Map jsonApiHeaders = getjsonApiHeaders(headers, wftToken)
        for (int i = 0; i <= 5; i++) {
            try {
                jsonApiHeaders["page"] = i;
                response = HttpClient.httpRequest(
                    "/api/v1/build_branch.json",
                    "POST",
                    jsonApiHeaders,
                    [:]
                )
                assert response["code"] == 200: "Unexpected HTTP code: ${response?.code}"
                expectedArtifact = response?.bodyJson?.items.find(condition)
                if (expectedArtifact)
                    return expectedArtifact
            }
            catch (Exception wftException) {
                Log.debug("Artifact not found in WFT. Error: ${wftException}")
            }
        }
    }

    static Map getEndpointHeaders(String projectVersion) {
        def headers = (projectVersion.contains("Esim"))
            ? [endpointPrefix: "build", columnOption: "deliverer.title"]
            : [endpointPrefix: "build_branch", columnOption: "branch.title"]

        headers["branch"] = (projectVersion.contains("CUS") ?
            (projectVersion in ["CUS1", "CUS3"] ? "CUS_TRUNK" : "CUS_2.0")
            : projectVersion
        )
        return headers
    }

    static String buildQueryNested(Map params) {
        if (!params) return ""
        def encode = {
            String s -> URLEncoder.encode(s, "UTF-8").replace("+", "%20")
        }
        return params.collect { String key, Object value ->
            String parsedValue = (value == null) ? "" : (value instanceof Map)
                ? JsonOutput.toJson(value) : value.toString()
            "${key}=${encode(parsedValue)}"
        }.join("&")
    }

    static String buildQueryParams(Map<String, Object> params) {
        return params
            .collect { k, v -> "${k}=${v}" }
            .join('&')
    }

}
