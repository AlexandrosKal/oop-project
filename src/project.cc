#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "freeway.h"
#include "size_types.h"

static bool Equals(const char* a, const char* b) {
  if (a[0] == '-') {
    return Equals(a + 1, b);
  }
  if (b[0] == '-') {
    return Equals(a, b + 1);
  }

  size_t a_len = strlen(a);
  if (a_len != strlen(b)) {
    return false;
  }
  for (size_t i = 0; i < a_len; ++i) {
    if (tolower(a[i]) != tolower(b[i])) {
      return false;
    }
  }
  return true;
}

int main(int argc, char** argv) {
  unsigned seed = time(NULL);
  int simulation_steps = 10;
  size_t num_segments = 5;
  size_t pass_limit = 10;
  int ready_percent = 30;
  for (int i = 1; i < argc; ++i) {
    if (Equals(argv[i], "seed")) {
      ++i;
      sscanf(argv[i], "%u", &seed);
    } else if (Equals(argv[i], "n")) {
      ++i;
      simulation_steps = atoi(argv[i]);
    } else if (Equals(argv[i], "nsegs")) {
      ++i;
      sscanf(argv[i], "%" PRIuS, &num_segments);
    } else if (Equals(argv[i], "k")) {
      ++i;
      sscanf(argv[i], "%" PRIuS, &pass_limit);
    } else if (Equals(argv[i], "percent")) {
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

  printf("Enter the capacities: ");
  std::vector<size_t> capacities(num_segments);
  for (size_t i = 0; i < capacities.size(); ++i) {
    scanf("%" PRIuS, &capacities[i]);
  }

  printf("\n");
  project::Freeway freeway(capacities, ready_percent, pass_limit);
  printf("Arithmos aftokiniton: %" PRIuS "\n", freeway.num_cars());
  for (int i = 0; i < simulation_steps; ++i) {
    printf("\nOperation: %d\n", i + 1);
    freeway.Operate();
  }
  return 0;
}
