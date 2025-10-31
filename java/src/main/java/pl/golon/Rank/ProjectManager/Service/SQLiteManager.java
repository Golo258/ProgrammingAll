package pl.golon.Rank.ProjectManager.Service;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.datatype.jsr310.JavaTimeModule;
import pl.golon.Rank.LightSQL;
import pl.golon.Rank.ProjectManager.Models.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.lang.reflect.Field;
import java.lang.reflect.Type;
import java.net.MalformedURLException;
import java.nio.charset.StandardCharsets;
import java.sql.*;
import java.util.*;

public class SQLiteManager {

    private String url; // jdbc:sqlite:task_db.db
    private Connection connection;
    private Statement statement;

    public SQLiteManager(String url) {
        this.url = url;
        this.connection = null;
        this.statement = null;
    }

    public void connect() throws SQLException, MalformedURLException {
        if (!this.url.isEmpty()) {
            this.setConnection(DriverManager.getConnection(this.url));
            if (this.getConnection() != null) {
                setStatement(getConnection().createStatement());
            }
        } else {
            throw new MalformedURLException("Empty database source given in url");
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

    void executeSqlQuery(String query, Object queryModel) throws SQLException {
        ArrayList<String> updateQuery = new ArrayList<>(
                Arrays.asList("INSERT", "UPDATE", "DELETE", "CREATE", "DROP", "ALTER")
        );
        String matchingElement = updateQuery.stream().filter(
                query::startsWith
        ).findFirst().orElse(null);

        if (matchingElement != null) {
            this.getStatement().executeUpdate(query);
        } else if (query.startsWith("SELECT")) {
            this.fetchQuery(query, queryModel);
        } else {
            throw new SQLException("Wrong query given");
        }
    }

    void fetchQuery(String fetchingQuery, Object queryModel) throws SQLException {
        if (getConnection() != null) {
            try (var recordResult = getStatement().executeQuery(fetchingQuery)) {
                while (recordResult.next()) {
                    var objectFields = this.getQueryObjectFields(fetchingQuery, queryModel);
                    this.formFetchOutput(objectFields, recordResult);
                }
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        } else {
            System.out.println("Connection failed. Cannot execute query");
        }
    }

    void formFetchOutput(LinkedHashMap<String, String> objectFields, ResultSet resultSet) throws Exception {
        StringBuilder outputForm = new StringBuilder();
        StringBuilder outputFormat = new StringBuilder();
        ArrayList<Integer> stringLengths = new ArrayList<>();
        for (Map.Entry<String, String> entry : objectFields.entrySet()) {
            String name = entry.getKey();
            String type = entry.getValue();
            if (type.contains("int")) {
                outputFormat.append("%-10s");
                outputForm.append(
                        resultSet.getInt(name)
                );
            } else if (type.contains("String")) {
                outputForm.append(
                        resultSet.getString(name)
                );
                outputFormat
                        .append("%-")
                        .append(resultSet.getString(name).length() + 7)
                        .append("s");
            } else if (type.contains("LocalDate")) {
                outputFormat.append("%-12s");
                outputForm.append(
                        resultSet.getString(
                                name
                        )
                );
            } else {
                throw new Exception("Given type" + type + "doesn't fit with formatting");
            }
            outputForm.append("|");
        }
        outputFormat.append("%n");
        String[] elements = outputForm.toString().split("\\|");
        System.out.printf(outputFormat.toString(), (Object[]) elements);
    }

    LinkedHashMap<String, String> getQueryObjectFields(String givenQuery, Object queryModel) throws Exception {
        Class<?> clazz = queryModel.getClass();
        Field[] fields = clazz.getDeclaredFields();
        LinkedHashMap<String, String> fieldAttributes = new LinkedHashMap<>();
        for (Field field : fields) {
            fieldAttributes.put(
                    field.getName(),
                    String.valueOf(field.getType()));
        }
        return fieldAttributes;
    }

    String getFormatForInsertionQuery(String givenQuery, Object queryModel, String modelName) throws Exception {
        LinkedHashMap<String, String> objectFields = this.getQueryObjectFields(givenQuery, queryModel);
        StringBuilder argumentsBuilder = new StringBuilder();
        for (Map.Entry<String, String> entry : objectFields.entrySet()) {
            if (entry.getKey().contains(objectFields.lastEntry().getKey())) {
                argumentsBuilder.append(entry.getKey()).append(") VALUES(");
            } else {
                argumentsBuilder.append(entry.getKey()).append(", ");
            }
        }
        givenQuery += argumentsBuilder.toString();
        System.out.println(givenQuery);
        ArrayList<Object>  modelsList = getInsertionModelsFromJsonFile("Static/dummy_data.json", modelName);
        if (modelsList != null){

        }
        return "";

    }
    ArrayList<Object> getInsertionModelsFromJsonFile(String filePath, String modelName) {
        try{
            InputStream inputStream = SQLiteManager.class.getClassLoader().getResourceAsStream(
                    filePath
            );
            assert inputStream != null;
            ObjectMapper mapper = new ObjectMapper();
            mapper.registerModule(new JavaTimeModule());
            JsonInsertedData [] dataArray = mapper.readValue(inputStream, JsonInsertedData[].class);
            for(JsonInsertedData jsonData: dataArray){
                if (jsonData.getTable().contains(modelName)){
                    Object wantedSQLModel = getClassByTableName(modelName);
                    ArrayList<Object> jsonModels = new ArrayList<>(jsonData.getData());
                    System.out.println(jsonModels);
                    for (Object jsonModel : jsonModels) {
                        jsonModel = mapper.convertValue(jsonModel, wantedSQLModel.getClass());
                        System.out.println(jsonModel);
                    }
                    return jsonModels;
                }
            }
            return null;
        }
        catch (IOException exception){
            System.out.println(exception.getMessage());
        }
    }
    void parseAdditionalRecordsFromCSV() {
        System.out.println("Siemaono");
    }

    public Connection getConnection() {
        return connection;
    }

    public Statement getStatement() {
        return statement;
    }

    public void setConnection(Connection connection) {
        this.connection = connection;
    }

    public void setStatement(Statement statement) {
        this.statement = statement;
    }

    public Object getClassByTableName(String tableName) {
        Object searchedObject = null;
        switch (tableName){
            case "employees" -> {searchedObject = new Employee();}
            case "projects" -> {searchedObject = new Project();}
            case "tasks" -> {searchedObject =  new Task();}
            case "ProjectAssignments" -> {searchedObject =  new ProjectAssignment();}
        };
        return searchedObject;
    }
}
