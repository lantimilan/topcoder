/**
 * Specify an API is hard.
 * This interview problem would be much easier
 * if I look up Java Doc at that time.
 *
 * implement a Hashtable using linear probing
 * rehash when load factor exceeded
 * assume hash_code() and equal() are available
 */
class MyHashtable {

// return number of elements in hashtable
public int size();

public bool isEmpty();

public Enumeration keys();

public Enumeration elements();

// returns true if hashtable contains value
public boolean contains(Object value);

// returns true if hashtable contains key
public boolean containsKey(Object key);

public Object get(Object key);

// rehash into a bigger table, called automatically when
// size exceeds load factor limit
protected void rehash();

// Throws NullPointerException if value is null
// Returns old value of key, or null if not present before
public Object put(Object key, Object value);

// do nothing if key not present
// Returns value of key, or null if key not found
public Object remove(Object key);

public void clear();

// a shallow copy, keys and elements themselves are NOT copied
public Object clone();

// converts to a rather lengthy String
public String toString();
};
