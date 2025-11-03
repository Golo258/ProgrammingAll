

-- QUERY: create_table
CREATE TABLE dS tasks (
    id SERIAL PRIMARY KEY,
    title VARCHAR(200) NOT NULL UNIQUE,
    description TEXT,
    completed BOOLEAN DEFAULT FALSE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- QUERY: insert_record
INSERT INTO tasks (title, completed, created_at)  VALUES
   ('Big Funny shopping', FALSE, '2024-02-05 12:00:00');

-- QUERY: insert_multi_records
INSERT INTO tasks (title,description, completed, created_at)  VALUES
   ('Big Funny shopping', FALSE, '2024-02-05 12:00:00'),
   ('Pay bills', 'Settle electricity and internet bills', TRUE, '2024-02-01 13:00:00'),
   ('Practice guitar', 'Learn new chords and practice scales', FALSE, '2024-03-01 14:00:00'),
   ('Write blog post', 'Publish about recent technological advancements', TRUE, '2024-04-01 15:00:00'),
   ('Attend webinar', 'Learn about the latest trends in AI', FALSE, '2024-05-01 18:00:00');

-- QUERY update_record
UPDATE tasks
    SET title = "Totally different title"
    WHERE id = 1;

-- QUERY update_records
UPDATE tasks
    SET completed = FALSE
    WHERE LENGTH(description) > 10;

-- QUERY remove_records
DELETE FROM tasks
    WHERE description IS NULL;

-- QUERY remove_table
DROP TABLE tasks;

-- READING files
-- QUERY: distinct  -- without repetitions
SELECT DISTINCT title FROM tasks;

-- QUERY where_operators
SELECT * FROM tasks
    WHERE id >= 1;
--    WHERE completed <> FALSE;  not equal
--    WHERE id BETWEEN 1 AND 10 range(1,100); including the thresholds
--    WHERE title IN ("Learn Python", "Learn SQL", "Learn JAVA");
--    WHERE title LIKE '%P%';
--    WHERE description IS NULL; -- only for null / not null use

-- QUERY where_cases
DO $$

END $$

SELECT *
    CASE
        WHEN id >= 1             THEN "record id > 1"
        WHEN completed <> FALSE  THEN "record completed is True"
        WHEN id BETWEEN 1 AND 10 THEN "record id is between 1-10"
        WHEN title IN ("Learn Python");

-- QUERY ordering_records
SELECT title FROM tasks
    ORDER BY id DESC; -- by default it ascending - ros


-- QUERY limitations
SELECT title, completed
    FROM Tasks
    LIMIT 2;

--  aggregate_functions
-- QUERY counting
SELECT COUNT(*) FROM tasks;

-- QUERY counting_distinct
SELECT COUNT(DISTINCT completed) FROM tasks; -- ignore duplicates by column

-- QUERY grouping
SELECT title, COUNT(*) as completed_tasks
    FROM tasks
    GROUP BY title;
-- other numeric_aggregation
SELECT MIN/MAX/SUM/AVG/(column) FROM tasks

-- QUERY regex_wildcard
SELECT * FROM tasks
WHERE title LIKE -- % zero or many  | _ one sign
    "a%" -- startswith a
    "%a" -- endswith a
    "%a%" -- which contains a
    "_a" -- string which contains random letter and a
    "%a_" -- contain a and last random letter from the end



