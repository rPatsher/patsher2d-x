#ifndef DIR_ACCESS_H
#define DIR_ACCESS_H

#include <filesystem>
#include <string>
#include <vector>


class DirAccess {
public:
    DirAccess(const std::string& directoryPath);
    ~DirAccess();
    std::vector<std::string> listFiles();
    bool create(const std::string& directoryName);
    bool remove(const std::string& directoryName);
    bool mkdir(const std::string& directoryName);
    bool changed_dir(const std::string& directoryName);
    bool copy(const std::string& source, const std::string& destination);
    bool copy_absolute(const std::string& source, const std::string& destination);
    bool current_is_dir();
    bool dir_exists(const std::string& directoryName);
    bool file_exists(const std::string& fileName);
    std::string get_current_dir();
    std::vector<std::string> get_directories();
    std::vector<std::string> get_directories_at(const std::string& directoryPath);
    std::string get_drive_name();
    std::vector<std::string> get_files();

private:
    std::filesystem::path dirPath;
};




#endif // DIR_ACCESS_H
