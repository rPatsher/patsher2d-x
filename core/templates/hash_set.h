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

#ifndef HASHSET_H
#define HASHSET_H

#include <iostream>
#include <list>
#include <vector>

#include <unordered_map>
#include <unordered_set>


#include <core/templates/list.h>

template<typename K, typename V>
class HashSet {
private:
    // Define the structure to hold key-value pairs
    struct KeyValuePair {
        K key;
        V value;
    }; 
    struct Element  {
        K key;
        V value;
    };

    // Define the hash table as a vector of lists of KeyValuePairs
    std::vector<std::list<KeyValuePair>> table;
    int size; // Number of elements in the hash table

    // Hash function to get the index for a given key
    int hash(const K& key) const {
        // Use a simple hash function for demonstration purposes
        return std::hash<K>{}(key) % table.size();
    }

public:
    // Constructor
    HashSet(int initialSize = 10) : size(0) {
        table.resize(initialSize);
    }

    // Destructor
    ~HashSet() {
        // Perform necessary cleanup
        table.clear();
    }

    // Method to insert a key-value pair into the hash table
    void insert(const K& key, const V& value) {
        int index = hash(key);
        KeyValuePair pair = {key, value};

        // Check if the key already exists
        for (const auto& kv : table[index]) {
            if (kv.key == key) {
                // Key already exists, update the value
                kv.value = value;
                return;
            }
        }

        // Key doesn't exist, insert the new key-value pair
        table[index].push_back(pair);
        size++;
    }

    // Method to retrieve a value for a given key
    V get(const K& key) const {
        int index = hash(key);

        // Search for the key in the corresponding list
        for (const auto& kv : table[index]) {
            if (kv.key == key) {
                return kv.value; // Return the value if found
            }
        }

        throw std::out_of_range("Key not found");
    }

    // Method to remove a key-value pair from the hash table
    void remove(const K& key) {
        int index = hash(key);

        // Search for the key in the corresponding list and remove if found
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                table[index].erase(it);
                size--;
                return;
            }
        }

        throw std::out_of_range("Key not found");
    }

    // Overloading the assignment operator =
HashSet& operator=(const HashSet& other) {
    if (this == &other) {
        return *this; // Check for self-assignment
    }

    // Clear current contents
    for (auto& list : table) {
        list.clear();
    }
    size = 0;

    // Copy elements from 'other' to 'this'
    table.resize(other.table.size());
    for (const auto& list : other.table) {
        for (const auto& el : list) {
            insert(el.key, el.value);
        }
    }

    return *this;
}

// Overloading the subscript operator []
V& operator[](const K& key) {
    int index = hash(key);

    for (auto& el : table[index]) {
        if (el.key == key) {
            return el.value; // Return reference to the value if the key exists
        }
    }

    // If the key doesn't exist, insert a new key-value pair and return a reference to its value
    Element element = {key, V()};
    table[index].push_back(element);
    size++;
    return table[index].back().value;
}

// Method to set a value for a given key and return its value
V setget(const K& key, const V& value) {
    int index = hash(key);

    auto it = std::find_if(table[index].begin(), table[index].end(), [&](const Element& el) {
        return el.key == key;
    });

    if (it != table[index].end()) {
        // Update the value if the key exists and return its value
        it->value = value;
        return it->value;
    } else {
        // If the key doesn't exist, insert a new key-value pair and return its value
        Element element = {key, value};
        table[index].push_back(element);
        size++;
        return value;
    }
}

// Method to get the value for a given key and set a new value if the key doesn't exist
V getset(const K& key, const V& value) {
    int index = hash(key);

    auto it = std::find_if(table[index].begin(), table[index].end(), [&](const Element& el) {
        return el.key == key;
    });

    if (it != table[index].end()) {
        return it->value; // Return the value if the key exists
    } else {
        // If the key doesn't exist, insert a new key-value pair and return the provided value
        Element element = {key, value};
        table[index].push_back(element);
        size++;
        return value;
    }
}

