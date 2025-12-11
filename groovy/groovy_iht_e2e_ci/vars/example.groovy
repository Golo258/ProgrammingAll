
def call(Map args = [:]) {
    echo "myStep: start, args=${args}"
    if (args.fail) {
        error "Requested failure"
    }
    def output = sh(script: "echo hello", returnStdout: true).trim()
    echo "myStep: output=${output}"
    return output
