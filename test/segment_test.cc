#include "segment.h"

namespace oop_project {

TEST(SegmentTest, EnterInsertsReadyCars) {
  Segment prev_segment = new Segment(10, NULL, 50, 5);
  Segment segment(10, prev_segment, 50, 5);
  size_t prev_ready = (prev_segment.ready_cars()).size();
  size_t num_before_enter = segment.num_cars();
  segment.Enter();
  ASSERT_LE(segment.num_cars(), 10)
  ASSERT_LE(segment.num_cars() , num_before_enter + prev_ready)
}

TEST(SegmentTest, RemovesCarsFromSegment) {
  Segment segment(10, NULL, 50, 5);
  std::vector<Cars*> ready_cars = segment.ready_cars();
  size_t ready_to_exit = 0;
  size_t num_before_exit = segment.num_cars();
  for(size_t i = 0; i < ready_cars.size(); ++i) {
    if(ready_cars[i]->exit_junction() == segment->enter_junction()() + 1) {
      ready_to_exit++;
    }
  }
  segment.Exit();
  ASSERT_LE(ready_to_exit, num_before_exit);
  ASSERT_EQ(segment.num_cars(), num_before_exit - ready_to_exit);
}

TEST(SegmentTest, PassesReadyCarsToNext) {
  Segment segment(10, NULL, 50, 5);
  Segment next_segment = new Segment(10, NULL, 50, 5);
  std::vector<Cars*> ready_cars = segment.ready_cars();
  size_t ready_to_pass = 0;
  for(size_t i = 0; i < ready_cars.size(); ++i) {
    if(ready_cars[i]->exit_junction() != segment->enter_junction() + 1) {
        ready_to_pass++;
    }
  }
  size_t number_before_pass = next_segment->num_cars();
  segment.Pass()
  ASSERT_LE(next_segment->num_cars(), 10);
  ASSERT_EQ(segment.num_cars(), number_before_pass - ready_to_pass);
}

TEST(SegmentTest, SetsReadyPercent) {
  Segment segment(10, NULL, 50, 5);
  size_t num_ready = (segment.ready_cars()).size()
  size_t not_ready_before_operate = segment.num_cars() - num_ready;
}
/*TEST(SegmentTest, SetsNextSegment) {
 Segment segment(10, NULL, 50, 5);
 Segment next_segment = new Segment(10, NULL, 50, 5);
 segment.set_next(next_segment);

} may not be needed*/

}  // namespace oop_project
