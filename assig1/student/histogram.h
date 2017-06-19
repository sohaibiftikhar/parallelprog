#ifndef HISTOGRAM_H_
#define HISTOGRAM_H_

#define BLOCKSIZE 8192 	// block size in byte
#define BYTESIZE 8 		// bits per byte
#define NNAMES 10 //number of names to search in the book

typedef char block_t[BLOCKSIZE];
typedef int histogram_t[NNAMES];

//The names to be searched in the book
static char const *names[NNAMES] __attribute__((unused)) = {"Pierre","Andrew","Nicholas","Natasha","Napoleon","Dolokhov","Anatole","Anna","Sonya","Boris"};

// produce histogram from blocks to histogram
void get_histogram(int nBlocks,
		           block_t *blocks,
		           int* histogram,
		           int num_threads);

// dump histogram to stdout
void print_histogram(histogram_t histogram);

#endif /* HISTOGRAM_H_ */
