package com.nokia.scripts


import groovy.json.JsonOutput
import groovy.json.JsonSlurperClassic
import okhttp3.*
import java.time.Duration

class HttpClient {
    static OkHttpClient client = new OkHttpClient.Builder()
        .callTimeout(Duration.ofSeconds(120))
        .build()

    static Map httpRequest(
        String url,
        String method,
        Object payload = null,
        Map<String, String> headers = [:]
    ) {

        String safeUrl = url?.replaceAll(/\?+$/, "")
        RequestBody body = null
        if (payload != null && method.equalsIgnoreCase("POST")) {
            String json = JsonOutput.toJson(payload)
            body = RequestBody.create(json, MediaType.parse("application/json; charset=utf-8"))
        }

        Request.Builder rb = new Request.Builder().url(safeUrl)
        headers?.each { k, v -> rb.addHeader(k, v) }
        rb.addHeader("Accept", "application/json")
        if (payload != null && method.equalsIgnoreCase("POST"))
            rb.addHeader("Content-Type", "application/json")

        switch (method.toUpperCase()) {
            case "GET": rb.get(); break
            case "POST": rb.post(body ?: RequestBody.create(new byte[0])); break
            case "PUT": rb.put(body ?: RequestBody.create(new byte[0])); break
            case "DELETE": rb.delete(body); break
            default: throw new IllegalArgumentException("Unsupported method: $method")
        }

        Response resp = client.newCall(rb.build()).execute()
        String raw = resp.body()?.string() ?: ""
        def jsonOut = null
        try {
            if (raw) jsonOut = new JsonSlurperClassic().parseText(raw)
        } catch (ignored) {
        }
        return [code: resp.code(), bodyJson: jsonOut, rawOut: raw]
    }
}
