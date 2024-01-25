#ifndef USTRING_H
#define USTRING_H

#include <iostream>
#include <string>

#include "core/templates/vector.h"
#include "core/templates/map.h"

class String {
private:
    char* str;

public:
    // Constructors and Destructor
    String();
    String(const char* s);
    String(const String& other);
    ~String();

    // Member functions
    int length() const;
    const char* c_str() const;

    // Search methods
    int find(const String& sub) const;
    int find(char c) const;

    // Reverse search methods
    int rfind(const String& sub) const;
    int rfind(char c) const;
    int rfindn(const String& sub, int pos) const;

    // Match methods
    bool match(const String& sub) const;
    bool matchn(const String& sub, int pos) const;

    // Check if string begins or ends with a substring
    bool begins_with(const String& prefix) const;
    bool ends_with(const String& suffix) const;

    // Check if the string is enclosed between two substrings
    bool is_enclosed_in(const String& prefix, const String& suffix) const;

    // Format the string by replacing placeholders
    String format(const String& replacement) const;

    // Replace occurrences of a specified substring
    String replace(const String& target, const String& replacement) const;

    // Replace the first occurrence of a specified substring
    String replace_first(const String& target, const String& replacement) const;

    // Replace a specified number of occurrences of a substring
    String replace_n(const String& target, const String& replacement, int n) const;

    // Repeat the string a specified number of times
    String repeat(int n) const;

    // Erase a portion of the string
    String erase(int start, int count) const;

    // Insert a substring at a specified position
    String insert(int pos, const String& str) const;

    // Left-pad the string with a specified character
    String lpad(int length, char padChar) const;

    // Right-pad the string with a specified character
    String rpad(int length, char padChar) const;

    // sprintf for formatting strings
    static String sprintf(const char* format, ...);

    // Reverse the string
    String reverse() const;

    // Convert the string to a numeric value
    double num() const;

    // Get the character at a specified position
    char chr(int pos) const;

    // Overloaded operators
    String& operator=(const String& other);
    String operator+(const String& other) const;
    bool operator==(const String& other) const;
    char& operator[](int index);
    const char& operator[](int index) const;
    


public:

    // Static method to convert a string of type char to int64_t
    static int64_t to_int(const char* p_str, int p_len = -1);

    // Static method to convert a string of type wchar_t to int64_t
    static int64_t to_int(const wchar_t* p_str, int p_len = -1);

    // Static method to convert a string of type char32_t to int64_t
    static int64_t to_int(const char32_t* p_str, int p_len = -1, bool p_clamp = false);


public:

    // Static method to convert a string of type char to double
    static double to_float(const char* p_str);

    // Static method to convert a string of type wchar_t to double
    static double to_float(const wchar_t* p_str, const wchar_t** r_end = nullptr);

    // Static method to convert a string of type char32_t to double
    static double to_float(const char32_t* p_str, const char32_t** r_end = nullptr);
    
    
    // Check if the current string is a subsequence of another string
    bool is_subsequence_of(const String& other) const;

private:
    // Helper method to check if the current string is a subsequence of another string starting from a specific position
    bool is_subsequence_from_position(const String& other, int startPos) const;
    
    // Split the string into a vector of substrings
    Vector<String> split(const String& p_splitter = "", bool p_allow_empty = true, int p_maxsplit = 0) const;

    // Split the string from the right into a vector of substrings
    Vector<String> rsplit(const String& p_splitter = "", bool p_allow_empty = true, int p_maxsplit = 0) const;

    // Macros for stringifying identifiers
    #define SNAME(identifier) #identifier
    #define STR(identifier) SNAME(identifier)

    // Friend function to overload the << operator for output
    friend std::ostream& operator<<(std::ostream& os, const String& s);
};

#endif // STRING_H
