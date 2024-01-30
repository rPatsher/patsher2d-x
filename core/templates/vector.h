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
    // Constructor
    Vector();

    // Destructor
    ~Vector();

    // Copy constructor
    Vector(const Vector<T>& other);

    // Assignment operator
    Vector<T>& operator=(const Vector<T>& other);

    // Add an element to the end of the vector
    void push_back(const T& element);

    // Access an element at a specific index
    T& operator[](size_t index) const;

    // Get the data array
    const T* get_data() const;

    // Insert an element at a specific index
    void insert(size_t index, const T& element);

    // Erase an element at a specific index
    void erase(size_t index);

    // Get the size of the vector
    size_t get_size() const;

    // Get the capacity of the vector
    size_t get_capacity() const;
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

void clear() {
        while (size > 0) {
            pop_back();
        }
    }

    // Check if the vector is empty
    bool empty() const {
        return size == 0;
    }

    // Resize the vector to a specified size
    void resize(size_t newSize, const T& value = T()) {
        while (size < newSize) {
            push_back(value);
        }
        while (size > newSize) {
            pop_back();
        }
    }

    // Reserve space for a specified capacity
    void reserve(size_t newCapacity) {
        if (newCapacity > capacity) {
            Node* newData = new Node[newCapacity];
            for (size_t i = 0; i < size; ++i) {
                newData[i].data = data[i].data;
                newData[i].next = &newData[i + 1];
            }
            newData[size - 1].next = nullptr;
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
    }

    // Shrink the vector's capacity to fit its size
    void shrink_to_fit() {
        if (size < capacity) {
            reserve(size);
        }
    }

    // Insert elements at a specific position
    Iterator insert(Iterator position, const T& value) {
        if (position.current == nullptr) {
            push_back(value);
            return Iterator(end());
        }

        Node* newNode = new Node(value);
        newNode->next = position.current->next;
        position.current->next = newNode;
        ++size;

        return Iterator(newNode);
    }

    // Erase an element at a specific position
    Iterator erase(Iterator position) {
        if (position.current == nullptr || position.current->next == nullptr) {
            throw std::out_of_range("Invalid iterator position");
        }

        Node* erasedNode = position.current->next;
        position.current->next = erasedNode->next;
        delete erasedNode;
        --size;

        return Iterator(position.current->next);
    }
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

// Cast vector elements to another type
    template <typename U>
    Vector<U> cast_to() const {
        Vector<U> result;
        Node* current = data;
        while (current != nullptr) {
            result.push_back(static_cast<U>(current->data));
            current = current->next;
        }
        return result;
    }


};




#endif // VECTOR_H
