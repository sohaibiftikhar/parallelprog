#ifndef HISTOGRAM_H_
#define HISTOGRAM_H_

#define BYTESIZE 8 		// bits per byte
#define NALPHABET 26	// number of letters in the alphabet
#define CHUNKSIZE 8192	// number of chunks for a task
#define TERMINATOR (char)255
#define NNAMES 10 //number of names to search in the book

typedef int histogram_t[NNAMES];
//The names to be searched in the book
static char const *names[NNAMES] __attribute__((unused)) = {"Pierre","Andrew","Nicholas","Natasha","Napoleon","Dolokhov","Anatole","Anna","Sonya","Boris"};

// produce histogram from blocks to histogram
void get_histogram(char *input,
				   int* histogram,
				   int num_threads);

// dump histogram to stdout
void print_histogram(histogram_t histogram);

#endif /* HISTOGRAM_H_ */
