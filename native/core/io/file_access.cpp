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
#include "file_access.h"


#include <iostream> // Include for simplicity, replace with proper implementation for compressed/encrypted files
#include <sstream>
#include <iterator>
#include <chrono>


#include "core/error/error_list.h"
#include "core/variant/variant.h"



FileAccess::FileAccess() {}

FileAccess::~FileAccess() {
    if (file.is_open()) {
        file.close();
    }
}


bool FileAccess::open(const String& path, ModeFlags mode) {
    std::ios_base::openmode fileMode = std::ios::out | std::ios::in;

    switch (mode) {
        case READ:
            fileMode |= std::ios::in;
            break;
        case WRITE:
            fileMode |= std::ios::out;
            break;
        case APPEND:
            fileMode |= std::ios::app;
            break;
        case READ_WRITE:
            fileMode |= std::ios::in | std::ios::out;
            break;
        case WRITE_READ:
            fileMode |= std::ios::out | std::ios::in;
            break;
    }

    filename = path;
    file.open(filename, fileMode);

    if (!file.is_open()) {
        ERR_PRINT("Error opening file\n" ,filename);
        return false;
    }
    mode = mode; 

    return true;


}


bool FileAccess::is_open() const {
    return file.is_open();

}


bool FileAccess::file_exists(const String& path) const {
    return std::filesystem::exists(path);

}

bool FileAccess::write(const String& data) const {
    if (file.is_open()) {
        file << data;
        return true;
    }

    ERR_PRINT("Error writing to file\n",filename);
    return false;
}

bool FileAccess::store_float(float value) {
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(&value), sizeof(float));
        return true;
    }

    ERR_PRINT("Error storing float to file: ", filename);
    return false;
}

bool FileAccess::store_pascal_string(const String& pascalString) {
    if (file.is_open()) {
        size_t length = pascalString.length();
        file.write(reinterpret_cast<const char*>(&length), sizeof(size_t));
        file << pascalString;
        return true;
    }

    lastError = "Error storing Pascal string to file: " + filename;
    return false;
}

bool FileAccess::store_buffer(const char* buffer, size_t size) {
    if (file.is_open()) {
        file.write(buffer, size);
        return true;
    }

    lastError = "Error storing buffer to file: " + filename;
    return false;
}

bool FileAccess::store_var(const void* variable, size_t size) {
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(variable), size);
        return true;
    }

    lastError = "Error storing variable to file: " + filename;
    return false;
}

bool FileAccess::write_16_To_file(uint16_t value) {
    if (file.is_open()) {
        // Add logic to write a 16-bit integer to the file
        file.write(reinterpret_cast<const char*>(&value), sizeof(uint16_t));
        return true;
    }

    lastError = "Error writing 16-bit integer to file: " + filename;
    return false;
}

bool FileAccess::read(String& data) {
    if (file.is_open()) {
        file.seekg(0, std::ios::beg);

        char ch;
        while (file.get(ch)) {
            data += ch;
        }

        return true;
    }

    lastError = "Error reading from file: " + filename;
    return false;
}

bool FileAccess::get_line_from_file(String& line) {
    if (file.is_open()) {
        std::getline(file, line);
        return true;
    }
    lastError = "Error getting line from file: " + filename;
    return false;
}

bool FileAccess::store_string(const String& data) {
    if (file.is_open()) {
        file << data << std::endl;
        return true;
    }
    ERR_PRINT("Error storing string to file", filename);
    return false;
}

bool FileAccess::get_var_from_file(void* variable, size_t size) {
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(variable), size);
        return true;
    }
    ERR_PRINT("Error getting variable from file ", filename);
    return false;
}

uint16_t FileAccess::get16() {
    uint16_t value = 0;

    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&value), sizeof(uint16_t));
    } else {
        lastError = "Error getting 16-bit integer from file: " + filename;
    }

    return value;
}

String FileAccess::get_file_path() const {
    return filename;
}

String FileAccess::get_open_error() const {
    return lastError;
}

void FileAccess::close() {
    if (file.is_open()) {
        file.close();
    }
}

