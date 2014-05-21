// Trie.java
//
// build a trie for word ladder problem
// The problem:
// given a source word in dict, find a sequence
// of transformation with only 1 char change
// could be insert/delete/substitute
// leading to the target word
// every intermediate word must also be the dict

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.HashMap;

public final class Trie {

    private static final class Node {
        private String word;
        private HashMap<String, Node> children;

        public Node() {
            this("");
        }

        public Node(String s) {
            word = s;
            children = new HashMap<String, Node>();
        }

        public String getWord() {
            return word;
        }

        public HashMap<String, Node> getChildren() {
            return children;
        }
    }

    public static final char WILDCARD = '*';
    private Node root;

    public Trie(List<String> dict) {
        root = new Node();
        build(dict);
    }

    private void build(List<String> dict) {
        for (String word : dict) {
            process(root, word, 0);
        }
    }

    private boolean isWildCard(char ch) {
        return ch == WILDCARD;
    }

    private void process(Node root, String word, int start) {
        if (start >= word.length()) return;
        String firstChar = word.substring(start,start+1);
        HashMap<String, Node> children = root.getChildren();
        Node child;
        if (children.containsKey(firstChar)) {
            child = children.get(firstChar);
        } else {
            if (start + 1 == word.length()) {
                child = new Node(word);
            } else {
                child = new Node();
            }
            children.put(firstChar, child);
        }
        process(child, word, start+1);
    }

    public List<String> query(String word) {
        return queryHelper(root, word, 0);
    }
    public List<String> queryHelper(Node root, String word, int start) {
        String firstChar = word.substring(start, start+1);
        HashMap<String, Node> children = root.getChildren();
        List<String> result = new ArrayList<String>();
        if (isWildCard(firstChar.charAt(0))) {
            for (String key: children.keySet()) {
                Node child = children.get(key);
                String w = child.getWord();
                if (start+1 == word.length()) {
                    if (!w.isEmpty()) {
                        result.add(w);
                    }
                } else if (start+1 < word.length()){
                    List<String> childList =
                        queryHelper(children.get(key), word, start+1);
                    result.addAll(childList);
                }
            }
        } else if (children.containsKey(firstChar)) {
            Node child = children.get(firstChar);
            String w = child.getWord();
            if (start+1 == word.length()) {
                if (!w.isEmpty()) {
                    result.add(w);
                }
            } else if (start+1 < word.length()) {
                List<String> s = queryHelper(children.get(firstChar), word, start+1);
                result.addAll(s);
            }
        }
        return result;
    }

    public static void main(String[] args) throws IOException {
        List<String> dict = new ArrayList<String>();
        BufferedReader inFile = new BufferedReader(new FileReader("US_EN_words.txt"));
        String word;
        while ((word = inFile.readLine()) != null) {
            dict.add(word);
        }
        Trie trie = new Trie(dict);
        String s = "sector****";
        List<String> result = trie.query(s);
        System.out.println(result);
    }
}
