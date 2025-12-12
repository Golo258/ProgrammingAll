package com.nokia.scripts.jenkins_local

class LocalShExecutor implements ShExecutor {
    @Override
    ShResult run(String command) {
        boolean isWindows = System
            .getProperty("os.name")
            .toLowerCase()
            .contains("win")
        String[] cmd = isWindows
            ? ["cmd.exe", "c/", command]
            : ["/bin/bash", "-lc", command]
        Process process = new ProcessBuilder(cmd)
            .redirectErrorStream(false)
            .start()
        String stdout = process.inputStream.getText("UTF-8")
        String stderr = process.errorStream.getText("UTF-8")
        int code = process.waitFor()
        return new ShResult(code, stdout, stderr)
    }
}

