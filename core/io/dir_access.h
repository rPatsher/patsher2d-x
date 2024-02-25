#ifndef DIR_ACCESS_H
#define DIR_ACCESS_H

#include <filesystem>

#include "core/object/ref_counted.h"
#include "core/string/ustring.h"
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
    Vector<String> list_files();
    bool create(const String& p_dir);
    bool remove(const String& p_dir);
    
    bool make_dir_recursive(const String& dirPath) const;
    

    bool mkdir(const String& p_dir);
    bool changed_dir(const String& p_dir);
    
    bool copy(const String& source, const String& destination);
    bool copy_absolute(const String& source, const String& destination);
    
    bool current_is_dir();
    bool erase_contents_recursive() const;

    bool exists(const String& dirPath) const;
    bool rename(const String& from, const String& to) const;

    String get_current_dir(bool includeDrive = true) const;
    String getFileSystemType() const;


    bool dir_exists(const String& p_dir);
    bool file_exists(const String& fileName);
    
    String get_current_dir();
    
    Vector<String> get_directories();
    Vector<String> get_directories_at(const String& directoryPath);
    
    String get_full_path(const String& path, AccessType access) const;
    AccessType get_access_type(const String& path) const;
    
    String fix_path(const String& path, AccessType access) const;

    bool change_dir(const String& dir);

    static DirAccess create_for_path(const String& path);
    bool dir_exists_absolute(const String& dirPath) const;

    Vector<String> get_directories_at(const String& dirPath) const;

    String get_drive_name();
    Vector<String> get_files();

protected:
    void _bind_methods();

private:
    std::filesystem::path dirPath;
};




#endif // DIR_ACCESS_H
