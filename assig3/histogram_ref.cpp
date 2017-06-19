#include "histogram.h"
#include <algorithm>

#include "names.h"

void get_histogram_ref(const std::vector<word_t>& words, histogram_t& histogram)
{
	for_each(begin(words), end(words), [&histogram](const word_t& word)
	{
		int res = getNameIndex(word.data());
		if (res != -1) histogram[res]++;
	});
}
