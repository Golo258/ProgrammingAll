package pl.golon.TaskManagerProject.Models;

public class Task {
    private static long taskCount = 0;
    private long id;
    private String title;
    private String description;
    private boolean status;

    public Task() {
    }

    public Task(String title, String description) {
        this.id = ++taskCount;
        this.title = title;
        this.description = description;
        this.status = false;
    }

    public Task(String title, String description, boolean status) {
        this.id = ++taskCount; // autoincrement at initialization
        this.title = title;
        this.description = description;
        this.status = status;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public boolean isStatus() {
        return status;
    }

    public void setStatus(boolean status) {
        this.status = status;
    }

    @Override
    public String toString() {
        return "Task{" +
                "id=" + id +
                ", title='" + title + '\'' +
                ", description='" + description + '\'' +
                ", status=" + status +
                '}';
    }
}
