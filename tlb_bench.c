/*
 * tlb_bench.c
 *
 *  Created on: 2015年12月10日
 *      Author: hexin
 */
#if __linux
#define _GNU_SOURCE
#include <sched.h>
#endif

#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <errno.h>

 int repetitions=100000;
 int num_pages=1024;

static inline uint32_t pow2roundup (uint32_t x){
  if (x==0) return 1;
  --x;
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;
  return x+1;
}
int main(int argc, char **argv) {

#if __linux
    #define CPUSETSIZE 8
    // pin this thread to one CPU
    int cpu = sched_getcpu();
    printf("# running on CPU %d; pinning to that CPU\n", cpu);
    cpu_set_t *cpu_set = CPU_ALLOC(CPUSETSIZE);
    size_t size = CPU_ALLOC_SIZE(CPUSETSIZE);
    CPU_ZERO_S(size, cpu_set);
    CPU_SET_S(cpu, size, cpu_set);
    pid_t pid = getpid();

    int rv = sched_setaffinity(pid, CPU_ALLOC_SIZE(CPUSETSIZE), cpu_set);
    if (rv < 0) {
        fprintf(stderr, "Error pinning thread to a CPU: %s\n", strerror(errno));
    }
#endif // __linux

	 struct option long_options[] = {
	    // These options don't set a flag
	    {"help",                      no_argument,       NULL, 'h'},
	    {"repetitions",                  required_argument, NULL, 'r'},
	    {"num-pages",              required_argument, NULL, 'n'},
	    {NULL, 0, NULL, 0}
	  };

	 int i, c;
	   while(1)
	     {
	       i = 0;
	       c = getopt_long(argc, argv, "hn:r:", long_options, &i);

	       if(c == -1)
	 	break;

	       if(c == 0 && long_options[i].flag == 0)
	 	c = long_options[i].val;

	       switch(c)
	 	{
	 	case 0:
	 	  /* Flag is automatically set */
	 	  break;
	 	case 'h':
	 	  printf("tlb test "
	 		 "\n"
	 		 "Usage:\n"
	 		 "  executable [options...]\n"
	 		 "\n"
	 		 "Options:\n"
	 		 "  -h, --help\n"
	 		 "        Print this message\n"
	 		 "  -r, --repetitions <int>\n"
	 		 "        Repetitions of the test case (default=100000)\n"
	 		 "  -n, --num-pages <int>\n"
	 		 "        Number of pages to access during test\n"
	 		 );
	 	  exit(0);
	 	case 'n':
	 	  num_pages = atoi(optarg);
	 	  break;
	 	case 'r':
	 	  repetitions = atol(optarg);
	 	  break;
	 	case '?':
	 	default:
	 	  printf("Use -h or --help for help\n");
	 	  exit(1);
	 	}
	     }

    int page_size = getpagesize();
    printf("# page size is %d\n", page_size);
    num_pages=pow2roundup(num_pages);
	 const int array_length = (page_size * num_pages)/sizeof(int);
	 int *array_ptr = (int*)malloc(array_length*sizeof(int));
//	 memset(array,0,sizeof(array));
	 int jump=page_size/sizeof(int);
	 int access_pages=1;
	volatile int  *array=array_ptr;//每次都从内存读取，屏蔽cache的影响
	 for (i = 0; i < array_length; ++i) {
		array[i]=0;
	}
	  while(access_pages<=num_pages) {
			  int r=0;
			  uint64_t total;
			  struct timeval start, end;
			  total = 0ULL;
			  uint64_t sample_count = 0;
			  for(r=0;r<repetitions;r++) {
				  	  i=0;
					 for(;i<access_pages*jump;i+=jump) {
						  gettimeofday(&start, NULL);
						  array[i]+=1;
						  gettimeofday(&end, NULL);
						  total+=(end.tv_sec * 1000000000 + end.tv_usec *1000) - (start.tv_sec * 1000000000 + start.tv_usec * 1000);
				         sample_count += 1;
					 }
			  }
			  uint64_t time_average = total / sample_count;
		      printf("%d\taverage nanoseconds per access:%llu\n", access_pages, (long long unsigned int)time_average);
		      access_pages*=2;
	  }
	 array=NULL;
      free (array_ptr);
  #if __linux
      CPU_FREE(cpu_set);
  #endif
      return 0;
}


