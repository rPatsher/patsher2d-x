#include "ustring.h"

#include <string.h>
#include <cstring>
#include <cstdarg>

// Constructors and Destructor
String::String() : str(nullptr) {}

String::String(const char* s) {
    if (s) {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    } else {
        str = nullptr;
    }
}

String::String(const String& other) {
    if (other.str) {
        str = new char[strlen(other.str) + 1];
        strcpy(str, other.str);
    } else {
        str = nullptr;
    }
}

String::~String() {
    delete[] str;
}

// Member functions
int String::length() const {
    return (str) ? strlen(str) : 0;
}

const char* String::c_str() const {
    return str;
}

// Search methods
int String::find(const String& sub) const {
    if (!str || !sub.str) {
        return -1;
    }

    char* found = strstr(str, sub.str);
    return (found) ? static_cast<int>(found - str) : -1;
}

int String::find(char c) const {
    if (!str) {
        return -1;
    }

    char* found = strchr(str, c);
    return (found) ? static_cast<int>(found - str) : -1;
}

// Reverse search methods
int String::rfind(const String& sub) const {
    if (!str || !sub.str) {
        return -1;
    }

    char* found = strrstr(str, sub.str);
    return (found) ? static_cast<int>(found - str) : -1;
}

int String::rfind(char c) const {
    if (!str) {
        return -1;
    }

    for (int i = length() - 1; i >= 0; --i) {
        if (str[i] == c) {
            return i;
        }
    }
    return -1;
}

int String::rfindn(const String& sub, int pos) const {
    if (!str || !sub.str || pos < 0 || pos >= length()) {
        return -1;
    }

    char* found = strrstr(str + pos, sub.str);
    return (found) ? static_cast<int>(found - str) : -1;
}

// Match methods
bool String::match(const String& sub) const {
    if (!str || !sub.str) {
        return false;
    }

    return strncmp(str, sub.str, sub.length()) == 0;
}

bool String::matchn(const String& sub, int pos) const {
    if (!str || !sub.str || pos < 0 || pos >= length()) {
        return false;
    }

    return strncmp(str + pos, sub.str, sub.length()) == 0;
}

// Check if string begins or ends with a substring
bool String::begins_with(const String& prefix) const {
    if (!str || !prefix.str) {
        return false;
    }

    int prefixLen = prefix.length();
    return (length() >= prefixLen) && (strncmp(str, prefix.str, prefixLen) == 0);
}

bool String::ends_with(const String& suffix) const {
    if (!str || !suffix،str ) {
		return false;
	}
	int suffixLen = suffix.length();
	return (length() >= suffixLen) && (strncmp(str + length() - suffixLen, suffix.str, suffixLen) == 0);
}


String String::format(const String& replacement) const { 
	String result(*this);
	
	// Replace placeholders in the result with the replacement string
	int placeholderPos = result.find("{}");
	while (placeholderPos != -1) {
    	result = result.replace("{}", replacement);
    	placeholderPos = result.find("{}");
	}

	return result;
}


String String::replace(const String& target, const String& replacement) const {
	if (!str || !target.str) {
		return *this;
		String result;
		int startPos = 0;

while (true) {
    int foundPos = find(target, startPos);

    if (foundPos == -1) {
        result = result + substr(startPos);
        break;
    }

    result = result + substr(startPos, foundPos - startPos) + replacement;
    startPos = foundPos + target.length();
}

return result;
		
	}
}

bool String::is_enclosed_in(const String& prefix, const String& suffix) const { 
	return begins_with(prefix) && ends_with(suffix);
}

// Check if the current string is a subsequence of another string
bool String::is_subsequence_of(const String& other) const {
    return is_subsequence_from_position(other, 0);
}

// Helper method to check if the current string is a subsequence of another string starting from a specific position
bool String::is_subsequence_from_position(const String& other, int startPos) const {
    if (!str || !other.str) {
        return false;
    }

    int len = length();
    int otherLen = other.length();

    // If the current string is empty, it is considered a subsequence of any string
    if (len == 0) {
        return true;
    }

    // If the other string is empty or the start position is beyond its length, it is not a subsequence
    if (otherLen == 0 || startPos >= otherLen) {
        return false;
    }

    int i = 0; // Index for the current string
    int j = startPos; // Index for the other string

    while (i < len && j < otherLen) {
        if (str[i] == other.str[j]) {
            // Match found, move to the next character in both strings
            ++i;
        }

        // Move to the next character in the other string
        ++j;
    }

    // If all characters in the current string were matched, it is a subsequence
    return (i == len);
}


// ... (existing code)

