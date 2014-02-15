// LRUCacheTest.java

import java.util.List;
import java.util.Scanner;

class LRUCacheTest {
    public static void main(String[] args) throws Exception {
        LRUCache<String, Integer> cache = new LRUCache(LRUCache.Entry.class);
        cache.put("A", 1);
        cache.put("B", 2);
        cache.put("C", 3);
        cache.put("D", 4);

        {
        List<Integer> valueList = cache.traverse();
        print(valueList);
        }

        cache.put("X", 10);
        cache.put("Y", 9);
        cache.put("Z", 8);
        cache.put("W", 7);

        {
        List<Integer> valueList = cache.traverse();
        print(valueList);
        }

        {
        cache.get("A");
        List<Integer> valueList = cache.traverse();
        print(valueList);
        }

        System.out.println("User command: ");
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNext()) {
            String key = scanner.next();
            cache.get(key);
            List<Integer> valueList = cache.traverse();
            print(valueList);
        }

    }

    private static <E> void print(List<E> list) {
        System.out.println("LRUCache:");
        for (E x : list) {
            System.out.print(x);
            System.out.print(" ");
        }
        System.out.println();
    }
}
