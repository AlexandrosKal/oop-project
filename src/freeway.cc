#include "freeway.h"
#include <cstdio>
#include "sizetypes.h"

namespace project {

Freeway::Freeway(size_t num_segments,  size_t segment_ready_percent,
                 const size_t* segment_capacities, size_t toll_pass_limit) {
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
    if (i >= 1) {
      prev->set_next(segments_[i]);
    }
    num_cars_ += segments_[i]->num_cars();
  }
  printf("Aftokinitodromos se leitourgia\n");
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
  printf("Arithmos aftokiniton: %" PRIuS "\n", num_cars_);
}

size_t Freeway::num_cars() const {
  return num_cars_;
}

const std::vector<Segment*>& Freeway::segments() const {
  return segments_;
}

}  // namespace project
