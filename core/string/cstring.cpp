
#include "cstring.h"
#include <cstring>


#include <cstdio>
#include <cstdlib>
#include <strings.h>
#include <regex>
#include <algorithm>
#include <sstream>

#include <map>
#include <call/json.h>
// Constructor
CString::CString() {
    str = new char[1];
    str[0] = '\0';
}

// Constructor with char pointer
CString::CString(const char *s) {
    int len = strlen(s);
    str = new char[len + 1];
    strcpy(str, s);
}

// Copy constructor
CString::CString(const CString &other) {
    int len = other.length();
    str = new char[len + 1];
    strcpy(str, other.str);
}

// Destructor
CString::~CString() {
    delete[] str;
}

// Member function: length
int CString::length() const {
    return strlen(str);
}

// Member function: c_str
const char* CString::c_str() const {
    return str;
}

// Member function: append
void CString::append(const char *s) {
    int len1 = strlen(str);
    int len2 = strlen(s);
    char *temp = new char[len1 + len2 + 1];
    strcpy(temp, str);
    strcat(temp, s);
    delete[] str;
    str = temp;
}

// Member function: assign
void CString::assign(const char *s) {
    delete[] str;
    int len = strlen(s);
    str = new char[len + 1];
    strcpy(str, s);
}

// Assignment operator overload
CString& CString::operator=(const CString &other) {
    if (this != &other) {
        delete[] str;
        int len = other.length();
        str = new char[len + 1];
        strcpy(str, other.str);
    }
    return *this;
}


void CString::create(const char *s) {
    delete[] str;
    int len = strlen(s);
    str = new char[len + 1];
    strcpy(str, s);
}


void CString::free() {
    delete[] str;
    // Set str to nullptr or allocate a new empty string as needed after deletion
    str = nullptr; // or str = new char[1]; str[0] = '\0';
}



void CString::strncat(const char *s, int num) {
    int len1 = strlen(str);
    int len2 = strlen(s);
    int copyLength = (len2 < num) ? len2 : num;
    char *temp = new char[len1 + copyLength + 1];
    strcpy(temp, str);
    strncat(temp, s, num);
    delete[] str;
    str = temp;
}

int CString::strncmp(const CString &other, int num) const {
    return strncmp(str, other.str, num);
}

void CString::strncpy(const char *s, int num) {
    delete[] str;
    str = new char[num + 1];
    strncpy(str, s, num);
    str[num] = '\0';
}

void CString::toupper() {
    int len = strlen(str);
    for (int i = 0; i < len; ++i) {
        str[i] = std::toupper(str[i]);
    }
}

void CString::tolower() {
    int len = strlen(str);
    for (int i = 0; i < len; ++i) {
        str[i] = std::tolower(str[i]);
    }
}


std::vector<CString> CString::split(const char delimiter) const {
    std::vector<CString> substrings;
    std::string temp(str);
    std::string delimiterStr(1, delimiter);
    size_t pos = 0;
    std::string token;
    while ((pos = temp.find(delimiterStr)) != std::string::npos) {
        token = temp.substr(0, pos);
        substrings.push_back(CString(token.c_str()));
        temp.erase(0, pos + 1);
    }
    substrings.push_back(CString(temp.c_str()));
    return substrings;
}

std::vector<CString> CString::rsplit(const char delimiter) const {
    std::vector<CString> substrings;
    std::string temp(str);
    std::string delimiterStr(1, delimiter);
    size_t pos = 0;
    std::string token;
    while ((pos = temp.rfind(delimiterStr)) != std::string::npos) {
        token = temp.substr(pos + 1);
        substrings.insert(substrings.begin(), CString(token.c_str()));
        temp.erase(pos);
    }
    substrings.insert(substrings.begin(), CString(temp.c_str()));
    return substrings;
}


int CString::rfind(const char *substr) const {
    std::string temp(str);
    std::string sub(substr);
    size_t found = temp.rfind(sub);
    return (found != std::string::npos) ? static_cast<int>(found) : -1;
}

int CString::find(const char *substr) const {
    std::string temp(str);
    std::string sub(substr);
    size_t found = temp.find(sub);
    return (found != std::string::npos) ? static_cast<int>(found) : -1;
}

int CString::cast_to_int() const {
    std::stringstream ss(str);
    int result;
    ss >> result;
    return result;
}

std::string CString::to_string() const {
    return std::string(str);
}


int CString::rfindn(const char *substr, int n) const {
    std::string temp(str);
    std::string sub(substr);
    int found = -1;
    for (int i = 0; i < n; ++i) {
        found = temp.rfind(sub, found - 1);
        if (found == std::string::npos) {
            return -1;
        }
    }
    return static_cast<int>(found);
}

int CString::findn(const char *substr, int n) const {
    std::string temp(str);
    std::string sub(substr);
    int found = -1;
    for (int i = 0; i < n; ++i) {
        found = temp.find(sub, found + 1);
        if (found == std::string::npos) {
            return -1;
        }
    }
    return static_cast<int>(found);
}



