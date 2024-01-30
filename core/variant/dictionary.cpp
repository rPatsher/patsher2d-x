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
#include "dictionary.h"


#include <memory.h>
#include <memory_resource>
#include <locale>

#include <vector>
#include <vector.h>


template <typename T>
Dictionary<T>::Dictionary(const std::initializer_list<std::pair<const std::string, T>>& initList)
    : data(initList) {}




template <typename T>
bool Dictionary<T>::is_empty() const {
    return data.empty();
}

template <typename T>
void Dictionary<T>::merge(const Dictionary<T>& other) {
    for (const auto& pair : other.data) {
        data[pair.first] = pair.second;
    }
}

template <typename T>
void Dictionary<T>::erase(const std::string& key) {
    auto it = data.find(key);
    if (it != data.end()) {
        data.erase(it);
    } else {
        throw std::out_of_range("Key not found in dictionary.");
    }
}

template <typename T>
void Dictionary<T>::append(const std::string& key, const T& value) {
    // Using insert to add or update a key-value pair
    data[key] = value;
}

template <typename T>
bool Dictionary<T>::operator==(const Dictionary<T>& other) const {
    return data == other.data;
}

template <typename T>
bool Dictionary<T>::operator!=(const Dictionary<T>& other) const {
    return !(*this == other);
}



template <typename T>
const T& Dictionary<T>::get_value_at_index(size_t index) const {
    if (index >= data.size()) {
        throw std::out_of_range("Index out of bounds.");
    }

    auto it = data.begin();
    std::advance(it, index);

    return it->second;
}

template <typename T>
T& Dictionary<T>::get(const std::string& key) {
    if (!contains(key)) {
        throw std::out_of_range("Key not found in dictionary.");
    }
    return data.at(key);
}

template <typename T>
T* Dictionary<T>::getptr(const std::string& key) {
    if (!contains(key)) {
        return nullptr;
    }
    return &data[key];
}




template <typename T>
void Dictionary<T>::duplicate(const Dictionary& other) {
    data = other.data;
}

template <typename T>
void Dictionary<T>::ref(const std::string& key) {
    auto it = data.find(key);
    if (it != data.end()) {
        ++(it->second.second); // Increment the reference count
    } else {
        throw std::out_of_range("Key not found in dictionary.");
    }
}



template <typename T>
void Dictionary<T>::unref(const std::string& key) {
    auto it = data.find(key);
    if (it != data.end()) {
        if (it->second.second > 0) {
            --(it->second.second); // Decrement the reference count
        } else {
            throw std::logic_error("Reference count already at zero.");
        }
    } else {
        throw std::out_of_range("Key not found in dictionary.");
    }
}

template <typename T>
bool Dictionary<T>::is_read_only() const {
    return read_only;
}

template <typename T>
T& Dictionary<T>::get_valid(const std::string& key, const T& default_value) const {
    if (contains(key)) {
        return get(key);
    } else {
        data[key] = default_value;
        return data[key];
    }
}

template <typename T>
std::vector<std::string> Dictionary<T>::get_key_list() const {
    std::vector<std::string> keys;
    keys.reserve(data.size());

    for (const auto& pair : data) {
        keys.push_back(pair.first);
    }

    return keys;
}

template <typename T>
std::string Dictionary<T>::get_key_at_index(size_t index) const {
    if (index >= data.size()) {
        throw std::out_of_range("Index out of bounds.");
    }

    auto it = data.begin();
    std::advance(it, index);

    return it->first;
}

template <typename T>
Dictionary<T>::Dictionary() {}

template <typename T>
void Dictionary<T>::insert(const std::string& key, const T& value) {
    data[key] = value;
}

template <typename T>
bool Dictionary<T>::contains(const std::string& key) const {
    return data.find(key) != data.end();
}

template <typename T>
T& Dictionary<T>::get(const std::string& key) {
    if (!contains(key)) {
        error("Key not found in dictionary.");
    }
    return data.at(key);
}

template <typename T>
void Dictionary<T>::remove(const std::string& key) {
    if (!contains(key)) {
        error("Key not found in dictionary.");
    }
    data.erase(key);
}

template <typename T>
size_t Dictionary<T>::size() const {
    return data.size();
}

template <typename T>
bool Dictionary<T>::empty() const {
    return data.empty();
}

template <typename T>
void Dictionary<T>::clear() {
    data.clear();
}

template <typename T>
void Dictionary<T>::push_back(const std::string& key, const T& value) {
    if (contains(key)) {
        error("Key already exists in dictionary.");
    }
    insert(key, value);
}

template <typename T>
void Dictionary<T>::error(const std::string& message) const {
    throw std::runtime_error(message);
    LOG_DEBUG(error);
}

template <typename T>
bool Dictionary<T>::has(const std::string& key) const {
    return contains(key);
}

template <typename T>
bool Dictionary<T>::has_all(const std::vector<std::string>& keys) const {
    return std::all_of(keys.begin(), keys.end(), [this](const std::string& key) {
        return contains(key);
    });
}



template <typename T>
T& Dictionary<T>::get_or_add(const std::string& key, const T& default_value) {
    if (!contains(key)) {
        data[key] = default_value;
    }
    return data[key];
}

template <typename T>
void Dictionary<T>::insert(const std::string& key, const T& value) {
    if (read_only) {
        throw std::logic_error("Dictionary is read-only. Cannot modify contents.");
    }
    data[key] = value;
}

template <typename T>
void Dictionary<T>::remove(const std::string& key) {
    if (read_only) {
        throw std::logic_error("Dictionary is read-only. Cannot modify contents.");
    }
    data.erase(key);
}

template <typename T>
std::string Dictionary<T>::find_key(const T& value) const {
    auto it = std::find_if(data.begin(), data.end(), [&](const auto& pair) {
        return pair.second == value;
    });

    if (it != data.end()) {
        return it->first;
    }

    return ""; // Return an empty string if value is not found in the dictionary
}

template <typename T>
std::string Dictionary<T>::id() const {
    std::ostringstream oss;
    oss << reinterpret_cast<std::uintptr_t>(this);
    return oss.str();
}

template <typename T>
size_t Dictionary<T>::size() const {
    return data.size();
}

template <typename T>
T& Dictionary<T>::operator[](const std::string& key) {
    return data[key];
}

template <typename T>
const T& Dictionary<T>::operator[](const std::string& key) const {
    auto it = data.find(key);
    if (it == data.end()) {
        throw std::out_of_range("Key not found in dictionary.");
    }
    return it->second;
}
