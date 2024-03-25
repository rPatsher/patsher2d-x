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
std::string Filesystem::get_path_absolute() const {
    return std::filesystem::absolute(directoryPath).string();
}

void Filesystem::seek(uint64_t p_position) {
    // Seek to the specified position in the file
    if (fileStream.is_open()) {
        fileStream.seekg(p_position, std::ios::beg); // Assuming you are using std::fstream for file operations
    }
}

uint64_t Filesystem::get_position() const {
    if (fileStream.is_open()) {
        return static_cast<uint64_t>(fileStream.tellg());
    }
    return 0;
}

uint64_t Filesystem::get_length() const {
    if (fileStream.is_open()) {
        std::streampos currentPos = fileStream.tellg();
        fileStream.seekg(0, std::ios::end);
        std::streampos length = fileStream.tellg();
        fileStream.seekg(currentPos, std::ios::beg);
        return static_cast<uint64_t>(length);
    }
    return 0;
}

bool Filesystem::file_exists(const std::string &p_name) const {
    std::filesystem::path filePath = directoryPath / p_name;
    return std::filesystem::exists(filePath);
}

std::chrono::system_clock::time_point Filesystem::_get_modified_time(const std::string &p_file) const {
    std::filesystem::path filePath = directoryPath / p_file;
    return std::filesystem::last_write_time(filePath);
}

std::filesystem::perms Filesystem::_get_unix_permissions(const std::string &p_file) const {
    std::filesystem::path filePath = directoryPath / p_file;
    return std::filesystem::status(filePath).permissions();
}

void Filesystem::close() {
    fileStream.close();
    openFilePath.clear();
}

ReadBlock Filesystem::read_block(size_t blockSize) {
    ReadBlock readBlock;

    if (fileStream.is_open()) {
        std::vector<uint8_t> buffer(blockSize);
        fileStream.read(reinterpret_cast<char*>(buffer.data()), blockSize);

        // Check how many bytes were actually read
        size_t bytesRead = static_cast<size_t>(fileStream.gcount());

        // Resize the ReadBlock data vector to the actual size read
        readBlock.data.resize(bytesRead);
        std::copy(buffer.begin(), buffer.begin() + bytesRead, readBlock.data.begin());

        readBlock.size = bytesRead;
    }

    return readBlock;
}

bool Filesystem::save(const std::vector<uint8_t>& data) {
    if (fileStream.is_open()) {
        fileStream.write(reinterpret_cast<const char*>(data.data()), data.size());
        return true;
    }

    return false;
}

std::vector<uint8_t> Filesystem::load() {
    std::vector<uint8_t> data;

    if (fileStream.is_open()) {
        fileStream.seekg(0, std::ios::end);
        size_t fileSize = static_cast<size_t>(fileStream.tellg());
        fileStream.seekg(0, std::ios::beg);
        data.resize(fileSize);
        fileStream.read(reinterpret_cast<char*>(data.data()), fileSize);
    }

    return data;
}

bool Filesystem::folder_removed(const std::string& folderName) {
    std::filesystem::path folderPath = directoryPath / folderName;

    try {
        std::filesystem::remove_all(folderPath);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

bool Filesystem::file_removed(const std::string& fileName) {
    std::filesystem::path filePath = directoryPath / fileName;

    try {
        std::filesystem::remove(filePath);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

bool Filesystem::set_access_type(const std::string& name, AccessType accessType) {
    std::filesystem::path itemPath = directoryPath / name;

    try {
        switch (accessType) {
            case AccessType::Read:
                std::filesystem::permissions(itemPath, std::filesystem::perms::owner_read,
                                             std::filesystem::perm_options::add);
                break;

            case AccessType::WRITE:
                std::filesystem::permissions(itemPath, std::filesystem::perms::owner_write,
                                             std::filesystem::perm_options::add);
                break;

            case AccessType::EXECUTE:
                std::filesystem::permissions(itemPath, std::filesystem::perms::owner_exec,
                                             std::filesystem::perm_options::add);
                break;

            case AccessType::ACCESS_FILESYSTEM:
                std::filesystem::permissions(itemPath, std::filesystem::perms::owner_read, std::filesystem::perm_options::add);
                break;

            case AccessType::ACCESS_USERDATA:
                std::filesystem::permissions(itemPath, std::filesystem::perms::owner_write,std::filesystem::perm_options::add);
                break;

            default:
                return false;
        }

        return true; 
    } catch (const std::exception& e) {
        return false;
    }
}

std::filesystem::path Filesystem::get_current_dir(bool includeDrive) {
    std::filesystem::path currentDir = std::filesystem::current_path();

    if (!includeDrive) {
        currentDir = currentDir.relative_path();
    }

    return currentDir;
}


bool Filesystem::make_dir(const std::string& dirName) {
    std::filesystem::path newDirPath = directoryPath / dirName;

    try {
        return std::filesystem::create_directory(newDirPath);
    } catch (const std::exception& e) {
        return false;
    }
}

bool Filesystem::dir_exists(const std::string& dirName) {
    std::filesystem::path dirPath = directoryPath / dirName;

    return std::filesystem::is_directory(dirPath);
}