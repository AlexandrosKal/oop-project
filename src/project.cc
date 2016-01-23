#include "freeway.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#ifdef _LP64
#define __PRIS_PREFIX "z"
#else
#define __PRIS_PREFIX
#endif

#define PRIuS __PRIS_PREFIX "u"

int main(int argc, char** argv) {
  unsigned seed = time(NULL);
  int simulation_steps = 10;
  size_t num_segments = 5;
  size_t toll_pass_limit = 10;
  int segment_ready_percent = 30;
  for (int i = 1; i < argc; ++i) {
    if (strcmp("-seed", argv[i]) == 0) {
      ++i;
      sscanf(argv[i], "%u", &seed);
    } else if (strcmp("-N", argv[i]) == 0) {
      ++i;
      simulation_steps = atoi(argv[i]);
    } else if (strcmp("-NSegs", argv[i]) == 0) {
      ++i;
      sscanf(argv[i], "%" PRIuS, &num_segments);
    } else if (strcmp("-K", argv[i]) == 0) {
      ++i;
      sscanf(argv[i], "%" PRIuS, &toll_pass_limit);
    } else if (strcmp("-Percent", argv[i]) == 0) {
      ++i;
      segment_ready_percent = atoi(argv[i]);
    }
  }
  printf("Seed: %u\n"
         "N: %d\n"
         "NSegs: %" PRIuS "\n"
         "K: %" PRIuS "\n"
         "Percent: %d\n",
         seed, simulation_steps, num_segments, toll_pass_limit,
         segment_ready_percent);

  size_t* segment_capacities = new size_t[num_segments];
  for (size_t i = 0; i < num_segments; ++i) {
    scanf("%" PRIuS, segment_capacities + i);
  }

  oop_project::Freeway freeway(num_segments, segment_ready_percent,
                               segment_capacities, toll_pass_limit);
  printf("Cars: %" PRIuS "\n", freeway.num_cars());
  for (int i = 0; i < simulation_steps; ++i) {
    printf("\nOperation: %d\n", i + 1);
    freeway.Operate();
  }

  delete[] segment_capacities;
  return 0;
}
