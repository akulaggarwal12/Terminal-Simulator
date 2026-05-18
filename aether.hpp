#ifndef AETHER_H
#define AETHER_H

#include <filesystem>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
namespace fs = std::filesystem;

namespace aether {
    int touch_file(std::stringstream &ss, fs::path currentpath);
    int rename_file (std::stringstream &ss, fs::path currentpath);
    int open_file(std::stringstream &ss, fs::path currentpath);
    int gedit_file (std::stringstream &ss, fs::path currentpath);
    int nano_file (std::stringstream &ss, fs::path currentpath);
    int change_dir(std::stringstream &ss, fs::path *currentpath);
    int make_dir (std::stringstream &ss, fs::path currentpath);
    int remove (std::stringstream &ss, fs::path currentpath);
    int list (fs::path currentpath, std::vector<std::string> &data_list, std::vector<std::string> &dir_list, std::vector<std::string> &file_list);
    int tab_list(fs::path currentpath, std::vector<std::string> &names, std::vector<std::string> &data_list, std::vector<std::string> &dir_list, std::vector<std::string> &file_list);
    int tab_func (std::string &input, fs::path currentpath, bool double_press, std::vector<std::string> &data_list, std::vector<std::string> &dir_list, std::vector<std::string> &file_list);
    int move_file (std::stringstream &ss, fs::path currentpath);
    int copy_file (std::stringstream &ss, fs::path currentpath);
    int duplicate_file (std::stringstream &ss, fs::path currentpath);
}

#endif
