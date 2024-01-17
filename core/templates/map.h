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

#ifndef MAP_H
#define MAP_H

#include <functional>
#include <stdexcept>
#include <vector>

template <typename Key, typename Value>
class Map {
private:
    struct Node {
        Key key;
        Value value;
        Node* next;

        Node(const Key& k, const Value& v) : key(k), value(v), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    Map() : head(nullptr), tail(nullptr) {}
    ~Map() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // ... (other methods)

    // Operator overloading

    // Assignment operator
    Map& operator=(const Map& other) {
        if (this != &other) {
            // Clear current map
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }

            // Copy from other map
            Node* current = other.head;
            while (current) {
                append(current->key, current->value);
                current = current->next;
            }
        }
        return *this;
    }

    // Addition operator to merge two maps
    Map operator+(const Map& other) const {
        Map result(*this);

        Node* current = other.head;
        while (current) {
            result.append(current->key, current->value);
            current = current->next;
        }

        return result;
    }

    // Equality operator
    bool operator==(const Map& other) const {
        Node* current = head;
        Node* otherCurrent = other.head;

        while (current && otherCurrent) {
            if (current->key != otherCurrent->key || current->value != otherCurrent->value) {
                return false;
            }
            current = current->next;
            otherCurrent = otherCurrent->next;
        }

        return (current == nullptr && otherCurrent == nullptr);
    }

    // Comparison operators
    bool operator<=(const Map& other) const {
        // Implement comparison logic here
        // For example: (this map is less than or equal to the other map)
    }

    bool operator>=(const Map& other) const {
        // Implement comparison logic here
        // For example: (this map is greater than or equal to the other map)
    }

    // Index operator to access values by key
    Value& operator[](const Key& key) {
        Node* current = head;
        while (current) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }

        // If the key is not found, create a new node with a default value
        append(key, Value());
        return tail->value;
    }

    void push_back(const Key& key, const Value& value) {
        append(key, value);
    }

    bool get(const Key& key, Value& value) const {
        Node* current = head;
        while (current) {
            if (current->key == key) {
                value = current->value;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool remove(const Key& key) {
        Node* current = head;
        Node* prev = nullptr;

        while (current) {
            if (current->key == key) {
                if (prev)
                    prev->next = current->next;
                else
                    head = current->next;

                if (current == tail) {
                    tail = prev;
                }

                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    void insert(const Key& key, const Value& value, size_t position) {
        if (position == 0) {
            Node* newNode = new Node(key, value);
            newNode->next = head;
            head = newNode;
            if (!tail) {
                tail = head;
            }
        } else {
            Node* current = head;
            for (size_t i = 0; i < position - 1 && current; ++i) {
                current = current->next;
            }
            if (current) {
                Node* newNode = new Node(key, value);
                newNode->next = current->next;
                current->next = newNode;
                if (!newNode->next) {
                    tail = newNode;
                }
            }
        }
    }

    struct Data {
        Key key;
        Value value;
    };

    bool get_map(std::vector<std::pair<Key, Value>>& result) const {
        Node* current = head;
        while (current) {
            result.push_back(std::make_pair(current->key, current->value));
            current = current->next;
        }
        return !result.empty();
    }

    bool find(const Key& key, Value& value) const {
        Node* current = head;
        while (current) {
            if (current->key == key) {
                value = current->value;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Reverse find: Find the last occurrence of a key in the map
    bool rfind(const Key& key, Value& value) const {
        Node* current = head;
        Node* found = nullptr;
        while (current) {
            if (current->key == key) {
                found = current;
            }
            current = current->next;
        }
        if (found) {
            value = found->value;
            return true;
        }
        return false;
    }


    void map(std::function<void(const Key&, Value&)> func) {
        Node* current = head;
        while (current) {
            func(current->key, current->value);
            current = current->next;
        }
    }

    bool get_key(const Key& key, std::vector<Value>& result) const {
        Node* current = head;
        bool found = false;
        while (current) {
            if (current->key == key) {
                result.push_back(current->value);
                found = true;
            }
            current = current->next;
        }
        return found;
    }

    std::vector<Data> data() const {
        std::vector<Data> result;
        Node* current = head;
        while (current) {
            result.push_back({current->key, current->value});
            current = current->next;
        }
        return result;
    }
};

#endif // MAP_H