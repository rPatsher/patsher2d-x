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

#ifndef ARRAY_H
#define ARRAY_H

#include <algorithm>
#include <iterator>

#include "core/variant/variant.h"
#include "core/string/string_buffer.h"
#include "core/error/error_list.h"

#include <climits>

class Object;
class String;
class SafeCounted;
class RefCounted;


class Array {
public:
	class Element {
private:
    int data;

public:
    Element(int value);
    int get_data() const;
    void set_data(int value);
};
private:
    Element* data;
    int size;
    int capacity;
public:
	void _ref(const Array &p_from) const;
public:
    class Iterator {
    private:
        Element* current;

    public:
        Iterator(Element* ptr);
        Iterator& operator++();
        Element& operator*() const;
        bool operator!=(const Iterator& other) const;
    };

    class ConstIterator {
    private:
        const Element* current;

    public:
        ConstIterator(const Element* ptr);
        ConstIterator& operator++();
        const Element& operator*() const;
        bool operator!=(const ConstIterator& other) const;
    };

    Array(int size);
    ~Array();
    
    
    
    bool operator==(const Array &p_array) const;
	bool operator!=(const Array &p_array) const;
	bool recursive_equal(const Array &p_array, int recursion_count) const;

    int get_size() const;
    int get_capacity() const;
    void set_size(int newSize);

    Element get_element_at(int index) const;
    void set_element_at(int index, const Element& value);

    void push_back(const Element& value);
    void insert(int index, const Element& value);
    void reserve(int newCapacity);
    void erase(int index);
    void sort();
    void unsort();
    
    Array duplicate(bool p_deep = false) const;
	Array recursive_duplicate(bool p_deep, int recursion_count) const;
	
	void append_array(const Array &p_array);
	Error resize(int p_new_size);

    Iterator begin();
    Iterator end();
    ConstIterator cbegin() const;
    ConstIterator cend() const;

    void assign(const Array& other);
    bool is_empty() const;
    void clear();
    void append(const Array& other);
};

#endif // ARRAY_H