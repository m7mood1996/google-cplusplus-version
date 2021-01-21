//
// Created by mahmood on 1/18/21.
//

#include <cstddef>
#include <fstream>
#include <iostream>
#include "Auto_complation_trie.h"
#include "utils.h"



Auto_complation_node::~Auto_complation_node()
{
}

Auto_complation_node::Auto_complation_node(char ch, bool root):m_ch(ch),root(root)
{

}

bool Auto_complation_node::is_empty()
{

    return m_cheldrens.empty();
}


Auto_complation_node *Auto_complation_trie::get_Node(char ch)
{

    return new Auto_complation_node(ch,false);
}

void Auto_complation_trie::insert(const std::string &prefix)
{
    if (prefix[0] < 65 or prefix[0] > 122)
        return;
    bool found;
    Auto_complation_node *pCrawl = m_root;
    size_t length = prefix.length();
    for (size_t i = 0; i < length; ++i)
    {
        if (i > 0 and (prefix[i] < 65 or prefix[i] > 122) and (prefix[i - 1] < 65 or prefix[i - 1] > 122))
            continue;
        found = false;
        for (size_t child_index = 0; child_index < pCrawl->m_cheldrens.size(); ++child_index){
            if (pCrawl->m_cheldrens[child_index]->m_ch == prefix[i])
            {
                pCrawl = pCrawl->m_cheldrens[child_index];
                found = true;
                break;
            }
        }
        if (!found)
        {
            Auto_complation_node * newNode = get_Node(prefix[i]);
            pCrawl->m_cheldrens.push_back( newNode);
            pCrawl = newNode;
        }

    }

}

std::vector<std::string> Auto_complation_trie::find_all_candidates(Auto_complation_node *node, std::string sentince)
{
    std::vector<std::string> sentince_candidate;
    std::vector<std::string> temp;
    if (node->is_empty())
    {
        sentince_candidate.push_back( sentince + node->m_ch);
        return sentince_candidate;
    }
    else
    {
        sentince = sentince + node->m_ch;
        for (size_t index = 0; index < node->m_cheldrens.size(); ++index)
        {
            temp = Auto_complation_trie::find_all_candidates(node->m_cheldrens[index], sentince);
            sentince_candidate.insert(sentince_candidate.end(), temp.begin(), temp.end());

        }

    }
    return sentince_candidate;
}

std::vector<std::string> Auto_complation_trie::auto_complation(const std::string &key){
    std::vector<std::string> candidates;
    std::vector<std::string> temp;
    Auto_complation_node* node = m_root;
    size_t length = key.length();

    for (size_t level = 0; level < length; ++level)
    {

        for (size_t index = 0; index < node->m_cheldrens.size(); ++index)
        {
            if ( node->m_cheldrens[index]->m_ch == key[level])
            {
                node = node->m_cheldrens[index];
                break;

            }
        }


        if (node->is_empty())
        {
            candidates.push_back(key);
            return candidates;
        }
    }

    for (size_t index = 0; index < node->m_cheldrens.size(); ++index)
    {
        if ( node->is_empty())
            continue;
        temp = Auto_complation_trie::find_all_candidates(node->m_cheldrens[index], key);
        candidates.insert(candidates.end(), temp.begin(), temp.end());
    }

    return candidates;
}

void Auto_complation_trie::fill_model(const std::string &directory_path)
{
    std::vector< std::string> all_files_path = get_all_files_paths(directory_path);
    size_t len = all_files_path.size();
    for (size_t i = 0; i < len; ++i)
    {
        std::cout << "file number: " << i << std::endl;
        process_file(all_files_path[i]);
    }

}

void Auto_complation_trie::process_file(std::string &file_path)
{
    std::ifstream file (file_path.c_str()); //file just has some sentences
    if (!file) {
        return;
    }
    std::string line;
    while (getline (file, line))
        processLine(line);

    file.close();

}

void Auto_complation_trie::processLine(std::string line)
{
    size_t len = line.length();
    size_t i = 0;
    string_to_lower(line);
    std::string prefix = line;

    while (i < len)
    {
        if(prefix != "" and prefix != "\r\n" and prefix != "\n" and prefix != "\r" ) {

            insert(prefix);
        }
        prefix = line.substr(i+1,len);
        ++i;
    }

}

Auto_complation_trie::Auto_complation_trie()
{
    m_root = new Auto_complation_node(0,true);
}

void Auto_complation_trie::string_to_lower(std::string &str)
{
    for (size_t i =0; i < str.length(); ++i)
    {
        str[i] = tolower(str[i]);
    }

}
