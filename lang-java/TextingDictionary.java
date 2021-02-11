package edu.nyu.cs9053.homework8;

import java.util.List;
import java.util.LinkedList;
import java.util.Arrays;

public class TextingDictionary {

    Trie<Character> dictionary;

    public TextingDictionary() {
        dictionary = new Trie<Character>();
    }

    public void insert(String word){
        dictionary.insert(stringToCharList(word));
    }

    public List<String> search(List<ValidTextKeyPress> prefixes) {
        List<String> results = new LinkedList<>();

        List<List<Character>> queries = assembleQueries(prefixes);
     
        for (List<Character> query : queries) {
            
            List<List<Character>> queryResults = dictionary.search(query);

            if (queryResults == null) {
                continue;
            }

            for (List<Character> singleResult : queryResults) {
                results.add(charListToString(singleResult));
            }
        }
        
        return results;
    }

    private List<List<Character>> assembleQueries(List<ValidTextKeyPress> keyPressList) {
        List<List<Character>> results = new LinkedList<>();
        List<Character> base = new LinkedList<>();

        results = recursiveAssembleQueries(keyPressList, base, results);

        return results;
    }

    private List<List<Character>> recursiveAssembleQueries(List<ValidTextKeyPress> keyPressList, List<Character> base, List<List<Character>> results) {
        if (keyPressList.size() == 0) {
            results.add(base);
            return results;
        }

        ValidTextKeyPress press = keyPressList.get(0);
        List<Character> charsFromPress = keyPressToCharList(press);

        for (Character c : charsFromPress) {           
            List<Character> newBase = new LinkedList<>(base);
            newBase.add(c);
            results = recursiveAssembleQueries(keyPressList.subList(1, keyPressList.size()), newBase, results);
        }

        return results;
    }

    private List<Character> stringToCharList(String input) {
        LinkedList<Character> result = new LinkedList<>();

        for(int i=0; i < input.length(); i++) {
            result.add(input.charAt(i));
        }
        return result;
    }

    private String charListToString(List<Character> input) {
        StringBuilder stringBuilder = new StringBuilder();

        for (Character c : input) {
            stringBuilder.append(c);
        }
        return stringBuilder.toString();
    }

    private List<Character> keyPressToCharList(ValidTextKeyPress press) {
        List<Character> result = new LinkedList<Character>();

        switch(press) {
            case TWO:
                result.addAll(Arrays.asList('a','b','c'));
                break;
            case THREE:
                result.addAll(Arrays.asList('d','e','f'));
                break;
            case FOUR:
                result.addAll(Arrays.asList('g','h','i'));
                break;
            case FIVE:
                result.addAll(Arrays.asList('j','k','l'));
                break;
            case SIX:
                result.addAll(Arrays.asList('m','n','o'));
                break;
            case SEVEN:
                result.addAll(Arrays.asList('p','q','r','s'));
                break;
            case EIGHT:
                result.addAll(Arrays.asList('t','u','v'));
                break;
            case NINE:
                result.addAll(Arrays.asList('w','x','y','z'));
                break;
            default:
                throw new AssertionError();
        }

        return result;
    }
}