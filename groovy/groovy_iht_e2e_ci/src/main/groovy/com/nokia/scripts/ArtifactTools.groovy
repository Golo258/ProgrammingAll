package com.nokia.scripts


import groovy.json.JsonOutput
import com.nokia.scripts.HttpClient

class ArtifactTools {

    static Map triggerRules = [
        P2: [
            CUS : [
                mainState: "RELEASED_FOR_QUICKTEST",
                labels   : ["L1PERF"]
            ],
            ESIM: [
                mainState: "RELEASED_FOR_QUICKTEST",
            ],
            RTG : [
                mainState: "RELEASED_FOR_QUICKTEST",
            ],
        ],
        P3: [
            CUS : [
                mainState: ".*", // any state is good,
                labels   : ["FUNCTIONAL"]
            ],
            ESIM: [
                mainState: "RELEASED_FOR_QUICKTEST",
            ]
        ]
    ]

    static Map getjsonApiHeaders(Map headers, String WFT_TOKEN) {
        return [
            items              : 100,
            sorting_field      : "created_at",
            sorting_direction  : "DESC",
            columns            : [
                0: [id: "version"],
                1: [id: "quicktest_status"],
                3: [id: "test_result_group", element: "1"],
                6: [id: "delivery_date"]
            ],
            projects : ["ALL"],
            view_filters_attributes: [
                0: [column: "version", operation: "eq"],
                1: [column: headers["columnOption"], operation: "eq", value: headers["branch"]]
            ],
            access_key : WFT_TOKEN
        ]
    }

    static void setBuildArtifactVariables(String project) {
        String projectName = project.split('_')[0]

        def cusBasedRules = getArtifactBasedRules(projectName, "P2")
        Log.debug("Headers: ${project}: ${cusBasedRules}")
        Map cusArtifact = getWftArtifacts(
                cusBasedRules["url"] as String,
                cusBasedRules["headers"] as Map,
                cusBasedRules["condition"] as Closure,
        )
        Log.debug("cusArtifact: ${cusArtifact}")
        def esimBasedRules = getArtifactBasedRules("Esim", "P2")
        def esimArtifact = getWftArtifacts(
            esimBasedRules["url"] as String,
            esimBasedRules["headers"] as Map,
            esimBasedRules["condition"] as Closure,
        )
        Log.debug("esimArtifact :${esimArtifact}")

    }

    static Map getWftArtifacts(String wftUrl, Map headers, Closure<Boolean> condition) {
        def response;
        def expectedArtifact = null;
        String wftToken = (headers?.branch == "RTG")
                ? "YwNnseOHtppL14ow3hSP1lO9hebBu3UWeiGs6KBd"
                : "YwNnseOHtppL14ow3hSP1lO9hebBu3UWeiGs6KBd"
        Map jsonApiHeaders = getjsonApiHeaders(headers, wftToken)
        for (int i = 0; i <= 5; i++) {
            try {
                jsonApiHeaders["page"] = i;
                response = HttpClient.httpRequest(
                    "https://wft.int.net.nokia.com:8091/ALL/api/v1/build_branch.json",
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


    static Map getArtifactBasedRules(String projectName, String phase) {
        String artifactType = projectName.split("\\d+")[0]
        Map headers = getEndpointHeaders(projectName)
        Log.debug("Headers: ${artifactType}: ${headers}")
        Closure<Boolean> artifactCondition
        Map artifactRules = triggerRules[phase][artifactType.toUpperCase()]
        Log.info("currentPhaseRules: ${artifactRules}")
        if (artifactType.contains("CUS")) {
            artifactCondition = { build ->
                Boolean mainState = (build?.quicktest_status?.state == artifactRules.mainState.toLowerCase())
                Boolean phaseState = (
                    build["test_result_group@1"].any { groupElement ->
                        (groupElement.result == "released") &&
                            (groupElement.test_type.contains(artifactRules.labels.first()))
                        }
                )
                return mainState && phaseState
            }
        } else { // ESIM | RTG
            artifactCondition = {
                it.quicktest_status?.state == artifactRules.mainState.toLowerCase()
            }
        }
        return [
            url      : "https://wft.int.net.nokia.com:8091/ALL/api/v1/${headers['endpointPrefix']}.json?",
            headers  : headers,
            condition: artifactCondition
        ]
    }
}
