//
// Created by mahmood on 1/18/21.
//

#include <dirent.h>
#include <iostream>
#include <fstream>
#include "utils.h"

std::vector<std::string> get_all_files_paths(const std::string &directory_path)
{
    std::vector<std::string> files_path = FileLister(directory_path.c_str());

    return  files_path;
}
std::vector<std::string> FileLister(const char* directoryName)
{
    std::vector<std::string> files_path;
    std::vector<std::string> temp;
    DIR *targetDirectory;
    struct dirent *entity;
    std::string name;
    if ((targetDirectory = opendir(directoryName)) != NULL)
    {
        while ((entity = readdir(targetDirectory)) != NULL)
        {
            std::string file_name = std::string(directoryName) + std::string(entity->d_name);
            if (file_name.c_str())
            {
                name = entity->d_name;
                if (name != "." && name != ".." && name[name.length()] != '.')
                {
                    //std::cout << file_name.c_str() << std::endl;
                    std::string dire = std::string(directoryName) + std::string(entity->d_name) + "/";
                    if (is_txt_extintion(file_name))
                        files_path.push_back(file_name);
                    temp = FileLister((const char*)dire.c_str());
                    files_path.insert(files_path.end(),temp.begin(),temp.end());
                }
            } else {
                std::cout << file_name.c_str() << std::endl;
            }
        }
        closedir (targetDirectory);
    }
    else
        return temp;

    return files_path;
}

bool is_txt_extintion(const std::string &file)
{
    size_t len = file.length();
    return file[len -1] == 't' && file[len -2] == 'x' && file[len - 3] == 't' && file[len - 4] == '.';
}


std::string read_file(const std::string &file_path)
{
    std::ifstream infile ( file_path.c_str() );
    std::string file_contents ( (std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    return file_contents;
}