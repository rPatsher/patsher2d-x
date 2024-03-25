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
#ifndef REF_COUNTED_H
#define REF_COUNTED_H




#include <varargs.h>
#include <variant>

class Variant;


class RefCounted {
public:
    RefCounted();
    RefCounted(int initialRefCount); // Parameterized constructor
    virtual ~RefCounted();

    bool init_ref();             // Initialize reference count
    bool reference();            // Add a reference
    bool unreference();          // Remove a reference
    int get_reference_count() const;  // Get the reference count
    bool is_referenced() const;  // Check if referenced

private:
    unsigned int refCount;
    bool isInitialized;
};

template<typename T>
class Ref {
public:
    Ref() : ptr(nullptr) {}
    Ref(T* ptr) : ptr(ptr) {
        if (ptr) {
            ptr->init_ref();
        }
    }
    template <class T_Other>
    Ref(const Ref<T_Other>& p_from) : ptr(nullptr) {
        ref_pointer(static_cast<T*>(p_from.get_ptr()));
    }
    Ref(const Variant& p_variant) : ptr(nullptr) {
        T* p_temp = std::get<T*>(p_variant);
        if (p_temp) {
            ref_pointer(p_temp);
        }
    }
    Ref(const Ref<T>& other) : ptr(other.ptr) {
        if (ptr) {
            ptr->reference();
        }
    }
    ~Ref() {
        if (ptr) {
            ptr->unreference();
        }
    }

    Ref<T>& operator=(const Ref<T>& other) {
        if (this != &other) {
            if (ptr) {
                ptr->unreference();
            }
            ptr = other.ptr;
            if (ptr) {
                ptr->reference();
            }
        }
        return *this;
    }

    T* operator->() const { return ptr; }
    T& operator*() const { return *ptr; }
    operator bool() const { return ptr != nullptr; }

    void ref(const Ref<T>& p_from) {
        if (ptr) {
            ptr->unreference();
        }
        ptr = p_from.ptr;
        if (ptr) {
            ptr->reference();
        }
    }

    void ref_pointer(T* p_ref) {
        if (ptr) {
            ptr->unreference();
        }
        ptr = p_ref;
        if (ptr) {
            ptr->reference();
        }
    }

    template <class T_Other>
    void reference_ptr(T_Other* p_ptr) {
        if (ptr) {
            ptr->unreference();
        }
        ptr = static_cast<T*>(p_ptr);
        if (ptr) {
            ptr->init_ref();
        }
    }

    void unref() {
        if (ptr) {
            ptr->unreference();
            ptr = nullptr;
        }
    }

    void instantiate() {
        if (!ptr) {
            ptr = new T();
            if (ptr) {
                ptr->init_ref();
            }
        }
    }

    const T* get_ptr() const { return ptr; }

    inline bool is_valid() const { return ptr != nullptr; }
    inline bool is_null() const { return ptr == nullptr; }

private:
    T* ptr;
};



#endif // REF_COUNTED_H