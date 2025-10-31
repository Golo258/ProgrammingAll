import {createContext, useContext, useEffect, useReducer, useState} from "react";
import {ThemeContext} from "../Contexts/ThemeContext";

/*
    useContext:
       getting access to context without using Context.Consumer component
    */

export function Hocks(props) {
    /*
    UseState - return array with two elements:
        var, and function which have impact on the var
        After every change of the var the components renders again
     */
    const [hour, setHour] = useState(1);
    const stateResult = (
        <div>
            <p>Hour: {hour}</p>
            <button onClick={() => setHour(hour + 1)}>Increment</button>
        </div>
    );

    /*
    useEffect - takes 2 arguments
        1. Effect function:
            will be executed after rendering component.
            Including code which will be the effect of rendering again the component
        2. Dependency table:
             [] - effect will be used once
             [var1, var2]- effect will be used on every variable changed
     */

    const [data, setData] = useState(null);
    useEffect(() => {
        fetch("https://jsonplaceholder.typicode.com/todos")
            .then(response => response.json())
            .then(data => setData(data))
            .catch(error => console.error("Error fetching data: ", error))
    }, []);

    const effectResult = (
        <div>
            <h1>Data:</h1>
            <pre>{JSON.stringify(data, null, 2)}</pre>
        </div>
    )


    return (
        <div className="hocks-container">
            {stateResult}
            {effectResult}
        </div>
    )
}

/*
    Context:
        We are loading context from seperated Component
        after can use its value or modify it
        Can be use in


 */

export function ThemedComponent() {
    // eslint-disable-next-line react-hooks/rules-of-hooks
    const theme = useContext(ThemeContext);
    const style = {
        backgroundColor: theme === "dark" ? '#333' : '#fff',
        color: theme === "dark" ? '#fff' : '#000',
        padding: '20px',
        borderRadius: '8px',
        textAlign: 'center'
    };
    return (
        <div style={style}>
            The current theme is {theme}.
        </div>
    )
}

/*
    UseReducer - used advanced state or many states
       Use reduction function like in Redux
       More advanced component state managment
 */

export function ReducerStates() {
    const reducer = (state, action) => {
        switch (action.type) {
            case "increment":
                return {count: state.count + 1};
            case "decrement":
                return {count: state.count - 1};
            default:
                throw new Error("Not validate state used");
        }
    };

    const [state, dispatch] = useReducer(reducer, {count: 0}); // 2- init state
    return (
        <div>
            <p>Count: {state.count}</p>
            <button onClick={
                () => dispatch({type: "increment"}) // action
            }>Increment
            </button>
            <button onClick={
                () => dispatch({type: "decrement"})
            }>Decrement
            </button>
        </div>
    )
}