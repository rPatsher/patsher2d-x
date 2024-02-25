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

#include <variant>
#include <type_traits>
#include <map>
#include <string>
#include <stdexcept>
#include <vector>

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
class RID;


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

    // Helper function to convert to a specific type
    template <typename T>
    T convert_to() const;

    // Operator overloads
    Variant& operator[](const String& key);
    const Variant& operator[](const String& key) const;
    Variant& operator=(const Variant& other);
    Variant* operator->();
    const Variant* operator->() const;
    Variant& operator*();
    const Variant& operator*() const;

private:
    VariantType variantValue;
    mutable std::size_t currentIndex = 0;
    VariantType variantValue;
    std::map<String, std::any> keyedValues; // Map to store values associated with keys
};






#endif // VARIANT_H