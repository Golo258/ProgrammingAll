import psycopg2

connection = psycopg2.connect(host="localhost",
                              dbname="postgres",
                              user="postgres",
                              password="asd",
                              port=5432)

cursor = connection.cursor() # commands executor

def create_table(cursor):
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS person (
            id INT PRIMARY KEY,
            name VARCHAR(255),
            age INT,
            gender CHAR
        )
    """)

def add_new_records(cursor):
    cursor.execute("""
        INSERT INTO person(id,name,age,gender) VALUES
        ( 1, 'mike', 40, 'm'),
        ( 2, 'xcv', 41, 'd'),
        ( 3, 'gds', 42, 'm'),
        ( 4, 'tyu', 43, 'k'),
        ( 5, 'ery', 44, 'm'),
        ( 6, 'ghdfh', 45, 'k')
    """)

select_result = cursor.execute(
    """
        SELECT * FROM person WHERE age > 40
    """
)
# print(cursor.fetchall())
for row in cursor.fetchall():
    print(row)

sql = cursor.mogrify(""" SELECT * FROM person WHERE starts_with(name, %s) AND age > %s; """,("x", 40))
print(sql)
cursor.execute(sql)
for row in cursor.fetchall():
    print(row)

connection.commit()
cursor.close()
connection.close()
