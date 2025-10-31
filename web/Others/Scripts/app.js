


// ---------------------------------------
document.addEventListener("DOMContentLoaded", function () {
        const taskForm = document.getElementById("taskForm");
        const newTaskButton = document.getElementById("addNewTaskButton");
        const taskInput = document.getElementById("taskInput");
        const taskList = document.getElementById("taskList");

        newTaskButton.addEventListener('click', addNewTask)

        function addNewTask(event) {
            event.preventDefault(); // Zapobiega wysyłaniu formularza i przeładowaniu strony
            const taskValue = taskInput.value.trim();
            if (taskValue !== "") {
                const newTask = document.createElement("li");
                newTask.textContent = taskValue;
                taskList.appendChild(newTask);
                taskInput.value = "";
            }
        }
    }
)
