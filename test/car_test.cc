#include "car.h"
#include "mock_segment.h"
#include "gtest/gtest.h"

namespace oop_project {

TEST(CarTest, InitializesDataMembers) {
  Segment* segment = new MockSegment;
  Car car(5, segment);
  ASSERT_EQ(5, car.exit_junction());
  ASSERT_EQ(segment, car.segment());
  ASSERT_EQ(false, car.ready());
}

TEST(CarTest, ReturnsSegment) {
  Segment* segment = new MockSegment;
  Car car(5, segment);
  ASSERT_EQ(segment, car.segment());
}

TEST(CarTest, ReturnsExitJunction) {
  Car car(5, NULL);
  ASSERT_EQ(5, car.exit_junction());
}

TEST(CarTest, ReturnsReady) {
  Car car(5, NULL);
  ASSERT_EQ(false, car.ready());
}

TEST(CarTest, ChangesSegmentValue) {
  Segment* segment = new MockSegment;
  Car car(5, NULL);
  car.set_segment(segment);
  ASSERT_EQ(segment, car.segment());
}

TEST(CarTest, ChangesReadyValue) {
  Car car(5, NULL);
  car.set_ready(true);
  ASSERT_EQ(true, car.ready());
}

}  // namespace oop_project
