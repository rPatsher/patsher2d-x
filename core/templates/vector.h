#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <algorithm>

/**
 * @brief A simple dynamic array implementation similar to std::vector.
 * @tparam T The type of elements stored in the vector.
 */
template<typename T>
class Vector {
private:
    T* data;        ///< Pointer to the dynamic array.
    size_t size;     ///< Current number of elements in the vector.
    size_t capacity; ///< Current capacity of the vector.

public:
    /**
     * @brief Default constructor for the Vector class.
     */
    Vector() : data(nullptr), size(0), capacity(0) {}

    /**
     * @brief Destructor for the Vector class.
     */
    ~Vector() {
        delete[] data;
    }

    /**
     * @brief Get the current size of the vector.
     * @return The number of elements in the vector.
     */
    size_t getSize() const {
        return size;
    }

    /**
     * @brief Get the current capacity of the vector.
     * @return The maximum number of elements the vector can hold without reallocation.
     */
    size_t getCapacity() const {
        return capacity;
    }

    /**
     * @brief Add an element to the end of the vector.
     * @param value The value to be added to the vector.
     */
    void push_back(const T& value) {
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

    /**
     * @brief Insert an element at a specific position in the vector.
     * @param pos Iterator pointing to the position where the element will be inserted.
     * @param value The value to be inserted.
     * @return Iterator pointing to the newly inserted element.
     */
    typename T* insert(typename T* pos, const T& value) {
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

    /**
     * @brief Erase an element at a specific position in the vector.
     * @param pos Iterator pointing to the element to be erased.
     * @return Iterator pointing to the element after the erased element.
     */
    typename T* erase(typename T* pos) {
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
    void sort() {
        std::sort(data, data + size);
    }

    /**
     * @brief Remove all elements from the vector.
     */
    void clear() {
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    /**
     * @brief Remove the last element from the vector.
     */
    void popBack() {
        if (size > 0) {
            size--;
        }
    }

    /**
     * @brief Change the size of the vector.
     * @param newSize The new size of the vector.
     * @param value The value to initialize new elements (if any).
     */
    void resize(size_t newSize, const T& value = T()) {
        if (newSize > size) {
            if (newSize > capacity) {
                reserve(newSize);
            }
            std::fill(data + size, data + newSize, value);
        } else if (newSize < size) {
            size = newSize;
        }
    }

    /**
     * @brief Reserve a new capacity for the vector.
     * @param newCapacity The new capacity to reserve.
     */
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
};

#endif // VECTOR_H
