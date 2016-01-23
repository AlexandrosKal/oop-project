#include "freeway.h"
#include "gtest/gtest.h"

namespace oop_project {

namespace {
const std::vector<size_t> kCapacities(10, 5);
}

TEST(FreewayTest, CorrectlyAssignsJunctionId) {
  size_t current_id = Junction::current_id();
  Freeway freeway(10, 50, kCapacities, 5);
  std::vector<Segment*> segments = freeway.segments();

  for (size_t i = 0; i < segments.size(); ++i) {
    ASSERT_EQ(segments[i]->enter_junction(), current_id + i);
  }
}

TEST(FreewayTest, CreatesCorrectNumberSegments) {
  Freeway freeway(10, 50, kCapacities, 5);
}

}  // namespace oop_project
