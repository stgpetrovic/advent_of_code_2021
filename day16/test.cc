#include <vector>

#include "day16/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day16, First) {
  auto result = VersionSum(std::vector<std::string>{"8A004A801A8002F478"});
  EXPECT_TRUE(result.ok()) << result.status();
  EXPECT_EQ(*result, 16);
}

TEST(Day16, Second) {
  auto result =
      VersionSum(std::vector<std::string>{"620080001611562C8802118E34"});
  EXPECT_TRUE(result.ok()) << result.status();
  EXPECT_EQ(*result, 12);
}

TEST(Day16, Third) {
  auto result =
      VersionSum(std::vector<std::string>{"C0015000016115A2E0802F182340"});
  EXPECT_TRUE(result.ok()) << result.status();
  EXPECT_EQ(*result, 23);
}

TEST(Day16, Fourth) {
  auto result =
      VersionSum(std::vector<std::string>{"A0016C880162017C3686B18A3D4780"});
  EXPECT_TRUE(result.ok()) << result.status();
  EXPECT_EQ(*result, 31);
}

TEST(Day16, Eval) {
  auto result = Eval(std::vector<std::string>{"C200B40A82"});
  EXPECT_TRUE(result.ok()) << result.status();
  EXPECT_EQ(*result, 3);
}
