#ifndef TOPCOMMONWORDS_TOPCOMMONWORDS_H
#define TOPCOMMONWORDS_TOPCOMMONWORDS_H

#include <map>
#include <string>
#include <vector>

inline constexpr std::string_view PUNCTUATION = R"(\,.:;"|!@#$%^&*()_+-=[]{}<>?/~`')";

inline const std::vector<std::string> IGNORED_WORDS = {"a", "an", "and", "in", "is", "it", "the"};

std::string strip(const std::string& word);

std::string lower(const std::string& word);

std::map<std::string, int> count_words(std::istream& in);

std::vector<std::pair<int, std::vector<std::string>>> rank_words(const std::map<std::string, int>& counts);

void print_top(const std::vector<std::pair<int, std::vector<std::string>>>& ranked, int n);

#endif //TOPCOMMONWORDS_TOPCOMMONWORDS_H
