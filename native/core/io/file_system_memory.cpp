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
#include "file_system_memory.h"

#include "core/error/error_list.h"
#include "core/error/error_macros.h"
#include "core/string/ustring.h"
#include "core/templates/vector.h"

#include <fstream>
#include <sstream>

FileSystemMemory::FileSystemMemory() : rootPath_(rootPath) {
    create_directory(rootPath);
}

FileSystemMemory::~FileSystemMemory() {
    // Perform any cleanup operations
}

bool FileSystemMemory::create_file(const std::string& filePath, const std::string& content) {
    std::ofstream file(getAbsolutePath(filePath));
    if (file.is_open()) {
        file << content;
        file.close();
        fileContents_[filePath] = content;
        fileStatus_[filePath] = true;
        return true;
    }
    errorMessages_[filePath] = "Failed to create file: " + filePath;
    return false;
}

bool FileSystemMemory::create_directory(const std::string& dirPath) {
    fs::path fullPath = get_absolute_path(dirPath);
    if (fs::create_directory(fullPath)) {
        return true;
    }
    errorMessages_[dirPath] = "Failed to create directory: " + dirPath;
    return false;
}

bool FileSystemMemory::delete_file(const std::string& filePath) {
    fs::path fullPath = getAbsolutePath(filePath);
    if (fs::remove(fullPath)) {
        fileContents_.erase(filePath);
        fileStatus_.erase(filePath);
        return true;
    }
    errorMessages_[filePath] = "Failed to delete file: " + filePath;
    return false;
}

bool FileSystemMemory::delete_directory(const std::string& dirPath) {
    fs::path fullPath = get_absolute_path(dirPath);
    if (fs::remove_all(fullPath) > 0) {
        return true;
    }
    errorMessages_[dirPath] = "Failed to delete directory: " + dirPath;
    ERR_WARN("Failed to delete directory\n", dirPath);
    return false;
}

std::string FileSystemMemory::read_file(const std::string& filePath) const {
    auto it = fileContents_.find(filePath);
    return (it != fileContents_.end()) ? it->second : "";
}

std::vector<std::string> FileSystemMemory::list_directory(const std::string& dirPath) {
    std::vector<std::string> fileList;
    fs::path fullPath = getAbsolutePath(dirPath);

    if (fs::exists(fullPath) && fs::is_directory(fullPath)) {
        for (const auto& entry : fs::directory_iterator(fullPath)) {
            fileList.push_back(entry.path().filename().string());
        }
    }

    return fileList;
}

bool FileSystemMemory::register_file(const std::string& fileName, const uint8_t* p_data, int dataLength) {
    std::string content(reinterpret_cast<const char*>(p_data), dataLength);
    return create_file(fileName, content);
}

bool FileSystemMemory::open_custom(const std::string& filePath, const uint8_t* p_data, int dataLength) {
    // Implement custom open logic here
    // For example, append data to an existing file or perform any other desired operations
    std::string content = read_Ffile(filePath);
    content += std::string(reinterpret_cast<const char*>(p_data), dataLength);
    return create_file(filePath, content);
}

bool FileSystemMemory::store_buffer(const std::string& filePath, const uint8_t* p_src, int length) {
    std::ofstream file(getAbsolutePath(filePath), std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(p_src), length);
        file.close();
        return true;
    }
    errorMessages_[filePath] = "Failed to store buffer to file: " + filePath;
    return false;
}

bool FileSystemMemory::is_open(const std::string& filePath) const {
    auto it = fileStatus_.find(filePath);
    return (it != fileStatus_.end()) ? it->second : false;
}

void FileSystemMemory::close(const std::string& filePath) {
    // Perform any necessary close operations here
    fileStatus_[filePath] = false;
}

bool FileSystemMemory::seek_end(const std::string& filePath, int64_t position) {
    std::ofstream file(getAbsolutePath(filePath), std::ios::app);
    if (file.is_open()) {
        file.seekp(position, std::ios::end);
        file.close();
        return true;
    }
    errorMessages_[filePath] = "Failed to seek to the end of file: " + filePath;
    return false;
}

bool FileSystemMemory::seek(const std::string& filePath, size_t position) {
    std::ofstream file(getAbsolutePath(filePath), std::ios::out | std::ios::ate);
    if (file.is_open()) {
        file.seekp(position, std::ios::beg);
        file.close();
        return true;
    }
    errorMessages_[filePath] = "Failed to seek to position in file: " + filePath;
    return false;
}

std::string FileSystemMemory::get_error() const {
    std::stringstream errors;
    for (const auto& entry : errorMessages_) {
        errors << entry.second << std::endl;
    }
    return errors.str();
}

bool FileSystemMemory::get_buffer(const std::string& filePath, uint8_t* p_dst, int length) {
    std::string content = read_file(filePath);
    if (content.length() >= static_cast<size_t>(length)) {
        std::memcpy(p_dst, content.data(), length);
        return true;
    }
    errorMessages_[filePath] = "Failed to get buffer from file: " + filePath;
    return false;
}

bool FileSystemMemory::file_exists(const std::string& filePath) const {
    return fs::exists(get_absolute_path(filePath));
}

fs::path FileSystemMemory::get_absolute_path(const std::string& path) const {
    return fs::absolute(rootPath_ / path);
}
