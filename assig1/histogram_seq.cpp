#include "histogram.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

void get_histogram(int nBlocks,
		   						 block_t *blocks,
		               int* histogram,
		               int num_threads)
{
	char current_word[20] = "";
	int c = 0;

	// loop over every character
	for (int i = 0; i < nBlocks; i++) {
		for (int j = 0; j < BLOCKSIZE; j++) {

			// if the character is an alphabet store it to form a word.
			if(isalpha(blocks[i][j])){
				current_word[c++] = blocks[i][j];
			}

			// if the character is not an alphabet it is the end of a word.
			// Compare the word with the list of names.
			else {
				current_word[c] = '\0';
				for(int k = 0; k < NNAMES; k++)	{
					if(!strcmp(current_word, names[k]))
						histogram[k]++;
				}
				c = 0;
			}
		}
	}
    for (int i=0; i<NNAMES; i++) {
        printf("%s: %d\n", names[i], histogram[i]);
    }
}
