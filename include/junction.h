#ifndef JUNCTION_H_
#define JUNCTION_H_

#include <vector>
#include "toll.h"

namespace oop_project {

class Junction {
 public:
  static const size_t kMaxTollsPerType;
  static const size_t kMaxCarsPerToll;

  Junction(size_t, size_t);
  ~Junction();

  std::vector<Car*> Operate(size_t);

  size_t id() const;
  size_t pass_limit() const;

 private:
  void AddRandomCars(std::vector<Toll*>&) const;
  size_t CountCars(std::vector<Toll*>&) const;
  std::vector<Car*> RemoveCars(std::vector<Toll*>&, size_t) const;

  static size_t current_id_;
  std::vector<Toll*> electronic_tolls_;
  size_t id_;
  std::vector<Toll*> manned_tolls_;
  size_t num_junctions_;
  size_t pass_limit_;
};

}  // namespace oop_project

#endif  // JUNCTION_H_
