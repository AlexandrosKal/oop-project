#include "segment.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include "size_types.h"

namespace project {

const size_t Segment::kMaxCars = 5;

Segment::Segment(size_t capacity, Segment* prev, int ready_percent,
                 size_t num_junctions, size_t pass_limit)
    : capacity_(capacity),
      entrance_(new Junction(num_junctions, pass_limit)),
      next_(NULL),
      prev_(prev),
      ready_percent_(ready_percent) {
  size_t num_cars = std::min(capacity_, rand() % kMaxCars + 1);
  cars_.resize(num_cars);
  for (size_t i = 0; i < cars_.size(); ++i) {
    size_t exit = rand() % (num_junctions - entrance_->id()) + entrance_->id() +
                  1;
    cars_[i] = new Car(exit, NULL);
  }
}

Segment::~Segment() {
  for (size_t i = 0; i < cars_.size(); ++i) {
    delete cars_[i];
  }
  delete entrance_;
}

void Segment::Enter() {
  size_t max_cars, ready_cars_before_pass = 0, num_passed_cars = 0;
  if (prev_ != NULL) {
    size_t num_cars_before_pass = cars_.size();
    ready_cars_before_pass = prev_->ready_cars().size();
    max_cars = capacity_ - cars_.size();
    prev_->Pass(max_cars);
    num_passed_cars = cars_.size() - num_cars_before_pass;
  }

  size_t cars_before_enter = entrance_->Cars().size();
  max_cars = capacity_ - cars_.size();
  std::vector<Car*> cars = entrance_->Operate(max_cars);
  if (cars.size() < cars_before_enter) {
    printf("Kathysteriseis stin eisodo tou komvou %" PRIuS "\n",
           entrance_->id());

    if (num_passed_cars < ready_cars_before_pass) {
      printf("Kathysteriseis meta ton komvo %" PRIuS "\n",
             entrance_->id());
    }
  } else {
    printf("Tireite tis apostaseis asfaleias sto tmima meta ton komvo %" PRIuS
           "\n", entrance_->id());
  }
  cars_.insert(cars_.end(), cars.begin(), cars.end());
}

void Segment::Exit() {
  for (size_t i = 0; i < cars_.size(); ++i) {
    if (cars_[i]->ready() && cars_[i]->exit() == entrance_->id() + 1) {
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

void Segment::Pass(size_t max_cars) {
  size_t passed_cars = 0;
  for (size_t i = 0; i < cars_.size(); ++i) {
    if (passed_cars == max_cars) {
      break;
    }
    if (cars_[i]->ready() && cars_[i]->exit() != entrance_->id() + 1) {
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

size_t Segment::entrance() const {
  return entrance_->id();
}

void Segment::set_next(Segment* next) {
  next_ = next;
}

}  // namespace project
