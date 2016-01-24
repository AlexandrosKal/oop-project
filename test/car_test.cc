#include "car.h"
#include "gtest/gtest.h"
#include "segment.h"

namespace project {

TEST(CarTest, InitializesDataMembers) {
  Segment segment(5, NULL, 5, 5, 5);
  Car car(5, &segment);
  ASSERT_EQ(car.exit_junction(), 5);
  ASSERT_EQ(car.ready(), false);
  ASSERT_EQ(car.segment(), &segment);
}

TEST(CarTest, ReturnsExitJunction) {
  Car car(5, NULL);
  ASSERT_EQ(car.exit_junction(), 5);
}

TEST(CarTest, ReturnsReady) {
  Car car(5, NULL);
  ASSERT_EQ(car.ready(), false);
}

TEST(CarTest, ReturnsSegment) {
  Segment segment(5, NULL, 5, 5, 5);
  Car car(5, &segment);
  ASSERT_EQ(car.segment(), &segment);
}

TEST(CarTest, ChangesReadyValue) {
  Car car(5, NULL);
  car.set_ready(true);
  ASSERT_EQ(car.ready(), true);
  car.set_ready(false);
  ASSERT_EQ(car.ready(), false);
}

TEST(CarTest, ChangesSegmentValue) {
  Segment segment(5, NULL, 5, 5, 5);
  Car car(5, NULL);
  car.set_segment(&segment);
  ASSERT_EQ(car.segment(), &segment);
}

}  // namespace project
