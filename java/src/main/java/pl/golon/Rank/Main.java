package pl.golon.Rank;

import java.sql.SQLException;

public class Main {
    public static void main(String[] args) {
//        performSQLoperations();
        showDataStructures();
    }
    static void performSQLoperations(){
        LightSQL sql = new LightSQL();
        try{
            sql.connect();
            sql.initQueriesMap();
            sql.executeFileQueries();
            sql.executeStudentInsertion();
            sql.fetchQuery();
            sql.disconnect();
        }
        catch (SQLException exception){
            System.out.println(exception.getMessage());
        }
    }
    static void showDataStructures(){
        DataStructsCollections struct = new DataStructsCollections();
        struct.presenceArrays();
        struct.presentLists();
    }
}
