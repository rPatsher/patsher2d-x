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
#include "string_utils.h"


#include <algorithm>
#include <cstdarg>
#include <sstream>
#include <codecvt>


std::string StringUtils::to_lower_case(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string StringUtils::to_upper_case(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::vector<std::string> StringUtils::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

bool StringUtils::starts_with(const std::string& str, const std::string& prefix) {
    return str.find(prefix) == 0;
}

bool StringUtils::ends_with(const std::string& str, const std::string& suffix) {
    return str.rfind(suffix) == (str.length() - suffix.length());
}

std::string StringUtils::format(const std::string& format, ...) {
    va_list args;
    va_start(args, format);

    // Determine the size of the formatted string
    size_t size = std::vsnprintf(nullptr, 0, format.c_str(), args) + 1;

    // Allocate a buffer to hold the formatted string
    std::string result(size, '\0');

    // Format the string and store it in the buffer
    std::vsnprintf(&result[0], size, format.c_str(), args);

    va_end(args);

    return result;
}

std::string StringUtils::create(const std::vector<std::string>& strings, const std::string& delimiter) {
    std::string result;
    for (const auto& str : strings) {
        result += str + delimiter;
    }
    // Remove the trailing delimiter if any
    if (!result.empty()) {
        result.pop_back();
    }
    return result;
}

std::string StringUtils::to_string(int value) {
    return std::to_string(value);
}

std::string StringUtils::to_string(double value) {
    return std::to_string(value);
}

std::string StringUtils::to_string(bool value) {
    return value ? "true" : "false";
}

std::map<int, double> StringUtils::to_p_map(const std::vector<std::pair<int, double>>& pairs) {
    std::map<int, double> result;
    for (const auto& pair : pairs) {
        result[pair.first] = pair.second;
    }
    return result;
}

std::string StringUtils::to_utils(const std::string& str1, const std::string& str2, const std::string& delimiter) {
    return str1 + delimiter + str2;
}

std::u16string StringUtils::utf8_to_utf16(const std::string& utf8str) {
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
    return convert.from_bytes(utf8str);
}

std::string StringUtils::utf16_to_utf8(const std::u16string& utf16str) {
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
    return convert.to_bytes(utf16str);
}

char16_t StringUtils::get_char_16(const std::u16string& str, size_t index) {
    if (index < str.length()) {
        return str[index];
    }
    return u'\0'; // Return null character if index is out of bounds
}

char StringUtils::get_char_8(const std::string& str, size_t index) {
    if (index < str.length()) {
        return str[index];
    }
    return '\0'; // Return null character if index is out of bounds


}

char StringUtils::get_char_at_index(const std::string& str, size_t index) {
    if (index < str.length()) {
        return str[index];
    }
    return '\0'; // Return null character if index is out of bounds
}

void StringUtils::set_char_at_index(std::string& str, size_t index, char newChar) {
    if (index < str.length()) {
        str[index] = newChar;
    }
    // Do nothing if index is out of bounds
}


std::string StringUtils::get_line(const std::string& str, size_t lineNumber, char delimiter) {
    std::vector<std::string> lines = split(str, delimiter);
    if (lineNumber < lines.size()) {
    }
}


