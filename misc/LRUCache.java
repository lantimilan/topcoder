/**
 * Implement an LRU Cache using doubly linked list and hashtable to achieve
 * O(1) lookup and update
 */

import java.util.HashMap;
import java.io.Console;

// because you need to access a list node in O(1) time
// you have to put that node in hashmap
public class LRUCache<K, V> {

    private static class Entry<K, V> {
        private K key;
        private V value;
        Entry<K, V> prev, next;

        Entry(K k, V v) {
            key = k;
            value = v;
            prev = next = null;
        }

        public K getKey() {
            return key;
        }

        public V getValue() {
            return value;
        }
    }

    private Entry<K, V> head;
    private HashMap<K, Entry<K, V>> hashmap;
    private int size;
    private static final int MAX_SIZE = 6;

    // must call init() before use
    void init() {
        head = new Entry<K, V>(null, null);
        head.prev = head.next = head;
        hashmap = new HashMap<K, Entry<K, V>>();
        size = 0;
    }

    private void removeFromList(Entry<K, V> entry) {
        entry.prev.next = entry.next;
        entry.next.prev = entry.prev;
    }

    private void insertFront(Entry<K, V> entry) {
        entry.next = head.next;
        entry.prev = head;
        head.next.prev = entry;
        head.next = entry;
    }

    private void moveToFront(Entry<K, V> entry) {
        removeFromList(entry);
        insertFront(entry);
    }

    public V get(K key) {
        if (!hashmap.containsKey(key)) {
            return null;
        }
        Entry<K, V> entry = hashmap.get(key);
        moveToFront(entry);
        return entry.getValue();
    }

    private void removeEldest() {
        Entry<K, V> entry = head.prev;
        removeFromList(entry);
        hashmap.remove(entry.getKey());
    }

    public void put(K key, V value) {
        size++;
        Entry<K, V> entry = new Entry<K, V>(key, value);
        insertFront(entry);
        hashmap.put(key, entry);
        if (size > MAX_SIZE) {
            removeEldest();
        }
    }

    public void dump() {
        Entry<K, V> entry = head;
        do {
            entry = entry.next;
            if (entry.getKey() != null) {
                System.out.println(entry.getKey() + " => " + entry.getValue());
            }
        } while (entry != head);
    }

    public static void main(String[] args) {
        String[] keyset = new String[]{"A", "B", "C", "D", "E", "F"};
        String[] valset = new String[]{"1", "2", "3", "4", "5", "6"};

        LRUCache<String, String> cache = new LRUCache<>();
        cache.init();
        for (int i = 0; i < keyset.length; ++i) {
            cache.put(keyset[i], valset[i]);
        }
        cache.dump();

        Console c = System.console();
        String cmd;
        while ((cmd = c.readLine("Pleae enter command:\n\t" +
            "get key\n\tput key value\n")) != null) {
            String[] tokens = cmd.split(" ");
            String op = tokens[0];
            if (op.equals("get")) {
                String key = tokens[1];
                String value = cache.get(key);
                cache.dump();
            } else if (op.equals("put")) {
                String key = tokens[1];
                String value = tokens[2];
                cache.put(key, value);
                cache.dump();
            } else if (op.equals("print")) {
                cache.dump();
            } else if (op.equals("quit") || op.equals("q")) {
                System.out.println("Bye");
                break;
            } else {
                System.err.println("Bad command. Type quit to exit");
            }
        }
    }
};
