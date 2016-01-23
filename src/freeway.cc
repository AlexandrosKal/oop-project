#include "freeway.h"

#ifdef _LP64
#define __PRIS_PREFIX "z"
#else
#define __PRIS_PREFIX
#endif

#define PRIuS __PRIS_PREFIX "u"

namespace oop_project {

Freeway::Freeway(size_t num_segments,  size_t segment_ready_percent,
                 const std::vector<size_t>& segment_capacities,
                 size_t toll_pass_limit) {
  num_cars_ = 0;
  size_t current_id = Junction::current_id();
  segments_.resize(num_segments);
  for (size_t i = 0; i < segments_.size(); ++i) {
    Segment* prev = NULL;
    if (i >= 1) {
      prev = segments_[i - 1];
    }

    segments_[i] = new Segment(segment_capacities[i], prev,
                               segment_ready_percent,
                               current_id + num_segments + 1,
                               toll_pass_limit);
    num_cars_ += segments_[i]->num_cars();
  }
  printf("The freeway is in operation.\n");
}

Freeway::~Freeway() {
  for (size_t i = 0; i < segments_.size(); ++i) {
    delete segments_[i];
  }
}

void Freeway::Operate() {
  num_cars_ = 0;
  for (int i = segments_.size() - 1; i >= 0; --i) {
    segments_[i]->Operate();
    num_cars_ += segments_[i]->num_cars();
  }
  printf("Car number: %" PRIuS "\n", num_cars_);
}

const std::vector<Segment*>& Freeway::segments() const {
  return segments_;
}

}  // namespace oop_project
