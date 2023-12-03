#include "../sim/progargs.hpp"
#include <gtest/gtest.h>

TEST(ProgargsTest, ValidInput) {
  int const argc = 4;
  std::vector<std::string> const arguments = {"10", "small.fld",
                                              "out/test.fld"};

  int const result = progargs(argc, arguments);

  ASSERT_EQ(result, 0);
}

TEST(ProgargsTest, InvalidNumberOfArguments) {
  int const argc = 3;
  std::vector<std::string> const arguments = {"10", "small.fld"};

  int const result = progargs(argc, arguments);

  ASSERT_EQ(result, -1);
}

TEST(ProgargsTest, InvalidTimeSteps) {
  int const argc = 4;
  std::vector<std::string> const arguments = {"aa", "small.fld",
                                              "out/test.fld"};

  int const result = progargs(argc, arguments);

  ASSERT_EQ(result, -1);
}

TEST(ProgargsTest, NegativeTimeSteps) {
  int const argc = 4;
  std::vector<std::string> const arguments = {"-10", "small.fld",
                                              "out/test.fld"};

  int const result = progargs(argc, arguments);

  ASSERT_EQ(result, -2);
}

TEST(ProgargsTest, CannotOpenInputFile) {
  int const argc = 4;
  std::vector<std::string> const arguments = {"10", "nonexistent.fld",
                                              "out/test.fld"};

  int const result = progargs(argc, arguments);

  ASSERT_EQ(result, -3);
}

TEST(ProgargsTest, CannotOpenOutputFile) {
  int const argc = 4;
  std::vector<std::string> const arguments = {"10", "small.fld",
                                              "out/nonexistent.fld"};

  int const result = progargs(argc, arguments);

  ASSERT_EQ(result, -4);
}
