#include "aether.hpp"
#include "raylib.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <string> 
#include <algorithm> 
#include <cstdlib>
namespace fs = std::filesystem;

namespace aether {

    // Creating the File
    int touch_file(std::stringstream &ss, fs :: path currentpath){
        std::string file_name;
        ss >> std::quoted(file_name);
        if(file_name.empty()){
            std::cout << "no filename in input\n";
            return 2;
        }
        else {
            currentpath = currentpath/file_name;
            
            if (!fs::exists(currentpath)) {
                std::ofstream outFile(currentpath, std::ios::app);
                if(outFile.is_open()) {
                    outFile << "File Content";
                    std::cout << "File Made";
                    outFile.close();
                }
                return 1;
            }
            return 0;
        }
    }
    // Renaming a File
    int rename_file (std::stringstream &ss, fs::path currentpath) {
        std::string old_name, new_name;
        
        ss >> std::quoted(old_name);
        ss >> std::quoted(new_name);
        if(old_name.empty() || new_name.empty()){
            std::cout << "no filename in input\n";
            return 2;
        }
        fs::path oldpath = currentpath/old_name;
        fs::path newpath = currentpath/new_name;
        
        if (fs::exists(oldpath)) {
            if (!fs::exists(newpath)) {
                std::error_code ec;
                fs::rename(oldpath, newpath,ec);
                return 1;
            }
            else return 4;
        }    
        else return 3;
    }

    // Opening the File
    int open_file(std::stringstream &ss, fs::path currentpath) {
        std::string file_name;
        
        ss>> std::quoted(file_name);
        if(file_name.empty()){
            std::cout << "no filename in input\n";
            return 2;
        }
        else {
            currentpath = currentpath/file_name;
            
            if (fs::exists(currentpath)) {
                std::string command = "xdg-open \"" + currentpath.string() + "\" &";
                system(command.c_str());
                return 1;
            }
            return 3;
        }
    }

    // Changing the Directory
    int change_dir(std::stringstream &ss, fs::path *currentpath) {
        std::string dir_name;
        
        ss >> std::quoted(dir_name);
        if(dir_name.empty()){
            std::cout << "no directory name in input\n";
            return 2;
        }
        else {
            fs::path dirpath = *currentpath/dir_name;
            if (fs::exists(dirpath)) {
                *currentpath = dirpath;
                return 1;
            }
            else 
            return 3;
        }
    }

    // Make Directory
    int make_dir (std::stringstream &ss, fs::path currentpath) {
        std::string dir_name;
        
        ss >> std::quoted(dir_name);
        if (dir_name.empty()) {
            std::cout << "no directory name in input\n";
            return 2;
        }
        else {
            currentpath = currentpath/dir_name;
            if (fs::exists(currentpath))
            return 0;
            else {
                fs::create_directories(currentpath);
                return 1;
            }
        }
    }

    // Removing the File / Directory
    int remove (std::stringstream &ss, fs::path currentpath) {
        std::string content;
        
        ss >> std::quoted(content);
        if (content.empty()) {
            std::cout << "no directory name in input\n";
            return 2;
        }
        else {
            currentpath = currentpath/content;
            if (!fs::exists(currentpath))
            return 3;
            else {
                uintmax_t del_count = fs::remove_all(currentpath);
                return 5;
            }
        }
    }

    // List Data
    int list (fs::path currentpath, std::vector<std::string> &data_list, std::vector<std::string> &dir_list, std::vector<std::string> &file_list) {
        data_list.clear();
        dir_list.clear();
        file_list.clear();
        for (const auto& entry : fs::directory_iterator(currentpath)) {
            data_list.push_back(entry.path().filename().string());
        }
        for (std::string data : data_list) {
            if (fs::is_directory(currentpath/data))
                dir_list.push_back(data);
            else
                file_list.push_back(data);
        }
        return 6;
    }

    // Gedit the File
    int gedit_file (std::stringstream &ss, fs::path currentpath) {
        std::string file_name;
        
        ss>> std::quoted(file_name);
        if(file_name.empty()){
            std::cout << "no filename in input\n";
            return 2;
        }
        else {
            currentpath = currentpath/file_name;
            
            if (fs::exists(currentpath)) {
                std::string command = "gedit \"" + currentpath.string() + "\" &";
                system(command.c_str());
                return 1;
            }
            return 3;
        }
    }

