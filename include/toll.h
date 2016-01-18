#ifndef TOLL_H_
#define TOLL_H_

#include <vector>
#include "car.h"

namespace oop_project {

class Toll {
 public:
  static const size_t kMaxCars;

  Toll(size_t, size_t);
  ~Toll();

  void Add(Car* /*car*/);
  std::vector<Car*> Remove();
  std::vector<Car*> Remove(size_t);

  size_t num_cars() const;

 private:
  std::vector<Car*> cars_;
};

}  // namespace oop_project

#endif  // TOLL_H_