int CString::matchn(const char *pattern, int n) const {
    std::regex regexPattern(pattern);
    std::string temp(str);
    std::smatch matches;

    int count = 0;
    while (std::regex_search(temp, matches, regexPattern)) {
        if (++count == n) {
            return static_cast<int>(matches.position());
        }
        temp = matches.suffix();
    }

    return -1;
}

int CString::rmatchn(const char *pattern, int n) const {
    std::regex regexPattern(pattern);
    std::string temp(str);
    std::smatch matches;

    int count = 0;
    std::string::const_reverse_iterator rit = temp.rbegin();
    while (std::regex_search(temp.begin(), temp.begin() + std::distance(temp.rbegin(), rit.base()), matches, regexPattern)) {
        if (++count == n) {
            return static_cast<int>(temp.size() - (matches.position() + matches.length()));
        }
        ++rit;
    }

    return -1;
}



bool CString::begins_with(const char *prefix) const {
    size_t prefixLen = strlen(prefix);
    size_t strLen = strlen(str);
    
    if (prefixLen > strLen) {
        return false;
    }

    return strncmp(str, prefix, prefixLen) == 0;
}

bool CString::ends_with(const char *suffix) const {
    size_t suffixLen = strlen(suffix);
    size_t strLen = strlen(str);
    
    if (suffixLen > strLen) {
        return false;
    }

    return strncmp(str + strLen - suffixLen, suffix, suffixLen) == 0;
}

void CString::replace(const char *oldStr, const char *newStr) {
    std::string temp(str);
    size_t pos = temp.find(oldStr);
    while (pos != std::string::npos) {
        temp.replace(pos, strlen(oldStr), newStr);
        pos = temp.find(oldStr, pos + strlen(newStr));
    }
    delete[] str;
    str = new char[temp.length() + 1];
    strcpy(str, temp.c_str());
}

void CString::replacen(const char *oldStr, const char *newStr, int n) {
    std::string temp(str);
    size_t pos = temp.find(oldStr);
    int count = 0;
    while (pos != std::string::npos && count < n) {
        temp.replace(pos, strlen(oldStr), newStr);
        pos = temp.find(oldStr, pos + strlen(newStr));
        ++count;
    }
    delete[] str;
    str = new char[temp.length() + 1];
    strcpy(str, temp.c_str());
}



void CString::lpad(int totalWidth, char padChar) {
    int currentLen = strlen(str);
    if (currentLen >= totalWidth) {
        return;  // No need to pad if the string is already equal to or longer than the specified width
    }

    int padLen = totalWidth - currentLen;
    char* paddedStr = new char[totalWidth + 1];

    std::fill(paddedStr, paddedStr + padLen, padChar);
    strcpy(paddedStr + padLen, str);

    delete[] str;
    str = paddedStr;
}

void CString::rpad(int totalWidth, char padChar) {
    int currentLen = strlen(str);
    if (currentLen >= totalWidth) {
        return;  // No need to pad if the string is already equal to or longer than the specified width
    }

    int padLen = totalWidth - currentLen;
    char* paddedStr = new char[totalWidth + 1];

    strcpy(paddedStr, str);
    std::fill(paddedStr + currentLen, paddedStr + totalWidth, padChar);

    delete[] str;
    str = paddedStr;
}

int CString::count(const char *substr) const {
    int count = 0;
    size_t substrLen = strlen(substr);
    const char *ptr = str;
    while ((ptr = strstr(ptr, substr)) != nullptr) {
        ++count;
        ptr += substrLen;
    }
    return count;
}

int CString::countn(const char *substr, int n) const {
    int count = 0;
    size_t substrLen = strlen(substr);
    const char *ptr = str;
    while ((ptr = strstr(ptr, substr)) != nullptr && count < n) {
        ++count;
        ptr += substrLen;
    }
    return count;
}


CString CString::left(int n) const {
    if (n >= 0 && n <= strlen(str)) {
        char *result = new char[n + 1];
        strncpy(result, str, n);
        result[n] = '\0';
        return CString(result);
    } else {
        return *this; // Return the original string if n is out of range
    }
}

CString CString::right(int n) const {
    int length = strlen(str);
    if (n >= 0 && n <= length) {
        char *result = new char[n + 1];
        strncpy(result, str + length - n, n);
        result[n] = '\0';
        return CString(result);
    } else {
        return *this; // Return the original string if n is out of range
    }
}


std::wstring CString::utf16() const {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}

std::string CString::utf8() const {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(std::wstring(str, str + strlen(str)));
}


size_t CString::hash() const {
    std::hash<const char*> hashFunc;
    return hashFunc(str);
}

size_t CString::hash64() const {
    std::hash<std::string> hashFunc;
    return hashFunc(str);
}
