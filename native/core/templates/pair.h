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

#ifndef PAIR_H
#define PAIR_H

#include <vector>
#include <algorithm>

/**
	* @class Pair
	* @brief The Pair class, as discussed earlier, is a generic template class that holds two values, typically referred to as a key-value pair. It's a simple data structure often used in programming to associate one value (the key) with another value (the value)
template <typename K, typename V>
*/

class Pair {
public:
    Pair(const K& key, const V& value) : key(key), value(value) {}

    K getKey() const {
        return key;
    }

    V getValue() const {
        return value;
    }

    // Pushes a copy of the current Pair to the end of a container
    void push_back(std::vector<Pair>& container) const {
        container.push_back(*this);
    }

    // Emplaces a Pair at the end of a container
    template <typename... Args>
    void emplace_back(std::vector<Pair>& container, Args&&... args) const {
        container.emplace_back(std::forward<Args>(args)...);
    }

    // Clears the container
    static void clear(std::vector<Pair>& container) {
        container.clear();
    }

    // Inserts a Pair at a specified position in the container
    template <typename... Args>
    static void insert(std::vector<Pair>& container, typename std::vector<Pair>::iterator position, Args&&... args) {
        container.insert(position, Pair(std::forward<Args>(args)...));
    }

    // Erases a Pair at a specified position in the container
    static void erase(std::vector<Pair>& container, typename std::vector<Pair>::iterator position) {
        container.erase(position);
    }

    // Checks if a key exists in the container
    static bool has(const std::vector<Pair>& container, const K& key) {
        return std::find_if(container.begin(), container.end(),
                            [&key](const Pair& pair) { return pair.getKey() == key; }) != container.end();
    }

    // Finds the iterator pointing to the Pair with the specified key
    static typename std::vector<Pair>::iterator find(std::vector<Pair>& container, const K& key) {
        return std::find_if(container.begin(), container.end(),
                            [&key](const Pair& pair) { return pair.getKey() == key; });
    }

    // Returns the iterator pointing to the end of the container
    static typename std::vector<Pair>::iterator end(std::vector<Pair>& container) {
        return container.end();
    }
    // Returns an iterator pointing to the next Pair in the container
    static typename std::vector<Pair>::iterator next(std::vector<Pair>& container, typename std::vector<Pair>::iterator current) {
        return std::next(current);
    }

    // Inserts a Pair at a specified position in the container
    template <typename... Args>
    static void insert_at(std::vector<Pair>& container, size_t index, Args&&... args) {
        typename std::vector<Pair>::iterator position = container.begin() + index;
        container.insert(position, Pair(std::forward<Args>(args)...));
    }

    // Removes a Pair at a specified position in the container
    static void remove_at(std::vector<Pair>& container, size_t index) {
        typename std::vector<Pair>::iterator position = container.begin() + index;
        container.erase(position);
    }
    
    class Iterator {
    public:
        explicit Iterator(typename std::vector<Pair>::iterator iter) : iterator(iter) {}

        Pair& operator*() const {
            return *iterator;
        }

        Iterator& operator++() {
            ++iterator;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return iterator != other.iterator;
        }

    private:
        typename std::vector<Pair>::iterator iterator;
    };

    // Get iterator pointing to the beginning of the container
    Iterator begin(std::vector<Pair>& container) {
        return Iterator(container.begin());
    }

    // Get iterator pointing to the end of the container
    Iterator end(std::vector<Pair>& container) {
        return Iterator(container.end());
    }
    
    class Node {
    public:
        Pair data;
        Node* next;

        explicit Node(const K& key, const V& value) : data(key, value), next(nullptr) {}
    };

    ~Pair() {} // Destructor to handle cleanup if needed

private:
    K key;
    V value;
};

#endif // PAIR_H