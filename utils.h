//
// Created by mahmood on 1/18/21.
//

#ifndef GOOGLE_UTILS_H
#define GOOGLE_UTILS_H

#include <vector>
#include <string>

std::vector<std::string> get_all_files_paths(const std::string &directory_path);
std::vector<std::string> FileLister(const char* directoryName);
bool is_txt_extintion(const std::string &file);

std::string read_file(const std::string &file_path);

#endif //GOOGLE_UTILS_H
