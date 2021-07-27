#include "ecpp/static_vector.hpp"
#include "initializer_list_helper.hpp"

#include <gtest/gtest.h>

#include <vector>


using namespace ecpp::testing;

constexpr std::size_t Capacity{10};

TEST(ecpp_static_vector, non_member_equality_comparison_operator) {
    ecpp::static_vector<int, 10> r1{1, 0, 1, 0, 1, 0, 2, 2, 1, 3};
    auto                         r1c = r1;                         // Exact copy
    ecpp::static_vector<int, 10> r2{1, 0, 1, 0, 1, 0, 2, 2, 1, 4}; // Last element different
    ecpp::static_vector<int, 10> r3{1, 0, 1, 0, 1, 0, 2, 2, 1};    // One element less

    EXPECT_TRUE(r1 == r1c);
    EXPECT_FALSE(r1 == r2);
    EXPECT_FALSE(r1 == r3);
    EXPECT_FALSE(r2 == r3);

    // Modify r1 to remove last element
    r1.pop_back();
    EXPECT_FALSE(r1 == r1c);
    EXPECT_FALSE(r1 == r2);
    EXPECT_TRUE(r1 == r3);
}


TEST(ecpp_static_vector, non_member_three_way_comparison_operator) {
    ecpp::static_vector<int, 10> r1{1, 0, 1, 0, 1, 0, 2, 2, 1, 3};
    auto                         r1c = r1;                         // Exact copy
    ecpp::static_vector<int, 10> r2{1, 0, 1, 0, 1, 0, 2, 2, 1, 4}; // Last element different
    ecpp::static_vector<int, 10> r3{1, 0, 1, 0, 1, 0, 2, 2, 1};    // One element less

    EXPECT_EQ(r1 <=> r1c, std::strong_ordering::equivalent);
    EXPECT_EQ(r1 <=> r2, std::strong_ordering::less);
    EXPECT_EQ(r1 <=> r3, std::strong_ordering::greater);
    EXPECT_EQ(r2 <=> r3, std::strong_ordering::greater);


    // Modify r1 to remove last element
    r1.pop_back();
    EXPECT_NE(r1 <=> r1c, std::strong_ordering::equivalent);
    EXPECT_EQ(r1 <=> r1c, std::strong_ordering::less);
    EXPECT_EQ(r1 <=> r2, std::strong_ordering::less);
    EXPECT_EQ(r1 <=> r3, std::strong_ordering::equivalent);
}


TEST(ecpp_static_vector, non_member_swap) {
    ecpp::static_vector<int, 10> r1{1, 0, 1, 0, 1, 0, 2, 2, 1, 3};
    auto                         r1c = r1;

    ecpp::static_vector<int, 10> r2{3, 7};
    auto                         r2c = r2;

    ecpp::swap(r1, r2);

    EXPECT_EQ(r1, r2c);
    EXPECT_EQ(r2, r1c);
}


TEST(ecpp_static_vector, non_member_erase) {
    ecpp::static_vector<int, 10> before{1, 0, 1, 0, 1, 0, 2, 2, 1, 3};

    EXPECT_EQ(before.size(), 10);
    ecpp::erase(before, 4); // Should remove nothing
    EXPECT_EQ(before.size(), 10);
    EXPECT_EQ(before, before);

    ecpp::erase(before, 0); // Should remove 3 elements
    ecpp::static_vector<int, 10> expected{1, 1, 1, 2, 2, 1, 3};
    EXPECT_EQ(before.size(), 7);
    EXPECT_EQ(before, expected);
}


TEST(ecpp_static_vector, non_member_erase_if) {
    ecpp::static_vector<int, 10> before{1, 0, 1, 0, 1, 0, 2, 2, 1, 3};

    EXPECT_EQ(before.size(), 10);
    ecpp::erase_if(before, [](auto const& i) { return i == 4; }); // Should remove nothing
    EXPECT_EQ(before.size(), 10);
    EXPECT_EQ(before, before);

    ecpp::erase_if(before, [](auto const& i) { return i == 0; }); // Should remove 3 elements
    ecpp::static_vector<int, 10> expected{1, 1, 1, 2, 2, 1, 3};
    EXPECT_EQ(before.size(), 7);
    EXPECT_EQ(before, expected);

    ecpp::erase_if(before, [](auto const& i) { return i == 1 || i == 2 || i == 3; }); // Should remove remaining elements
    EXPECT_EQ(before.size(), 0);
}
