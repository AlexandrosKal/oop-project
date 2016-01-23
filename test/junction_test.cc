#include "junction.h"
#include "gtest/gtest.h"

namespace oop_project {

TEST(JunctionTest, HandlesZeroCarsOperation) {
  Junction junction(10, 5);
  std::vector<Car*> cars = junction.Operate(0);
  ASSERT_EQ(cars.size(), 0);
  for (size_t i = 0; i < cars.size(); ++i) {
    delete cars[i];
  }
}

TEST(JunctionTest, HandlesPositiveCarsOperation) {
  Junction junction(10, 5);
  std::vector<Car*> cars = junction.Operate(20);
  ASSERT_LE(cars.size(), 3 * 5);
  ASSERT_LE(cars.size(), 20);
  for (size_t i = 0; i < cars.size(); ++i) {
    delete cars[i];
  }

  cars = junction.Operate(4);
  ASSERT_LE(cars.size(), 4);
  for (size_t i = 0; i < cars.size(); ++i) {
    delete cars[i];
  }
}

TEST(JunctionTest, IncreasesIdByOne) {
  Junction junction0(10, 5);
  Junction junction1(10, 5);
  Junction junction2(10, 5);
  ASSERT_GE(junction0.id(), 0);
  ASSERT_EQ(junction1.id(), junction0.id() + 1);
  ASSERT_EQ(junction2.id(), junction0.id() + 2);
}

TEST(JunctionTest, ReturnsPassLimit) {
  Junction junction(10, 5);
  ASSERT_EQ(junction.pass_limit(), 5);
}

}  // namespace oop_project
