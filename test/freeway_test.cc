#include "freeway.h"
#include "gtest/gtest.h"

namespace project {

namespace {

const std::vector<size_t> kCapacities(10, 5);

}

TEST(FreewayTest, CorrectlyAssignsJunctionId) {
  size_t current_id = Junction::current_id();
  Freeway freeway(kCapacities, 50, 5);
  const std::vector<Segment*>& segments = freeway.segments();
  for (size_t i = 0; i < segments.size(); ++i) {
    ASSERT_EQ(segments[i]->entrance(), current_id + i);
  }
}

TEST(FreewayTest, CreatesCorrectNumberSegments) {
  Freeway freeway(kCapacities, 50, 5);
  ASSERT_EQ(freeway.segments().size(), 10);
}

TEST(FreewayTest, CreatesSegmentsWithCorrectCapacity) {
  Freeway freeway(kCapacities, 50, 5);
  const std::vector<Segment*>& segments = freeway.segments();
  for (size_t i = 0; i < segments.size(); ++i) {
    ASSERT_EQ(segments[i]->capacity(), kCapacities[i]);
  }
}

TEST(FreewayTest, UpdatesNumCarsAfterOperate) {
  Freeway freeway(kCapacities, 50, 5);
  const std::vector<Segment*>& segments = freeway.segments();
  size_t cars = 0;
  for (size_t i = 0; i < segments.size(); ++i) {
    cars += segments[i]->num_cars();
  }
  ASSERT_EQ(freeway.num_cars(), cars);
}

}  // namespace project
