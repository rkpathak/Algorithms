#include <iostream>
#include <unordered_map>
#include <list>

class LRUCache {
public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        auto it = cache.find(key);
        if (it == cache.end()) {
            return -1;
        }
        // Move the accessed item to the front of the list
        //TODO change this
            accessOrder.erase(it->second.second);
            accessOrder.push_front(key);
            it->second.second = accessOrder.begin();
        //accessOrder.splice(accessOrder.begin(), accessOrder, it->second.second);
        return it->second.first;
    }

    void put(int key, int value) {
        auto it = cache.find(key);
        if (it != cache.end()) {
            // Update the value and move the item to the front of the list
            accessOrder.erase(it->second.second);
            accessOrder.push_front(key);
            it->second.first = value;
            it->second.second = accessOrder.begin();
            //accessOrder.splice(accessOrder.begin(), accessOrder, it->second.second);
        } else {
            if (cache.size() == capacity) {
                // Remove the least recently used item
                int lruKey = accessOrder.back();
                accessOrder.pop_back();
                cache.erase(lruKey);
            }
            // Insert the new item
            accessOrder.push_front(key);
            cache[key] = {value, accessOrder.begin()};
        }
    }

private:
    int capacity;
    std::list<int> accessOrder; // Doubly linked list to maintain access order of keys
    std::unordered_map<int, std::pair<int, std::list<int>::iterator>> cache; // Hash map to store key-value pairs and list iterators
};

// Example usage:
int main() {
    LRUCache lruCache(2);
    lruCache.put(1, 1);
    lruCache.put(2, 2);
    std::cout << lruCache.get(1) << std::endl; // returns 1
    lruCache.put(3, 3); // evicts key 2
    std::cout << lruCache.get(2) << std::endl; // returns -1 (not found)
    lruCache.put(4, 4); // evicts key 1
    std::cout << lruCache.get(1) << std::endl; // returns -1 (not found)
    std::cout << lruCache.get(3) << std::endl; // returns 3
    std::cout << lruCache.get(4) << std::endl; // returns 4
    return 0;
}
