/*
    Components:
        primary building material for application
        parts of user interface
        can be used many times and connected with each other
    Props:
        properties - passing data from component to the parent of a
        child component. Its final - cannot be changed

    State:
        inner state of component
        its mutable ( can be changed )
        each change of the state is rendering the component again

    Example:
        Getting output from user and update the name from Form
 */

import React, {useState} from "react";
import '../Styles/UserProfile.css';
import UserImage from "../Assets/Images/user1.png";
import UserImage2 from "../Assets/Images/user2.png";

/*
    JSX syntax - it connects javascript with html
    example:
        const element = <h1> Butter in the bottle </h1>
    with variables
        const intro = <p> My bro {broName}</p>
    Attributes:
        class -> className | for -> htmlFor

    Not operate with style, instead using JS objects
    const bodyStyle = {
        color : "blue",
        fontSize: "20px"
    };
    element = <span style={bodyStyle}> Styled Text</span>

    Example
 */

export function PersonalGreet(props) {

    function checkGender(name) {
        if (name.toLowerCase().endsWith("a")) {
            return "lady"
        } else {
            return "gentleman";
        }
    }

    const gender = checkGender(props.name);

    return (
        <div>
            <h1>Hello {props.name} {gender}</h1>
        </div>
    )
}

/*
 change of state, component is automatically rendered again
 after the state is changed
 */
export function SimpleCounter() {
    const [count, setCount] = useState(0);

    const handleClick = () => {
        setCount(count + 1);
    }
    return (
        <div className="counterBody">
            <h2>Current count {count}</h2>
            <button onClick={handleClick}>Increment counter</button>
        </div>
    )
}

export function UserProfile({name, age, bio, avatarUrl}) {
    const getBackColorBasedOnAge = (age) => {
        const [pinkColor, greenColor, blueColor] =
            ['#FFDDC1', '#C1E1C1', '#C1C1E1']
        if (age < 18) return pinkColor;
        if (age < 30) return greenColor;
        return blueColor;
    }

    const nameStyle = {
        color: '#333',
        fontSize: '24px',
        marginBottom: '10px',
    };

    nameStyle.backgroundColor = getBackColorBasedOnAge(age);
    return (
        <div className="profile-container">
            <img src={avatarUrl} alt={`${name}'s avatar`} className="avatar"/>
            <h1 style={nameStyle}>{name}</h1>
            <p className="bio">Age: {age}</p>
            <p className="bio">{bio}</p>

        </div>

    )
}

/*
    Event handling:

 */

export function EventHandling() {
    const [message, setMessage] = useState("Click the Button !");
    const buttonClick = () => {
        const showedMessage = message.includes("clicked") ?
            "Click the Button" : "Button clicked"
        setMessage(showedMessage)
    };

    const [inputValue, setInputValue] = useState("");
    const inputFieldChange = (event) => {
        setInputValue(event.target.value);
        console.log(event)
    }

    const [hovered, setHovered] = useState(false);
    const mouseEventStyles = {
        width: '200px',
        height: '200px',
        backgroundColor: hovered ? 'lightblue' : 'lightgray',
        display: 'flex',
        alignItems: 'center',
        justifyContent: 'center',
        transition: 'background-color 0.3s',
    };

    return (
        <div className="handlers">
            <div className="buttons">
                <p>{message}</p>
                <button onClick={buttonClick}>Click Me!</button>
            </div>
            <div className="inputs">
                <input type="text" value={inputValue} onChange={inputFieldChange}/>
                <span>Typed Value: {inputValue}</span>
            </div>
            <div style={mouseEventStyles}
                 onMouseEnter={ (event) => {setHovered(true); console.log(event)}}
                 onMouseLeave={ () => setHovered(false)}

            >
                {hovered ? 'Hovered!' : 'Hover over me'}
            </div>
        </div>
    )
}

export function BegginAll(){
    return (
        <div className="container">
            <PersonalGreet name="Ania"/>
            <SimpleCounter/>
            <div className="users">
                <UserProfile
                    name="Janek Kowalski"
                    age={28}
                    bio="A passionate developer with a love for React and JavaScript."
                    avatarUrl={UserImage}
                />
                <UserProfile
                    name="Anna Nowak"
                    age={22}
                    bio="Frontend developer with a focus on user experience and design."
                    avatarUrl={UserImage2}
                />
            </div>
            <EventHandling/>
        </div>
    )
}