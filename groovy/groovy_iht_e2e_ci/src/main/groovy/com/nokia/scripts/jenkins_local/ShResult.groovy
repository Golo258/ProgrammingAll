package com.nokia.scripts.jenkins_local

class ShResult {
    final int exitCode;
    final String stdout;
    final String stderr;

    ShResult(int exitCode, String stdout, String stderr) {
        this.exitCode = exitCode;
        this.stdout = stdout;
        this.stderr = stderr;
    }

    boolean isSuccess() {
        exitCode == 0;
    }
}
