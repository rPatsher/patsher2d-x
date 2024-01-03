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

#include <c-logger/src/logger.h>

#include <unordered_map>
#include <string>
#include <vector>
#include <initializer_list>


template <typename T>
class Dictionary {
public:
    Dictionary();
    Dictionary(const std::initializer_list<std::pair<const std::string, T>>& initList);

public:
    void insert(const std::string& key, const T& value);
    bool contains(const std::string& key) const;
    T& get(const std::string& key);

    void ref(const std::string& key);
    void unref(const std::string& key);


    void remove(const std::string& key);
    size_t size() const;

    bool empty() const;
    void clear();

    void push_back(const std::string& key, const T& value);
    void error(const std::string& message) const;

    bool has(const std::string& key) const;
    bool has_all(const std::vector<std::string>& keys) const;

    void Dictionary<T>::erase(const std::string& key);

    T& get_valid(const std::string& key, const T& default_value) const;
    std::string find_key(const T& value) const;

    bool is_empty() const;
    void merge(const Dictionary<T>& other);

    std::vector<std::string> keys() const;
    std::vector<T> values() const;

    void append(const std::string& key, const T& value);
    void duplicate(const Dictionary& other);


    bool is_read_only() const;
    T& get_valid(const std::string& key, const T& default_value) const;

    const T& get_value_at_index(size_t index) const;
    T& get_or_add(const std::string& key, const T& default_value);

    T& operator[](const std::string& key);
    const T& operator[](const std::string& key) const;

    T& get(const std::string& key);
    T* getptr(const std::string& key);

    std::string id() const;
    size_t size() const;

    std::vector<std::string> get_key_list() const;
    std::string get_key_at_index(size_t index) const;

    bool operator==(const Dictionary<T>& other) const;
    bool operator!=(const Dictionary<T>& other) const;
private:
    std::unordered_map<std::string, T> data;
    bool read_only = false;
};


#endif // DICTIONARY_H