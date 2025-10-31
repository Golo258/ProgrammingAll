import './Styles/App.css';
import {BegginAll} from './Components/Beggin';
import {DataFetcher} from "./Components/DataFetcher";
import {Hocks, ReducerStates, ThemedComponent} from "./Components/Hocks";
import {ThemeContext} from "./Contexts/ThemeContext";
import {TaskManagement} from "./Components/ReducerTaskManagment";

function App() {
    return (
        <div className="App">
            {/*<BegginAll/>*/}
            {/*<Hocks/>*/}
            {/*<DataFetcher />*/}
            {/*<ThemeContext.Provider value="dark">*/}
            {/*    <ThemedComponent/>*/}
            {/*</ThemeContext.Provider>*/}
            {/*<ReducerStates/>*/}
            <TaskManagement/>
        </div>
    );
}

export default App;
