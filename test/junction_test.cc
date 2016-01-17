#include "junction.h"
#include "gtest/gtest.h"

namespace oop_project {

TEST(JunctionTest, InitializesDataMembers) {
  Junction junction(10, 5);
  ASSERT_EQ(5, junction.pass_limit());
}

TEST(JunctionTest, ReturnsPassLimit) {
  Junction junction(10, 5);
  ASSERT_EQ(5, junction.pass_limit());
}

TEST(JunctionTest, IncreasesIdByOne) {
  Junction junction0(10, 5);
  Junction junction1(10, 5);
  Junction junction2(10, 5);
  ASSERT_EQ(junction1.id(), junction0.id() + 1);
  ASSERT_EQ(junction2.id(), junction0.id() + 2);
}

TEST(JunctionTest, HandlesPositiveCarsOperation) {
  Junction junction(10, 5);
  std::vector<Car*> cars = junction.Operate(6);
  ASSERT_GE(junction.pass_limit(), cars.size());
  cars = junction.Operate(4);
  ASSERT_GE(4, cars.size());
}
TEST(JunctionTest, HandlesZeroCarsOperation) {
  Junction junction(10, 5);
  std::vector<Car*> cars = junction.Operate(0);
  ASSERT_EQ(0, cars.size());
}

}  // namespace oop_project
