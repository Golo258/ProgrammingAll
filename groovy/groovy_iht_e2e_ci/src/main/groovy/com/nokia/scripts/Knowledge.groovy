package com.nokia.scripts

import com.nokia.scripts.Log as log

/*
    Operacje na kolekcjach
        - each, eachWithIndex
        - collect (mapowanie)
        - find, findAll (filtrowanie)
        - any, every (warunki logiczne)
        - groupBy, countBy
        - sort, reverse, unique
        - flatten, collectMany
        - inject (reduce)
    Operacje na Stringach:
        - split, readLines
        - trim, replaceAll, replaceFirst
        - tokenize
        - toUpperCase, toLowerCase
        - substring, take, drop
    Regex w Groovim:
        Operatory: =~ (partial match), ==~ (full match)
        Matcher i group()
        replaceAll z regexem
        Kotwice ^, \$, grupy (), klasy znaków [a-z], \\d, \\s
    
    Przydatne skróty i idiomy:
       - *.property (spread operator)
       - ?. (safe navigation)
       - ?: (elvis operator)
       - with, tap
 */

class Knowledge {
    class Collections_Playground {

        Collections_Playground() {};
        /* List management */

        void listsCreations() {
            def automaticInit = [1, 2, 3, 4]
            List<Integer> ints = [51, 56, 25, 67];// typowanie generyczne
            List mixed = [1, "more", 25.67]; // mieszanie typów
            List empty = [];
            // Jawne wybieranie typu listy
            List<Integer> arrayNumbers = new ArrayList<Integer>(
                [1, 12, 516, 733]
            )
            List<String> linkedStrings = new LinkedList<String>(
                ["One", "some", "other"]
            )
            // definiowanie z zakresu
            def rangeList = (1..12).toList()
            def explusiveList = (1..<4).toList()
            def charsRangeList = ('a'..'e').toList();
            // konwersje
            def fromListToSet = [1, 2, 2, 51, 1, 6] as Set
            def fromSetToList = fromListToSet as List
            // z javy
            def javaList = Arrays.asList(1, 2, 51);// stałej długości
            def java9List = List.of(1, 2, 3); //niemutowalna
            log.debug(javaList)
        }

        void listsOperations() {
            log.info("Adding new items to list")
            def baseList = [1, 2];
            baseList << 3 // na koniec
            baseList.add(51);
            baseList += [22, 68]; // konkatenaacja Listy
            log.info("Removing items from list")
            baseList.remove(5); // po indexie
            baseList.remove((Integer) 2) // pierwsze wystapienie liczby 2
            baseList -= [51, 3]; // wystapienia liczb
        }

        void listsAccess() {
            log.info("Acess to list items")
            def base = [10, 20, 30, 40, 50]
            Integer byIndex = base[2];
            Integer lastOne = base[-1];
            List rangeNumbers = base[1..3];
            List choseIndexes = base[1, 5];
            List subList = base.subList(2, 5)
        }

        void listsIteration_Transformation() {
            def numbers = [5, 6, 71];
            numbers.each { //iteracja
                log.info("Numb: ${numbers}")
            }
            /*  jesli nie zwrócisz to zostanie bez zmian wartość
                 zawsze zwróci liste tej samej długości co wykonuje .collect
                tworzy nowa liste
             */
            def mappingNumbers = numbers.collect { numb ->
                log.debug("Numb value before: ${numb}")
                if (numb % 2 == 0) {
                    return numb * 2
                } else {
                    return numb * 3
                };
            }
            log.debug("Mapped numbers: ${mappingNumbers}")
            //filtrowanie - lambda oczekuje true / false
            def filterReturnFirstOne = numbers.find { numb ->
                log.debug("Filtering ${numb}")
                return numb % 2 == 0
            }
            // wszystkie pasujące elementy (lista, może być pusta).
            def allEvens = numbers.findAll { it % 2 == 0 }
            // unique - przechodz iprzez liste i usuwa duplikaty
            def onlyUnique = numbers.unique()
            // bezpieczne wydobycie .getAt
            Integer saveValue = numbers.getAt(2)
            // bezpieczne dołożenie
            numbers.putAt(5, 10); // reszte wypełni nullami
        }
    }

    void show_collections() {
        Collections_Playground collections = new Collections_Playground();
        /* List management */
        log.info("List management Playground")
        collections.listsCreations();
        collections.listsOperations();
        collections.listsAccess();
        collections.listsIteration_Transformation();
    }
}