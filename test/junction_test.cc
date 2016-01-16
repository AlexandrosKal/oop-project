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

TEST(JunctionTest, IdIncreasesByOne) {
    Junction junction0(10, 5);
    Junction junction1(10, 5);
    Junction junction2(10, 5);
    ASSERT_EQ(junction1.id(), junction0.id() + 1);
    ASSERT_EQ(junction2.id(), junction0.id() + 2);
}

TEST(JunctionTest, OperateHandlesPositive) {
    Junction junction(10, 5);
    std::vector<Car*> cars;
    cars = junction.Operate(6);
    ASSERT_GE(junction.pass_limit(), cars.size());
    cars = junction.Operate(4);
    ASSERT_GE(4, cars.size());
}
TEST(Junction, OperateHandlesZero) {
    Junction junction(10, 5);
    std::vector<Car*> cars;
    cars = junction.Operate(6);
}

}  // namespace oop_project
