#include "gtest/gtest.h"
#include <iostream>

int factorial(int n) { return 1; }

TEST(checkVar, shouldGiveCorrect)
{

    EXPECT_EQ(factorial(1), 1);
}