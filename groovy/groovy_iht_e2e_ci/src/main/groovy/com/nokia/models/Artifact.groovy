package com.nokia.models
/*
    Instance representing WFT artifact
*/

class MainState {
    private String status;
    private boolean started;

    MainState(String status, boolean started) {
        this.status = status
        this.started = started
    }

    String getStatus() {
        return status
    }

    boolean getStarted() {
        return started
    }


    @Override
    public String toString() {
        return "MainState{" +
            "status='" + status + '\'' +
            ", started=" + started +
            '}';
    }
}

class PhaseState {
    private String label;
    private String status;

    PhaseState(String label, String status) {
        this.label = label
        this.status = status
    }

    String getLabel() {
        return label
    }

    String getStatus() {
        return status
    }

    @Override
    public String toString() {
        return "PhaseState{" +
            "label='" + label + '\'' +
            ", status='" + status + '\'' +
            '}';
    }
}

class Artifact {
    private String buildName;
    private MainState mainState;
    private List<PhaseState> phaseStates;

    Artifact(Map jsonWftData) {
        this.buildName = jsonWftData?.version
        this.mainState = new MainState(
            jsonWftData?.quicktest_status?.state,
            jsonWftData?.quicktest_status?.started
        )
        this.phaseStates = jsonWftData["test_result_group@1"].collect { phase ->
            new PhaseState(
                phase?.test_type,
                phase?.result
            )
        }
    }

    String getBuildName() {
        return buildName
    }

    MainState getMainState() {
        return mainState
    }

    List<PhaseState> getPhaseStates() {
        return phaseStates
    }

    void setMainState(MainState mainState) {
        this.mainState = mainState
    }

    void setBuildName(String buildName) {
        this.buildName = buildName
    }

    void setPhaseStates(List<PhaseState> phaseStates) {
        this.phaseStates = phaseStates
    }

    @Override
    public String toString() {
        return "Artifact{" +
            "buildName='" + buildName + '\'' +
            ", mainState=" + mainState +
            ", phaseStates=" + phaseStates +
            '}';
    }
}
