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
