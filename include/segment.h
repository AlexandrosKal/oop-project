#ifndef SEGMENT_H_
#define SEGMENT_H_

#include <vector>
#include "junction.h"

namespace project {

class Segment {
 public:
  static const size_t kMaxCars;

  Segment(size_t, Segment*, int, size_t, size_t);
  ~Segment();

  void Enter();
  void Exit();
  void Operate();
  void Pass(size_t);

  const std::vector<Car*>& cars() const;
  size_t num_cars() const;
  const std::vector<Car*> ready_cars() const;
  size_t capacity() const;
  size_t entrance() const;
  void set_exit(Junction* /*exit*/);
  const Junction* exit() const;
  void set_next(Segment* /*next*/);

 private:
  void Ready();

  const size_t capacity_;
  std::vector<Car*> cars_;
  Junction* entrance_;
  Junction* exit_;
  Segment* next_;
  Segment* prev_;
  const int ready_percent_;
};

}  // namespace project

#endif  // SEGMENT_H_
