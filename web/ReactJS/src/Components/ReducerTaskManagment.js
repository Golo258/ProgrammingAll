import {useReducer, useState} from "react";

const initialState = {
    tasks: []
};

const reducer = (state, action) => {
    console.log("STate:")
    console.log(state)
    console.log("Action:")
    console.log(action)
    switch (action.type) {
        case "ADD_TASK":
            return {
                ...state, tasks: [...state.tasks, action.payload]
            };
        case "REMOVE_TASK":
            return {
                ...state, tasks: state.tasks.filter(
                    task => task.id !== action.payload
                )
            };
        case "TOGGLE_TASK" :
            return {
                ...state, tasks: state.tasks.map(
                    task => task.id === action.payload ? {...task, completed: !task.completed} : task
                )
            };
        default:
            throw new Error("Unknown action type")
    }
};

export function TaskManagement() {

    const [state, dispatch] = useReducer(reducer, initialState);
    const [taskName, setTaskName] = useState('');
    const handleAddTask = () => {
        const newTask = {
            id: Date.now(),
            name: taskName,
            completed: false
        }
        dispatch({type: "ADD_TASK", payload: newTask});
        setTaskName("");
    };
    const handleRemoveTask = (taskId) => {
        dispatch({type: "REMOVE_TASK", payload: taskId})
    };

    const handleToggleTask = (taskId) => {
        dispatch({type: "TOGGLE_TASK", payload:taskId})
    }

    return (
        <div>
            <h1>Task List: </h1>
            <input type="text"
                   value={taskName}
                   onChange={(event) => setTaskName(event.target.value)}
                   placeholder="Enter task name"
            />
            <button onClick={handleAddTask}> Add Task</button>
            <ul>
                {state.tasks.map(task => (
                    <li key={task.id}>
                        <span style={{textDecoration: task.completed ? 'line-through' : 'none'}}>
                            {task.name}
                        </span>
                        <button onClick={() => handleToggleTask(task.id)}>
                            {task.completed ? 'Undo' : 'Complete'}
                        </button>
                        <button onClick={() => handleRemoveTask(task.id)}>Remove</button>
                    </li>
                ))}
            </ul>
        </div>
    )


}