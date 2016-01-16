#ifndef JUNCTION_H_
#define JUNCTION_H_

#include "toll.h"
#include <cstddef>
#include <vector>

namespace oop_project {

class Junction {
 public:
  static const size_t kMaxTollsPerType;
  static const size_t kRandomCarsPerToll;

  Junction(size_t, size_t);

  size_t id() const;
  size_t pass_limit() const;
  size_t num_junctions() const;

  std::vector<Car*> Operate(size_t);

 private:
  static size_t current_id_;
  std::vector<Toll*> manned_tolls_;
  std::vector<Toll*> electronic_tolls_;
  size_t id_;
  size_t num_junctions_;
  size_t pass_limit_;
};

}  // namespace oop_project

#endif  // JUNCTION_H_
