CREATE TABLE Orders (
    OrderID INT PRIMARY KEY IDENTITY(1,1),
    CustomerName NVARCHAR(100),
    OrderDate DATE,
    TotalAmount DECIMAL(10, 2)
);

INSERT INTO Orders (CustomerName, OrderDate, TotalAmount)
VALUES ('Jan Kowalski', '2024-07-01', 150.00),
       ('Anna Nowak', '2024-07-02', 200.00);


UPDATE Orders
SET TotalAmount = 180.00
WHERE OrderID = 1;


DELETE FROM Orders
WHERE OrderID = 1;


SELECT * FROM Orders;


SELECT * FROM Orders
WHERE OrderDate >= '2024-07-01' AND OrderDate <= '2024-07-31';


SELECT * FROM Orders
ORDER BY OrderDate DESC;

# ORDER BY sortuje wyniki na podstawie kolumny.
# DESC oznacza sortowanie malejąco, ASC sortowanie rosnąco (domyślnie).

SELECT COUNT(*) AS NumberOfOrders, SUM(TotalAmount) AS TotalSales
FROM Orders
WHERE OrderDate >= '2024-07-01' AND OrderDate <= '2024-07-31';

SELECT Wiek, COUNT(*) AS LiczbaPracowników
FROM Pracownicy
GROUP BY Wiek;

#GROUP BY grupuje wyniki na podstawie wartości w kolumnie.
# jest  tutaj np kilka pracowników z tym samym wiekiem i my chcemy je zgrupować
# Musi być funkcja agregująca,

Indexy:
     struktura danych, która poprawia szybkość operacji wyszukiwania, sortowania,a filtrowania, na tabeli
     Użyteczne przy dużej ilości danych

     Rodzaje:
        Indeks Zwykły (Non-clustered Index): 
            Tworzy oddzielną strukturę, która wskazuje na lokalizację danych w tabeli. Może być używany do wielu kolumn.
            CREATE INDEX idx_OrderDate
            ON Orders (OrderDate);

        Indeks Klastrowy (Clustered Index):
             Określa fizyczny porządek danych w tabeli według wartości kolumny indeksu. 
             Może być tylko jeden na tabele.
            CREATE CLUSTERED INDEX idx_OrderID
            ON Orders (OrderID);

        Indeks Unikalny (Unique Index): 
            Zapewnia, że wartości w kolumnie są unikalne.
            CREATE UNIQUE INDEX idx_CustomerName
            ON Orders (CustomerName);

        DROP INDEX idx_OrderDate ON Orders;


Sumowanie i grupowanie:
    SELECT 
        CustomerID, 
        COUNT(OrderID) AS NumberOfOrders,
        SUM(TotalAmount) AS TotalSpent
    FROM 
        
        Orders
    GROUP BY 
        CustomerID
    ORDER BY 
        TotalSpent DESC;

--  Pierwsze wyniki są grupowane w kolumny CustomerId, Numberoforders, TotalSpent
--  A potem sortowane malejaco wzgledem wartosci z totalspent

Funkcja agrregująca z warunkiem:
    SELECT 
        OrderDate, 
FFF        AVG(TotalAmount) AS AverageOrderAmount
    FROM 
        Orders
    WHERE 
        OrderDate >= '2024-01-01'
    GROUP BY 
        OrderDate
    HAVING 
        AVG(TotalAmount) > 100;

Podzapytania:
    SELECT 
        SubQuery.CustomerID, 
        COUNT(SubQuery.OrderID) AS NumberOfOrders
    FROM 
        (SELECT CustomerID, OrderID FROM Orders WHERE OrderDate >= '2024-07-01') AS SubQuery
    GROUP BY 
        SubQuery.CustomerID;

Tabele: 
Pracownicy:
    ID  Imię    IDDepartamentu
    1   Anna    2
    2   Piotr   1
    3   Kasia   NULL
    4   Tomasz  3


Departamenty:
    ID  Nazwa
    1   IT
    2   Finanse
    3   Marketing
    4   HR

#INNER JOIN zwraca rekordy, które mają pasujące wartości w obu tabelach.
#   warunek musi sie zgadzac, inaczej nie zwroci tego rekordu
    SELECT Pracownicy.Imię,  Departamenty.Nazwa
    FROM Pracownicy
    INNER JOIN Departamenty ON Pracownicy.IDDepartamentu = Departamenty.ID;

Imię    Nazwa
Anna    Finanse
Piotr   IT
Tomasz  Marketing

#LEFT JOIN zwraca wszystkie rekordy z lewej tabeli i pasujące rekordy z prawej tabeli. 
# jesli warunek nie jest spelniony to w takim rekordzie zostanie z pawerj dane null
    SELECT Pracownicy.Imię, Departamenty.Nazwa
    FROM Pracownicy
    LEFT JOIN Departamenty ON Pracownicy.IDDepartamentu = Departamenty.ID;

Imię    Nazwa
Anna    Finanse
Piotr   IT
Kasia   NULL
Tomasz  Marketing

#RIGHT JOIN zwraca wszystkie rekordy z prawej tabeli i pasujące rekordy z lewej tabeli. 
# jesli warunek nie jest spelniony to w takim rekordzie zostanie z lewej dane null

    SELECT Pracownicy.Imię, Departamenty.Nazwa
    FROM Pracownicy
    RIGHT JOIN Departamenty ON Pracownicy.IDDepartamentu = Departamenty.ID;


Imię    Nazwa
Anna    Finanse
Piotr   IT
Tomasz  Marketing
NULL    HR