void FileAccess::flush() {
    if (file.is_open()) {
        file.flush();
    }
}

bool FileAccess::get8(uint8_t& value) {
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&value), sizeof(uint8_t));
        return true;
    }

    lastError = "Error getting 8-bit integer from file: " + filename;
    return false;
}

Vector<uint8_t> FileAccess::get_file_as_bytes() const {
    Vector<uint8_t> bytes;

    if (file.is_open()) {
        file.seekg(0, std::ios::end);
        std::streamsize fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        bytes.resize(static_cast<size_t>(fileSize));

        if (file.read(reinterpret_cast<char*>(bytes.data()), fileSize))
            return bytes;
    }

    lastError = "Error getting file as bytes: " + filename;
    return bytes;  // Return an empty vector if there was an error
}

String FileAccess::get_error() const {
    return lastError;
}

Vector<String> FileAccess::get_csv_Line(char delimiter) {
    Vector<String> fields;
    String line;

    if (file.is_open() && std::getline(file, line)) {
        std::istringstream stream(line);
        String field;

        while (std::getline(stream, field, delimiter)) {
            fields.push_back(field);
        }
    }

    return fields;
}

uint16_t FileAccess::get16() {
    uint16_t value = 0;

    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&value), sizeof(uint16_t));
    } else {
        ERR_PRINT("Error getting 16-bit integer from file\n" , filename);
    }

    return value;
}

String FileAccess::get_as_text() {
    String content;

    if (file.is_open()) {
        file.seekg(0, std::ios::end);
        std::streamsize fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        content.resize(static_cast<size_t>(fileSize));
        
        if (file.read(&content[0], fileSize))
            return content;
    }

    ERR_PRINT("Error getting file content as text\n" , filename);
    return content;  // Return an empty string if there was an error
}



std::chrono::system_clock::time_point FileAccess::get_modified_time() const {
  std::chrono::system_clock::time_point timePoint;

    if (file.is_open()) {
#ifdef _WIN32
        // Windows-specific code to get file modification time
        FILETIME ftCreate, ftAccess, ftWrite;
        GetFileTime(file.native_handle(), &ftCreate, &ftAccess, &ftWrite);
        ULARGE_INTEGER ull;
        ull.LowPart = ftWrite.dwLowDateTime;
        ull.HighPart = ftWrite.dwHighDateTime;
        timePoint = std::chrono::system_clock::from_time_t(ull.QuadPart / 10000000ULL - 11644473600ULL);
#else
        // Unix-like system code to get file modification time
        struct stat result;
        if (stat(filename.c_str(), &result) == 0) {
            timePoint = std::chrono::system_clock::from_time_t(result.st_mtime);
        }
#endif
    } else {
        lastError = "Error getting file modified time: " + filename;
    }

    return timePoint;
}

bool FileAccess::set_modified_time(const std::chrono::system_clock::time_point& newTime) {
    if (file.is_open()) {
#ifdef _WIN32
        // Windows-specific code to set file modification time
        FILETIME ft;
        ULARGE_INTEGER ull;
        ull.QuadPart = std::chrono::duration_cast<std::chrono::seconds>(newTime.time_since_epoch()).count() * 10000000ULL + 11644473600ULL * 10000000ULL;
        ft.dwLowDateTime = ull.LowPart;
        ft.dwHighDateTime = ull.HighPart;
        SetFileTime(file.native_handle(), nullptr, nullptr, &ft);
        return true;
#else
        // Unix-like system code to set file modification time
        struct stat st;
        struct utimbuf new_times;

        if (stat(filename.c_str(), &st) == 0) {
            new_times.actime = st.st_atime;
            new_times.modtime = std::chrono::system_clock::to_time_t(newTime);
            return utime(filename.c_str(), &new_times) == 0;
        }
#endif
    } else {
        lastError = "Error setting file modified time: " + filename;
    }

    return false;
}


void FileAccess::_bind_methods() {
	Class::bind_method("open" , &FileAccess::open);
	Class::bind_method("close", & FileAccess::close);
	Class::bind_method("store_string", & FileAccess::store_string);
	
}