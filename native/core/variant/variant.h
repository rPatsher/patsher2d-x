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

#ifndef VARIANT_H
#define VARIANT_H



#include "core/templates/map.h"
#include "core/error/error_macros.h"
#include "core/templates/hash_map.h"


template <typename T>
class Vector<T>;



class Vector2;
class Vector3;
class Vector4;
class Color;
class Rect2;
class Size2;
class Signal;
class Quat;
class AABB;
class Object;
class Array;
class Dictionary;
class Plane;
class Transform3D;
class Transform2D;
class Quaternion;
class String;

#include <cstdint>
#include <cstdio>
#include <variant>
#include <type_traits>
#include <stdexcept>
#include <pair>


struct PropertyInfo;
struct MethodInfo;

typedef Vector<uint8_t> PackedByteArray;
typedef Vector<int32_t> PackedInt32Array;
typedef Vector<int64_t> PackedInt64Array;
typedef Vector<float> PackedFloat32Array;
typedef Vector<double> PackedFloat64Array;
typedef Vector<real_t> PackedRealArray;
typedef Vector<String> PackedStringArray;
typedef Vector<Vector2> PackedVector2Array;
typedef Vector<Vector3> PackedVector3Array;
typedef Vector<Vector4> PackedVector4Array;
typedef Vector<Color> PackedColorArray;

class Variant {
public:
    enum Type {
		NIL,

		// atomic types
		BOOL,
		INT,
		FLOAT,
		STRING,

		// math types
		VECTOR2,
		VECTOR2I,
		RECT2,
		RECT2I,
		VECTOR3,
		VECTOR3I,
		TRANSFORM2D,
		VECTOR4,
		VECTOR4I,
		PLANE,
		QUATERNION,
		AABB,
		BASIS,
		TRANSFORM3D,
		PROJECTION,

		// misc types
		COLOR,
		NODE,
		NODE_PATH,
		RID,
		OBJECT,
		CALLABLE,
		SIGNAL,
		DICTIONARY,
		ARRAY,

		// typed arrays
		PACKED_BYTE_ARRAY,
		PACKED_INT32_ARRAY,
		PACKED_INT64_ARRAY,
		PACKED_FLOAT32_ARRAY,
		PACKED_FLOAT64_ARRAY,
		PACKED_STRING_ARRAY,
		PACKED_VECTOR2_ARRAY,
		PACKED_VECTOR3_ARRAY,
		PACKED_COLOR_ARRAY,

		VARIANT_MAX
	};

    using VariantType = std::variant<
        std::monostate,
        bool,
        int,
        float,
        double,
        String,
        Vector2,
        Vector3,
        Vector4,
        Color,
        Rect2,
        Size2, 
        AABB,
        PackedStringArray,
        PackedByteArray,
        PackedColorArray,
        PackedFloat32Array,
        PackedFloat64Array,
        PackedVector2Array,
        PackedVector3Array,
        PackedVector4Array,
        PackedRealArray      
    >;
    
    Vector<Type> get_property_list() const {
        return { get_type<Types>()... };
    }
    
    template <typename T>
    void push_back(const T& element) {
        if constexpr (std::is_same_v<T, Array>) {
            std::get<Array>(variantValue).push_back(element);
        } else {
            ERR_PRINT("Push back only supported for ARRAY type\n");
        }
    }
    struct ObjData {
    	ObjectID id;
        Object *obj = nullptr;
    };
    _INLINE_ void clear() {
    	static const bool needs_deinit[Variant::VARIANT_MAX] = {
    		false, //NIL,
            false, //BOOL,
            false, //INT,
            false, //FLOAT,
            true, //STRING,
            false, //VECTOR2,
            false, //VECTOR2I,
            false, //RECT2,
            false, //RECT2I,
            false, //VECTOR3,
            false, //VECTOR3I,
            true, //TRANSFORM2D,
            false, //VECTOR4,
                        false, //VECTOR4I,
                        false, //PLANE,
                        false, //QUATERNION,
                        true, //AABB,
                        true, //BASIS,
                        true, //TRANSFORM,
                        true, //PROJECTION,

                        // misc types
                        false, //COLOR,
                        true, //STRING_NAME,
                        true, //NODE_PATH,
                        false, //RID,
                        true, //OBJECT,
                        true, //CALLABLE,
                        true, //SIGNAL,
                        true, //DICTIONARY,
                        true, //ARRAY,

                        // typed arrays
                        true, //PACKED_BYTE_ARRAY,
                        true, //PACKED_INT32_ARRAY,
                        true, //PACKED_INT64_ARRAY,
                        true, //PACKED_FLOAT32_ARRAY,
                        true, //PACKED_FLOAT64_ARRAY,
                        true, //PACKED_STRING_ARRAY,
                        true, //PACKED_VECTOR2_ARRAY,
                        true, //PACKED_VECTOR3_ARRAY,
                        true, //PACKED_COLOR_ARRAY,
            };
    }
    

    // Get the name of the stored type
    String get_type_name() const {
        return get_type_name_impl(variantValue);
    }
    
    void set_key(const String& key, const Variant& value);
    Variant get_key(const String& key) const;
    bool has_key(const String& key) const;
    void remove_key(const String& key);

    // Array manipulation methods
    void append_element(const Variant& element);
    Variant get_element(size_t index) const;
    size_t get_array_size() const;
    
    bool is_nil() const;
    bool is_bool() const;
    bool is_int() const;
    bool is_real() const;
    bool is_string() const;

    // Conversion methods
    bool to_bool() const;
    int to_int() const;
    double to_real() const;
    String to_string() const;
    
    // Helper function to map type to enum
    template <typename T>
    static constexpr Type get_type();

    // Helper function to check if the stored type matches the provided type
    template <typename T>
    bool is_type() const;

	
    template <typename T>
    T convert_to() const;
    
    Vector<String> get_builtin_method_list() const;

    size_t get_builtin_method_hash() const;
    
    String get_builtin_method_info(const String& method_name) const;

    int get_builtin_method_argument_count(const String& method_name) const;

    // Operator overloads
    Variant& operator[](const String& key);
    const Variant& operator[](const String& key) const;
    Variant& operator=(const Variant& other);
    Variant* operator->();
    const Variant* operator->() const;
    Variant& operator*();
    const Variant& operator*() const;
    
    Variant(unsigned char p_char);
    Variant(unsigned short p_short);
    
    operator bool() const;
	operator signed int() const;
	operator unsigned int() const; 
	operator signed short() const;
	operator unsigned short() const;
	operator signed char() const;
	operator unsigned char() const;
	operator int64_t() const;
	operator uint64_t() const;
	
	operator char32_t() const;
	operator float() const;
	operator double() const;
	operator String() const;
	operator Vector2() const;
	operator Vector2i() const;
	operator Rect2() const;
	operator Rect2i() const;
	operator Vector3() const;
	operator Vector3i() const;
	operator Vector4() const;
	operator Vector4i() const;
	operator Plane() const;
	operator ::AABB() const;
	operator Quaternion() const;
	operator Basis() const;
	operator Transform2D() const;
	operator Transform3D() const;
	operator Projection() const;
    

private:
    VariantType variantValue;
    mutable std::size_t currentIndex = 0;
    VariantType variantValue;
    Map<String, std::any> keyedValues; // Map to store values associated with keys
    std::unordered_map<String, std::pair<std::string, int>> methodInfoMap;
};







#endif // VARIANT_H