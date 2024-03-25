*
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
#include "variant.h"



#include "core/string/ustring.h"
#include "core/variant/array.h"
#include "core/variant/dictionary.h"
#include "core/object/m_object.h"
#include "core/math/vector2.h"
#include "core/math/vector3.h"
#include "core/math/color.h"
#include "core/math/rect2.h"
#include "core/math/rect2i.h"


#include "core/templates/vector.h"
#include "core/templates/hash_map.h"
#include "core/templates/hash_set.h"

Variant& Variant::operator[](const std::string& key) {
    auto& dictionary = std::get<Map<String, Variant>>(variantValue);
    return dictionary[key];
}

const Variant& Variant::operator[](const String& key) const {
    const auto& dictionary = std::get<Map<String, Variant>>(variantValue);
    auto it = dictionary.find(key);
    if (it != dictionary.end()) {
        return it->value;
    } else {
        throw ERR_PRINT("key not found in dictionary\n");
    }
}

Variant& Variant::operator=(const Variant& other) {
    variantValue = other.variantValue;
    return *this;
}

Variant* Variant::operator->() {
    return std::get<Variant*>(variantValue);
}

const Variant* Variant::operator->() const {
    return std::get<Variant*>(variantValue);
}

Variant& Variant::operator*() {
    return *std::get<Variant*>(variantValue);
}

const Variant& Variant::operator*() const {
    return *std::get<Variant*>(variantValue);
}


String Variant::get_builtin_method_info(const std::string& method_name) const {
    auto it = methodInfoMap.find(method_name);
    if (it != methodInfoMap.end()) {
        return it->second.first;
    } else {
        ERR_PRINT("Information not available for", method_name);
    }
}

int Variant::get_builtin_method_argument_count(const String& method_name) const {
    auto it = methodInfoMap.find(method_name);
    if (it != methodInfoMap.end()) {
        return it->second.second;
    } else {
        return -1;
    }
}


Vector<String> Variant::get_builtin_method_list() const {
    Vector<String> methodList;
    for (const auto& entry : methodInfoMap) {
        methodList.push_back(entry.first);
    }
    return methodList;
}

std::size_t Variant::get_builtin_method_hash() const {
    std::size_t hash = 0;
    for (const auto& entry : methodInfoMap) {
        hash ^= std::hash<String>{}(entry.first);
    }
    return hash;
}




Variant::Variant(unsigned char p_char) : variantValue(static_cast<int>(p_char)) {}

Variant::Variant(unsigned short p_short) : variantValue(static_cast<int>(p_short)) {}




Variant::operator unsigned long() const {
    return static_cast<unsigned long>(std::get<int>(variantValue));
}

Variant::operator signed long() const {
    return static_cast<signed long>(std::get<int>(variantValue));
}

Variant::operator signed int() const {
    return std::get<int>(variantValue);
}

Variant::operator uint64_t() const {
    return static_cast<uint64_t>(std::get<int>(variantValue));
}




Variant::operator int64_t() const {
    return static_cast<int64_t>(std::get<int>(variantValue));
}

Variant::operator String() const {
    return String(std::get<int>(variantValue));
}


operator unsigned short() const {
    return static_cast<unsigned short>(std::get<int>(variantValue));
}

Variant::operator signed short() const {
    return static_cast<signed short>(std::get<int>(variantValue));
}

