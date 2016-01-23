#include "junction.h"
#include <cstdlib>

namespace oop_project {

const size_t Junction::kMaxTollsPerType = 3;
const size_t Junction::kMaxCarsPerToll = 2;

Junction::Junction(size_t num_junctions, size_t pass_limit)
  : id_(current_id_++), num_junctions_(num_junctions), pass_limit_(pass_limit) {
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


const std::vector<Car*> Junction::Cars() const {
  std::vector<Car*> ret, temp;
  for (size_t i = 0; i < manned_tolls_.size(); ++i) {
    temp = manned_tolls_[i]->cars();
    ret.insert(ret.end(), temp.begin(), temp.end());
  }
  for (size_t i = 0; i < electronic_tolls_.size(); ++i) {
    temp = electronic_tolls_[i]->cars();
    ret.insert(ret.end(), temp.begin(), temp.end());
  }
  return ret;
}

size_t Junction::NumCars() const {
  return CountCars(manned_tolls_) + CountCars(electronic_tolls_);
}

std::vector<Car*> Junction::Operate(size_t max_allowed_cars) {
  size_t manned_cars = std::min(pass_limit_, CountCars(manned_tolls_));
  size_t electronic_cars = std::min(2 * pass_limit_,
                                    CountCars(electronic_tolls_));

  std::vector<Car*> manned_ret, electronic_ret;
  if (manned_cars + electronic_cars <= max_allowed_cars) {
    manned_ret = RemoveCars(manned_tolls_, manned_cars);
    electronic_ret = RemoveCars(electronic_tolls_, electronic_cars);

    if (manned_cars == pass_limit_ && electronic_cars == 2 * pass_limit_) {
      ++pass_limit_;
    }
  } else {
    size_t allowed_cars = std::min(manned_cars, max_allowed_cars);
    manned_ret = RemoveCars(manned_tolls_, allowed_cars);
    electronic_ret = RemoveCars(electronic_tolls_,
                                max_allowed_cars - manned_ret.size());
    --pass_limit_;
  }
  std::vector<Car*> ret = manned_ret;
  ret.insert(ret.end(), electronic_ret.begin(), electronic_ret.end());

  AddRandomCars(manned_tolls_);
  AddRandomCars(electronic_tolls_);
  return ret;
}

size_t Junction::current_id() {
  return current_id_;
}

size_t Junction::id() const {
  return id_;
}

size_t Junction::pass_limit() const {
  return pass_limit_;
}

void Junction::AddRandomCars(const std::vector<Toll*>& tolls) const {
  for (size_t i = 0; i < tolls.size(); ++i) {
    size_t toll_num_cars = rand() % kMaxCarsPerToll;
    for (size_t j = 0; j < toll_num_cars; ++j) {
      size_t exit_junction = rand() % (num_junctions_ - id_) + id_ + 1;
      tolls[i]->Add(new Car(exit_junction, NULL));
    }
  }
}

size_t Junction::CountCars(const std::vector<Toll*>& tolls) const {
  size_t ret = 0;
  for (size_t i = 0; i < tolls.size(); ++i) {
    ret += tolls[i]->num_cars();
  }
  return ret;
}

std::vector<Car*> Junction::RemoveCars(const std::vector<Toll*>& tolls,
                                       size_t num_cars) const {
  std::vector<Car*> ret, temp;
  size_t sum = 0;
  for (size_t i = 0; i < tolls.size(); ++i) {
    if (sum + tolls[i]->num_cars() > num_cars) {
      temp = tolls[i]->Remove(num_cars - sum);
      ret.insert(ret.end(), temp.begin(), temp.end());
      break;
    }
    temp = tolls[i]->Remove();
    ret.insert(ret.end(), temp.begin(), temp.end());
    sum += temp.size();
  }
  return ret;
}

size_t Junction::current_id_ = 0;

}  // namespace oop_project