    // Nano the File
    int nano_file (std::stringstream &ss, fs::path currentpath) {
        std::string file_name;
        
        ss>> std::quoted(file_name);
        if(file_name.empty()){
            std::cout << "no filename in input\n";
            return 2;
        }
        else {
            currentpath = currentpath/file_name;
            
            if (fs::exists(currentpath)) {
                std::string command = "nano \"" + currentpath.string() + "\" &";
                system(command.c_str());
                return 1;
            }
            return 3;
        }
    }
    
    // Double Tab Listing
    int tab_list(fs::path currentpath, std::vector<std::string> &names, std::vector<std::string> &data_list, std::vector<std::string> &dir_list, std::vector<std::string> &file_list) {
        data_list.clear();
        dir_list.clear();
        file_list.clear();
        for (std::string data : names) {
            if (fs::is_directory(currentpath/data))
                dir_list.push_back(data);
            else
                file_list.push_back(data);
        }
        return 6;
    }

    // Tab Function
    int tab_func (std::string &input, fs::path currentpath, bool double_press, std::vector<std::string> &data_list, std::vector<std::string> &dir_list, std::vector<std::string> &file_list) {
        std::stringstream ss(input);
        std::string word, output = "";
        std::vector<std::string> words, names;
        
        if (input.length() <= 0) return 1;
        
        else if (input[input.length() - 1] == ' ' && double_press)
            return list (currentpath, data_list, dir_list, file_list);
        
        while (ss >> word)
            words.push_back(word);
            
        for (const auto& entry : fs::directory_iterator(currentpath)) {
            if (!entry.path().filename().string().find(words[words.size() - 1], 0))
                names.push_back(entry.path().filename().string());
        }
        
        if (!double_press) {
            if (names.size() == 1) {
                words[words.size() - 1] = names[0];
                for (std::string str : words) {
                    output += str;
                    if (str != words[words.size() - 1])
                        output += " ";
                }
                input = output;
            }
            else if (names.size()) {
                int n = names[0].length();
                for (int i = 1; i < names.size(); i++) {
                    int m = 0;
                    while (m < names[0].length() && m < names[i].length() && names[0][m] == names[i][m])
                        m ++;
                    n = std::min(n, m);
                    if (n == 1)
                        break;
                }
                words[words.size() - 1] = names[0].substr(0, n);
                for (std::string str : words) {
                    output += str;
                    if (str != words[words.size() - 1])
                        output += " ";
                }
                input = output;
            }
            return 1;
        }
        else if (double_press) {
            return tab_list(currentpath, names, data_list, dir_list, file_list);
        }
        return 1;
    }
    
    // Move File
    int move_file (std::stringstream &ss, fs::path currentpath) {
        std::string file_name, dest;
        ss >> std::quoted(file_name);
        if(file_name.empty()){
            std::cout << "no filename in input\n";
            return 2;
        }
        ss >> std::quoted(dest);
        fs::path destpath = dest;
        if (!fs::is_directory(destpath))
            return 3;
        currentpath = currentpath / file_name;
        destpath = destpath / file_name;
        fs::rename (currentpath, destpath);
        return 1;
    }
    
    // Copy File
    int copy_file (std::stringstream &ss, fs::path currentpath) {
        std::string file_name, dest;
        ss >> std::quoted(file_name);
        if(file_name.empty()){
            std::cout << "no filename in input\n";
            return 2;
        }
        ss >> std::quoted(dest);
        fs::path destpath = dest;
        if (!fs::is_directory(destpath))
            return 3;
        currentpath = currentpath / file_name;
        destpath = destpath / file_name;
        fs::copy_file (currentpath, destpath);
        return 1;
    }
    
    // Duplicate File
    int duplicate_file (std::stringstream &ss, fs::path currentpath) {
        std::string file_name, dest;
        ss >> std::quoted(file_name);
        if(file_name.empty()){
            std::cout << "no filename in input\n";
            return 2;
        }
        currentpath = currentpath / file_name;
        std::string new_name = currentpath.stem().string() + "_copy" + currentpath.extension().string();
        fs::path dest_path = currentpath;
        dest_path.replace_filename(new_name);
        fs::copy_file(currentpath, dest_path);
        return 1;
    }
}
