#include "histogram.h"

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "names.h"

#define NUM_HASHES 512

// container for args //passed one time never changed
struct pthread_args {
    struct queue* q;
    // pthread_mutex_t count_mutex;
    char* buffer; // 8 bytes
    int histogram[NNAMES]; // 8 bytes
};

struct queue {
    struct node *head;
    struct node *tail;
    pthread_mutex_t mtx;// = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cv;// = PTHREAD_COND_INITIALIZER;
    char queue_empty;
};

struct queue* make_queue() {
    struct queue *q = (struct queue*)malloc(sizeof(struct queue));
    q->head = NULL;
    q->tail = NULL;
    pthread_mutex_init(&(q->mtx), NULL);
    pthread_cond_init(&(q->cv), NULL);
    q->queue_empty = 1; // Initially the queue is empty
    return q;
}

struct node {
    int start_block;
    int end_block;
    struct node* next;
    char d[48];
};

void enqueue(struct queue* q, int start, int end) {
    struct node* node = (struct node*)malloc(sizeof(node));
    node->start_block = start;
    node->end_block = end;
    node->next = NULL;
    pthread_mutex_lock(&(q->mtx));
    if (q->tail == NULL) {
        q->head = node;
        q->tail = node;
    } else {
        q->tail->next = node;
        q->tail = node;
    }
    q->queue_empty = 0;
    pthread_cond_signal(&q->cv);
    pthread_mutex_unlock(&q->mtx);
}

struct node* dequeue(struct queue* q) {
    struct node* node = NULL;
    pthread_mutex_lock(&q->mtx);
    while(q->queue_empty) // wait for items
        pthread_cond_wait(&q->cv, &q->mtx);
    if (q->head != NULL) {
        node = q->head;
        q->head = q->head->next;
        node->next = NULL; // Disconnect
        if (q->head == NULL) {// Queue is now empty
            q->tail = q->head;
            q->queue_empty = 1;
        }
    }
    pthread_mutex_unlock(&q->mtx);
    return node;
}


void* process_blocks(void* args_ptr) {

    struct pthread_args* arg = (struct pthread_args*)args_ptr;
    for(int i=0; i<NNAMES; i++) arg->histogram[i] = 0;
    while (1) {
        struct node* node = dequeue(arg->q);
        int start_block = node->start_block;
        int end_block = node->end_block;
        char done = (start_block == -1) ? 1 : 0;
        //printf("Start:%d End%d\n", start_block, end_block);
        free(node);
        if (done) break;
        else {
            char current_word[20] = "";
            int c = 0;
            for (int i=start_block; i<end_block; i++) {
                if (isalpha(arg->buffer[i]) && i%CHUNKSIZE!=0) {
                    current_word[c++] = arg->buffer[i];
                } else {
                    current_word[c] = '\0';
                    int res = getNameIndex(current_word);
                    if (res != -1) {
                        //pthread_mutex_lock(&(arg->count_mutex));
                        arg->histogram[res]++;
                        //pthread_mutex_unlock(&(arg->count_mutex));
                    }
                    c = 0;
                }
            }
        }
    }
    return NULL;
}


void get_histogram(char *buffer, int* histogram, int num_threads) {
    pthread_t* threads = (pthread_t*)calloc(num_threads, sizeof(pthread_t));
    struct pthread_args *args = (struct pthread_args*)calloc(num_threads, sizeof(struct pthread_args));
    for (int i=0; i<num_threads; ++i) {
        args[i].q = make_queue();
        // pthread_mutex_init(&(args[i].count_mutex), NULL);
        args[i].buffer = buffer;
        // args[i].histogram = histogram;
        pthread_create(threads+i , NULL, &process_blocks, args + i);
    }
    int start_block = 0;
    int tid = 0;
    long increment = CHUNKSIZE*20;
    for (int i = 0; buffer[i]!=TERMINATOR; i+=CHUNKSIZE) { 
        // We still need to go one by one cause we dont know the length of the buffer
        if (buffer[i+1]==TERMINATOR || i%increment == 0) {
            enqueue(args[tid].q, start_block, i+1);
            // printf("Gave work: %d to %d\n", start_block, i+1);
            start_block = i+1; // For the next time
            tid = (tid + 1) % num_threads;
        }
    }
    // Closing work
    for (int i=0; i<num_threads; i++) {
        enqueue(args[i].q, -1, -1);
    }
    for (int i=0; i<num_threads; i++) {
        pthread_join(threads[i], NULL);
        for (int j=0; j<NNAMES; j++) {
            histogram[j] += args[i].histogram[j];
        }
    }
    free(threads);
}
