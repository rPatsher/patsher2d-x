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

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <vector>
#include <map>

class StringUtils {
public:
    struct Data {
        int intValue;
        double doubleValue;
        std::string stringValue;
        bool boolValue;

        // Operator for comparing two Data instances
        bool operator==(const Data& other) const {
            return intValue == other.intValue &&
                   doubleValue == other.doubleValue &&
                   stringValue == other.stringValue &&
                   boolValue == other.boolValue;
        }

        // Operator for assigning one Data instance to another
        Data& operator=(const Data& other) {
            if (this != &other) {
                intValue = other.intValue;
                doubleValue = other.doubleValue;
                stringValue = other.stringValue;
                boolValue = other.boolValue;
            }
            return *this;
        }
    };

    static std::string toLowerCase(const std::string& str);
    static std::string toUpperCase(const std::string& str);
  
    static std::vector<std::string> split(const std::string& str, char delimiter);
    
    static bool startsWith(const std::string& str, const std::string& prefix);
    static bool endsWith(const std::string& str, const std::string& suffix);
    
    static std::string format(const std::string& format, ...);
    static std::string create(const std::vector<std::string>& strings, const std::string& delimiter);
    
    static std::string to_string(int value);
    static std::string to_string(double value);
    
    static std::string to_string(bool value);
    static std::map<int, double> to_p_map(const std::vector<std::pair<int, double>>& pairs);
    
    static std::string to_utils(const std::string& str1, const std::string& str2, const std::string& delimiter);
    static std::u16string utf8_to_utf16(const std::string& utf8str);
    
    static std::string utf16_to_utf8(const std::u16string& utf16str);
    static char16_t get_char_16(const std::u16string& str, size_t index);
    
    static char get_char_8(const std::string& str, size_t index);
    static char get_char_at_index(const std::string& str, size_t index);
    
    static void set_char_at_index(std::string& str, size_t index, char newChar);
    static std::string get_line(const std::string& str, size_t lineNumber, char delimiter = '\n');
    static std::string get_rline(const std::string& str, size_t lineNumber, char delimiter = '\n');
    
    static Data extractData(const std::string& str);
    
    static std::string join(const std::vector<std::string>& strings, const std::string& delimiter);
    static std::string join_path(const std::vector<std::string>& components);
    
    static bool is_valid(const std::string& str);
    
    static bool is_null(const std::string& str);
    static bool is_empty(const std::string& str);
};


class Char16 {
    public:
        static std::u16string to_utf16(const std::string& utf8str);
        static std::string to_utf8(const std::u16string& utf16str);
        static char16_t get_char(const std::u16string& str, size_t index);
        static void set_char(std::u16string& str, size_t index, char16_t newChar);


};

class Utf8 {
    public:
        static std::string to_utf8(const std::u16string& utf16str);
        static std::u16string to_utf16(const std::string& utf8str);
        static char get_char(const std::string& str, size_t index);
        static void set_char(std::string& str, size_t index, char newChar);

};


#endif // STRING_UTILS_H
