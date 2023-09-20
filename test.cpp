#include "SimpleProfiler.h"
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

std::string empty_function()
{
    profile();
    return __FUNCTION__;
}

TEST(general_tests, empty_function_test)
{
    std::string func_name = empty_function();

    EXPECT_EQ(Timer::summary_map.size(), 1);
    EXPECT_EQ(func_name, "empty_function");
    EXPECT_EQ(Timer::summary_map[func_name].second.size(), 1);
    EXPECT_EQ(Timer::summary_map[func_name].first, Timer::summary_map[func_name].second[0]);
    EXPECT_LT(Timer::summary_map[func_name].first, 0.005);

    Timer::reset();
}

std::string another_empty_function()
{
    profile();
    return __FUNCTION__;
}

TEST(general_tests, multiple_call_test)
{
    int n = 5;
    std::string func_name;
    for(int i = 0; i<n; i++) func_name = another_empty_function();

    EXPECT_EQ(Timer::summary_map.size(), 1);
    EXPECT_EQ(func_name, "another_empty_function");
    EXPECT_EQ(Timer::summary_map[func_name].second.size(), n);

    double total_time = 0;
    for(auto& actual_time : Timer::summary_map[func_name].second)
        total_time += actual_time;

    EXPECT_EQ(Timer::summary_map[func_name].first, total_time);
    EXPECT_LT(Timer::summary_map[func_name].first, 0.005);

    Timer::reset();
}

std::string yet_another_empty_function()
{
    profile();
    return __FUNCTION__;
}

TEST(general_tests, multiple_function_test)
{
    int n = 5, m = 4, l = 3;
    std::string func_name1, func_name2, func_name3;
    for(int i = 0; i<n; i++) func_name1 = empty_function();
    for(int i = 0; i<m; i++) func_name2 = another_empty_function();
    for(int i = 0; i<l; i++) func_name3 = yet_another_empty_function();

    EXPECT_EQ(Timer::summary_map.size(), 3);

    EXPECT_EQ(func_name1, "empty_function");
    EXPECT_EQ(func_name2, "another_empty_function");
    EXPECT_EQ(func_name3, "yet_another_empty_function");

    EXPECT_EQ(Timer::summary_map[func_name1].second.size(), n);
    EXPECT_EQ(Timer::summary_map[func_name2].second.size(), m);
    EXPECT_EQ(Timer::summary_map[func_name3].second.size(), l);

    double total_time1 = 0;
    for(auto& actual_time : Timer::summary_map[func_name1].second)
        total_time1 += actual_time;
    EXPECT_EQ(Timer::summary_map[func_name1].first, total_time1);

        double total_time2 = 0;
    for(auto& actual_time : Timer::summary_map[func_name2].second)
        total_time2 += actual_time;
    EXPECT_EQ(Timer::summary_map[func_name2].first, total_time2);

        double total_time3 = 0;
    for(auto& actual_time : Timer::summary_map[func_name3].second)
        total_time3 += actual_time;
    EXPECT_EQ(Timer::summary_map[func_name3].first, total_time3);

    Timer::reset();
}