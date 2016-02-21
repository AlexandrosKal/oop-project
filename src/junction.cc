#include "junction.h"
#include <cstdlib>

namespace project {

const size_t Junction::kMaxTollsPerType = 3;
const size_t Junction::kMaxCarsPerToll = 2;

Junction::Junction() : id_(current_id_++), num_junctions_(0), pass_limit_(0) {
}

Junction::Junction(size_t num_junctions, size_t pass_limit)
  : id_(current_id_++), num_junctions_(num_junctions), pass_limit_(pass_limit) {
  size_t num_manned = rand() % kMaxTollsPerType + 1;
  manned_.resize(num_manned);
  for (size_t i = 0; i < manned_.size(); ++i) {
    manned_[i] = new Toll(id_, num_junctions_);
  }

  size_t num_electronic = rand() % kMaxTollsPerType + 1;
  electronic_.resize(num_electronic);
  for (size_t i = 0; i < electronic_.size(); ++i) {
    electronic_[i] = new Toll(id_, num_junctions_);
  }
}

Junction::~Junction() {
  for (size_t i = 0; i < manned_.size(); ++i) {
    delete manned_[i];
  }
  for (size_t i = 0; i < electronic_.size(); ++i) {
    delete electronic_[i];
  }
}

const std::vector<Car*> Junction::Cars() const {
  std::vector<Car*> ret;
  for (size_t i = 0; i < manned_.size(); ++i) {
    const std::vector<Car*>& temp = manned_[i]->cars();
    ret.insert(ret.end(), temp.begin(), temp.end());
  }
  for (size_t i = 0; i < electronic_.size(); ++i) {
    const std::vector<Car*>& temp = electronic_[i]->cars();
    ret.insert(ret.end(), temp.begin(), temp.end());
  }
  return ret;
}

size_t Junction::NumCars() const {
  return NumCars(manned_) + NumCars(electronic_);
}

std::vector<Car*> Junction::Operate(size_t max_cars) {
  size_t manned_cars = std::min(pass_limit_, NumCars(manned_));
  size_t electronic_cars = std::min(2 * pass_limit_, NumCars(electronic_));

  std::vector<Car*> manned_ret, electronic_ret;
  if (manned_cars + electronic_cars <= max_cars) {
    manned_ret = RemoveCars(manned_, manned_cars);
    electronic_ret = RemoveCars(electronic_, electronic_cars);

    if (manned_cars == pass_limit_ && electronic_cars == 2 * pass_limit_) {
      ++pass_limit_;
    }
  } else {
    size_t allowed_cars = std::min(manned_cars, max_cars);
    manned_ret = RemoveCars(manned_, allowed_cars);
    electronic_ret = RemoveCars(electronic_, max_cars - manned_ret.size());
    --pass_limit_;
  }
  std::vector<Car*> ret = manned_ret;
  ret.insert(ret.end(), electronic_ret.begin(), electronic_ret.end());

  AddRandomCars(manned_);
  AddRandomCars(electronic_);
  return ret;
}

size_t Junction::current_id() {
  return current_id_;
}

size_t Junction::num_electronic() const {
  return electronic_.size();
}

size_t Junction::id() const {
  return id_;
}

size_t Junction::num_manned() const {
  return manned_.size();
}

size_t Junction::pass_limit() const {
  return pass_limit_;
}

void Junction::AddRandomCars(const std::vector<Toll*>& tolls) const {
  for (size_t i = 0; i < tolls.size(); ++i) {
    size_t num_cars = rand() % kMaxCarsPerToll;
    for (size_t j = 0; j < num_cars; ++j) {
      size_t exit = rand() % (num_junctions_ - id_ - 1) + id_ + 1;
      tolls[i]->Add(new Car(exit, NULL));
    }
  }
}

size_t Junction::NumCars(const std::vector<Toll*>& tolls) const {
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

}  // namespace project
