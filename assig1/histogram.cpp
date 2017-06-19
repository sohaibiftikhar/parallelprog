#include <stdio.h>

#include "histogram.h"

#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))
#define NLINES 20

// get the maximum number of characters per letter
int max_chars(histogram_t histogram) {
	int max = 0;

	for (int i=0; i<NNAMES; ++i)
		max = MAX(histogram[i], max);

	return max;
}

void print_histogram(histogram_t histogram) {

	int max = max_chars(histogram);
	int y;

	// print line by line
	for (int i=NLINES; i>=0; i--) {

		// calculate and print y labels
		y = (i*max) / NLINES;
		printf("%10d:", y);

		// print histogram with proper spacing
		for (int j=0; j<NNAMES; j++) {
			if(j==0) {
				if (histogram[j] >= y)
				printf("%4c|", 0);
				else
				printf("%5c", 0);
			}
			else if(j<3){
				if (histogram[j] >= y)
				printf("%7c|", 0);
				else
				printf("%8c", 0);
			}

			else if(j<7) {
				if (histogram[j] >= y)
				printf("%9c|", 0);
				else
				printf("%10c", 0);
			}
			else {
				if (histogram[j] >= y)
				printf("%6c|", 0);
				else
				printf("%7c", 0);
			}
		}
		printf("\n");
	}

	// print x labels
	printf("%12c", 0);
	for (int j=0; j<NNAMES; j++) {
		printf("%2c%s", 0, names[j]);
	}
}
