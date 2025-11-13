#include <gtest/gtest.h>
extern "C" char *func(int num, int base);

TEST(FuncBaseConvert, PowersOfTwo) {
    struct TestCase {
        int num;
        int base;
        const char *expected;
    } tests[] = {
        {5, 1, "101"},
        {15, 1, "1111"},
        {33, 2, "201"},
        {255, 3, "377"},
        {1234, 4, "4D2"},
        {1023, 5, "VV"},
        {0, 1, "0"},
        {0, 4, "0"},
        {31, 1, "11111"},
        {127, 3, "177"},
        {63, 2, "333"},
        {255, 4, "FF"},
        {100, 5, "34"},
        {1, 3, "1"},
        {2, 2, "2"},
    };
    for (int i = 0; i < 15; ++i) {
        char *result = func(tests[i].num, tests[i].base);
        std::cout << "Test " << i+1 << ": num=" << tests[i].num << " base=" << tests[i].base
                  << ", got=\"" << result << "\", expected=\"" << tests[i].expected << "\"\n";
        EXPECT_STREQ(result, tests[i].expected)
            << "num=" << tests[i].num << " base=" << tests[i].base << " (Test #" << i+1 << ")";
    }
}
