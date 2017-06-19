#include <iostream>
#include <chrono>
#include <vector>
#include <cstring>
#include <array>
#include <fstream>
#include <string>
#include <memory>
#include <algorithm>
#include <sstream>
#include <iterator>

#include "histogram.h"

int main(int argc, char** argv)
{
    histogram_t histogram {{ 0 }};
    char const *filename = "war_and_peace.txt";
    long num_threads = 1, repetitions = 0;

    // argument handling
    if (argc < 2 || argc > 4) {
        printf("usage: %s filename [#threads] [#repetition]\n", argv[0]);
        return 1;
    }
    if (argc >= 2)
        filename = argv[1];
    if (argc >= 3)
        if ((num_threads = strtol(argv[2], NULL, 0)) == 0 || num_threads < 0) {
            fprintf(stderr, "#threads not valid!\n");
            return 1;
        }
    if (argc >= 4)
        if ((repetitions = strtol(argv[3], NULL, 0)) == 0 || repetitions < 0) {
            fprintf(stderr, "#repetition not valid!\n");
            return 1;
        }

    std::cout << "\nProcess " << filename << " by " << num_threads << " with "
              << repetitions << " repetition(s)\n\n";

    std::ifstream file(filename, std::ios::binary);
    if (file.fail()) {
        std::cerr << "Could not open file " << filename;
        exit(EXIT_FAILURE);
    }

    std::string str = read_stream_into_string(file);

    // copy all words into a vector of predetermined size of character arrays with size 8
    auto words = std::make_unique<std::vector<word_t>>(WORDCOUNT);
    char const * word = nullptr;
    int count = 0, wordCount = 0;

    for (unsigned int i = 0; i < str.size(); ++i) {
        if (str[i] < 0 || (!std::isalnum(str[i]) && str[i] != '_')) {
            if (word) {
                auto currentWord = &words.get()->at(wordCount++);
                std::memcpy(currentWord, word, std::min(count, 8));
            }
            word = nullptr;
        } else if (!word) {
            word = &str[i];
            count = 0;
        }
        count++;
    }

    // replicate vector
    if (repetitions) {
        auto copy = *words.get();
        for (int i = 0; i < repetitions; ++i)
            words->insert(std::end(*words), std::begin(copy), std::end(copy));
    }

    // build the histogram
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    start = std::chrono::steady_clock::now();
    get_histogram(*words.get(), histogram, num_threads);
    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    print_histogram(histogram);
    std::cout << "\nTime: " << elapsed_seconds.count() << " seconds\n";

    return 0;
}
