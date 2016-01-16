#include "toll.h"
#include <cstdlib>

namespace oop_project {

const size_t Toll::kMaxCars = 5;

Toll::Toll(size_t current_junction, size_t num_junctions) {
  size_t num_cars = rand() % kMaxCars + 1;
  cars_.resize(num_cars);
  for (size_t i = 0; i < cars_.size(); ++i) {
    size_t exit_junction = rand() % (num_junctions - current_junction) +
                           current_junction;
    cars_[i] = new Car(exit_junction, NULL);
  }
}

void Toll::Add(Car* car) {
  cars_.push_back(car);
}

std::vector<Car*> Toll::Remove() {
  return Remove(cars_.size());
}

std::vector<Car*> Toll::Remove(size_t num_cars) {
  std::vector<Car*> ret;
  if (cars_.size() > num_cars) {
    ret.insert(ret.begin(), cars_.begin(), cars_.begin() + num_cars);
    cars_.erase(cars_.begin(), cars_.begin() + num_cars);
  } else {
    ret = cars_;
    cars_.clear();
  }
  return ret;
}

size_t Toll::num_cars() const {
  return cars_.size();
}

}  // namespace oop_project