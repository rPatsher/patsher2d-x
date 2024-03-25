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
    bool begins_with(const String& prefix) const;
    bool ends_with(const String& suffix) const;
    bool is_enclosed_in(const String& prefix, const String& suffix) const;
    String format(const String& replacement) const;
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

    void c_str();

    int substr(int pos , int p_pos) const;

    // Convert the string to a numeric value
    double num() const;

    // Get the character at a specified position
    char chr(int pos) const;
    
    similarity(const String &p_string) const;
	String format(const Variant &values, const String &placeholder = "{_}") const;
	String replace_first(const String &p_key, const String &p_with) const;
	String replace(const String &p_key, const String &p_with) const;
	String replace(const char *p_key, const char *p_with) const;
	String replacen(const String &p_key, const String &p_with) const;
	String repeat(int p_count) const;
	String reverse() const;
	String insert(int p_at_pos, const String &p_string) const;
	String erase(int p_pos, int p_chars = 1) const;
	String pad_decimals(int p_digits) const;
	String pad_zeros(int p_digits) const;
	String trim_prefix(const String &p_prefix) const;
	String trim_suffix(const String &p_suffix) const;
	String lpad(int min_length, const String &character = " ") const;
	String rpad(int min_length, const String &character = " ") const;
	String sprintf(const Array &values, bool *error) const;
	String quote(const String &quotechar = "\"") const;
	String unquote() const;
	static String num(double p_num, int p_decimals = -1);
	static String num_scientific(double p_num);
	static String num_real(double p_num, bool p_trailing = true);
	static String num_int64(int64_t p_num, int base = 10, bool capitalize_hex = false);
	static String num_uint64(uint64_t p_num, int base = 10, bool capitalize_hex = false);
	static String chr(char32_t p_char);
	static String md5(const uint8_t *p_md5);
	static String hex_encode_buffer(const uint8_t *p_buffer, int p_len);
	Vector<uint8_t> hex_decode() const;

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
    Vector<String> split(const String& p_splitter = "", bool p_allow_empty = true, int p_maxsplit = 0) const;
    Vector<String> rsplit(const String& p_splitter = "", bool p_allow_empty = true, int p_maxsplit = 0) const;

    // Macros for stringifying identifiers
    #define SNAME(identifier) #identifier
    #define STR(identifier) SNAME(identifier)

    // Friend function to overload the << operator for output
    friend std::ostream& operator<<(std::ostream& os, const String& s);

    enum {
    	npos = -1
    };
};

#endif // STRING_H
