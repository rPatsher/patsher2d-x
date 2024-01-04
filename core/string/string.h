#ifndef STRING_H
#define STRING_H

#include <iostream>

class String {
private:
    char* m_data;
    size_t m_length;

public:
    String();
    String(const char* data);
    String(const String& other);
    ~String();

    String& operator=(const String& other);
    friend std::ostream& operator<<(std::ostream& stream, const String& string);

    const char* getData() const;
    size_t getLength() const;
    void copy_from(const wchar_t* p_cstr);
    void copy_from(const wchar_t* p_cstr, const int p_clip_to); // Overloaded copy_from
    bool _base_is_subsequence_of(const String& p_string, bool case_insensitive) const;
    int _count(const String& p_string, int p_from, int p_to, bool p_case_insensitive) const;

    bool operator==(const String& p_str) const;
    bool operator!=(const String& p_str) const;

    String operator+(const String& p_str) const;
    String operator+(char32_t p_char) const;

    signed char naturalcasecmp_to(const String& p_str) const;
    signed char naturalnocasecmp_to(const String& p_str) const;

    signed char casecmp_to(const String& p_str) const;
    signed char nocasecmp_to(const String& p_str) const;

    bool is_valid_string() const;

    String substr(int p_from, int p_chars = -1) const; // Declaration of substr
    int find(const String& p_str, int p_from = 0) const; // Declaration of find

   









};

#endif
