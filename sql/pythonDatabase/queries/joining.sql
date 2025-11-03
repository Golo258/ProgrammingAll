

--ONE TO ONE RELATIONSHIP
CREATE TABLE IF NOT EXISTS "capital" (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100)
);
CREATE TABLE IF NOT EXISTS "country" (
    id SERIAL PRIMARY KEY,
    title VARCHAR(100),
    capital_id INTEGER UNIQUE,
    CONSTRAINT fk_capital
        FOREIGN KEY(capital_id)
        REFERENCES capital(id)
        ON DELETE CASCADE
);

INSERT INTO capital (name) VALUES
    ('Washington, D.C.'),
    ('Ottawa'),
    ('London'),
    ('Berlin'),
    ('Paris'),
    ('Rome'),
    ('Tokyo'),
    ('Canberra'),
    ('Beijing');

INSERT INTO country (title, capital_id) VALUES
    ('United States', 1),
    ('Canada', 2),
    ('United Kingdom', 3),
    ('Germany', 4),
    ('France', 5),
    ('Italy', 6),
    ('Japan', 7),
    ('Australia', 8),
    ('China', 9);

--ONE TO MANY RELATIONSHIP
-- one element is related to one|many elements

CREATE TABLE IF NOT EXIST "customer" (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100),
    address VARCHAR(100),
    email VARCHAR(100),
);

CREATE TABLE IF NOT EXIST "order" (
    id SERIAL PRIMARY KEY,
    creation_date DATE,
    amount INTEGER,
    price DOUBLE PRECISION,
    customer_id INTEGER,
    CONSTRAINT fk_customer
        FOREIGN KEY (customer_id)
        REFERENCES customer(id)
       ON DELETE CASCADE
);
INSERT INTO "customer" (name, address, email)
VALUES
    ('John Doe', '123 Main St', 'john.doe@example.com'),
    ('Jane Smith', '456 Oak St', 'jane.smith@example.com'),
    ('Mike Johnson', '789 Pine St', 'mike.johnson@example.com');

INSERT INTO "order" (creation_date, amount, price, customer_id)
VALUES
    ('2023-01-01', 1, 100.00, 1),
    ('2023-01-02', 2, 150.00, 1),
    ('2023-01-03', 1, 200.00, 2),
    ('2023-01-06', 1, 200.00, 2),
    ('2023-01-04', 3, 300.00, 3),
    ('2023-01-05', 2, 250.00, 3);

SELECT cst.name as customer_name,
       odr.price as order_price,
       odr.amount order_amount
FROM "order" odr
JOIN customer cst on cst.id = odr.customer_id;


--MANY TO MANY RELATIONSHIP

CREATE TABLE IF NOT EXISTS "student" (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL
);

CREATE TABLE IF NOT EXISTS "course" (
    id SERIAL PRIMARY KEY,
    title VARCHAR(100) NOT NULL
);

CREATE TABLE IF NOT EXISTS "student_courses" (
    student_id INTEGER,
    course_id  INTEGER,
    PRIMARY KEY (student_id, course_id),
    CONSTRAINT fk_student
        FOREIGN KEY(student_id) REFERENCES student(id),
    CONSTRAINT fk_course
        FOREIGN KEY(course_id) REFERENCES course(id)
);

INSERT INTO manyMany.student (name)
VALUES ('Alice'),
       ('Bob'),
       ('Charlie'),
       ('David'),
       ('Eva');

-- Wstawianie wartości do tabeli course
INSERT INTO manyMany.course (title)
VALUES ('Mathematics'),
       ('Physics'),
       ('Chemistry'),
       ('Biology'),
       ('Computer Science');

INSERT INTO manyMany.student_courses (student_id, course_id)
VALUES (1, 1), -- Alice zapisuje się na Mathematics
       (1, 3), -- Alice zapisuje się na Chemistry
       (2, 1), -- Bob zapisuje się na Mathematics
       (2, 2), -- Bob zapisuje się na Physics
       (3, 4), -- Charlie zapisuje się na Biology
       (4, 2), -- David zapisuje się na Physics
       (4, 5), -- David zapisuje się na Computer Science
       (5, 3), -- Eva zapisuje się na Chemistry
       (5, 5); -- Eva zapisuje się na Computer Science


-- Filtering data
SELECT student.name as student_name,
       course.title as course_tile
FROM
    manyMany.student_courses sc
JOIN
    manyMany.student student on sc.student_id = student.id
JOIN
    manyMany.course course on sc.course_id = course.id
ORDER BY
    student.name;