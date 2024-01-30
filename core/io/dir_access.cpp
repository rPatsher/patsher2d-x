#include "dir_access.h"




std::vector<std::string> DirAccess::get_directories() const {
    std::vector<std::string> directories;

    for (const auto& entry : std::filesystem::directory_iterator(basePath)) {
        if (entry.is_directory()) {
            directories.push_back(entry.path().filename().string());
        }
    }

    return directories;
}

bool DirAccess::remove(const std::string& name) const {
    std::filesystem::path itemPath = basePath / name;

    // Check if the item exists
    if (!std::filesystem::exists(itemPath)) {
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


bool DirAccess::rename(const std::string& from, const std::string& to) const {
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


bool DirAccess::change_dir(const std::string& dir) {
    std::filesystem::path newDir = basePath / dir;

    // Check if the new directory exists
    if (!std::filesystem::exists(newDir) || !std::filesystem::is_directory(newDir)) {
        return false; // Directory does not exist
    }

    basePath = newDir;
    return true;
}

DirAccess DirAccess::create_for_path(const std::string& path) {
    return DirAccess(path);
}




bool DirAccess::dir_exists_absolute(const std::string& dirPath) const {
    std::filesystem::path absoluteDirPath = std::filesystem::absolute(dirPath);
    return std::filesystem::exists(absoluteDirPath) && std::filesystem::is_directory(absoluteDirPath);
} 



std::vector<std::string> DirAccess::get_directories_at(const std::string& dirPath) const {
    std::filesystem::path targetPath = basePath / dirPath;
    std::vector<std::string> directories;

    if (std::filesystem::exists(targetPath) && std::filesystem::is_directory(targetPath)) {
        for (const auto& entry : std::filesystem::directory_iterator(targetPath)) {
            if (entry.is_directory()) {
                directories.push_back(entry.path().filename().string());
            }
        }
    }

    return directories;
}
