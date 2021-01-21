#include <iostream>

#include "Auto_complation_trie.h"


int main() {

    Auto_complation_trie a;
    a.fill_model("/home/mahmood/Desktop/Google/data/");

    std::vector<std::string> result = a.auto_complation("h");
    return 0;
}
