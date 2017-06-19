#ifndef HISTOGRAM_H_
#define HISTOGRAM_H_

#include <vector>
#include <array>
#include <sstream>

#define BYTESIZE 8 		// bits per byte
#define NALPHABET 26	// number of letters in the alphabet
#define CHUNKSIZE 8192	// number of chunks for a task
#define TERMINATOR (char)255
#define NNAMES 10 //number of names to search in the book
#define WORDCOUNT 576616

static char const *names[NNAMES] __attribute__((unused)) = {"Pierre","Andrew","Nicholas","Natasha","Napoleon","Dolokhov","Anatole","Anna","Sonya","Boris"};

using word_t = std::array<char, 8>;
using histogram_t = std::array<int, NNAMES>;

// produce histogram from blocks to histogram
void get_histogram(const std::vector<word_t>& words,
				   histogram_t& histogram,
				   int num_threads);

// dump histogram to stdout
void print_histogram(histogram_t histogram);

template <typename CharT, typename Traits, typename Allocator = std::allocator<CharT>>
auto read_stream_into_string(std::basic_istream<CharT, Traits>& in, Allocator alloc = {})
{
    std::basic_ostringstream<CharT, Traits, Allocator>
            ss(std::basic_string<CharT, Traits, Allocator>(std::move(alloc)));

    if (!(ss << in.rdbuf())) throw std::ios_base::failure{"error"};

    return ss.str();
}


#endif /* HISTOGRAM_H_ */
