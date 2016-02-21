#include "freeway.h"
#include <cstdio>
#include "size_types.h"

namespace project {

Freeway::Freeway(const std::vector<size_t>& capacities, int ready_percent,
                 size_t pass_limit) : num_cars_(0) {
  size_t current_id = Junction::current_id();
  segments_.resize(capacities.size());
  for (size_t i = 0; i < segments_.size(); ++i) {
    Segment* prev = NULL;
    if (i >= 1) {
      prev = segments_[i - 1];
    }
    segments_[i] = new Segment(capacities[i], prev, ready_percent,
                               current_id + segments_.size() + 1, pass_limit);
    if (i >= 1) {
      prev->set_next(segments_[i]);
    }
    num_cars_ += segments_[i]->num_cars();
  }
  if (!segments_.empty()) {
    segments_[segments_.size() - 1]->set_exit(new Junction);
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
  for (std::vector<Segment*>::reverse_iterator it = segments_.rbegin();
       it != segments_.rend(); ++it) {
    (*it)->Operate();
    num_cars_ += (*it)->num_cars();
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
