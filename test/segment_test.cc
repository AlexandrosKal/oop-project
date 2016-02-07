#include "segment.h"
#include "gtest/gtest.h"

namespace project {

TEST(SegmentTest, CreatesRandomCars) {
  Segment segment(10, NULL, 50, 5, 5);
  ASSERT_GE(segment.num_cars(), 1);
  ASSERT_LE(segment.num_cars(), Segment::kMaxCars);
  ASSERT_LE(segment.num_cars(), 10);
  ASSERT_LE(segment.ready_cars().size(), 50 * segment.num_cars() / 100);
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
  std::vector<Car*> ready_cars = segment.ready_cars();
  size_t num_before_exit = segment.num_cars();

  size_t ready_to_exit = 0;
  for (size_t i = 0; i < ready_cars.size(); ++i) {
    if (ready_cars[i]->exit() == segment.entrance() + 1) {
      ++ready_to_exit;
    }
  }

  segment.Exit();
  ASSERT_EQ(segment.num_cars(), num_before_exit - ready_to_exit);
}

TEST(SegmentTest, Operates) {
  Segment segment(10, NULL, 50, 100, 5);
  std::vector<Car*> prev_ready_cars = segment.ready_cars();
  segment.Operate();
  std::vector<Car*> ready_cars = segment.ready_cars();

  ASSERT_GE(ready_cars.size(), prev_ready_cars.size());
  ASSERT_LE(ready_cars.size() - prev_ready_cars.size(),
            50 * segment.num_cars() / 100);
}

TEST(SegmentTest, PassesReadyCars) {
  Segment segment(10, NULL, 50, 100, 5);
  Segment next_segment(10, NULL, 50, 100, 5);
  segment.set_next(&next_segment);

  std::vector<Car*> ready_cars = segment.ready_cars();
  size_t ready_to_pass = 0;
  for (size_t i = 0; i < ready_cars.size(); ++i) {
    if (ready_cars[i]->exit() != segment.entrance() + 1) {
        ++ready_to_pass;
    }
  }

  size_t num_before_pass = segment.num_cars();
  segment.Pass(5);
  ASSERT_GE(static_cast<int>(segment.num_cars()),
            static_cast<int>(num_before_pass) - 5);
  ASSERT_GE(segment.num_cars(), num_before_pass - ready_to_pass);
  ASSERT_LE(next_segment.num_cars(), 10);
}

TEST(SegmentTest, CreatesCarsWithGreaterExitJunction) {
  Segment segment(10, NULL, 50, 100, 5);
  std::vector<Car*> cars = segment.cars();
  for (size_t i = 0; i < cars.size(); ++i) {
    ASSERT_GT(cars[i]->exit(), segment.entrance());
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

TEST(SegmentTest, ReturnsEnterJunction) {
  Segment segment0(10, NULL, 50, 100, 5);
  Segment segment1(10, NULL, 50, 100, 5);
  Segment segment2(10, NULL, 50, 100, 5);
  ASSERT_GE(segment0.entrance(), 0);
  ASSERT_EQ(segment1.entrance(), segment0.entrance() + 1);
  ASSERT_EQ(segment2.entrance(), segment0.entrance() + 2);
}

}  // namespace project
