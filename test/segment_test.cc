#include "segment.h"
#include "gtest/gtest.h"

namespace project {

TEST(SegmentTest, CreatesRandomCars) {
  Segment segment(10, NULL, 50, 5, 5);
  ASSERT_GE(segment.num_cars(), 1);
  ASSERT_LE(segment.num_cars(), Segment::kMaxCars);
  ASSERT_LE(segment.num_cars(), 10);
  ASSERT_EQ(segment.ready_cars().size(), 50 * segment.num_cars() / 100);
  const std::vector<Car*>& cars = segment.cars();
  for (size_t i = 0; i < cars.size(); ++i) {
    ASSERT_EQ(cars[i]->segment(), &segment);
  }
}

TEST(SegmentTest, EntersLessOrEqualToCapacity) {
  Segment prev_segment(10, NULL, 50, 100, 5);
  Segment segment(10, &prev_segment, 50, 100, 5);
  prev_segment.set_next(&segment);
  segment.Enter();
  ASSERT_LE(segment.num_cars(), 10);
}

TEST(SegmentTest, RemovesCarsFromFreeway) {
  Segment segment(10, NULL, 50, 100, 5);
  Junction junction;
  segment.set_exit(&junction);
  std::vector<Car*> ready_cars = segment.ready_cars();
  size_t num_before_exit = segment.num_cars();

  size_t ready_to_exit = 0;
  for (size_t i = 0; i < ready_cars.size(); ++i) {
    if (ready_cars[i]->exit() == segment.exit()->id()) {
      ++ready_to_exit;
    }
  }

  segment.Exit();
  ASSERT_EQ(segment.num_cars(), num_before_exit - ready_to_exit);
}

TEST(SegmentTest, Operates) {
  Segment prev_segment(10, NULL, 50, 100, 5);
  Segment segment(10, &prev_segment, 50, 100, 5);
  Junction junction;
  segment.set_exit(&junction);
  prev_segment.set_next(&segment);
  std::vector<Car*> prev_ready_cars = segment.ready_cars();
  segment.Operate();
  std::vector<Car*> ready_cars = segment.ready_cars();

  ASSERT_GE(ready_cars.size(), prev_ready_cars.size());
  ASSERT_EQ(ready_cars.size() - prev_ready_cars.size(),
            50 * segment.num_cars() / 100);
  const std::vector<Car*>& cars_after_operation = segment.cars();
  for (size_t i = 0; i < cars_after_operation.size(); ++i) {
    ASSERT_EQ(cars_after_operation[i]->segment(), &segment);
  }
}

TEST(SegmentTest, PassesReadyCars) {
  Segment segment(10, NULL, 50, 100, 5);
  Segment next_segment(10, NULL, 50, 100, 5);
  segment.set_next(&next_segment);

  std::vector<Car*> ready_cars = segment.ready_cars();
  size_t ready_to_pass = 0;
  for (size_t i = 0; i < ready_cars.size(); ++i) {
    if (ready_cars[i]->exit() != segment.exit()->id()) {
      ++ready_to_pass;
    }
  }

  size_t num_before_pass = segment.num_cars();
  segment.Pass(5);
  if (num_before_pass >= 5) {
    ASSERT_GE(segment.num_cars(), num_before_pass - 5);
  }
  ASSERT_GE(segment.num_cars(), num_before_pass - ready_to_pass);
  ASSERT_LE(next_segment.num_cars(), 10);
}

TEST(SegmentTest, CreatesCarsWithGreaterExit) {
  Segment segment(10, NULL, 50, 100, 5);
  Junction junction;
  segment.set_exit(&junction);
  const std::vector<Car*>& cars = segment.cars();
  for (size_t i = 0; i < cars.size(); ++i) {
    ASSERT_GE(cars[i]->exit(), segment.exit()->id());
  }
}

TEST(SegmentTest, ReturnsReadyCars) {
  Segment segment(10, NULL, 50, 100, 5);
  std::vector<Car*> ready_cars = segment.ready_cars();

  ASSERT_LE(ready_cars.size(), segment.num_cars());
  for (size_t i = 0; i < ready_cars.size(); ++i) {
    ASSERT_EQ(ready_cars[i]->ready(), true);
  }
}

TEST(SegmentTest, ReturnsCapacity) {
  Segment segment(10, NULL, 50, 100, 5);
  ASSERT_EQ(segment.capacity(), 10);
}

TEST(SegmentTest, ReturnsEntrance) {
  Segment segment0(10, NULL, 50, 100, 5);
  Segment segment1(10, NULL, 50, 100, 5);
  Segment segment2(10, NULL, 50, 100, 5);
  ASSERT_GE(segment0.entrance(), 0);
  ASSERT_EQ(segment1.entrance(), segment0.entrance() + 1);
  ASSERT_EQ(segment2.entrance(), segment0.entrance() + 2);
}

TEST(SegmentTest, SetsExit) {
  Segment prev_segment(10, NULL, 50, 100, 5);
  Segment segment(10, &prev_segment, 50, 100, 5);
  prev_segment.set_next(&segment);
  ASSERT_EQ(prev_segment.exit()->id(), segment.entrance());

  Junction junction;
  segment.set_exit(&junction);
  ASSERT_EQ(segment.exit()->id(), junction.id());
}

}  // namespace project
