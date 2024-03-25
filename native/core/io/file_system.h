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
#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <filesystem>
#include <vector>
#include <string>
#include <fstream>


#include "core/object/ref_counted.h"
#include "core/templates/vector.h"
#include "core/templates/list.h"
#include "core/io/file_access.h"


class String;


class Filesystem : public RefCounted {
	CLASS(Filesystem, RefCounted);
public:
	enum AccessType {
    	READ,
    	WRITE,
    	EXECUTE,
    	ACCESS_FILESYSTEM,
    	ACCESS_USERDATA
	};
public:
	struct FileInfo {
		String name;
    	std::filesystem::path path;
    	std::chrono::system_clock::time_point modifiedTime;
    	std::filesystem::perms permissions;
    	bool isDirectory;
    	uintmax_t size;
    	AccessType accessType;
    	
    FileInfo(const std::filesystem::path& folderPath)
        : name(folderPath.filename().string()), path(folderPath), isDirectory(true) {
        modifiedTime = std::filesystem::last_write_time(folderPath);
        permissions = std::filesystem::status(folderPath).permissions();
        size = 0; // Directories don't have a size
    }
    };
    
    struct ReadBlock {
    Vector<uint8_t> data;
    size_t size;

    ReadBlock(const Vector<uint8_t>& blockData, size_t blockSize) : data(blockData), size(blockSize) {}
	};

public:
    ReadBlock read_block(size_t blockSize);   
    bool save(const Vector<uint8_t>& data);
    Vector<uint8_t> load();
    bool folder_removed(const String& folderName);
    bool file_removed(const String& fileName);
    void resource_created();
    void make_scene_confirm();
    FileInfo get_file_info(const String& name);
    Vector<std::filesystem::path> get_uncollapsed_paths();
    Vector<std::filesystem::path> get_selected_paths();
    bool set_access_type(const String& name, AccessType accessType);
    bool make_dir(const String& dirName);
    bool dir_exists(const String& dirName);
    std::filesystem::path get_current_dir(bool includeDrive = true);
    bool copy_dir(const String& fromDir, const String& toDir, int chmodFlags = -1, bool copyLinks = false);
    bool copy(const String& from, const String& to, int chmodFlags = -1);


protected:
	void _bind_methods() {}
	
private:
    std::filesystem::path directoryPath;
    std::fstream fileStream;
    String openFilePath;
    
};

#endif // FILESYSTEM_H