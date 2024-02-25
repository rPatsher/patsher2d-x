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
#ifndef SCRIPT_H
#define SCRIPT_H


#include "core/object/ref_counted.h"
#include "core/object/m_class.h"
#include "core/string/ustring.h"
#include "core/variant/dictionary.h"
#include "core/templates/hash_set.h"
#include "core/templates/map.h"
#include "core/templates/typed_array.h"


#include <cstring>
#include <array>
#include <cassert>



class Script : public RefCounted {
	CLASS(Script, RefCounted);

public:
    static void can_init();
    static void get_base_script(); 
    static String get_global_names();
    static void set_source_code(const String& p_code);
    String get_source_code() const;
    static void set_script_name(const String& name);
    String get_script_name() const;


protected:
	void _bind_methods();


private:
    Ref<Script> script;
    bool can_init;
    String code;
    String name;
    Dictionary p_type;
    
    
    
public:
	Script();
    ~Script();
};




#endif 