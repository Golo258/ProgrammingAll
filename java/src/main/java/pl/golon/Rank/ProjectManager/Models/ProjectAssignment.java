package pl.golon.Rank.ProjectManager.Models;

public class ProjectAssignment {
    private int assignmentId;
    private String role;
    private int employeeId;
    private int projectId;

    public ProjectAssignment() {
    }
    public ProjectAssignment(int assignmentId, String role, int employeeId, int projectId) {
        this.assignmentId = assignmentId;
        this.role = role;
        this.employeeId = employeeId;
        this.projectId = projectId;
    }

    public int getAssignmentId() {
        return assignmentId;
    }

    public void setAssignmentId(int assignmentId) {
        this.assignmentId = assignmentId;
    }

    public String getRole() {
        return role;
    }

    public void setRole(String role) {
        this.role = role;
    }

    public int getEmployeeId() {
        return employeeId;
    }

    public void setEmployeeId(int employeeId) {
        this.employeeId = employeeId;
    }

    public int getProjectId() {
        return projectId;
    }

    public void setProjectId(int projectId) {
        this.projectId = projectId;
    }
}
