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

#include <algorithm>
#include <cstdio>

template <typename T>
class Vector {
private:
    class Node {
    public:
        T data;
        Node* next;

        // Node constructor
        Node(const T& value) : data(value), next(nullptr) {}
    };

public:
    // Iterator struct
    struct Iterator {
        Node* current;

        // Iterator constructor
        Iterator(Node* node) : current(node) {}

        // Overload the dereference operator
        T& operator*() const {
            return current->data;
        }

        // Overload the pre-increment operator
        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        // Overload the equality operator
        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        // Overload the inequality operator
        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };

private:
    Node* data;
    size_t size;
    size_t capacity;

public:
    Vector();
    ~Vector();
    Vector(const Vector<T>& other);
    Vector<T>& operator=(const Vector<T>& other);
    void push_back(const T& element);
    T& operator[](size_t index) const;
    const T* get_data() const;
    void insert(size_t index, const T& element);
    void erase(size_t index);
    size_t get_size() const;
    size_t get_capacity() const;
    void clear();
    void sort();
    void reserve(size_t newCapacity);
    bool empty() const;
    typename T* erase(typename T* pos);
    typename T* insert(typename T* pos, const T& value);
    void resize(size_t newSize, const T& value = T());
    
    
    
    
public:

    // Get the data array
    const T* get_data() const {
        T* dataArray = new T[size];
        Node* current = data;
        size_t index = 0;
        while (current != nullptr) {
            dataArray[index++] = current->data;
            current = current->next;
        }
        return dataArray;
    }

    // Get the local array of data
    T* get_local() const {
        T* localArray = new T[size];
        std::copy(get_data(), get_data() + size, localArray);
        return localArray;
    }

    // Get the begin iterator
    Iterator begin() const {
        return Iterator(data);
    }

    // Get the end iterator
    Iterator end() const {
        return Iterator(nullptr);
    }

    // Get the array of data
    const T* get_array_data() const {
        return get_data();
    }
};
// Get the data array
template <typename T>
const T* Vector<T>::get_data() const {
    T* dataArray = new T[size];
    Node* current = data;
    size_t index = 0;
    while (current != nullptr) {
        dataArray[index++] = current->data;
        current = current->next;
    }
    return dataArray;
}


// Insert an element at a specific index
template <typename T>
void Vector<T>::insert(size_t index, const T& element) {
    if (index > size) {
        throw std::out_of_range("Index out of range");
    }

    if (index == 0) {
        Node* newNode = new Node(element);
        newNode->next = data;
        data = newNode;
    } else {
        Node* current = data;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        Node* newNode = new Node(element);
        newNode->next = current->next;
        current->next = newNode;
    }

    ++size;
}

// Erase an element at a specific index
template <typename T>
void Vector<T>::erase(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }

    Node* temp;
    if (index == 0) {
        temp = data;
        data = data->next;
    } else {
        Node* current = data;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        temp = current->next;
        current->next = temp->next;
    }

    delete temp;
    --size;
}

void reserve(size_t newCapacity) {
        if (newCapacity > capacity) {
            T* newData = new T[newCapacity];
            std::copy(data, data + size, newData);
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
}

/**
     * @brief Access an element in the vector by index.
     * @param index The index of the element to access.
     * @return A reference to the element at the specified index.
     * @throws std::out_of_range if the index is out of bounds.
     */
    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];

}


template<typename T>
bool Vector<T>::empty() const {
        return size == 0;
}
/**
     * @brief Add an element to the end of the vector.
     * @param value The value to be added to the vector.
     */
     
template <typename T>
void Vector<T>::push_back(const T& value) {
	if (size == capacity) {
		if (capacity == 0) {
        	capacity = 1;
        } else {
            capacity *= 2;
        }

            T* newData = new T[capacity];
            std::copy(data, data + size, newData);
            delete[] data;
            data = newData;
        }

        data[size++] = value;
    
}
template<typename T>
typename T* Vector<T>::erase(typename T* pos) {
        size_t index = pos - data;
        if (index >= size) {
            throw std::out_of_range("Erase position out of range");
        }

        std::copy(data + index + 1, data + size, data + index);
        size--;

        return data + index;
}

    /**
     * @brief Sort the elements in the vector.
     */
     
template<typename T>
void Vector<T>::sort() {
	std::sort(data, data + size);
}

    /**
     * @brief Remove all elements from the vector.
     */
   
   
template <typename T>
void Vector<T>::clear() {
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;

}

/**
     * @brief Change the size of the vector.
     * @param newSize The new size of the vector.
     * @param value The value to initialize new elements (if any).
     */
     
template<typename T>
void Vector<T>::resize(size_t newSize, const T& value = T()) {
        if (newSize > size) {
            if (newSize > capacity) {
                reserve(newSize);
            }
            std::fill(data + size ,data + newSize, value);
        } else if (newSize < size) {
            size = newSize;
        }
}

/**
     * @brief Reserve a new capacity for the vector.
     * @param newCapacity The new capacity to reserve.
     */
   
template<typename T>
void Vector<T>::reserve(size_t newCapacity) {
        if (newCapacity > capacity) {
            T* newData = new T[newCapacity];
            std::copy(data, data + size, newData);
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }

}

/**
     * @brief Insert an element at a specific position in the vector.
     * @param pos Iterator pointing to the position where the element will be inserted.
     * @param value The value to be inserted.
     * @return Iterator pointing to the newly inserted element.
     */
     
template<typename T>
typename T* Vector<T>::insert(typename T* pos, const T& value) {
        size_t index = pos - data;
        if (index > size) {
            throw std::out_of_range("Insert position out of range");
        }

        if (size == capacity) {
            if (capacity == 0) {
                capacity = 1;
            } else {
                capacity *= 2;
            }

            T* newData = new T[capacity];
            std::copy(data, data + index, newData);
            newData[index] = value;
            std::copy(data + index, data + size, newData + index + 1);
            delete[] data;
            data = newData;
            size++;
        } else {
            std::copy_backward(data + index, data + size, data + size + 1);
            data[index] = value;
            size++;
        }

        return data + index;
}
 
Vector() : data(nullptr), size(0), capacity(0) {}

    /**
     * @brief Destructor for the Vector class.
     */
   - ~Vector() {
        delete[] data;
    }
    








#endif // VECTOR_H
