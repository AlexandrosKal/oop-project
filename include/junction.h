#ifndef JUNCTION_H_
#define JUNCTION_H_

#include <vector>
#include "toll.h"

namespace project {

class Junction {
 public:
  static const size_t kMaxTollsPerType;
  static const size_t kMaxCarsPerToll;

  Junction();
  Junction(size_t, size_t);
  ~Junction();

  const std::vector<Car*> Cars() const;
  size_t NumCars() const;
  std::vector<Car*> Operate(size_t);

  static size_t current_id();
  size_t num_electronic() const;
  size_t id() const;
  size_t num_manned() const;
  size_t pass_limit() const;

 private:
  void AddRandomCars(const std::vector<Toll*>&) const;
  size_t NumCars(const std::vector<Toll*>&) const;
  std::vector<Car*> RemoveCars(const std::vector<Toll*>&, size_t) const;

  static size_t current_id_;
  std::vector<Toll*> electronic_;
  const size_t id_;
  std::vector<Toll*> manned_;
  const size_t num_junctions_;
  size_t pass_limit_;
};

}  // namespace project

#endif  // JUNCTION_H_
