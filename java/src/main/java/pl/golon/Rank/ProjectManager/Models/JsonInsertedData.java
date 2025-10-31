package pl.golon.Rank.ProjectManager.Models;

import java.util.ArrayList;
import java.util.List;

public class JsonInsertedData {
    private String table;
    private List data;

    public JsonInsertedData() {
    }

    public JsonInsertedData(String table, List data) {
        this.table = table;
        initList(table);
        this.data = data;
    }

    public String getTable() {
        return table;
    }
    private void initList(String wantedModel) {
        switch (wantedModel) {
            case "employees" -> this.data = new ArrayList<Employee>();
            case "tasks" -> this.data = new ArrayList<Task>();
            case "projects" -> this.data = new ArrayList<Project>();
            case "ProjectAssignments" -> this.data = new ArrayList<ProjectAssignment>();
            default -> this.data = new ArrayList<>(); // Domyślna lista, jeśli model nie jest znany
        }
    }

    public void setTable(String table) {
        this.table = table;
    }

    public List getData() {
        return data;
    }

    public void setData(List data) {
        this.data = data;
    }
}
