#include "ast.h"
#include "calc.h"

#include "gtest/gtest.h"

TEST(Calculator, Sum) {
    ASSERT_EQ(4, Eval(Parse("2 + 2").get()));
}

TEST(Calculator, Product) {
    ASSERT_EQ(4, Eval(Parse("2 * 2").get()));
}
