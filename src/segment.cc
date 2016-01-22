#include "segment.h"
#include <cstdlib>

namespace oop_project {

const size_t Segment::kMaxCars = 5;

Segment::Segment(size_t capacity, Segment* prev, int ready_percent,
                 size_t num_junctions, size_t toll_pass_limit)
    : capacity_(capacity),
      enter_junction_(new Junction(num_junctions, toll_pass_limit)),
      next_(NULL),
      prev_(prev),
      ready_percent_(ready_percent) {
  size_t num_cars = std::min(capacity_, rand() % kMaxCars + 1);
  cars_.resize(num_cars);
  for (size_t i = 0; i < cars_.size(); ++i) {
    size_t exit_junction = rand() % (num_junctions - enter_junction_->id()) +
                           enter_junction_->id();
    cars_[i] = new Car(exit_junction, NULL);
  }
}

Segment::~Segment() {
  for (size_t i = 0; i < cars_.size(); ++i) {
    delete cars_[i];
  }
  delete enter_junction_;
}

void Segment::Enter() {
  size_t max_allowed_cars;
  std::vector<Car*> passed_cars;
  if (prev_ != NULL) {
    max_allowed_cars = capacity_ - cars_.size();
    passed_cars = prev_->Pass(max_allowed_cars);
    cars_.insert(cars_.end(), passed_cars.begin(), passed_cars.end());
  }

  max_allowed_cars = capacity_ - cars_.size();
  passed_cars = enter_junction_->Operate(max_allowed_cars);
  cars_.insert(cars_.end(), passed_cars.begin(), passed_cars.end());
}

void Segment::Exit() {
  for (size_t i = 0; i < cars_.size(); ++i) {
    if (cars_[i]->ready() &&
        cars_[i]->exit_junction() == enter_junction_->id() + 1) {
      delete cars_[i];
      cars_.erase(cars_.begin() + i);
    }
  }
}

void Segment::Operate() {
  Exit();
  Enter();

  std::random_shuffle(cars_.begin(), cars_.end());
  size_t num_new_ready = ready_percent_ * cars_.size() / 100;
  size_t num_changed_cars = 0;
  for (size_t i = 0; i < cars_.size(); ++i) {
    if (num_changed_cars == num_new_ready) {
      break;
    }
    if (!cars_[i]->ready()) {
      cars_[i]->set_ready(true);
      ++num_changed_cars;
    }
  }
}

std::vector<Car*> Segment::Pass(size_t max_allowed_cars) {
  std::vector<Car*> ret;
  for (size_t i = 0; i < cars_.size(); ++i) {
    if (ret.size() == max_allowed_cars) {
      break;
    }
    if (cars_[i]->ready() &&
        cars_[i]->exit_junction() != enter_junction_->id() + 1) {
      ret.push_back(cars_[i]);
      cars_.erase(cars_.begin() + i);
    }
  }
  return ret;
}

size_t Segment::num_cars() const {
  return cars_.size();
}

std::vector<Car*> Segment::ready_cars() const {
  std::vector<Car*> ret;
  for (size_t i = 0; i < cars_.size(); ++i) {
    if (cars_[i]->ready()) {
      ret.push_back(cars_[i]);
    }
  }
  return ret;
}

size_t Segment::enter_junction() const {
  return enter_junction_->id();
}

void Segment::set_next(Segment* next) {
  next_ = next;
}

}  // namespace oop_project
