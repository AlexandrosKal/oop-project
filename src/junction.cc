#include "junction.h"
#include <algorithm>
#include <cstdlib>

namespace oop_project {

const size_t Junction::kMaxTollsPerType = 5;
const size_t Junction::kMaxCarsPerToll = 5;

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

Junction::~Junction() {
  for (size_t i = 0; i < manned_tolls_.size(); ++i) {
    delete manned_tolls_[i];
  }
  for (size_t i = 0; i < electronic_tolls_.size(); ++i) {
    delete electronic_tolls_[i];
  }
}

std::vector<Car*> Junction::Operate(size_t max_allowed_cars) {
  size_t manned_cars = 0, electronic_cars = 0;
  for (size_t i = 0; i < manned_tolls_.size(); ++i) {
    manned_cars += manned_tolls_[i]->num_cars();
  }
  for (size_t i = 0; i < electronic_tolls_.size(); ++i) {
    electronic_cars += electronic_tolls_[i]->num_cars();
  }
  size_t sum_cars = manned_cars + electronic_cars;

  std::vector<Car*> ret;
  if (manned_cars <= pass_limit_ && electronic_cars <= 2 * pass_limit_ &&
      sum_cars <= max_allowed_cars) {
    std::vector<Car*> temp;
    for (size_t i = 0; i < manned_tolls_.size(); ++i) {
      temp = manned_tolls_[i]->Remove();
      ret.insert(ret.end(), temp.begin(), temp.end());
    }
    for (size_t i = 0; i < electronic_tolls_.size(); ++i) {
      temp = electronic_tolls_[i]->Remove();
      ret.insert(ret.end(), temp.begin(), temp.end());
    }
    if (sum_cars == 3 * pass_limit_) {
      pass_limit_++;
    }
  } else if (sum_cars > max_allowed_cars)  {
    size_t manned_cars_pass = (max_allowed_cars / 3) / manned_tolls_.size();
    size_t electronic_cars_pass = (2 * max_allowed_cars / 3) /
                                   electronic_tolls_.size();
    std::vector<Car*> temp;
    for (size_t i = 0; i < manned_tolls_.size(); ++i) {
      temp = manned_tolls_[i]->Remove(manned_cars_pass);
      ret.insert(ret.end(), temp.begin(), temp.end());
    }
    for (size_t i = 0; i < electronic_tolls_.size(); ++i) {
      temp = electronic_tolls_[i]->Remove(electronic_cars_pass);
      ret.insert(ret.end(), temp.begin(), temp.end());
    }
    pass_limit_--;
  } else {
    size_t manned_cars_pass = (pass_limit_) / manned_tolls_.size();
    size_t electronic_cars_pass = (2 * pass_limit_) /
                                   electronic_tolls_.size();
    std::vector<Car*> temp;
    for (size_t i = 0; i < manned_tolls_.size(); ++i) {
      temp = manned_tolls_[i]->Remove(manned_cars_pass);
      ret.insert(ret.end(), temp.begin(), temp.end());
    }
    for (size_t i = 0; i < electronic_tolls_.size(); ++i) {
      temp = electronic_tolls_[i]->Remove(electronic_cars_pass);
      ret.insert(ret.end(), temp.begin(), temp.end());
    }
  }

  // Add random cars to both the electronic and the manned tolls

  for (size_t i = 0; i < manned_tolls_.size(); ++i) {
    size_t m_toll_num_cars = rand() % kMaxCarsPerToll;
    for (size_t j = 0; j < m_toll_num_cars; ++j) {
      Car* car = new Car(rand() % (num_junctions_ - id_) + id_, NULL);
      manned_tolls_[i]->Add(car);
    }
  }

  for (size_t i = 0; i < electronic_tolls_.size(); ++i) {
    size_t e_toll_num_cars = rand() % kMaxCarsPerToll;
    for (size_t j = 0; j < e_toll_num_cars; ++j) {
      Car* car = new Car(rand() % (num_junctions_ - id_) + id_, NULL);
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
