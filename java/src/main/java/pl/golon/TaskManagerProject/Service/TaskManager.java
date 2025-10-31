package pl.golon.TaskManagerProject.Service;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;
import pl.golon.TaskManagerProject.Models.Task;

import java.io.*;
import java.lang.reflect.Array;
import java.net.URISyntaxException;
import java.net.URL;
import java.nio.file.Paths;
import java.text.FieldPosition;
import java.util.*;

public class TaskManager {

    String env = "dev";
    ObjectMapper mapper = new ObjectMapper();
    ArrayList<Task> userTasks;
    Map<String, Runnable> options = new TreeMap<>(
            Map.of(
                    "[add] Append new Task to task list", this::addNewTask,
                    "[view] Show the whole task list", this::showTaskList,
                    "[remove] Pop task based on id from task list", this::removeTaskById,
                    "[show] Presence specific task based on its id", this::showTaskById,
                    "[complete]  Assign task as completed ", this::assignTaskAsCompleted,
                    "[options] Show list of options", this::presentOption,
                    "[load] Load new created tasks to json file", this::loadTaskListToJson
            )
    );
    ;
    BufferedReader reader = new BufferedReader(
            new InputStreamReader(System.in)
    );

    public TaskManager(ArrayList<Task> userTasks) {
        this.userTasks = userTasks;
    }

    public boolean runOptions() throws IOException {
        System.out.println("Enter job which you want to do: ");
        try {
            String inputChoice = this.reader.readLine();
            if (inputChoice.equalsIgnoreCase("Quit")) {
                return false;
            } else {
                options.entrySet().stream()
                        .filter(entry -> entry.getKey().contains(inputChoice.toLowerCase()))
                        .findFirst()
                        .ifPresent(
                                entry -> {
                                    System.out.println("You choose option: "
                                            + entry.getKey().subSequence(0, entry.getKey().indexOf(']') + 1));
                                    entry.getValue().run();
                                }
                        );
                return true;
            }
        } catch (Exception exception) {
            System.out.println(exception.getMessage());
        }
        return false;
    }

    public void presentOption() {
        for (Map.Entry<String, Runnable> entry : this.options.entrySet()) {
            System.out.println("Option: " + entry.getKey());
        }
    }

    public void addNewTask() {
        if (userTasks == null) {
            userTasks = new ArrayList<>();
        }
        System.out.println("Enter task title and then description");
        try {
            Task task = new Task(this.reader.readLine(), this.reader.readLine());
            this.verifyLastTaskId(task);
            System.out.println("Your new created task: " + task);
            this.userTasks.add(task);
        } catch (IOException exception) {
            System.out.println("Error reading input: " + exception.getMessage());
        } catch (Exception exception) {
            System.out.println("Error: " + exception.getMessage());
        }
    }

    public void showTaskList() {
        System.out.println("Let's print this bad boys: ");
        this.userTasks.forEach(
                System.out::println
        );
    }

    public void removeTaskById() {
        showTaskList();
        try {
            Task searchedTask = this.getTaskById("remove");
            this.userTasks.remove(searchedTask);
        } catch (Exception exception) {
            System.out.println(exception.getMessage());
        }
    }


    public void showTaskById() {
        Task searchedTask = this.getTaskById("show");
        System.out.println(searchedTask);
    }

    public void assignTaskAsCompleted() {
        Task searchedTask = this.getTaskById("complete");
        searchedTask.setStatus(true);
    }

    public void loadTaskListToJson() {
        try {
            File jsonFile = this.getJsonFileBasedOnEnv();
            ArrayList<Task> fileTasks = this.mapper.readValue(
                    jsonFile, new TypeReference<ArrayList<Task>>() {
                    }
            );
            this.userTasks.addAll(fileTasks);
            this.userTasks.sort(Comparator.comparing(Task::getId));
            this.mapper.writeValue(jsonFile, this.userTasks);
        } catch (Exception exception) {
            System.out.println(exception.getMessage());
        }
    }

    public Task getTaskById(String action) {
        showTaskList();
        System.out.println("Which one would you like to " + action + "? [id]");
        try {
            long chosenTaskId = Integer.parseInt(
                    this.reader.readLine()
            );
            return this.userTasks.stream()
                    .filter(
                            element -> element.getId() == chosenTaskId
                    )
                    .findFirst().orElseThrow(() -> new Exception("Task with id " + chosenTaskId + " not found in list"));
        } catch (Exception exception) {
            System.out.println(exception.getMessage());
        }
        return null;
    }

    public void verifyLastTaskId(Task task) {
        try {
            File jsonFile = this.getJsonFileBasedOnEnv();
            ArrayList<Task> fileTasks = this.mapper.readValue(
                    jsonFile, new TypeReference<ArrayList<Task>>() {
                    }
            );
            if (!this.userTasks.isEmpty()) {
                fileTasks.addAll(this.userTasks);
            }
            long max_id = fileTasks.stream()
                    .max(Comparator.comparing(
                            Task::getId
                    )).get().getId();
            task.setId(max_id + 1);
        } catch (Exception exception) {
            System.out.println(exception.getMessage());
        }
    }

    public File getJsonFileBasedOnEnv() throws URISyntaxException {
        File jsonFile = null;
        if (this.env.contains("dev")) {
            jsonFile = Paths.get("src/main/resources/Static/taskList.json").toFile();
        } else if (this.env.contains("prod")) {
            URL url = getClass().getClassLoader().getResource("Static/taskList.json");
            assert url != null;
            jsonFile = Paths.get(
                    url.toURI()
            ).toFile();
        }
        return jsonFile;
    }

    public ArrayList<Task> getUserTasks() {
        return userTasks;
    }

    public void setUserTasks(ArrayList<Task> userTasks) {
        this.userTasks = userTasks;
    }

    public Map<String, Runnable> getOptions() {
        return options;
    }

    public void setOptions(Map<String, Runnable> options) {
        this.options = options;
    }

    public BufferedReader getReader() {
        return reader;
    }

    public void setReader(BufferedReader reader) {
        this.reader = reader;
    }
}
