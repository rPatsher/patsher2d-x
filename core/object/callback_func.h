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

#ifndef CALLBACK_FUNC_H
#define CALLBACK_FUNC_H

#include <functional>
#include <string>
#include <utility>

#include "core/object/m_class.h"
#include "core/templates/vector.h"


template <typename T>
class CallbackFunc {
public:
    // Define the struct DataBack
    struct DataBack {
        T* obj;
        bool flags;
        int size;
        void* m_meta;
        Vector<DataBack>* data;

        DataBack(T* o, bool f) : obj(o), flags(f) {}
        DataBack() {}
        ~DataBack() {}
    };

    explicit CallbackFunc();
    explicit CallbackFunc(std::function<void(T*, DataBack)> callback, T* obj);

    void executeCallback(DataBack data);
    void emit(DataBack data);

    // Overloaded init functions
    void init();
    void init(std::function<void(T*, DataBack)> callback, T* obj);

    // New function to emit a callback with a given name, member function, and object
    static void emit_call(const std::string& name, std::function<void(T*, DataBack)>& func, T* obj, DataBack data);

    // New function to get the stored callback function and object
    std::pair<std::function<void(T*, DataBack)>, T*> get_call() const;

    // New functions to check the state
    bool is_callback_enabled() const;
    bool is_called() const;
    bool is_init() const;
    bool is_enabled() const;

    // New function to get the object associated with the callback
    T* get_obj_call_back() const;

    // New function to get the memory address of the stored callback function
    std::size_t get_callback_memory() const;

    // New functions to create instances
    static CallbackFunc<T> create(const std::string& name, std::function<void(T*, DataBack)>& func, T* obj);
    static CallbackFunc<T> create();

private:
    std::function<void(T*, DataBack)> callbackFunction;
    T* object;
    bool initialized;
    bool enabled;
    bool callbackEnabled;
};

#define CALLBACK_FUNC

#endif // CALLBACK_FUNC_H
