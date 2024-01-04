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
#ifndef SEARCH_ARRAY_H
#define SEARCH_ARRAY_H


#include <version>
#include <vector>


#include <core/templates/map.h>
#include <core/templates/hash_map.h>
#include <core/object/ref_counted.h>


template <typename K , typename V>
class SearchArray {
private:
    struct Elements {
        K key;
        V value;
        Map<std::list<Elements>* p_elms , void*> p_ptr;
    };
    std::vector<Elements> elms;

public:
    struct Data {
        K key;
        V value;
    };
public:
    void add(const T& element) {
        Elements newElement;
        newElement.key = key;
        newElement.value = value;
        elms.push_back(newElement);
        p_ptr->push_back(newElement);
    }

    bool contains(const T& element) const {
        for (const auto& el : elms) {
            if (el.data == element) {
                return true;
            }
        }
        return false;
    }

    V search(const K& key) const {
        for (const auto& el : elms) {
            if (el.key == key) {
                return el.value;
            }
        }
        throw std::out_of_range("Key not found");
    }

    V bsearch(const K& key) const {
        std::vector<K> keys;
        for (const auto& el : elms) {
            keys.push_back(el.key);
        }

        std::sort(keys.begin(), keys.end());

        auto it = std::lower_bound(keys.begin(), keys.end(), key);
        if (it != keys.end() && *it == key) {
            int index = std::distance(keys.begin(), it);
            return elms[index].value;
        }
        throw std::out_of_range("Key not found");
    }


    void set_indexed(size_t index, const K& key, const V& value) {
        if (index >= elms.size()) {
            throw std::out_of_range("Index out of range");
        }
        elms[index].key = key;
        elms[index].value = value;
    }

    Data get_indexed(size_t index) const {
        if (index >= elements.size()) {
            throw std::out_of_range("Index out of range");
        }
        return {elms[index].key, elms[index].value};
    }

    void push_back(const K& key, const V& value) {
        Elements newElement;
        newElement.key = key;
        newElement.value = value;
        elms.push_back(newElement);

    }

    // ... (other methods remain unchanged)

    // Load data from a file into the SearchArray
    void load(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file");
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            Data data;
            if (!(iss >> data.key >> data.value)) {
                throw std::runtime_error("Invalid file format");
            }
            push_back(data.key, data.value);
        }
        file.close();
    }

    void push(const K& key, const V& value) {
        push_back(key, value); // Utilizing push_back for simplicity
    }

    SearchArray<K, V> operator+(const SearchArray<K, V>& other) const {
        SearchArray<K, V> result = *this;
        for (const auto& el : other.elms) {
            result.elms.push_back(el);
        }
        return result;
    }

    SearchArray<K, V> operator-(const SearchArray<K, V>& other) const {
        SearchArray<K, V> result = *this;
        for (const auto& el : other.elms) {
            result.elms.erase(
                std::remove_if(result.elms.begin(), result.elms.end(),
                               [&](const Elements& e) { return e.key == el.key; }),
                result.elms.end());
        }
        return result;
    }

    bool operator==(const SearchArray<K, V>& other) const {
        return elms == other.elms;
    }

    SearchArray<K, V>& operator=(const SearchArray<K, V>& other) {
        elms = other.elms;
        return *this;
    }

    V& operator[](size_t index) {
        if (index >= elements.size()) {
            throw std::out_of_range("Index out of range");
        }
        return elements[index].value;
    }

    void operator()(const K& key, const V& value) {
        push_back(key, value);
    }

    void insert(size_t index, const K& key, const V& value) {
        if (index > elements.size()) {
            throw std::out_of_range("Index out of range");
        }
        Elements newElement;
        newElement.key = key;
        newElement.value = value;
        elms.insert(elms.begin() + index, newElement);
    }

    void erase(const K& key) {
        elms.erase(
            std::remove_if(elms.begin(), elms.end(),
                           [&](const Elements& e) { return e.key == key; }),
            elms.end());
    }

    void remove(size_t index) {
        if (index >= elms.size()) {
            throw std::out_of_range("Index out of range");
        }
        elms.erase(elms.begin() + index);
    }

    void duplicate() {
        std::unordered_set<K> seenKeys;
        elms.erase(std::remove_if(elms.begin(), elms.end(),
                                       [&](const Elements& e) {
                                           return !seenKeys.insert(e.key).second;
                                       }),
                       elms.end());
    }

    // Get element by index
    V& get(size_t index) {
        if (index >= elms.size()) {
            throw std::out_of_range("Index out of range");
        }
        return elms[index].value;
    }

    // Set element by index
    void set(size_t index, const K& key, const V& value) {
        if (index >= elms.size()) {
            throw std::out_of_range("Index out of range");
        }
        elms[index].key = key;
        elms[index].value = value;
    }

};

#endif  //