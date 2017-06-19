#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <cstring>

#include "histogram.h"
#include "histogram_ref.h"

int main(int argc, char **argv)
{
	int failed = 0;
	histogram_t histogram_ref = {{0}};
	char const *filename = "war_and_peace.txt";

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

	// build the histograms
	get_histogram_ref(*words.get(), histogram_ref);

	for (int nThreads = 1; nThreads <= 8; nThreads++) {
		histogram_t histogram = {{0}};		
		get_histogram(*words.get(), histogram, nThreads);
		for (int i = 0; i < NNAMES; i++) {
			if (histogram_ref[i] != histogram[i]) {
				fprintf(stderr, "Computation with %d threads failed:\n", nThreads);
				fprintf(stderr, "Wrong result for %s: %d (correct: %d)\n",
						names[i], histogram[i], histogram_ref[i]);
				failed = 1;
				break;
			}
		}
		if (failed)
			break;
	}
	/* end test */

	return failed;
}
