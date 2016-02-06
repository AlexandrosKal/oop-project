#include "segment.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include "size_types.h"

namespace project {

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
                           enter_junction_->id() + 1;
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
  size_t max_allowed_cars, ready_cars_before_pass = 0, num_passed_cars = 0;
  if (prev_ != NULL) {
    size_t num_cars_before_pass = cars_.size();
    ready_cars_before_pass = prev_->ready_cars().size();
    max_allowed_cars = capacity_ - cars_.size();
    prev_->Pass(max_allowed_cars);
    num_passed_cars = cars_.size() - num_cars_before_pass;
  }

  size_t cars_before_enter = enter_junction_->Cars().size();
  max_allowed_cars = capacity_ - cars_.size();
  std::vector<Car*> cars = enter_junction_->Operate(max_allowed_cars);
  if (cars.size() < cars_before_enter) {
    printf("Kathysteriseis stin eisodo tou komvou %" PRIuS "\n",
           enter_junction_->id());

    if (num_passed_cars < ready_cars_before_pass) {
      printf("Kathysteriseis meta ton komvo %" PRIuS "\n",
             enter_junction_->id());
    }
  } else {
    printf("Tireite tis apostaseis asfaleias sto tmima meta ton komvo %" PRIuS
           "\n", enter_junction_->id());
  }
  cars_.insert(cars_.end(), cars.begin(), cars.end());
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

void Segment::Pass(size_t max_allowed_cars) {
  size_t passed_cars = 0;
  for (size_t i = 0; i < cars_.size(); ++i) {
    if (passed_cars == max_allowed_cars) {
      break;
    }
    if (cars_[i]->ready() &&
        cars_[i]->exit_junction() != enter_junction_->id() + 1) {
      cars_[i]->set_ready(false);
      next_->cars_.push_back(cars_[i]);
      cars_.erase(cars_.begin() + i);
      ++passed_cars;
    }
  }
}

const std::vector<Car*>& Segment::cars() const {
  return cars_;
}

size_t Segment::num_cars() const {
  return cars_.size();
}

const std::vector<Car*> Segment::ready_cars() const {
  std::vector<Car*> ret;
  for (size_t i = 0; i < cars_.size(); ++i) {
    if (cars_[i]->ready()) {
      ret.push_back(cars_[i]);
    }
  }
  return ret;
}

size_t Segment::capacity() const {
  return capacity_;
}


size_t Segment::enter_junction() const {
  return enter_junction_->id();
}

void Segment::set_next(Segment* next) {
  next_ = next;
}

}  // namespace project
