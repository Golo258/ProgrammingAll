package pl.golon.TaskManagerProject.App;

import pl.golon.TaskManagerProject.Models.Task;
import pl.golon.TaskManagerProject.Service.TaskManager;

import java.io.IOException;
import java.util.ArrayList;

public class TaskManagerApp {

    public static void main(String[] args) throws IOException {
        TaskManager manager = new TaskManager(
                new ArrayList<>()
        );
        manager.presentOption();
        boolean isRunning = true;
        while (isRunning) {
            isRunning = manager.runOptions();
        }
    }
}