// Overloading the equality operator ==
bool operator==(const HashSet& other) const {
    if (size != other.size) {
        return false;
    }

    for (const auto& list : table) {
        for (const auto& el : list) {
            if (!other.contains(el.key) || other.get(el.key) != el.value) {
                return false;
            }
        }
    }

    return true;
}

// Overloading the {} operator to insert key-value pairs using { } syntax
void operator()(const K& key, const V& value) {
    insert(key, value);
}



    // Method to check if a key exists in the hash table
    bool contains(const K& key) const {
        int index = hash(key);

        // Search for the key in the corresponding list
        for (const auto& kv : table[index]) {
            if (kv.key == key) {
                return true; // Key found
            }
        }

        return false; // Key not found
    }

    // Method to check if the hash table is empty
    bool isEmpty() const {
        return size == 0;
    }
    // Method to retrieve a value for a given key
V get(const K& key) const {
    int index = hash(key);

    auto it = std::find_if(table[index].begin(), table[index].end(), [&](const Element& el) {
        return el.key == key;
    });

    if (it != table[index].end()) {
        return it->value; // Return the value if found
    } else {
        throw std::out_of_range("Key not found");
    }
}


// Method to insert a key-value pair into the hash table
void insert(const K& key, const V& value) {
    int index = hash(key);
    Element element = {key, value};

    // Check if the key already exists
    auto it = std::find_if(table[index].begin(), table[index].end(), [&](const Element& el) {
        return el.key == key;
    });

    if (it != table[index].end()) {
        // Key already exists, update the value
        it->value = value;
    } else {
        // Key doesn't exist, insert the new key-value pair
        table[index].push_back(element);
        size++;
    }
}

// Method to add an element (key-value pair) to the hash set
void push(const K& key, const V& value) {
    insert(key, value);
}

// Method to add an element (key-value pair) to the hash set
// It's similar to push, but returns an iterator to the inserted element
typename std::list<Element>::iterator push_back(const K& key, const V& value) {
    int index = hash(key);
    Element element = {key, value};
    table[index].push_back(element);
    size++;
    auto lastElement = table[index].end();
    --lastElement;
    return lastElement;
}

// Method to find an element by its key and return an iterator to it
typename std::list<Element>::iterator find(const K& key) {
    int index = hash(key);

    for (auto it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->key == key) {
            return it; // Return iterator to the found element
        }
    }

    return table[index].end(); // Return end iterator if not found
}

// Method to return the end iterator of the hash set for a given key
typename std::list<Element>::iterator end(const K& key) {
    int index = hash(key);
    return table[index].end();
}

// Method to remove a key-value pair from the hash table
void erase(const K& key) {
    int index = hash(key);

    auto it = std::find_if(table[index].begin(), table[index].end(), [&](const Element& el) {
        return el.key == key;
    });

    if (it != table[index].end()) {
        table[index].erase(it);
        size--;
    } else {
        throw std::out_of_range("Key not found");
    }
}

