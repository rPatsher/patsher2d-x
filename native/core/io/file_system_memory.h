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
#ifndef FILE_SYSTEM_MEMORY_H
#define FILE_SYSTEM_MEMORY_H

#include <filesystem>
#include <unordered_map>


#include <cstdint>

#include "core/templates/vector.h"
#include "core/string/ustring.h"

enum Error;

namespace fs = std::filesystem;

class FileSystemMemory : public RefCounted {
public:
    FileSystemMemory();
    ~FileSystemMemory();

    // Methods to interact with the file system
    bool create_file(const String& filePath, const String& content);
    bool create_directory(const String& dirPath);
    bool delete_file(const String& filePath);
    bool delete_directory(const String& dirPath);
    String read_file(const String& filePath) const;
    Vector<String> list_directory(const String& dirPath);

    // Methods for handling custom file operations
    bool register_file(const String& fileName, const uint8_t* p_data, int dataLength);
    bool open_custom(const String& filePath, const uint8_t* p_data, int dataLength);
    bool store_buffer(const String& filePath, const uint8_t* p_src, int length);
    
    // File status methods
    bool is_open(const String& filePath) const;
    void close(const String& filePath);

    // Seek methods
    bool seek_end(const String& filePath, int64_t position);
    bool seek(const String& filePath, size_t position);

    // Error and buffer methods
    String get_error() const;
    bool get_buffer(const String& filePath, uint8_t* p_dst, int length);
    
    // File existence check
    bool file_exists(const String& filePath) const;

private:
    // Helper functions
    fs::path get_absolute_path(const String& path) const;

    // Data members
    fs::path rootPath_;
    std::unordered_map<String, String> fileContents_;
    std::unordered_map<String, bool> fileStatus_;
    std::unordered_map<String, String> errorMessages_;
};

#endif // FILE_SYSTEM_MEMORY_H