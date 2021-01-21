//
// Created by mahmood on 1/18/21.
//

#ifndef GOOGLE_AUTO_COMPLATION_TRIE_H
#define GOOGLE_AUTO_COMPLATION_TRIE_H

#include <string>
#include <vector>

struct Auto_complation_node{
    char m_ch;
    bool root;
    std::vector<Auto_complation_node *> m_cheldrens;

    bool is_empty();
    Auto_complation_node(char ch, bool root=false);
    ~Auto_complation_node();

private:
    Auto_complation_node();
};

class Auto_complation_trie {


public:
    Auto_complation_trie();
    Auto_complation_node* get_Node(char ch);

    void insert(const std::string &prefix);

    static std::vector< std::string> find_all_candidates(Auto_complation_node* node, std::string sentince);

    std::vector< std::string> auto_complation(const std::string &key);

    void fill_model(const std::string& files_path);



private:


    void process_file(std::string &file_path);

    void processLine(std::string line);

    void string_to_lower(std::string &str);


    Auto_complation_node* m_root;
};


#endif //GOOGLE_AUTO_COMPLATION_TRIE_H