// Method to set a new value for a given key
void set(const K& key, const V& value) {
    int index = hash(key);

    auto it = std::find_if(table[index].begin(), table[index].end(), [&](const Element& el) {
        return el.key == key;
    });

    if (it != table[index].end()) {
        it->value = value; // Update the value if the key exists
    } else {
        throw std::out_of_range("Key not found");
    }
}



    // Method to initialize the hash set from a provided unordered_map
    void init_from(const std::unordered_map<K, V>& map) {
        clear(); // Clear the current elements

        // Reserve space based on the provided map's size
        reserve(map.size());

        // Insert elements from the provided map
        for (const auto& pair : map) {
            insert(pair.first, pair.second);
        }
    }
    int lookup_pos(const K& key) const {
        int index = hash(key);

        for (size_t i = 0; i < table[index].size(); ++i) {
            if (table[index][i].key == key) {
                return static_cast<int>(index);
            }
        }

        return -1; // Return -1 if key is not found
    }

    bool remove_at(const K& key) {
        int index = hash(key);

        auto it = std::find_if(table[index].begin(), table[index].end(), [&](const Element& el) {
            return el.key == key;
        });

        if (it != table[index].end()) {
            table[index].erase(it);
            size--;
            return true; // Return true indicating successful removal
        }

        return false; // Return false indicating key not found
    }

    // Method to create an indexed version of the hash set based on a provided function
    template<typename NewKey>
    std::unordered_map<NewKey, V> indexed(std::function<NewKey(const K&)> indexingFunction) const {
        std::unordered_map<NewKey, V> indexedMap;

        for (const auto& list : table) {
            for (const auto& el : list) {
                NewKey newKey = indexingFunction(el.key);
                indexedMap[newKey] = el.value;
            }
        }

        return indexedMap;
    }

    HashSet<NewK, NewV> cast_to() const {
    HashSet<NewK, NewV> newSet;

    // Copy elements by converting keys and values to the new types
    for (const auto& list : table) {
        for (const auto& el : list) {
            NewK newKey = static_cast<NewK>(el.key); // Convert key to NewK type
            NewV newValue = static_cast<NewV>(el.value); // Convert value to NewV type
            newSet.insert(newKey, newValue);
        }
    }

    return newSet;
}

void append(const HashSet& other) {
    for (const auto& list : other.table) {
        for (const auto& el : list) {
            insert(el.key, el.value);
        }
    }
}

// Method to clear all elements from the HashSet
void clear() {
    for (auto& list : table) {
        list.clear();
    }
    size = 0;
}

    bool replace(const K& key, const V& newValue, V& replaced) {
    int index = hash(key);

    for (auto& el : table[index]) {
        if (el.key == key) {
            replaced = el.value; // Store the old value
            el.value = newValue; // Replace with the new value
            return true; // Return true indicating successful replacement
        }
    }

    return false; // Return false indicating key not found
}

    // Method to apply a transformation function to each value in the hash set
    template<typename NewValue>
    HashSet<K, NewValue> map(std::function<NewValue(const V&)> mappingFunction) const {
        HashSet<K, NewValue> mappedSet;

        for (const auto& list : table) {
            for (const auto& el : list) {
                NewValue newValue = mappingFunction(el.value);
                mappedSet.insert(el.key, newValue);
            }
        }

        return mappedSet;
    }

    // Method to create a duplicate of the HashSet
    HashSet<K, V> duplicate() const {
        HashSet<K, V> duplicateSet;

        for (const auto& list : table) {
            for (const auto& el : list) {
                duplicateSet.insert(el.key, el.value);
            }
        }

        return duplicateSet;
    }

    bool is_null() const {
        return size == 0;
    }

    // Method to get the size (number of elements) of the HashSet
    int size() const {
        return size;
    }

    // Method to insert a key-value pair into the hash table at a specific hash value
    void insert_with_hash(const K& key, const V& value, int hashValue) {
        if (hashValue < 0 || hashValue >= static_cast<int>(table.size())) {
            throw std::out_of_range("Invalid hash value");
        }

        Element element = {key, value};
        table[hashValue].push_back(element);
        size++;
    }

    void resize_and_rehash(int newCapacity) {
        if (newCapacity <= 0) {
            throw std::invalid_argument("Invalid capacity");
        }

        std::vector<std::list<Element>> newTable(newCapacity);
        
        // Rehash all elements into the new table
        for (const auto& list : table) {
            for (const auto& el : list) {
                int newIndex = std::hash<K>{}(el.key) % newCapacity;
                newTable[newIndex].push_back(el);
            }
        }

        table = std::move(newTable);
    }

    // Method to reserve space in the hash set for a specified number of elements
    void reserve(int newCapacity) {
        if (newCapacity <= 0) {
            throw std::invalid_argument("Invalid capacity");
        }

        table.clear(); // Clear the existing table
        table.resize(newCapacity); // Resize the table to the new capacity
    }

    // Method to get the size of the hash table
    int getSize() const {
        return size;
    }
};

#endif /* HASHSET_H */