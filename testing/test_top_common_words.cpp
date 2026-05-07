#include <sstream>
#include <string>
#include <vector>
#include <ranges>
#include "TopCommonWords.h"
#include "gtest/gtest.h"
#include "rapidcheck/gtest.h"

namespace r = std::ranges;
namespace rv = r::views;

TEST(Example, StringStreamInputGeneration) {
    //test content
    const std::string content("Hope you are learning a lot.");
    std::stringstream input_stream(content); //make a string stream over the content
    std::vector<std::string> answer{ //this is just to have something to check against
        "Hope", "you", "are",
        "learning", "a", "lot."
    };

    //iota gives us the values 0, 1, 2, 3, ...
    //zip allows us to iterate over the index, input words, and answers together
    //rv::istream<std::string> causes us to read out one "word" at a time from the string stream
    for (const auto& [index, input_word, answer_word] : rv::zip(rv::iota(0), rv::istream<std::string>(input_stream), answer)) {
        EXPECT_EQ(input_word, answer_word) << input_word << " and " << answer_word << " differ at index " << index;
    }

}