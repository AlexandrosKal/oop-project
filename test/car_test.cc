#include "car.h"
#include "gtest/gtest.h"
#include "segment.h"

namespace oop_project {

TEST(CarTest, InitializesDataMembers) {
  Segment segment(5, NULL, 5, 5, 5);
  Car car(5, &segment);
  ASSERT_EQ(5, car.exit_junction());
  ASSERT_EQ(false, car.ready());
  ASSERT_EQ(&segment, car.segment());
}

TEST(CarTest, ReturnsExitJunction) {
  Car car(5, NULL);
  ASSERT_EQ(5, car.exit_junction());
}

TEST(CarTest, ReturnsReady) {
  Car car(5, NULL);
  ASSERT_EQ(false, car.ready());
}

TEST(CarTest, ReturnsSegment) {
  Segment segment(5, NULL, 5, 5, 5);
  Car car(5, &segment);
  ASSERT_EQ(&segment, car.segment());
}

TEST(CarTest, ChangesReadyValue) {
  Car car(5, NULL);
  car.set_ready(true);
  ASSERT_EQ(true, car.ready());
  car.set_ready(false);
  ASSERT_EQ(false, car.ready());
}

TEST(CarTest, ChangesSegmentValue) {
  Segment segment(5, NULL, 5, 5, 5);
  Car car(5, NULL);
  car.set_segment(&segment);
  ASSERT_EQ(&segment, car.segment());
}

}  // namespace oop_project
