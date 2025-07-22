#include <iostream>
#include <unordered_map>
#include <list>

class LFUCache {
public:
    LFUCache(int capacity) : capacity(capacity), minFreq(0) {}

    int get(int key) {
        if (capacity == 0) return -1;
        auto it = keyToVal.find(key);
        if (it == keyToVal.end()) return -1;
        updateFrequency(key);
        return it->second;
    }

    void put(int key, int value) {
        if (capacity == 0) return;
        if (keyToVal.find(key) != keyToVal.end()) {
            keyToVal[key] = value;
            updateFrequency(key);
        } else {
            if (keyToVal.size() == capacity) {
                int evictKey = freqToKeys[minFreq].back();
                freqToKeys[minFreq].pop_back();
                if (freqToKeys[minFreq].empty()) {
                    freqToKeys.erase(minFreq);
                }
                keyToVal.erase(evictKey);
                keyToFreq.erase(evictKey);
            }
            keyToVal[key] = value;
            keyToFreq[key] = 1;
            freqToKeys[1].push_front(key);
            minFreq = 1;
        }
    }

private:
    int capacity;
    int minFreq;
    std::unordered_map<int, int> keyToVal; // Key to value
    std::unordered_map<int, int> keyToFreq; // Key to frequency
    std::unordered_map<int, std::list<int>> freqToKeys; // Frequency to list of keys

    void updateFrequency(int key) {
        int freq = keyToFreq[key];
        freqToKeys[freq].remove(key);
        if (freqToKeys[freq].empty()) {
            freqToKeys.erase(freq);
            if (minFreq == freq) {
                minFreq++;
            }
        }
        keyToFreq[key]++;
        freqToKeys[keyToFreq[key]].push_front(key);
    }
};

// Example usage:
int main() {
    LFUCache lfuCache(2);
    lfuCache.put(1, 1);
    lfuCache.put(2, 2);
    std::cout << lfuCache.get(1) << std::endl; // returns 1
    lfuCache.put(3, 3); // evicts key 2
    std::cout << lfuCache.get(2) << std::endl; // returns -1 (not found)
    std::cout << lfuCache.get(3) << std::endl; // returns 3
    lfuCache.put(4, 4); // evicts key 1
    std::cout << lfuCache.get(1) << std::endl; // returns -1 (not found)
    std::cout << lfuCache.get(3) << std::endl; // returns 3
    std::cout << lfuCache.get(4) << std::endl; // returns 4
    return 0;
}
