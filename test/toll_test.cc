#include "toll.h"
#include "gtest/gtest.h"

namespace oop_project {

TEST(TollTest, CreatesCar) {
  Toll toll(5, 10);
  ASSERT_GE(toll.num_cars(), 1);
  ASSERT_LE(toll.num_cars(), Toll::kMaxCars);
}

TEST(TollTest, AddsCar) {
  Toll toll(5, 10);
  size_t prev_num_cars = toll.num_cars();

  Car* car = new Car(10, NULL);
  toll.Add(car);
  ASSERT_EQ(toll.num_cars(), prev_num_cars + 1);
}

TEST(TollTest, HandlesZeroRemoval) {
  Toll toll(5, 10);
  std::vector<Car*> cars = toll.Remove(0);
  ASSERT_EQ(cars.size(), 0);
}

TEST(TollTest, RemovesSomeCars) {
  Toll toll(5, 10);
  size_t prev_num_cars = toll.num_cars();

  std::vector<Car*> cars = toll.Remove(prev_num_cars - 1);
  ASSERT_EQ(cars.size(), prev_num_cars - 1);
}

TEST(TollTest, HandlesOverflowRemoval) {
  Toll toll(5, 10);
  int num_cars = toll.num_cars();

  std::vector<Car*> cars = toll.Remove(num_cars + 10);
  ASSERT_LE(cars.size(), num_cars);
}

TEST(TollTest, RemovesAllCars) {
  Toll toll(5, 10);
  size_t prev_num_cars = toll.num_cars();

  std::vector<Car*> cars = toll.Remove();
  ASSERT_EQ(cars.size(), prev_num_cars);
  ASSERT_EQ(toll.num_cars(), 0);
}

}  // namespace oop_project
