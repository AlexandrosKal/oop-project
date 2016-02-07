#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "freeway.h"
#include "size_types.h"

int main(int argc, char** argv) {
  unsigned seed = time(NULL);
  int simulation_steps = 10;
  size_t num_segments = 5;
  size_t pass_limit = 10;
  int ready_percent = 30;
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
      sscanf(argv[i], "%" PRIuS, &pass_limit);
    } else if (strcmp("-Percent", argv[i]) == 0) {
      ++i;
      ready_percent = atoi(argv[i]);
    }
  }
  printf("Seed: %u\n"
         "N: %d\n"
         "NSegs: %" PRIuS "\n"
         "K: %" PRIuS "\n"
         "Percent: %d\n",
         seed, simulation_steps, num_segments, pass_limit, ready_percent);

  srand(seed);

  std::vector<size_t> capacities(num_segments);
  for (size_t i = 0; i < capacities.size(); ++i) {
    scanf("%" PRIuS, &capacities[i]);
  }

  project::Freeway freeway(capacities, ready_percent, pass_limit);
  printf("Cars: %" PRIuS "\n", freeway.num_cars());
  for (int i = 0; i < simulation_steps; ++i) {
    printf("\nOperation: %d\n", i + 1);
    freeway.Operate();
  }

  return 0;
}
