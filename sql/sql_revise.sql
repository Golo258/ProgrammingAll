

-- Polecenia
-- 1. Select | (select ) jaka kolumna (From ) z czego 
    Select * From tabela;
    -- Funkcje agregujące
        Select COUNT(*) AS total_records from tabela; count records and return column
        Select SUM(column) As total_sum from tabela; sum numbers from specific column
        Select AVG(column) -- count average of column numbers
        Select MIN(column) / MAX(column)
    
    -- reszta
        Select Distinct column from tablela; zwraca tylko unikalne wartosci
        Select * from tabela where column = 12  # tylko rekordy spelniajace warunek
        Select * from tawbela where number Between  1 AND 12;
        SELECT GROUP_CONCAT(column) AS combined_text FROM tabela;

    -- group by: grupowanie wynikow wedlug column
    -- czesto uzywane z funkcjami agregujacymi 
        Select department, COUNT(*) as employee_count
        From employees
        Group By department; # count bedzie liczony tylko dla grupy z GroupBy

    -- order by: sortowanie wynikow zapytania według column
    -- sortujemy rosnaćo ASC, lub malejaco DESC
        Select * from products
        Order By price DESC;

-- 2. Insert
    INSERT INTO tabela (kolumna1, kolumna2) VALUES (wartosc1, wartosc2);
-- 3. Update
    UPDATE tabela SET kolumna = nowa_wartosc WHERE warunek;
-- 4. Delete
    DELETE FROM tabela WHERE warunek;
-- 5. Join
    -- łączenie danych z wielu tabel na podstawie kryteiow
        -- INNER JOIN - na podstawie warunku złączenia
    Select orders.order_id , customers.customer_name
    From orders
    INNER JOIN customer ON orders.customer_id = customer.customer_id; 
    # tylko te wiersze ktore spelniaja warunek (ON .. )

    -- LEFT JOIN- zwraca rekordy z Lewej(pierwszej w zapytaniu) tabeli
    -- a także te które pasują z drugiej ( prawej)
    Select customers.name, orders.id
    From customers
    LEFT JOIN orders customer.id = orders.customer_id
    -- zwracane wszystkie z customers, oraz jesli spelnia to z prawej albo null
    Tak samo z RIGHT JOIN ale odwrotnie

    --FULL JOIN, zwraca wszystkie rekordy, dopasowując rekordy tabeli 
    SELECT customers.name, orders.id
    From customers
    FULL JOIN orders ON customers.id = orders.customer_id;

-- 6. Union 
    -- Łączenie wynikow kilku zapytań SELECt
    -- Usuwa duplikaty i zwraca tylko unikalne wiersze
    -- kolumny musza być zgodne 
    -- kolejnosc kolumn jest ustalona na podstawie pierwszego selecta
    SELECT user, user_name FROM users
    Union
    SELECt user, user_name FROM customers;

    # łączenie wyników z różnych warunków
    SELECT name FROM customers where country="USA"
    UNION SELECT name FROM customers where country="Poland"

-- 7. Transactions:
    Sekwencja operacji wykonywana jako jedna atomowa jednostka: (calosciowo)
        ALbo wszystko przejdzie albo żadna z nich
        Izolacja, transakcje jdendo usera sa izolowane od innego

        BEGIN TRANSACTION;
        UPDATE accounts SET balance = balance - 100 WHERE account_id = 123;
        INSERT INTO transactions (account_id, amount, type) VALUES (123, 100, 'withdrawal');
        COMMIT; - zatwierdza dane - trwałe zmiany
        lub 
        ROLLBACK; anuluje transakcje, cofając wprowadzone zmiany

--8: Indeksy:
    --- struktury danych, pomagające wyszukiwanie danych. 
    -- pomaga to silnikowi bazy danych wyszkukiwać dane "skanowanie indeksu"
    -- a) jednokolumnowe - dla pojedynczych Kolumn
        CREATE INDEX  idx_last_name ON employees ( lastname); 
    -- b) wielokolumnowe 
        CREATE INDEX idx_firstname_lastname ON employees (firstname, lastname);
    -- c) unikalne - uniemożliwiają dodanie duplikatów danych w tabeli
        CREATE UNIQUE INDEX idx_email ON users (email);
    -- d) pełnotekstowe - przyspieszenie wyszukiwania na podstawie treści tesktwoej
        CREATE FULLTEXT INDEX indx_description ON products (description);

-- 9: subqueryies:
    1. W warunkach where:
        SELECT * FROM orders
        WHERE customer_id IN (SELECT customer_id FROM customers WHERE country = "USA")

    2. W klauzulach FROM:
        SELECT customer_id, total_spent
        FROM (SELECT customer_id, SUM(amount) AS total_spent FROM orders GROUP BY customer_id) 
        AS customer_orders;
    
    3. W klauzulach SELECT:
        SELECT customer_id, (SELECT MAX(amount) FROM orders WHERE customer_id = customers.customer_id)
        AS max_order_amount
        FROM customers;

--10. Filtrowanie:
    -a) HAving - filtorwanie wyników grupowyania na podstawie warunku - stosowane po grupowaniu
        SELECT customer_id, SUM(amount) AS total_amount
        FROM orders
        GROUP By customer_id
        HAVING SUm(amount) > 600;

-- 11. Warunkowe:
    CASE- pozwala wybierać wartość w zależności od kryterów
        SELECT employee_id,
            CASE    
                WHEN salary > 5000 THEN 'High'
                WHEN salary > 3000 THEN 'medium'
                ELSE 'Low'
            END AS salary_level
        FROM employees;

--12. Operacje na tekstach:
    Manipulowanie stringami, dzielenie, łaczenie, zmienianie
        CONCAT: Łączenie dwóch lub więcej ciągów znaków.
        SUBSTRING: Wyodrębnianie podciągu znaków z ciągu.
        UPPER / LOWER: Konwersja liter na duże / małe.
        LENGTH / CHAR_LENGTH: Określanie długości ciągu znaków.
        TRIM: Usuwanie białych znaków z początku i końca ciągu.
        LEFT / RIGHT: Pobieranie określonej liczby znaków z lewej / prawej strony ciągu.

    SELECT CONCAT(firstname, " ", lastname ) AS full_name,
        UPPER(job_title;) AS big_title,
        SUBSTRING(city, 1, 3 ) AS city_code
    FROM employees;
    