#FULL JOIN zwraca rekordy, które mają pasujące wartości w obu tabelach, oraz rekordy z obu tabel, 
#   Wszystkie rekordy z obu tabel będą zwrócone. 
#   Dla rekordów, które nie mają dopasowania w drugiej tabeli, wartości będą NULL
    SELECT Pracownicy.Imię, Departamenty.Nazwa
    FROM Pracownicy
    FULL JOIN Departamenty ON Pracownicy.IDDepartamentu = Departamenty.ID;

Imię    Nazwa
Piotr   IT
Anna    Finanse
Tomasz  Marketing
NULL    HR
Kasia   NULL


#ALTER TABLE modyfikuje istniejącą tabelę (np. dodanie nowej kolumny).
    ALTER TABLE Pracownicy
    ADD DataZatrudnienia DATE;

Na wielu tabelach:
    SELECT 
        Orders.OrderID, 
        Customers.CustomerName, 
        Orders.TotalAmount
    FROM 
        Orders
    INNER JOIN 
        Customers
    ON 
        Orders.CustomerID = Customers.CustomerID
    WHERE 
        Orders.OrderDate >= '2024-08-01';

Transakcje:
    BEGIN TRANSACTION;

    BEGIN TRY
        -- Operacja 1: Wstawienie nowego klienta
        INSERT INTO Customers (CustomerID, CustomerName) 
        VALUES (1001, 'New Customer');

        -- Operacja 2: Dodanie zamówienia dla nowego klienta
        INSERT INTO Orders (OrderID, CustomerID, OrderDate, TotalAmount) 
        VALUES (2001, 1001, '2024-08-11', 250.00);

        -- Jeśli wszystko się powiedzie, zatwierdzamy transakcję
        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        -- Jeśli coś poszło nie tak, wycofujemy transakcję
        ROLLBACK TRANSACTION;
        
        -- Wyświetlamy błąd
        SELECT ERROR_MESSAGE() AS ErrorMessage;
    END CATCH;

8. Procedury składowane (Stored Procedures)
Procedury składowane to zestaw instrukcji SQL, które można przechowywać w bazie danych i wywoływać w razie potrzeby. Ułatwiają one wielokrotne używanie skomplikowanych operacji.
Przykład:

CREATE PROCEDURE DodajPracownika
    @Imie NVARCHAR(50),
    @Nazwisko NVARCHAR(50),
    @Wiek INT
AS
BEGIN
    INSERT INTO Pracownicy (Imie, Nazwisko, Wiek)
    VALUES (@Imie, @Nazwisko, @Wiek);
END;

# Tabele z relacjami
One-to-One
W relacji one-to-one każdy rekord w jednej tabeli jest powiązany z 
    dokładnie jednym rekordem w drugiej tabeli, i odwrotnie.

CREATE TABLE Osoby (
    ID INT PRIMARY KEY,
    Imię NVARCHAR(50),
    Nazwisko NVARCHAR(50)
);

CREATE TABLE Adresy (
    ID INT PRIMARY KEY,
    IDOsoby INT UNIQUE, -- Klucz obcy wskazujący na tabelę Osoby
    Ulica NVARCHAR(100),
    Miasto NVARCHAR(50),
    FOREIGN KEY (IDOsoby) REFERENCES Osoby(ID)
);

#------------------------
One-to-Many
W relacji one-to-many jeden rekord w jednej tabeli jest powiązany z wieloma rekordami w drugiej tabeli.
CREATE TABLE Klienci (
    ID INT PRIMARY KEY,
    Imię NVARCHAR(50),
    Nazwisko NVARCHAR(50)
);
# Dla danego klienta może być wiele zamówień
CREATE TABLE Zamówienia (
    ID INT PRIMARY KEY,
    IDKlienta INT, -- Klucz obcy wskazujący na tabelę Klienci
    DataZamówienia DATE,
    Kwota DECIMAL(10, 2),
    FOREIGN KEY (IDKlienta) REFERENCES Klienci(ID)
);
#--------------------
many-to-many
W relacji many-to-many wiele rekordów w jednej tabeli może być powiązanych z wieloma rekordami w drugiej tabeli.
Aby modelować tę relację, używamy tabeli łączącej (tabeli pośredniczącej).

CREATE TABLE Studenci (
    ID INT PRIMARY KEY,
    Imię NVARCHAR(50),
    Nazwisko NVARCHAR(50)
);

CREATE TABLE Kursy (
    ID INT PRIMARY KEY,
    Nazwa NVARCHAR(100)
);
CREATE TABLE StudenciKursy (
    IDStudenta INT,
    IDKursu INT,
    PRIMARY KEY (IDStudenta, IDKursu),
    FOREIGN KEY (IDStudenta) REFERENCES Studenci(ID),
    FOREIGN KEY (IDKursu) REFERENCES Kursy(ID)
);

#----------------
ALTER - dodawanie relacji
-- 1. Dodaj nową kolumnę do tabeli Zamówienia
ALTER TABLE Zamówienia
ADD IDKlienta INT;

-- 2. Dodaj klucz obcy, który łączy kolumnę IDKlienta z tabelą Klienci
ALTER TABLE Zamówienia
ADD CONSTRAINT FK_Zamówienia_Klienci
FOREIGN KEY (IDKlienta) REFERENCES Klienci(ID);

#-------------
Usuwanie klucza obcego
-- Usuń klucz obcy z tabeli Zamówienia
ALTER TABLE Zamówienia
DROP CONSTRAINT FK_Zamówienia_Klienci;