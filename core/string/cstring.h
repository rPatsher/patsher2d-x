// CString.h
#ifndef CSTRING_H
#define CSTRING_H



#include <cstdio>
#include <cstdlib>


#include <string>


class CString {
private:
    char *str;

public:
    // Constructors and destructor
    CString();
    CString(const char *s);
    CString(const CString &other);
    ~CString();
public:
    void create(const char *s);
    void free();

    void strcpy(const char *s);
    int strcmp(const CString &other) const;
    void strcat(const char *s);
    int strlen() const;

    void strncat(const char *s, int num);
    int strncmp(const CString &other, int num) const;
    void strncpy(const char *s, int num);
    void toupper();
    void tolower();

    std::vector<CString> split(const char delimiter) const;
    std::vector<CString> rsplit(const char delimiter) const;

    int rfind(const char *substr) const;
    int find(const char *substr) const;

    int cast_to_int() const;
    std::string to_string() const;

    void lpad(int totalWidth, char padChar);
    void rpad(int totalWidth, char padChar);


    int count(const char *substr) const;
    int countn(const char *substr, int n) const;


    int rfindn(const char *substr, int n) const;
    int findn(const char *substr, int n) const;

    int matchn(const char *pattern, int n) const;
    int rmatchn(const char *pattern, int n) const;

    bool begins_with(const char *prefix) const;
    bool ends_with(const char *suffix) const;

    void replace(const char *oldStr, const char *newStr);
    void replacen(const char *oldStr, const char *newStr, int n);

    CString left(int n) const;
    CString right(int n) const;
    
    std::wstring utf16() const;
    std::string utf8() const;
    
    size_t hash() const;
    size_t hash64() const;

    // Member functions
    int length() const;
    const char* c_str() const;

    void append(const char *s);
    void assign(const char *s);
    CString& operator=(const CString &other);
};

#endif // CSTRING_H
