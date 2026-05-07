#include <iostream>
#include <fstream>
#include "TopCommonWords.h"

int main(int argc, char** argv) {
    std::cout << "Usage: ./TopCommonWords path_to_file [num_words_to_find]" << std::endl;

    const std::string path = argv[1];
    const int n = (argc >= 3) ? std::stoi(argv[2]) : 10;  // default N = 10

    // Open file for reading only (ifstream, not fstream — needs read perms only)
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Error: could not open file: " << path << "\n";
        return 1;
    }

    const auto counts = count_words(file);
    const auto ranked = rank_words(counts);
    print_top(ranked, n);

    return 0;
}
