#include "dir_access.h"

#include "core/io/file_system.h" 
#include "core/templates/vector.h"
#include "core/string/ustring.h" 

#include <filesystem>
#include <thread>


Vector<String> DirAccess::get_directories() const {
    Vector<String> directories;

    for (const auto& entry : std::filesystem::directory_iterator(basePath)) {
        if (entry.is_directory()) {
            directories.push_back(entry.path().filename().string());
        }
    }

    return directories;
}

bool DirAccess::remove(const String& name) const {
    std::filesystem::path itemPath = basePath / name;

    // Check if the item exists
    if (!std::filesystem::exists(itemPath)) {
        ERR_PRINT("Item does not exist\n" , itemPath);
        return false; // Item does not exist
        
    }

    // Perform the removal
    try {
        if (std::filesystem::is_directory(itemPath)) {
            std::filesystem::remove_all(itemPath);
        } else {
            std::filesystem::remove(itemPath);
        }
    } catch (const std::exception&) {
        return false; // Failed to remove
    }

    return true;
}


bool DirAccess::rename(const String& from, const String& to) const {
    std::filesystem::path source = basePath / from;
    std::filesystem::path destination = basePath / to;

    // Check if the source exists
    if (!std::filesystem::exists(source)) {
        return false; // Source does not exist
    }

    // Perform the rename operation
    try {
        std::filesystem::rename(source, destination);
    } catch (const std::exception&) {
        return false; // Failed to rename
    }

    return true;
}


bool DirAccess::change_dir(const String& dir) {
    std::filesystem::path newDir = basePath / dir;

    // Check if the new directory exists
    if (!std::filesystem::exists(newDir) || !std::filesystem::is_directory(newDir)) {
        return false; // Directory does not exist
    }

    basePath = newDir;
    return true;
}

DirAccess DirAccess::create_for_path(const String& path) {
    return DirAccess(path);
}


bool DirAccess::dir_exists_absolute(const String& dirPath) const {
    std::filesystem::path absoluteDirPath = std::filesystem::absolute(dirPath);
    return std::filesystem::exists(absoluteDirPath) && std::filesystem::is_directory(absoluteDirPath);
} 



Vector<String> DirAccess::get_directories_at(const String& dirPath) const {
    std::filesystem::path targetPath = basePath / dirPath;
    Vector<String> directories;

    if (std::filesystem::exists(targetPath) && std::filesystem::is_directory(targetPath)) {
        for (const auto& entry : std::filesystem::directory_iterator(targetPath)) {
            if (entry.is_directory()) {
                directories.push_back(entry.path().filename().string());
            }
        }
    }

    return directories;
}
