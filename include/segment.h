#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "junction.h"

namespace oop_project {

class Segment {
 public:
  static const size_t kMaxCars;

  Segment(size_t, Segment*, int, size_t, size_t);
  ~Segment();

  void Enter();
  void Exit();
  void Operate();
  void Pass(size_t);

  size_t num_cars() const;
  const std::vector<Car*> ready_cars() const;
  size_t enter_junction() const;
  void set_next(Segment* /*next*/);

 private:
  const size_t capacity_;
  std::vector<Car*> cars_;
  Junction* enter_junction_;
  Segment* next_;
  Segment* prev_;
  const int ready_percent_;
};

}  // namespace oop_project

#endif  // SEGMENT_H_
