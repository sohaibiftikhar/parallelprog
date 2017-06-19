#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "histogram.h"

#define NUM_HASHES 512
// container for args
struct pthread_args {
    int start_block; // 4 bytes 
    int end_block;  // 4 bytes
    block_t* blocks; // 4 bytes
    long *hashes; // 4 bytes
    histogram_t histogram; // NNAMES * 4bytes = 40
    char c[8]; //padding to fill up 64 bytes
};

// simplistic hash function but may work in this case
// http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash_word(const char *str)
{
    unsigned long hash = 5381;
    // printf("hash called for: %s\n", str);
    while (*str) { // while c is not zero
        hash = ((hash << 5) + hash) + *str++; /* hash * 33 + c */
    }

    return hash;
}


void* process_blocks(
        int start_block, 
        int end_block, 
        block_t* blocks, 
        long* hashes, 
        histogram_t histogram) {
    char current_word[20] = "";
    int c = 0;
    // initialize to zero
    for (int i=0; i<NNAMES; i++) histogram[i] = 0;

    // printf("Start:%d End%d\n", start_block, end_block);
    for (int i = start_block; i < end_block; i++) {
        for (int j = 0; j < BLOCKSIZE; j++) {
            // if the character is an alphabet store it to form a word.
            if (isalpha(blocks[i][j])){
                 current_word[c++] = blocks[i][j];
            }
            // if the character is not an alphabet it is the end of a word.
            // Compare the word with the list of names.
            else {
                current_word[c] = '\0';
                unsigned long hash = hash_word(current_word) % NUM_HASHES;
                if (hashes[hash] == 1) {
                    for (int k = 0; k < NNAMES; k++) {
                        if (!strcmp(current_word, names[k])) {
                            histogram[k]++;
                        }
                    }
                }
                c = 0;
            }
        }
    } 
    return NULL;
}

void* process_blocks_wrapper(void* args_ptr) {
    struct pthread_args* arg = (struct pthread_args*)args_ptr; 
    return process_blocks(arg->start_block, arg->end_block, arg->blocks, arg->hashes, arg->histogram);
}


void get_histogram(int nBlocks, block_t *blocks, histogram_t histogram, int num_threads)
{
	// write your parallel solution here
    long hashes[NUM_HASHES] = {0};
    for (int i=0; i<NNAMES; ++i) {
        hashes[hash_word(names[i]) % NUM_HASHES] = 1;
    }
    pthread_t* threads = (pthread_t*)calloc(num_threads, sizeof(pthread_t));
    struct pthread_args *args = (struct pthread_args*)malloc(sizeof(struct pthread_args)*num_threads); 
    int increment = nBlocks/num_threads;
    int current_start = 0;
    for (int i=0; i<num_threads; ++i) {
        args[i].start_block = current_start;
        args[i].end_block = ((i < num_threads-1) ? current_start + increment : nBlocks);
        args[i].blocks = blocks;
        args[i].hashes = hashes;
        current_start  = args[i].end_block;
        pthread_create(threads+i , NULL, &process_blocks_wrapper , args + i);
    }
    for (int i=0; i<num_threads; i++) {
        pthread_join(threads[i], NULL);
        // Merge histograms
        for (int j=0; j<NNAMES; j++) {
            histogram[j] += args[i].histogram[j];
        }
    }
    
    free(args);
    free(threads);
}
