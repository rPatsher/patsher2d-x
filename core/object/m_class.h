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



#ifndef M_CLASS_H
#define M_CLASS_H



#include <map>
#include <string>

#include <cstdio>
#include <cstdlib>

#include "core/typedefs.h"

class MClass {

private: 
    std::map<std::string , std::string> m_map;
    std::map<std::string, std::map<std::string, std::string>> ptr_class; 
    std::map<std::string, std::map<std::string, std::vector<std::string>>> array_class; // Map of class array properties and default values
    std::map<std::string, std::vector<std::string>> p_property;
    std::map<std::string, std::map<std::string, std::vector<std::string>>> mcls_ptr; // Map of class array properties and default values
    




    static MClass* signelton;


#define MCLASS_API

#define MCLASS(m_class , m_inshit) \
private: \
    void operator=(const m_class eval) {} \
    friend class MClass; \
public: \ 
    static void get_mclass() {} \
    std::string get_static_mclass() { \
        return m_class; \
    } \
    static int get_index_value() { \
        static int* ptr; \
        return ptr; \
    } \
    static void set_data_ptr() { \ 
        const std::vector<std::string>* p_vec; \
        p_vec->push_back(m_class); \
        p_vec->push_back(m_inshit); \
    } \
    static std::vector<std::string> get_data_ptr() { \
        return p_vec; \
    } \
    m_inshit::get_class_static_ptr() \
    std::vector<std::string> get_class_static_ptr() { \
    return p_vec; \
    } \ 
    m_inshit::get_class_name() \
    std::string get_class_name(const std::string& p_str) { \
        get_class_name(m_class); \
    }\
    template <typename T> \
        T* get_extension_class() const { \
            return dynamic_cast<T*>(this); \
        } \
    int get_dictionary_index_value(const std::string& key) const { \
            auto keyIter = classDictionary[#m_class].find(key); \
            if (keyIter != classDictionary[#m_class].end()) { \
                return keyIter->second; \
            } \
            return 0; \
        } /


public:
    void add_property(const std::string& m_class, const std::string& name, const std::string& value);
    std::string get_property(const std::string& m_class, const std::string& name) const;

    std::map<std::string, std::string> get_class_properties(const std::string& m_class) const;
    

#define ADD_PROPERTY(m_type , m_name , m_method) \
    MClass::add_property(m_type , m_name , m_method) 


};





#endif // 