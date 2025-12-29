package com.nokia.scripts.jenkins_local

class ShResult {
    final int exitCode;
    final String stdOut;
    final String stdErr;

    ShResult(int exitCode, String stdOut, String stdErr) {
        this.exitCode = exitCode;
        this.stdOut = stdOut;
        this.stdErr = stdErr;
    }

    boolean isSuccess() {
        exitCode == 0;
    }
    /*
        operator overloading - przeciążanie operatorów
            .getAt() odpowiada za:
                - dostep do elementu przez []
                - destrukturyzacje (x,y,z) = obiekt

     */

    def getAt(int index) {
        switch (index) {
            case 0: return exitCode;
            case 1: return stdOut
            case 2: return stdErr
            default:
                throw new IndexOutOfBoundsException(
                    "Invalid index: ${index}"
                )
        }
    }

    @Override
    String toString() { "exit=${exitCode}\nSTDOUT:\n${stdOut}\nSTDERR:\n${stdErr}" }

}