// Split the string into a vector of substrings
Vector<String> String::split(const String& p_splitter, bool p_allow_empty, int p_maxsplit) const {
    Vector<String> result;

    if (p_splitter.empty()) {
        // Split by any whitespace character
        char* token = strtok(str, " \t\n\r\f\v");
        while (token != nullptr) {
            result.push_back(String(token));
            token = strtok(nullptr, " \t\n\r\f\v");

            if (p_maxsplit > 0 && result.size() >= static_cast<size_t>(p_maxsplit)) {
                break;
            }
        }
    } else {
        // Split by the specified splitter string
        size_t splitter_len = p_splitter.length();
        int remaining_splits = p_maxsplit;

        char* token = strtok(str, p_splitter.c_str());
        while (token != nullptr) {
            result.push_back(String(token));
            token = strtok(nullptr, p_splitter.c_str());

            if (p_maxsplit > 0 && result.size() >= static_cast<size_t>(p_maxsplit)) {
                break;
            }
        }
    }

    if (!p_allow_empty) {
        result.erase(remove_if(result.begin(), result.end(), [](const String& s) { return s.empty(); }), result.end());
    }

    return result;
}

// Split the string from the right into a vector of substrings
Vector<String> String::rsplit(const String& p_splitter, bool p_allow_empty, int p_maxsplit) const {
    // Reverse the string and perform a regular split, then reverse the result
    String reversed_str = reverse();
    Vector<String> reversed_result = reversed_str.split(p_splitter.reverse(), p_allow_empty, p_maxsplit);

    Vector<String> result;
    for (const String& s : reversed_result) {
        result.push_back(s.reverse());
    }

    return result;
}

// ... (existing code)// ... (existing code)

// Split the string into a vector of substrings
Vector<String> String::split(const String& p_splitter, bool p_allow_empty, int p_maxsplit) const {
    Vector<String> result;

    if (p_splitter.empty()) {
        // Split by any whitespace character
        char* token = strtok(str, " \t\n\r\f\v");
        while (token != nullptr) {
            result.push_back(String(token));
            token = strtok(nullptr, " \t\n\r\f\v");

            if (p_maxsplit > 0 && result.size() >= static_cast<size_t>(p_maxsplit)) {
                break;
            }
        }
    } else {
        // Split by the specified splitter string
        size_t splitter_len = p_splitter.length();
        int remaining_splits = p_maxsplit;

        char* token = strtok(str, p_splitter.c_str());
        while (token != nullptr) {
            result.push_back(String(token));
            token = strtok(nullptr, p_splitter.c_str());

            if (p_maxsplit > 0 && result.size() >= static_cast<size_t>(p_maxsplit)) {
                break;
            }
        }
    }

    if (!p_allow_empty) {
        result.erase(remove_if(result.begin(), result.end(), [](const String& s) { return s.empty(); }), result.end());
    }

    return result;
}



// ... (existing code)

// Static method to convert a string of type char to int64_t
int64_t String::to_int(const char* p_str, int p_len) {
    if (!p_str) {
        return 0;
    }

    int64_t result = 0;
    if (p_len == -1) {
        p_len = static_cast<int>(strlen(p_str));
    }

    for (int i = 0; i < p_len; ++i) {
        result = result * 10 + (p_str[i] - '0');
    }

    return result;
}


// Replace the first occurrence of a specified substring
String String::replace_first(const String& target, const String& replacement) const {
    if (!str || !target.str) {
        return *this;
    }

    String result(*this);
    int foundPos = result.find(target);

    if (foundPos != -1) {
        result = result.substr(0, foundPos) + replacement + result.substr(foundPos + target.length());
    }

    return result;
}

// Replace a specified number of occurrences of a substring
String String::replace_n(const String& target, const String& replacement, int n) const {
    if (n <= 0) {
        return *this;
    }

    String result(*this);
    int startPos = 0;

    for (int i = 0; i < n; ++i) {
        int foundPos = result.find(target, startPos);

        if (foundPos == -1) {
            break;
        }

        result = result.substr(0, foundPos) + replacement + result.substr(foundPos + target.length());
        startPos = foundPos + replacement.length();
    }

    return result;
}

// Repeat the string a specified number of times
String String::repeat(int n) const {
    if (n <= 0) {
        return String();
    }

    String result;
    for (int i = 0; i < n; ++i) {
        result = result + *this;
    }

    return result;
}

// Erase a portion of the string
String String::erase(int start, int count) const {
    if (!str || start < 0 || count <= 0) {
        return *this;
    }

    int len = length();
    if (start >= len) {
        return *this;
    }

    int endPos = start + count;
    if (endPos > len) {
        endPos = len;
    }

    String result;
    result.str = new char[len - (endPos - start) + 1];

    // Copy characters before the erased portion
    strncpy(result.str, str, start);

    // Copy characters after the erased portion
    strncpy(result.str + start, str + endPos, len - endPos);

    // Null-terminate the result
    result.str[len - (endPos - start)] = '\0';

    return result;
}

// Insert a substring at a specified position
String String::insert(int pos, const String& str) const {
    if (!str || pos < 0) {
        return *this;
    }

    int len = length();
    int insertLen = str.length();
    int resultLen = len + insertLen;

    String result;
    result.str = new char[resultLen + 1];

    // Copy characters before the insertion point
    strncpy(result.str, this->str, pos);

    // Copy the inserted substring
    strncpy(result.str + pos, str.str, insertLen);

    // Copy characters after the insertion point
    strncpy(result.str + pos + insertLen, this->str + pos, len - pos);

    // Null-terminate the result
    result.str[resultLen] = '\0';

    return result;
}

