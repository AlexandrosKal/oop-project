#include "junction.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

namespace oop_project {

const size_t Junction::kMaxTollsPerType = 5;
const size_t Junction::kRandomCarsPerToll = 5;

Junction::Junction(size_t num_junctions, size_t pass_limit)
  : id_(++current_id_), num_junctions_(num_junctions), pass_limit_(pass_limit) {
  size_t num_manned_tolls = rand() % kMaxTollsPerType + 1;
  manned_tolls_.resize(num_manned_tolls);
  for (size_t i = 0; i < manned_tolls_.size(); ++i) {
    manned_tolls_[i] = new Toll(id_, num_junctions_);
  }

  size_t num_electronic_tolls = rand() % kMaxTollsPerType + 1;
  electronic_tolls_.resize(num_electronic_tolls);
  for (size_t i = 0; i < electronic_tolls_.size(); ++i) {
    electronic_tolls_[i] = new Toll(id_, num_junctions_);
  }
}

std::vector<Car*> Junction::Operate(size_t max_allowed_cars) {
  size_t sum_cars = 0;

  for (size_t i = 0; i < manned_tolls_.size(); ++i) {
    sum_cars += manned_tolls_[i]->num_cars();
  }
  for (size_t i = 0; i < electronic_tolls_.size(); ++i) {
    sum_cars += electronic_tolls_[i]->num_cars();
  }

  std::vector<Car*> ret;
  if (sum_cars <= 3 * pass_limit_ && sum_cars <= max_allowed_cars) {
    std::vector<Car*> temp;
    for (size_t i = 0; i < manned_tolls_.size(); ++i) {
      temp = manned_tolls_[i]->Remove();
      ret.insert(ret.begin(), temp.begin(), temp.end());
    }
  } else {
    size_t limit = std::min(3 * pass_limit_, max_allowed_cars);
    size_t cars_pass = (limit / (manned_tolls_.size() +
                        electronic_tolls_.size()));
    std::vector<Car*> temp;
    for (size_t i = 0; i < manned_tolls_.size(); ++i) {
      temp = manned_tolls_[i]->Remove(cars_pass);
      ret.insert(ret.begin(), temp.begin(), temp.end());
    }
  }

  for (size_t i = 0; i < manned_tolls_.size(); ++i) {
  size_t m_toll_num_cars = rand() % kRandomCarsPerToll;
    for (size_t j = 0; j < m_toll_num_cars; ++j) {
      Car* car = new Car((rand() % num_junctions_ - id_) + id_, NULL);
      manned_tolls_[i]->Add(car);
    }
  }

  for (size_t i = 0; i < electronic_tolls_.size(); ++i) {
  size_t e_toll_num_cars = rand() % kRandomCarsPerToll;
    for (size_t j = 0; j < e_toll_num_cars; ++j) {
      Car* car = new Car((rand() % num_junctions_ - id_) + id_, NULL);
      electronic_tolls_[i]->Add(car);
    }
  }
  return ret;
}

size_t Junction::id() const {
  return id_;
}

size_t Junction::pass_limit() const {
  return pass_limit_;
}

size_t Junction::current_id_ = 0;

}  // namespace oop_project
