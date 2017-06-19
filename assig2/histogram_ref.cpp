#include "histogram.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "names.h"

void get_histogram_ref(char *buffer, int* histogram)
{
	char current_word[20] = "";
	int c = 0;
	for (int i=0; buffer[i]!=TERMINATOR; i++) {
		if(isalpha(buffer[i]) && i%CHUNKSIZE!=0 ){
			current_word[c++] = buffer[i];
		} else {
			current_word[c] = '\0';
			int res = getNameIndex(current_word);
			if (res != -1)
				histogram[res]++;
			c = 0;
		}
	}
}
