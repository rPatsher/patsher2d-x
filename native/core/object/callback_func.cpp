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

#include "callback_func.h"
#include <iostream>

template <typename T>
CallbackFunc<T>::CallbackFunc()
    : callbackFunction(nullptr), object(nullptr), initialized(false), callbackEnabled(true) {}

template <typename T>
CallbackFunc<T>::CallbackFunc(std::function<void(T*, DataBack)> callback, T* obj)
    : callbackFunction(callback), object(obj), initialized(true), callbackEnabled(true) {}

template <typename T>
void CallbackFunc<T>::executeCallback(DataBack data) {
    if (initialized && callbackEnabled && callbackFunction) {
        callbackFunction(object, data);
    }
}

template <typename T>
void CallbackFunc<T>::emit(DataBack data) {
    executeCallback(data);
}

template <typename T>
void CallbackFunc<T>::init() {
    callbackFunction = nullptr;
    object = nullptr;
    initialized = true;
    callbackEnabled = true;
}

template <typename T>
void CallbackFunc<T>::init(std::function<void(T*, DataBack)> callback, T* obj) {
    callbackFunction = callback;
    object = obj;
    initialized = true;
    callbackEnabled = true;
}

template <typename T>
void CallbackFunc<T>::emit_call(const std::string& name, std::function<void(T*, DataBack)>& func, T* obj, DataBack data) {
    func(obj, data);
}

template <typename T>
std::pair<std::function<void(T*, DataBack)>, T*> CallbackFunc<T>::get_call() const {
    return std::make_pair(callbackFunction, object);
}

template <typename T>
bool CallbackFunc<T>::is_callback_enabled() const {
    return callbackEnabled;
}
template <typename T>
bool CallbackFunc<T>::is_enabled() const {
	return enabled;

template <typename T>
bool CallbackFunc<T>::is_called() const {
    return initialized && callbackEnabled && callbackFunction;
}

template <typename T>
bool CallbackFunc<T>::is_init() const {
    return initialized;
}

template <typename T>
T* CallbackFunc<T>::get_obj_call_back() const {
    return object;
}

template <typename T>
std::size_t CallbackFunc<T>::get_callback_memory() const {
    return typeid(callbackFunction.target_type()).hash_code();
}

template <typename T>
CallbackFunc<T> CallbackFunc<T>::create(const std::string& name, std::function<void(T*, DataBack)>& func, T* obj) {
    CallbackFunc<T> callbackInstance;
    callbackInstance.init(func, obj);
    return callbackInstance;
}

template <typename T>
CallbackFunc<T> CallbackFunc<T>::create() {
    CallbackFunc<T> callbackInstance;
    return callbackInstance;
}
