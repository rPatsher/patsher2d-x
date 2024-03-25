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

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <unordered_map>
#include <initializer_list>

#include "core/error/error_macros.h"
#include "core/string/ustring.h"
#include "core/templates/vector.h"

class Dictionary {
public:
    Dictionary();
    Dictionary(const std::initializer_list<std::pair<const String, T>>& initList);

public:
    void insert(const String& key, const T& value);
    bool contains(const String& key) const;
    T& get(const String& key);

    void ref(const String& key);
    void unref(const String& key);


    void remove(const String& key);
    size_t size() const;

    bool empty() const;
    void clear();

    void push_back(const String& key, const T& value);
    void error(const String& message) const;

    bool has(const String& key) const;
    bool has_all(const Vector<String>& keys) const;

    void Dictionary erase(const String& key);

    Variant get_valid(const String& key, const T& default_value) const;
    String find_key(const T& value) const;

    bool is_empty() const;
    void merge(const Dictionary& other);

    Vector<String> keys() const;
    Vector<T> values() const;

    void append(const String& key, const T& value);
    void duplicate(const Dictionary& other);


    bool is_read_only() const;
    T& get_valid(const String& key, const T& default_value) const;

    const T& get_value_at_index(size_t index) const;
    T& get_or_add(const String& key, const T& default_value);

    Dictionary operator[](const String& key);
    Variant operator[](const String& key) const;

    Variant get(const String& key);
    Variant getptr(const String& key);

    String id() const;
    size_t size() const;

    Vector<String> get_key_list() const;
    String get_key_at_index(size_t index) const;

    bool operator==(const Dictionary<T>& other) const;
    bool operator!=(const Dictionary<T>& other) const;
private:
    std::unordered_map<String, Variant> data;
    bool read_only = false;
};


#endif // DICTIONARY_H