

CREATE TABLE IF NOT EXISTS employees
(
    id        INTEGER PRIMARY KEY AUTOINCREMENT,
    firstName VARCHAR(100) UNIQUE,
    lastName  VARCHAR(255),
    email     VARCHAR(255) UNIQUE,
    hireDate  DATE
);

INSERT INTO employees (firstName, lastName, email, hireDate)
VALUES ('John', 'Doe', 'john.doe@example.com', '2023-01-15'),
       ('Jane', 'Smith', 'jane.smith@example.com', '2023-02-20');


CREATE TABLE IF NOT EXISTS projects
(
    id        INTEGER PRIMARY KEY AUTOINCREMENT,
    name      VARCHAR(100) UNIQUE,
    startDate DATE,
    endDAte   DATE
);


INSERT INTO projects (name, startDate, endDAte)
VALUES ('Tick tack toe ', '2023-01-15', '2023-08-30'),
       ('Training app', '2022-05-20', '2023-02-12');

--  one-to-many relation

CREATE TABLE IF NOT EXISTS tasks
(
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    description VARCHAR(255),
    dueDate     DATE,
    status      TEXT CHECK ( status IN ('TODO', 'IN PROGRESS', 'DONE', 'COMPLETED')),
    projectId   INT,
    FOREIGN KEY (projectId) REFERENCES projects (id)
);

INSERT INTO tasks (description, dueDate, status, projectId)
VALUES ('Design Database Schema', '2024-01-15', 'TODO', 1),
       ('Implement API Endpoints', '2024-02-15', 'IN PROGRESS', 1),
       ('Create primary feature view', '2023-05-12', 'TODO', 2),
       ('Refactor backend endpoints structure', '2023-02-15', 'DONE', 2);

CREATE TABLE IF NOT EXISTS ProjectAssignments
(
    assignmentId INTEGER PRIMARY KEY AUTOINCREMENT,
    ROLE          VARCHAR(100),
    employeeId   INT,
    projectId    INT,
    FOREIGN KEY (employeeId) REFERENCES employees (id),
    FOREIGN KEY (projectId) REFERENCES projects (id)
);


INSERT INTO ProjectAssignments (employeeId, projectId, role)
VALUES
    (1, 1, 'Developer'),
    (2, 1, 'Project Manager');