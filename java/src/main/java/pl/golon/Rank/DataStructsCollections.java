package pl.golon.Rank;


import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

/*
Data Structures and Algorithms
Zadanie 3: Odwracanie Listy
Napisz funkcję, która odwraca podaną listę jednokierunkową (linked list).

 */
public class DataStructsCollections {


    private int[] temperatures = new int[10];
    private List<String> wordsList;

    void presenceArrays() {
        Random random = new Random();
        for (int index = 0; index < this.getTemperatures().length; index++) {
            this.setTemperatureIndexValue(index, random.nextInt(100 + 1));
        }
        int randomIndex = random.nextInt(10);
        System.out.println("Index " + randomIndex + " of array= " + getTemperatures()[randomIndex]);
    }

    public void presentLists() {
 /* List - uporzadkowana kolejkca, przechowywanie elementow w kolejnosci
     ArrayList - oparta na tablicy dynamicznej, szybki dostep przez index. Powolone dodawanie i usuwanie
   * */
        this.setWordsList(new ArrayList<>());
        this.getWordsList().add("Simple");
        this.getWordsList().add("But not as much");
        this.getWordsList().forEach(System.out::println);
     // LinkedList - oparta na węzłach - szybkie dodawanie na poczatku i koncu, dostep do indeksow wolny
        this.setWordsList(new LinkedList<>());
        this.getWordsList().add("Hard");
        this.getWordsList().add("much no so");
        this.getWordsList().forEach(System.out::println);
    }

    public int[] getTemperatures() {
        return temperatures;
    }

    public void setTemperatureIndexValue(int index, int value) {
        if (value != 0) {
            this.temperatures[index] = value;
        }
    }

    public List<String> getWordsList() {
        return wordsList;
    }

    public void setWordsList(List<String> wordsList) {
        this.wordsList = wordsList;
    }
}
