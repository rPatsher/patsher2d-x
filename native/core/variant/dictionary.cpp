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

#include "core/variant/variant.h"
#include "core/string/ustring.h"



#include <memory.h>
#include <memory_resource>
#include <locale>
#include <vector>
#include <vector.h>


Dictionary<T>::Dictionary(const std::initializer_list<std::pair<const String, T>>& initList)
    : data(initList) {}




bool Dictionary::is_empty() const {
    return data.empty();
}

void Dictionary::merge(const Dictionary& other) {
    for (const auto& pair : other.data) {
        data[pair.first] = pair.second;
    }
}

void Dictionary::erase(const String& key) {
    auto it = data.find(key);
    if (it != data.end()) {
        data.erase(it);
    } else {
        throw std::out_of_range("Key not found in dictionary.");
    }
}

void Dictionary::append(const String& key, const Variant& value) {
    // Using insert to add or update a key-value pair
    data[key] = value;
}

bool Dictionary::operator==(const Dictionary& other) const {
    return data == other.data;
}

bool Dictionary::operator!=(const Dictionary& other) const {
    return !(*this == other);
}


Variant Dictionary::get_value_at_index(size_t index) const {
    if (index >= data.size()) {
        throw std::out_of_range("Index out of bounds.");
    }

    auto it = data.begin();
    std::advance(it, index);

    return it->second;
}


Variant Dictionary::get(const String& key) {
    if (!contains(key)) {
        throw std::out_of_range("Key not found in dictionary.");
    }
    return data.at(key);
}

Variant Dictionary::getptr(const String& key) {
    if (!contains(key)) {
        return nullptr;
    }
    return &data[key];
}



void Dictionary::duplicate(const Dictionary& other) {
    data = other.data;
}

void Dictionary::ref(const String& key) {
    auto it = data.find(key);
    if (it != data.end()) {
        ++(it->second.second); // Increment the reference count
    } else {
        throw std::out_of_range("Key not found in dictionary.");
    }
}



void Dictionary::unref(const String& key) {
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

bool Dictionary::is_read_only() const {
    return read_only;
}

Variant Dictionary::get_valid(const String& key, const Variant& default_value) const {
    if (contains(key)) {
        return get(key);
    } else {
        data[key] = default_value;
        return data[key];
    }
}

Vector<String> Dictionary::get_key_list() const {
    Vector<String> keys;
    keys.reserve(data.size());

    for (const auto& pair : data) {
        keys.push_back(pair.first);
    }

    return keys;
}

String Dictionary::get_key_at_index(size_t index) const {
    if (index >= data.size()) {
        throw std::out_of_range("Index out of bounds.");
    }

    auto it = data.begin();
    std::advance(it, index);

    return it->first;
}


Dictionary::Dictionary() {}


void Dictionary::insert(const String& key, const T& value) {
    data[key] = value;
}


bool Dictionary::contains(const String& key) const {
    return data.find(key) != data.end();
}


String Dictionary::get(const String& key) {
    if (!contains(key)) {
        error("Key not found in dictionary.");
    }
    return data.at(key);
}

void Dictionary::remove(const String& key) {
    if (!contains(key)) {
        error("Key not found in dictionary.");
    }
    data.erase(key);
}

size_t Dictionary::size() const {
    return data.size();
}

bool Dictionary::empty() const {
    return data.empty();
}

void Dictionary::clear() {
    data.clear();
}

void Dictionary::push_back(const String& key, const T& value) {
    if (contains(key)) {
        error("Key already exists in dictionary.");
    }
    insert(key, value);
}

void Dictionary::error(const String& message) const {
    throw std::runtime_error(message);
}

bool Dictionary::has(const String& key) const {
    return contains(key);
}

bool Dictionary::has_all(const Vector<String>& keys) const {
    return std::all_of(keys.begin(), keys.end(), [this](const String& key) {
        return contains(key);
    });
}



Variant Dictionary::get_or_add(const String& key, const Vsriant& default_value) {
    if (!contains(key)) {
        data[key] = default_value;
    }
    return data[key];
}


void Dictionary::insert(const String& key, const Variant& value) {
    if (read_only) {
        throw std::logic_error("Dictionary is read-only. Cannot modify contents.");
    }
    data[key] = value;
}

void Dictionary::remove(const String& key) {
    if (read_only) {
        throw std::logic_error("Dictionary is read-only. Cannot modify contents.");
    }
    data.erase(key);
}

String Dictionary::find_key(const Variant& value) const {
    auto it = std::find_if(data.begin(), data.end(), [&](const auto& pair) {
        return pair.second == value;
    });

    if (it != data.end()) {
        return it->first;
    }

    return ""; // Return an empty string if value is not found in the dictionary
}



String Dictionary::id() const {
    std::ostringstream oss;
    oss << reinterpret_cast<std::uintptr_t>(this);
    return oss.str();
}

size_t Dictionary::size() const {
    return data.size();
}

Variant Dictionary::operator[](const String& key) {
    return data[key];
}

Variant Dictionary::operator[](const String& key) const {
    auto it = data.find(key);
    if (it == data.end()) {
        throw std::out_of_range("Key not found in dictionary.");
    }
    return it->second;
}
