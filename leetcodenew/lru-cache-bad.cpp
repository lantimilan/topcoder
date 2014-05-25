/**
 * use circular doubly linked list and hashmap to achieve O(1) access and O(1) insert/delete
 * we need list node to contain key so that we can remove entry from hashmap
 * we also need hashmap entry as <key, listnode*> so that we can get list node in O(1) given key
 *
 * this implementation use std::map, which is implmented using Red Black Tree,
 * access is O(logn) but we could replace it with a C++ hash_map if one available
*/
class LRUCache{
public:
    LRUCache(int capacity) {
        this->head = new Node(-1, -1);  // dummy head
        this->head->prev = this->head->next = this->head;
        // hashmap uses std::map default constructor
        this->size = 0;
        this->capacity = capacity;
    }
    int get(int key) {
        if (hashmap.count(key)) {
        // get node in list
            Node *entry = hashmap[key];
        // get value
            int value = entry->value;
        // move node to front
            moveToFront(entry);
            return value;
        }
        return -1;  // could throw exception if key not found
    }
    void set(int key, int value) {
        if (hashmap.count(key)) {
            Node *entry = hashmap[key];
            entry->value = value;
            moveToFront(entry);
            return;
        }
        bool removeEldest = false;
        if (++size > capacity) {
            size = capacity;
            removeEldest = true;
        }
        Node *entry = new Node(key, value);
        hashmap[key] = entry;
        // insert entry at head
        Node *first = head->next;
        head->next = entry;
        entry->prev = head;
        entry->next = first;
        first->prev = entry;
        if (removeEldest) {
            Node *eldest = head->prev;
            int key = eldest->key;
            hashmap.erase(key);
            head->prev = eldest->prev;
            eldest->prev->next = head;
            delete eldest;
        }
    }
private:
    struct Node {
        int key;
        int value;
        Node *prev, *next;
        Node(int key, int value) {
            this->key = key; this->value = value;
            prev = next = NULL;
        }
    };
    Node *head;
    map<int, Node*> hashmap;
    int size;
    int capacity;
    void moveToFront(Node *entry) {
        Node *first = head->next;  // this is a bug: need to remove entry before insert after head
        entry->prev->next = entry->next;
        entry->next->prev = entry->prev;
        head->next = entry;
        entry->prev = head;
        entry->next = first;
        first->prev = entry;
    }
};
