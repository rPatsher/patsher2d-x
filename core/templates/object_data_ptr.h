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
#ifndef OBJECT_DATA_PTR_H
#define OBJECT_DATA_PTR_H

#include <memory> // For std::make_shared, std::make_unique, etc.
#include <algorithm>  // For rfind() find()

#include <vector>


template<typename T>
class ObjectDataPtr {
private:
    T* ptr;

public:
    ObjectDataPtr() : ptr(nullptr) {}

    explicit ObjectDataPtr(T* p) : ptr(p) {}

    ~ObjectDataPtr() {
        delete ptr;
    }

    // Copy constructor
    ObjectDataPtr(const ObjectDataPtr<T>& other) {
        if (other.ptr) {
            ptr = new T(*other.ptr);
        } else {
            ptr = nullptr;
        }
    }

    // Copy assignment operator
    ObjectDataPtr<T>& operator=(const ObjectDataPtr<T>& other) {
        if (this != &other) {
            delete ptr;
            if (other.ptr) {
                ptr = new T(*other.ptr);
            } else {
                ptr = nullptr;
            }
        }
        return *this;
    }

    // Overloaded operators
    T* operator->() const {
        return ptr;
    }

    T& operator*() const {
        return *ptr;
    }

    T* get() const {
        return ptr;
    }


    // Set the pointer to a new value
    void set(T* p) {
        if (ptr != p) {
            delete ptr;
            ptr = p;
        }
    }

    // Function to clone the object pointed by ObjectDataPtr
    std::unique_ptr<T> clone() const {
        if (!ptr) {
            return nullptr;
        }
        return std::make_unique<T>(*ptr);
    }

    // Make a shared pointer to the object
    std::shared_ptr<T> make_shared() const {
        return std::make_shared<T>(*ptr);
    }

    // Make a unique pointer to the object
    std::unique_ptr<T> make_unique() const {
        return std::make_unique<T>(*ptr);
    }

    // Allocate memory for a new object of type T using new
    void allocate() {
        if (!ptr) {
            ptr = new T();
        }
    }

    // Deallocate memory for the object
    void deallocate() {
        delete ptr;
        ptr = nullptr;
    }

    // Push an element into the object pointed by the pointer (assuming it's a container like vector)
    void push_back(const typename T::value_type& value) {
        if (ptr) {
            ptr->push_back(value);
        }
    }

    // Get size of the object pointed to
    typename T::size_type size() const {
        return ptr ? ptr->size() : 0;
    }

    // Get pointer to data
    typename T::value_type* data() const {
        return ptr ? ptr->data() : nullptr;
    }

    // Access element at specified index
    typename T::value_type& index(typename T::size_type i) const {
        if (ptr && i < ptr->size()) {
            return (*ptr)[i];
        } else {
            throw std::out_of_range("Index out of bounds");
        }
    }

    // Get the container object itself
    T& container() const {
        if (ptr) {
            return *ptr;
        } else {
            throw std::runtime_error("Pointer is null");
        }
    }

    // Insert an element at a specified position
    void insert(typename T::iterator position, const typename T::value_type& value) {
        if (ptr) {
            ptr->insert(position, value);
        }
    }

    // Find a value within the container
    typename T::iterator find(const typename T::value_type& value) const {
        if (ptr) {
            return std::find(ptr->begin(), ptr->end(), value);
        } else {
            throw std::runtime_error("Pointer is null");
        }
    }

    // Find the last occurrence of a value within the container
    typename T::reverse_iterator rfind(const typename T::value_type& value) const {
        if (ptr) {
            return std::find(ptr->rbegin(), ptr->rend(), value);
        } else {
            throw std::runtime_error("Pointer is null");
        }
    }

    // Set a value at a specified index
    void setv(typename T::size_type i, const typename T::value_type& value) const {
        if (ptr && i < ptr->size()) {
            (*ptr)[i] = value;
        } else {
            throw std::out_of_range("Index out of bounds");
        }
    }

    // Get a value at a specified index
    typename T::value_type getv(typename T::size_type i) const {
        if (ptr && i < ptr->size()) {
            return (*ptr)[i];
        } else {
            throw std::out_of_range("Index out of bounds");
        }
    }
};

// Function to create a new ObjectDataPtr that holds a clone of the provided pointer
template<typename T>
ObjectDataPtr<T> CloneObjectDataPtr(const ObjectDataPtr<T>& objData) {
    return ObjectDataPtr<T>(objData.clone().release());
}

#endif //OBJECTDATAPTR_H