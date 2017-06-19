#include "histogram.h"
#include "names.h"
#include<iostream>
// #include <future>
#include <thread>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

void get_counts(const std::vector<word_t>& words, uint** histogram, uint start, uint end) {
    *histogram = new uint[NNAMES]();
    cout<<"start:"<<start<<" end:"<<end<<endl;
    for(uint i=start; i<end; ++i) {
        int res = getNameIndex(words[i].data());
        if (res != -1) (*histogram)[res]++;
    }
}

void get_histogram(const std::vector<word_t>& words, histogram_t& histogram, int num_threads)
{
    size_t size = words.size();
    uint batchSize = size/num_threads;
    thread *t = new thread[num_threads];
    uint* histograms[64];
    for (int i=0; i<num_threads;i++) {
        uint start = i*batchSize;
        uint step = start+batchSize;
        uint end = (step < size) ? step : size;
        //cout<<"ostart:"<<start<<" oend:"<<end<<endl;
        t[i] = thread(get_counts, std::ref(words),histograms + i,start,end);
    }
    for (int i=0; i<num_threads; i++) {
        t[i].join();
        for (uint j=0; j<NNAMES; j++)
            histogram[j]+= histograms[i][j];
        // delete[] histograms[i];
    };
    delete[] t;
}
