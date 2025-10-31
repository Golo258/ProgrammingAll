package pl.golon.Rank;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.HashMap;

public class LightSQL {
    private HashMap<String, String> queries = new HashMap<>();
    private Connection connection = null;
    private Statement statement = null;


    public void initQueriesMap() {
        this.updateQueries("SELECT ALL", "SELECT * FROM students;");
        this.updateQueries("SELECT GRATER", "SELECT *  FROM students WHERE grade > 85;");
        this.updateQueries("UPDATE JOHN", "UPDATE students SET grade =  96 WHERE name = 'john doe';;");
        this.updateQueries("REMOVE GREATER", "DELETE FROM students WHERE grade = (select max(grade) from students);");
        this.updateQueries("INSERT MANY STUDENTS", "INSERT INTO students (name, grade) VALUES\n" +
                "    ('Alice Johnson', 90),\n" +
                "    ('Bob Smith', 85),\n" +
                "    ('Charlie Brown', 78),\n" +
                "    ('Diana Prince', 92),\n" +
                "    ('Ethan Hunt', 81),\n" +
                "    ('Fiona Gallagher', 87),\n" +
                "    ('George Costanza', 74),\n" +
                "    ('Hannah Montana', 88),\n" +
                "    ('Ian Malcolm', 95),\n" +
                "    ('Judy Hopps', 80);"
        );

    }

    public void connect() throws SQLException {
        String url = "jdbc:sqlite:task_db.db";
        this.setConnection(DriverManager.getConnection(url));
        if (this.getConnection() != null) {
            setStatement(getConnection().createStatement());
        }
    }

    public void disconnect() throws SQLException {
        if (getStatement() != null) {
            getStatement().close();
        }
        if (getConnection() != null) {
            getConnection().close();
        }
    }

    void executeFileQueries() throws SQLException {
        String sqlQuery = readQueryFile("Static/queries.sql");
        getStatement().execute(sqlQuery);
    }
    void executeStudentInsertion() throws  SQLException{
        String queryValue = getQueries().get("INSERT MANY STUDENTS");
        getStatement().executeUpdate(queryValue);
    }

    void fetchQuery() throws SQLException {
        if (getConnection() != null) {
            var recordResult = getStatement().executeQuery("SELECT * FROM students");
            try (var resultSet = getStatement().executeQuery("SELECT * FROM students")) {
                while (recordResult.next()) {
                    System.out.printf("%-5s%-25s%-10s%n",
                            recordResult.getInt("id"),
                            recordResult.getString("name"),
                            recordResult.getDouble("grade")
                    );
                }
            }
        } else {
            System.out.println("Connection failed. Cannot execute query");
        }
    }

    static String readQueryFile(String filePath) {
        StringBuilder contentBuilder = new StringBuilder();
        try (
                InputStream stream = LightSQL.class.getClassLoader().getResourceAsStream(filePath);
                BufferedReader reader = new BufferedReader(new InputStreamReader(stream, StandardCharsets.UTF_8))
        ) {
            if (stream == null) {
                throw new IOException("File " + filePath + " hasn't been found in resources");
            }
            String currentLine;
            while ((currentLine = reader.readLine()) != null) {
                contentBuilder.append(currentLine).append("\n");
            }
        } catch (Exception exception) {
            System.out.println(exception.getMessage());
        }
        return contentBuilder.toString();
    }

    public HashMap<String, String> getQueries() {
        return queries;
    }

    public Connection getConnection() {
        return connection;
    }

    public Statement getStatement() {
        return statement;
    }

    public void updateQueries(String key, String value) {
        this.queries.put(key, value);
    }

    public void setConnection(Connection connection) {
        this.connection = connection;
    }

    public void setStatement(Statement statement) {
        this.statement = statement;
    }
}
