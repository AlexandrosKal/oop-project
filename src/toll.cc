#include "toll.h"
#include <cstdlib>

namespace project {

const size_t Toll::kMaxCars = 2;

Toll::Toll(size_t current_junction, size_t num_junctions) {
  size_t num_cars = rand() % kMaxCars + 1;
  cars_.resize(num_cars);
  for (size_t i = 0; i < cars_.size(); ++i) {
    size_t exit = rand() % (num_junctions - current_junction) +
                  current_junction + 1;
    cars_[i] = new Car(exit, NULL);
  }
}

Toll::~Toll() {
  for (size_t i = 0; i < cars_.size(); ++i) {
    delete cars_[i];
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
    ret.insert(ret.end(), cars_.begin(), cars_.begin() + num_cars);
    cars_.erase(cars_.begin(), cars_.begin() + num_cars);
  } else {
    ret = cars_;
    cars_.clear();
  }
  return ret;
}

const std::vector<Car*>& Toll::cars() const {
  return cars_;
}

size_t Toll::num_cars() const {
  return cars_.size();
}

}  // namespace project
