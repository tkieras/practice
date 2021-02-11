package edu.nyu.cs9053.homework8;

import java.util.List;
import java.util.LinkedList;
import java.util.Map;
import java.util.HashMap;
import java.util.Set;

public class Trie<T> {

    private static class Node<T> {

        private final T data;

        private final Map<T, Node<T>> children;

        private final boolean terminal;

        protected Node(T data, boolean terminal) {
            this.data = data;
            this.children = new HashMap<>();
            this.terminal = terminal;
        }

        T getData(){
            return data;
        }

        boolean isTerminal(){
            return terminal;
        }
    }

    private final Node<T> root;

    public Trie() {
        root = new Node<T>(null, false);
    }

    public void insert(List<T> sequence) {
        Node<T> cursor = root;
        boolean terminal;

        for(int i=0; i < sequence.size(); i++){
            T thisValue = sequence.get(i);

            if (!cursor.children.containsKey(thisValue)) {

                if (i == sequence.size()-1) {
                    terminal = true;
                } else {
                    terminal = false;
                }
                cursor.children.put(thisValue, new Node<T>(thisValue, terminal));
            }
            cursor = cursor.children.get(thisValue);
        }
    }

    public List<List<T>> search(List<T> sequence) {
        List<T> base = new LinkedList<>();
        List<List<T>> result = new LinkedList<>();
        Node<T> cursor = root;
        
        for (T thisValue : sequence) {
            if (cursor.children.containsKey(thisValue)) {
                cursor = cursor.children.get(thisValue);
                base.add(cursor.getData());
            } else {
                return null;
            }
        }

        if (cursor.isTerminal()) {
            result.add(base);
        }
        if (!cursor.children.isEmpty()) {
            Set<T> childKeys = cursor.children.keySet();
            for (T childKey : childKeys) {
                result.addAll(recursiveSearch(new LinkedList<T>(base), cursor.children.get(childKey)));
            }
        }

        return result;
    }

    private List<List<T>> recursiveSearch(List<T> base, Node<T> node) {
        List<List<T>> result = new LinkedList<>();

        base.add(node.getData());
        
        if (node.isTerminal()) {
            result.add(base);
        }
        if(!node.children.isEmpty()){
            Set<T> childKeys = node.children.keySet();
            
            for (T childKey : childKeys) {
                Node<T> child = node.children.get(childKey);
                result.addAll(recursiveSearch(new LinkedList<T>(base), child));
            }
        }
        return result;       
    }
}