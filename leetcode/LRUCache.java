// LRUCache2.java

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

public class LRUCache<K, V> {
    public void put(K key, V value) throws Exception {
        Entry<K, V> entry = clazz.newInstance();
        entry.key = key;
        entry.value = value;

        entry.next = head.next;
        entry.prev = head;
        if (head.next != null) head.next.prev = entry;
        head.next = entry;
        hashMap.put(key, entry);
    }

    public V get(K key) {
        if (!hashMap.containsKey(key)) return null;
        Entry<K, V> entry = hashMap.get(key);
        entry.prev.next = entry.next;
        if (entry.next != null) {
            entry.next.prev = entry.prev;
        }
        entry.next = head.next;
        entry.prev = head;
        if (head.next != null) head.next.prev = entry;
        head.next = entry;
        return entry.getValue();
    }

    public LRUCache(Class<Entry<K, V>> clazz) throws Exception {
        this.clazz = clazz;
        head = clazz.newInstance(); head.next = null;
        hashMap = HashMap.class.newInstance();
    }

    List<V> traverse() {
        List<V> valueList = new ArrayList<V>();
        Entry<K, V> entry = head.next;
        while (entry != null) {
            valueList.add(entry.getValue());
            entry = entry.next;
        }
        return valueList;
    }

    private Class<Entry<K, V>> clazz;

    public static class Entry<K, V> {
        private K key;
        private V value;
        private Entry<K, V> prev;
        private Entry<K, V> next;

        public V getValue() {
            return value;
        }
    }

    private HashMap<K, Entry<K, V>> hashMap;
    private Entry<K, V> head;

}
