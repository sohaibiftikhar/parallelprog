#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "helper.h"
#include "loop_alignment.h"


#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif


// Use clock_gettime in linux, clock_get_time in OS X.
void get_monotonic_time(struct timespec *ts){
#ifdef __MACH__
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
  clock_get_time(cclock, &mts);
  mach_port_deallocate(mach_task_self(), cclock);
  ts->tv_sec = mts.tv_sec;
  ts->tv_nsec = mts.tv_nsec;
#else
  clock_gettime(CLOCK_MONOTONIC, ts);
#endif
}



unsigned long **get_int64_twodim_array(size_t num)
{
	unsigned long **array = (unsigned long**)malloc(num * sizeof(*array));
	if (array == NULL) {
		fprintf(stderr, "out of memory\n");
		exit(1);
	}

	for (int i = 0; i < num; i++) {
		array[i] = (unsigned long*)malloc(num * sizeof(unsigned long));
		if (array[i] == NULL) {
			fprintf(stderr, "out of memory\n");
			exit(1);
		}
	}
	for (size_t i = 0; i < num; i++)
		for (size_t j = 0; j < num; j++)
			array[i][j] = num - j;

	return array;
}

int main(int argc, char** argv) {

	int N = 100;
	int num_threads = 4;
	int input;

	while ((input = getopt(argc, argv, "t:n:")) != -1)
	{
		switch (input)
		{
		case 't':
			if (sscanf(optarg, "%d", &num_threads) != 1)
				goto error;
			break;

		case 'n':
			if (sscanf(optarg, "%d", &N) != 1)
				goto error;
			break;

		case '?':
			error: printf(
			    "Usage:\n"
			    "-t \t number of threads used in computation\n"
			    "-n \t number of iterations\n"
			    "\n"
			    "Example:\n"
			    "%s -t 4 -n 2500\n", argv[0]);
			exit(EXIT_FAILURE);
			break;
		}
	}

	unsigned long **a = get_int64_twodim_array(N + 1);
	unsigned long **b = get_int64_twodim_array(N + 1);
	unsigned long **c = get_int64_twodim_array(N + 1);
	unsigned long **d = get_int64_twodim_array(N + 1);

	struct timespec begin, end;

	//clock_gettime(CLOCK_REALTIME, &begin);
    get_monotonic_time(&begin);
	compute(a, b, c, d, N, num_threads);
	//clock_gettime(CLOCK_REALTIME, &end);
    get_monotonic_time(&end);

	printf("\nTime: %.3lf seconds\n", ts_to_double(ts_diff(begin, end)));

	free(a);
	free(b);
	free(c);
	free(d);
	return 0;
}

