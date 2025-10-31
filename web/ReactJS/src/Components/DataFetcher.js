import {useEffect, useState} from "react";


export function DataFetcher() {

    const [todoId, setId] = useState(1);
    const [data, setData] = useState(null);
    const [loading, setLoading] = useState(true);
    const [error, setError] = useState(null);

    useEffect(() => {
        setLoading(true);
        fetch(`https://jsonplaceholder.typicode.com/todos/${todoId}`)
            .then(response => {
                if (!response.ok) throw new Error("Network response was not ok");
                return response.json();
            })
            .then(data => {
                setData(data);
                setLoading(false);
            })
            .catch(error => {
                console.error("Error fetching data", error);
                setError(error);
                setLoading(false);
            })
    }, [todoId]);
    if (loading) {
        return <p>Loading ... </p>
    }
    if (error) return <p>Error: {error.message}</p>
    const firstElement = data.id
    return (
        <div>
            <h1>Data for Id {todoId}</h1>
            <h1>{firstElement}</h1>
            <pre>{JSON.stringify(data, null, 2)}</pre>
            <button onClick={() => setId(todoId + 1)}>Get Id</button>
        </div>
    )
}