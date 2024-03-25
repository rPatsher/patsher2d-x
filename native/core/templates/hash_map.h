/**
 * MIT License

Copyright (c) 2024/2025 rPatsher

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <iostream>
#include <vector>
#include <list>
#include <functional> // Include functional library for hash




template<typename K, typename V>
class HashMap {
private:
    std::vector<std::list<Element<K, V>>> table;
    int size;
    int capacity; // Track the total capacity of the table

template<typename K, typename V>
struct Element {
    K key;
    V value;

    Element(const K& k, const V& v) : key(k), value(v) {}
};

public:

    size_t hash(const K& key) const {
        return std::hash<K>{}(key) % capacity;
    }

    void rehash(int newCapacity) {
        std::vector<std::list<Element<K, V>>> newTable(newCapacity);
        for (const auto& chain : table) {
            for (const auto& entry : chain) {
                size_t index = std::hash<K>{}(entry.key) % newCapacity;
                newTable[index].push_back(entry);
            }
        }
        table = std::move(newTable);
        capacity = newCapacity;
    }

public:
    HashMap(int initialSize = 10) : size(0), capacity(initialSize) {
        table.resize(capacity);
    }

    int get_size() const {
        return size;
    }

    bool is_empty() const {
        return size == 0;
    }

    void insert(const K& key, const V& value) {
        if (size >= capacity) {
            // Resize and rehash if load factor is high
            resize(capacity * 2);
        }
        size_t index = hash(key);
        table[index].emplace_back(key, value);
        ++size;
    }

    // Get and other methods...

    void resize(int newCapacity) {
        if (newCapacity <= 0) return; // Avoid negative or zero capacity
        if (newCapacity != capacity) {
            rehash(newCapacity);
        }
    }

    void clear() {
        for (auto& chain : table) {
            chain.clear();
        }
        size = 0;
    }

    V get_value(const K& key) {
        auto it = find(key);
        return (it != end()) ? it->value : V(); // Return value if found, else default value of V
    }

    K get_key(const V& value) {
        for (const auto& chain : table) {
            for (const auto& entry : chain) {
                if (entry.value == value) {
                    return entry.key;
                }
            }
        }
        return K(); // Return default value of K if not found
    }

    typename std::list<Element<K, V>>::iterator find(const K& key) {
        size_t index = hash(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                return it;
            }
        }
        return table[index].end();
    }

    typename std::list<Element<K, V>>::iterator end() {
        return typename std::list<Element<K, V>>::iterator();
    }

    V* getptr(const K& key) {
        auto it = find(key);
        return (it != end()) ? &it->value : nullptr;
    }

    bool replace(const K& key, const V& value) {
        auto it = find(key);
        if (it != end()) {
            it->value = value;
            return true;
        }
        return false;
    }

    void reserve(int newCapacity) {
        if (newCapacity > capacity) {
            resize(newCapacity);
        }
    }




    ~HashMap() {
        // Destructor implementation...
    }
};

#endif /* HASHMAP_H */