#ifndef DIR_ACCESS_H
#define DIR_ACCESS_H

#include <filesystem>
#include <string>
#include <vector>

#include "core/object/ref_counted.h"
#include "core/string/string.h"
#include "core/templates/vector.h"
#include "core/error/error_list.h"

class DirAccess : public RefCounted {
    CLASS(DirAccess , RefCounted);

public:
    enum AccessType {
        READ,
        WRITE,
        EXCUTE,
        ACCESS_FILESYSTEM,
        ACCESS_RESOURCES
    };

public:
    DirAccess();
    ~DirAccess();

public:
    std::vector<std::string> list_files();
    bool create(const std::string& directoryName);
    bool remove(const std::string& directoryName);
    
    bool make_dir_recursive(const std::string& dirPath) const;
    

    bool mkdir(const std::string& directoryName);
    bool changed_dir(const std::string& directoryName);
    
    bool copy(const std::string& source, const std::string& destination);
    bool copy_absolute(const std::string& source, const std::string& destination);
    
    bool current_is_dir();
    bool erase_contents_recursive() const;

    bool exists(const std::string& dirPath) const;
    bool rename(const std::string& from, const std::string& to) const;

    std::string get_current_dir(bool includeDrive = true) const;
    std::string getFileSystemType() const;


    bool dir_exists(const std::string& directoryName);
    bool file_exists(const std::string& fileName);
    
    std::string get_current_dir();
    
    std::vector<std::string> get_directories();
    std::vector<std::string> get_directories_at(const std::string& directoryPath);
    
    std::string get_full_path(const std::string& path, AccessType access) const;
    AccessType get_access_type(const std::string& path) const;
    
    std::string fix_path(const std::string& path, AccessType access) const;

    bool change_dir(const std::string& dir);

    static DirAccess create_for_path(const std::string& path);
    bool dir_exists_absolute(const std::string& dirPath) const;

    std::vector<std::string> get_directories_at(const std::string& dirPath) const;

    std::string get_drive_name();
    std::vector<std::string> get_files();

protected:
    void _bind_methods();

private:
    std::filesystem::path dirPath;
};




#endif // DIR_ACCESS_H
