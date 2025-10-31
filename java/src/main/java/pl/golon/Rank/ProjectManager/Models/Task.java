package pl.golon.Rank.ProjectManager.Models;

import java.time.LocalDate;

public class Task {
    private int id;
    private String description;
    private LocalDate dueDate;
    private String status; // TODO, IN PROGRESS, DONE, COMPLETED
    private int projectId;

    public Task() {
    }
    public Task(int id, String description, LocalDate dueDate, String status, int projectId) {
        this.id = id;
        this.description = description;
        this.dueDate = dueDate;
        this.status = status;
        this.projectId = projectId;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public LocalDate getDueDate() {
        return dueDate;
    }

    public void setDueDate(LocalDate dueDate) {
        this.dueDate = dueDate;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public int getProjectId() {
        return projectId;
    }

    public void setProjectId(int projectId) {
        this.projectId = projectId;
    }
}
