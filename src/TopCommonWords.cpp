#include <algorithm>
#include <iostream>
#include <ranges>
#include <string>
# include "TopCommonWords.h"

namespace r  = std::ranges;
namespace rv = std::ranges::views;

std::string strip(const std::string& word) {
    auto is_punct = [](char c) {
        return PUNCTUATION.find(c) != std::string_view::npos;
    };
    auto stripped = word
        | rv::drop_while(is_punct)
        | rv::reverse
        | rv::drop_while(is_punct)
        | rv::reverse;
    return std::string(stripped.begin(), stripped.end());
}

std::string lower(const std::string& word) {
    auto lowered = word | rv::transform([](char c) {
        return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    });
    return std::string(lowered.begin(), lowered.end());
}

std::map<std::string, int> count_words(std::istream& in) {
    std::map<std::string, int> counts;

    for (const std::string& raw : r::istream_view<std::string>(in)) {
        std::string word = lower(strip(raw));

        if (word.empty()) { continue; }

        if (r::find(IGNORED_WORDS, word) != IGNORED_WORDS.end()) { continue; }

        ++counts[word];
    }
    return counts;
}

std::vector<std::pair<int, std::vector<std::string>>> rank_words(const std::map<std::string, int>& counts) {
    std::map<int, std::vector<std::string>, std::greater<int>> by_count;
    for (const auto& [word, count] : counts) {
        by_count[count].push_back(word);
    }

    std::vector<std::pair<int, std::vector<std::string>>> ranked;
    for (auto& [count, words] : by_count) {
        r::sort(words);
        ranked.emplace_back(count, std::move(words));
    }
    return ranked;
}

void print_top(const std::vector<std::pair<int, std::vector<std::string>>>& ranked, int n) {
    int displayed = 0;
    int rank = 1;

    for (const auto& [count, words] : ranked) {
        if (displayed >= n) { break; }

        std::cout << rank << ".) These words appeared " << count << " times: {";

        for (int i = 0; i < static_cast<int>(words.size()); ++i) {
            if (i > 0) { std::cout << ", "; }
            std::cout << words[i];
        }
        std::cout << "}\n";

        ++rank;
        ++displayed;
    }
}