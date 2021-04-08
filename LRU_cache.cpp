/**
 *  LRU CACHE IMPL with
 *  Time : O(1)
 *  Space : O(n)
 */ 

/**
 *  Implementaiton 1: Without using any STL Linked list
 */

struct Node {
    int key, val;
    Node *next = NULL, *prev = NULL;

    Node(int _key, int _val) {
        key = _key;
        val = _val;
    }
};

class LRUCache {
    public:

    Node *head = NULL;
    Node *tail = NULL;
    unordered_map<int, Node*> nodes;
    int size = 0;
    int max_size;

    LRUCache(int capacity) {
        max_size = capacity;
    }

    int get(int key) {
        if (!nodes.count(key)) {
            return -1;
        } else {
            Node *node = nodes[key];

            if (node == tail) {
                // do nothing
            } else if (node == head) {
                node->next->prev = NULL;
                head = head->next;
                tail->next = node;
                node->prev = tail;
                node->next = NULL;
                tail = tail->next;
            } else {
                node->prev->next = node->next;
                node->next->prev = node->prev;
                tail->next = node;
                node->prev = tail;
                node->next = NULL;
                tail = tail->next;
            }

            return node->val;
        }
    }

    void set(int key, int val) {
        if (!nodes.count(key)) {
            Node *new_node = new Node(key, val);
            if (size == 0) {
                // insert new_node at the head
                head = tail = new_node;
                size++;
                nodes[key] = new_node;
            } else if (size == max_size) {
                // first delete the head
                nodes.erase(head->key);
                head = head->next;
                if (!head) { // capacity == 1
                    tail = NULL;
                } else { //  capacity > 1
                    head->prev = NULL;
                }
                

                // insert new_node at the end
                if (!head) {
                    head = tail = new_node;
                    nodes[key] = new_node;
                } else {
                    tail->next = new_node;
                    new_node->prev = tail;
                    tail = tail->next;
                    nodes[key] = new_node;
                }
            } else {
                // insert new_node at the end
                tail->next = new_node;
                new_node->prev = tail;
                tail = tail->next;
                nodes[key] = new_node;
                size++;
            }
        } else {
            Node *node = nodes[key];
            node->val = val;

            if (node == tail) {
                // do nothing
            } else if (node == head) {
                node->next->prev = NULL;
                head = head->next;
                tail->next = node;
                node->prev = tail;
                node->next = NULL;
                tail = tail->next;
            } else {
                node->prev->next = node->next;
                node->next->prev = node->prev;
                tail->next = node;
                node->prev = tail;
                node->next = NULL;
                tail = tail->next;
            }
        }
    }
};


/**
 * Implementation 2 : With using STL linkedlist 
 */

class LRUCache {
    public:

    int cap;
    list<pair<int, int>> lst;
    unordered_map<int, list<pair<int, int>>::iterator> ma;

    LRUCache(int capacity) {
        cap = capacity;
    }

    int get(int key) {
        if (ma.count(key)) {
            auto it = ma[key];
            int val = it->second;
            
            lst.erase(it);
            
            lst.push_front({key, val});
            ma[key] = lst.begin();

            return val;
        } else {
            return -1;
        }
    }

    void set(int key, int val) {
        if (ma.count(key)) {
            auto it = ma[key];
            lst.erase(it);
            
            lst.push_front({key, val});
            ma[key] = lst.begin();
        } else {
            if (ma.size() == cap) {
                ma.erase(lst.back().first);
                lst.pop_back();
                
                lst.push_front({key, val});
                ma[key] = lst.begin();
            } else {
                lst.push_front({key, val});
                ma[key] = lst.begin();
            }
        }
    }
};