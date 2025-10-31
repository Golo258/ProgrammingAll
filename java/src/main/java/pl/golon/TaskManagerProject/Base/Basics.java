package pl.golon.TaskManagerProject.Base;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Random;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Basics {
    private int number;

    public Basics(int number) {
        this.number = number;
    }

    public static void main(String[] args) {
        Basics basics = new Basics(10);

        basics.dataTypes_Operators();
        int numberFromUserInput = basics.getUserInput();
        if (numberFromUserInput != 0) basics.conditionalStatements(numberFromUserInput);
        else basics.conditionalStatements(5);
        basics.loopsAndHandling();
    }

    public void loopsAndHandling(){
        Random rand = new Random();
        for (int i = 0 ; i < rand.nextInt(10+1 ); i ++){
            System.out.println("Iteration:" + i);
        }
//        Exception handling
        try{
            int [] simpleNumbers ={ 1, 2, 3 };
            System.out.println(simpleNumbers[5]);
        }
        catch (ArrayIndexOutOfBoundsException boundException){
            System.out.println(boundException.getMessage());
        }
        finally {
            System.out.println("And the block is always handle ");
        }
    }
    public int getNumber() {
        return number;
    }

    public  void dataTypes_Operators() {
        int numb = 5;
        double float_numb = 4.5;
        boolean flag = true;
        char sign = 'a';
        String word = "What's up";

        int convertedFloat = numb + (int) float_numb;
        boolean isEqual = (numb == convertedFloat);
        boolean isGreater = (numb > numb);
        System.out.printf(
                "Converted %d \n IsEqual %B", numb, convertedFloat
        );
    }

    public  void conditionalStatements(int number) {
        if (number > 0) {
            System.out.println("Is positive");
        } else if (number < 0) {
            System.out.println("Is negative");
        } else {
            System.out.println("Is equal");
        }
    }

    public  int getUserInput() {
        BufferedReader reader = new BufferedReader(
                new InputStreamReader(System.in)
        );
        try {
            System.out.println("Enter number: ");
            String input = reader.readLine();
            Pattern pattern = Pattern.compile("-?\\d+");
            Matcher matcher = pattern.matcher((input));
            ArrayList<Integer> numbers = new ArrayList<>();
            while (matcher.find()) {
                numbers.add(Integer.valueOf(matcher.group()));
            }
            return numbers.get(0);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }

    public void setNumber(int number) {
        this.number = number;
    }
}
