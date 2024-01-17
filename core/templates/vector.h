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
#ifndef VECTOR_H
#define VECTOR_H


#include <array>
#include <vector>

#include <cstdint> 

#include "core/templates/map.h"
#include "core/variant/dictionary.h"

template <typename T>
class Vector {
private:
    T* array;
    size_t capacity;
    size_t size;

public:
    // Constructor
    Vector() : array(nullptr), capacity(0), size(0) {}

    // Destructor
    ~Vector() {
        delete[] array;
    }

    void push_back(const T& element) {
        if (size >= capacity) {
            size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
            T* new_array = new T[new_capacity];
            for (size_t i = 0; i < size; ++i) {
                new_array[i] = array[i];
            }
            delete[] array;
            array = new_array;
            capacity = new_capacity;
        }
        array[size++] = element;
    }
    
    
    size_t getSize() const {
        return size;
    }

   void fill(const T& p_elem) {
    for (size_t i = 0; i < size; ++i) {
        array[i] = p_elem;
    }

    }
    void remove_at(int p_index) {
    if (p_index < 0 || p_index >= size) {
        throw std::out_of_range("Index out of range");
    }
    for (size_t i = p_index; i < size - 1; ++i) {
        array[i] = array[i + 1];
    }
    size--;
    }

    Vector<T> slice(int p_begin, int p_end = INT_MAX) const {
    p_end = (p_end > size) ? size : p_end;
    p_begin = (p_begin < 0) ? 0 : p_begin;

    if (p_begin >= p_end) {
        return Vector<T>();
    }



    Vector<T> result;
    for (int i = p_begin; i < p_end; ++i) {
        result.push_back(array[i]);
    }
    return result;
}
template <class T>
bool operator!=(const Vector<T>& p_arr) const {
    if (size != p_arr.size) {
        return true; 
    }

    for (size_t i = 0; i < size; ++i) {
        if (array[i] != p_arr[i]) {
            return true;
        }
    }

    return false;  
}

Vector<uint8_t> to_byte_array() const {
    Vector<uint8_t> byte_array;
    for (size_t i = 0; i < size; ++i) {
        uint8_t* bytes = reinterpret_cast<uint8_t*>(&array[i]);
        for (size_t j = 0; j < sizeof(T); ++j) {
            byte_array.push_back(bytes[j]);
        }
    }
    return byte_array;
}



    // Function to access elements by index
    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return array[index];
    }

     T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("???? ???? ??????");
        }
        return array[index];
    }

    // ??? ???????? ????? ?????
    void fill(const T& p_elem) {
        for (size_t i = 0; i < size; ++i) {
            array[i] = p_elem;
        }
    }
};

#endif // VECTOR_H
