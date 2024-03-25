/*
 * Copyright 2024 rPatsher
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
#include "dir_access.h"

#include "core/io/file_system.h" 
#include "core/templates/vector.h"
#include "core/string/ustring.h" 
#include "core/template/hash_map.h"
#include "core/templates/list.h"
#include "core/typedefs.h"

#include <filesystem>
#include <thread>
#include <list>


bool DirAccess::make_dir_recursive(const String& dirPath) const {
    std::filesystem::path fullPath = basePath / dirPath;

    // Check if the directory already exists
    if (std::filesystem::exists(fullPath)) {
        return false; // Directory already exists
    }

    // Create the directory and its parents recursively
    return std::filesystem::create_directories(fullPath);
}

bool DirAccess::erase_contents_recursive() const {
    // Check if the directory exists
    if (!std::filesystem::exists(basePath) || !std::filesystem::is_directory(basePath)) {
        return false; // Directory does not exist
    }

    // Remove the contents recursively
    for (const auto& entry : std::filesystem::directory_iterator(basePath)) {
        if (entry.is_directory()) {
            std::filesystem::remove_all(entry.path());
        } else {
            std::filesystem::remove(entry.path());
        }
    }

    return true;
}

bool DirAccess::file_exists(const String& fileName) const {
    std::filesystem::path filePath = basePath / fileName;
    return std::filesystem::exists(filePath) && std::filesystem::is_regular_file(filePath);
}

bool DirAccess::exists(const String& dirPath) const {
    std::filesystem::path fullPath = basePath / dirPath;
    return std::filesystem::exists(fullPath) && std::filesystem::is_directory(fullPath);
}

bool DirAccess::copy(const String& from, const String& to, int chmodFlags) const {
    std::filesystem::path source = basePath / from;
    std::filesystem::path destination = basePath / to;

    // Check if the source exists
    if (!std::filesystem::exists(source)) {
        return false; // Source does not exist
    }

    // Check if the destination directory exists
    make_dir_recursive(to);

    // Copy the file or directory
    try {
        if (std::filesystem::is_directory(source)) {
            std::filesystem::copy(source, destination, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
        } else {
            std::filesystem::copy_file(source, destination, std::filesystem::copy_options::overwrite_existing);
        }
        // Apply chmod flags if provided
        if (chmodFlags != -1) {
            std::filesystem::permissions(destination, std::filesystem::perms(chmodFlags), std::filesystem::perm_options::replace);
        }
    } catch (const std::exception&) {
        return false; // Failed to copy
    }

    return true;
}

bool DirAccess::make_dir(const String& dirName) const {
    std::filesystem::path newDirPath = basePath / dirName;

    // Check if the directory already exists
    if (std::filesystem::exists(newDirPath)) {
        return false; // Directory already exists
    }

    // Create the new directory
    return std::filesystem::create_directory(newDirPath);
}

 bool DirAccess::make_dir_recursive_absolute(const String& dirPath) const {
    std::filesystem::path absoluteDirPath = std::filesystem::absolute(dirPath);

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
    if (!std::filesystem::exists(itemPath)) {
        ERR_PRINT("Item does not exist\n" , itemPath);
        return false; // Item does not exist
        
    }
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


    if (!std::filesystem::exists(source)) {
        return false; // source does not exist
    }
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

Vector<String> DirAccess::get_files() const {
    Vector<String> files;

    for (const auto& entry : std::filesystem::directory_iterator(basePath)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().filename().string());
        }
    }

    return files;
}

Vector<String> DirAccess::get_directories() const {
    Vector<String> directories;

    for (const auto& entry : std::filesystem::directory_iterator(basePath)) {
        if (entry.is_directory()) {
            directories.push_back(entry.path().filename().string());
        }
    }

    return directories;
}

Vector<String> DirAccess::list_dir_begin() const {
    Vector<String> contents;

    for (const auto& entry : std::filesystem::directory_iterator(basePath)) {
        contents.push_back(entry.path().filename().string());
    }

    return contents;
}

String DirAccess::get_current_dir(bool includeDrive) const {
    if (includeDrive) {
        return basePath.string();
    } else {
        return basePath.filename().string();
    }
}


String DirAccess::get_full_path(const String& path, AccessType access) const {
    std::filesystem::path fullPath;

    switch (access) {
        case AccessType::Read:
        case AccessType::Write:
        case AccessType::Execute:
            fullPath = basePath / path;
            break;

        case AccessType::ACCESS_FILESYSTEM:
            fullPath = basePath / "filesystem" / path;
            break;

        case AccessType::ACCESS_RESOURCES:
            fullPath = basePath / "resources" / path;
            break;
    }

    return fullPath.string();
}