// Left-pad the string with a specified character
String String::lpad(int length, char padChar) const {
    if (length <= 0) {
        return *this;
    }

    int len = length();
    if (len >= length) {
        return *this;
    }

    String result;
    result.str = new char[length + 1];

    // Fill the left-pad characters
    for (int i = 0; i < length - len; ++i) {
        result.str[i] = padChar;
    }

    // Copy the original string
    strcpy(result.str + length - len, str);

    // Null-terminate the result
    result.str[length] = '\0';

    return result;
}

// Right-pad the string with a specified character
String String::rpad(int length, char padChar) const {
    if (length <= 0) {
        return *this;
    }

    int len = length();
    if (len >= length) {
        return *this;
    }

    String result;
    result.str = new char[length + 1];

    // Copy the original string
    strcpy(result.str, str);

    // Fill the right-pad characters
    for (int i = len; i < length; ++i) {
        result.str[i] = padChar;
    }

    // Null-terminate the result
    result.str[length] = '\0';

    return result;
}





// sprintf for formatting strings
String String::sprintf(const char* format, ...) {
    const int bufferSize = 256;
    char buffer[bufferSize];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, bufferSize, format, args);
    va_end(args);

    return String(buffer);
}

// Reverse the string
String String::reverse() const {
    int len = length();
    if (len <= 1) {
        return *this;
    }

    String result(*this);
    for (int i = 0, j = len - 1; i < j; ++i, --j) {
        char temp = result.str[i];
        result.str[i] = result.str[j];
        result.str[j] = temp;
    }

    return result;
}

// Convert the string to a numeric value
double String::num() const {
    if (!str) {
        return 0.0;
    }

    return strtod(str, nullptr);
}

// Get the character at a specified position
char String::chr(int pos) const {
    if (!str || 






// Static method to convert a string of type wchar_t to int64_t
int64_t String::to_int(const wchar_t* p_str, int p_len) {
    if (!p_str) {
        return 0;
    }

    int64_t result = 0;
    if (p_len == -1) {
        p_len = static_cast<int>(wcslen(p_str));
    }

    for (int i = 0; i < p_len; ++i) {
        result = result * 10 + (p_str[i] - L'0');
    }

    return result;
}

// Static method to convert a string of type char32_t to int64_t
int64_t String::to_int(const char32_t* p_str, int p_len, bool p_clamp) {
    if (!p_str) {
        return 0;
    }

    int64_t result = 0;
    if (p_len == -1) {
        // Assuming char32_t strings are null-terminated
        while (p_str[p_len] != U'\0') {
            ++p_len;
        }
    }

    for (int i = 0; i < p_len; ++i) {
        if (p_clamp) {
            // Clamp the result to avoid overflow
            if (result > (std::numeric_limits<int64_t>::max() - (p_str[i] - U'0')) / 10) {
                return std::numeric_limits<int64_t>::max();
            }
        }

        result = result * 10 + (p_str[i] - U'0');
    }

    return result;
}

// ... (existing code)






// Split the string from the right into a vector of substrings
Vector<String> String::rsplit(const String& p_splitter, bool p_allow_empty, int p_maxsplit) const {
    // Reverse the string and perform a regular split, then reverse the result
    String reversed_str = reverse();
    Vector<String> reversed_result = reversed_str.split(p_splitter.reverse(), p_allow_empty, p_maxsplit);

    Vector<String> result;
    for (const String& s : reversed_result) {
        result.push_back(s.reverse());
    }

    return result;
}



// Split the string into a vector of substrings
Vector<String> String::split(const String& p_splitter, bool p_allow_empty, int p_maxsplit) const {
    Vector<String> result;

    if (p_splitter.empty()) {
        // Split by any whitespace character
        char* token = strtok(str, " \t\n\r\f\v");
        while (token != nullptr) {
            result.push_back(String(token));
            token = strtok(nullptr, " \t\n\r\f\v");

            if (p_maxsplit > 0 && result.size() >= static_cast<size_t>(p_maxsplit)) {
                break;
            }
        }
    } else {
        // Split by the specified splitter string
        size_t splitter_len = p_splitter.length();
        int remaining_splits = p_maxsplit;

        char* token = strtok(str, p_splitter.c_str());
        while (token != nullptr) {
            result.push_back(String(token));
            token = strtok(nullptr, p_splitter.c_str());

            if (p_maxsplit > 0 && result.size() >= static_cast<size_t>(p_maxsplit)) {
                break;
            }
        }
    }

    if (!p_allow_empty) {
        result.erase(remove_if(result.begin(), result.end(), [](const String& s) { return s.empty(); }), result.end());
    }

    return result;
}

// Split the string from the right into a vector of substrings
Vector<String> String::rsplit(const String& p_splitter, bool p_allow_empty, int p_maxsplit) const {
    // Reverse the string and perform a regular split, then reverse the result
    String reversed_str = reverse();
    Vector<String> reversed_result = reversed_str.split(p_splitter.reverse(), p_allow_empty, p_maxsplit);

    Vector<String> result;
    for (const String& s : reversed_result) {
        result.push_back(s.reverse());
    }

    return result;
}

