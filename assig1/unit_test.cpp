#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "histogram.h"
#include "histogram_ref.h"

int main(int argc, char **argv)
{
	int nThreads, i, failed = 0;
	//histogram_t histogram = {0}, histogram_ref = {0};
	histogram_t histogram_ref = {0};
	struct stat st;
	int nBlocks;
	block_t *blocks;
	char const *filename = "war_and_peace.txt";

	// get file size and allocate array
	stat(filename, &st);
	nBlocks = st.st_size / BLOCKSIZE;
	nBlocks += (st.st_size % BLOCKSIZE) == 0 ? 0 : 1;
	blocks = (block_t*)malloc(nBlocks * BLOCKSIZE * BYTESIZE);


	// open file and read all blocks
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "Could not open file %s", filename);
		exit(EXIT_FAILURE);
	}
	if (fread(blocks, BLOCKSIZE, nBlocks, fp) == 0) {
		fprintf(stderr, "Could not read from file %s", filename);
		exit(EXIT_FAILURE);
	}
	// build the histograms	
	get_histogram_ref(nBlocks, blocks, histogram_ref);


	fclose(fp);

	for (nThreads = 1; nThreads <= 8; nThreads++) {
		//memset(histogram, 0, sizeof(histogram));
		//fprintf(stderr, "%ld\n", sizeof(*blocks));
		// open file and read all blocks
		fp = fopen(filename, "r");
		if (fp == NULL) {
			fprintf(stderr, "Could not open file %s", filename);
			exit(EXIT_FAILURE);
		}
		if (fread(blocks, BLOCKSIZE, nBlocks, fp) == 0) {
			fprintf(stderr, "Could not read from file %s", filename);
			exit(EXIT_FAILURE);
		}
		histogram_t histogram = {0};
		get_histogram(nBlocks, blocks, histogram, nThreads);
		for (i = 0; i < NNAMES; i++) {
			if (histogram_ref[i] != histogram[i]) {
				fprintf(stderr, "Computation with %d threads failed:\n", nThreads);
				fprintf(stderr, "Wrong result for %s: %d (correct: %d)\n",
						names[i], histogram[i], histogram_ref[i]);
				failed = 1;
				break;
			}
		}
		if (failed == 1)
			break;
		fclose(fp);
	}
	/* end test */

	free(blocks);
	return failed;
}
