#ifndef CAR_H_
#define CAR_H_

#include "segment.h"
#include <cstddef>

namespace oop_project {

class Car {
 public:
  Car(size_t, Segment*);

  size_t exit_junction() const;

  void set_ready(bool /*ready*/);
  bool ready() const;

  void set_segment(Segment* /*segment*/);
  const Segment* segment() const;

 private:
  size_t exit_junction_;
  bool ready_;
  Segment* segment_;
};

}  // namespace oop_project

#endif  // CAR_H_
