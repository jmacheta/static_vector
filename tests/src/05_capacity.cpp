#include "ecpp/static_vector.hpp"
#include "initializer_list_helper.hpp"

#include <gtest/gtest.h>

#include <vector>


using namespace ecpp::testing;

constexpr std::size_t Capacity{10};

TEST(ecpp_static_vector, capacity_empty) {
    ecpp::static_vector<int, Capacity> tempEmpty;
    EXPECT_TRUE(tempEmpty.empty());

    tempEmpty.push_back({});
    EXPECT_FALSE(tempEmpty.empty());

    auto                               iList = initializer_sequence<int, Capacity>()();
    ecpp::static_vector<int, Capacity> tempNonEmpty(iList);

    EXPECT_FALSE(tempNonEmpty.empty());

    tempNonEmpty.clear();
    EXPECT_TRUE(tempNonEmpty.empty());
}


TEST(ecpp_static_vector, capacity_size) {
    ecpp::static_vector<int, Capacity> tempEmpty;
    EXPECT_EQ(tempEmpty.size(), 0);

    tempEmpty.push_back({});
    EXPECT_EQ(tempEmpty.size(), 1);


    auto                               iList = initializer_sequence<int, Capacity>()();
    ecpp::static_vector<int, Capacity> tempNonEmpty(iList);
    EXPECT_EQ(tempNonEmpty.size(), Capacity);

    tempNonEmpty.pop_back();
    EXPECT_EQ(tempNonEmpty.size(), Capacity - 1);

    tempNonEmpty.clear();
    EXPECT_EQ(tempNonEmpty.size(), 0);
}


TEST(ecpp_static_vector, capacity_max_size) {
    ecpp::static_vector<int, Capacity> temp1;
    EXPECT_EQ(temp1.max_size(), Capacity);

    ecpp::static_vector<int, Capacity + 200> temp2;
    EXPECT_EQ(temp2.max_size(), Capacity + 200);
}


TEST(ecpp_static_vector, capacity_reserve) {
    ecpp::static_vector<int, Capacity> temp1;
    EXPECT_EQ(temp1.size(), 0);
    EXPECT_EQ(temp1.max_size(), Capacity);
    EXPECT_EQ(temp1.capacity(), Capacity);

    temp1.reserve(1);
    EXPECT_EQ(temp1.size(), 0);
    EXPECT_EQ(temp1.max_size(), Capacity);
    EXPECT_EQ(temp1.capacity(), Capacity);

    temp1.reserve(Capacity);
    EXPECT_EQ(temp1.size(), 0);
    EXPECT_EQ(temp1.max_size(), Capacity);
    EXPECT_EQ(temp1.capacity(), Capacity);

    EXPECT_THROW(temp1.reserve(Capacity + 1), std::length_error);
}


TEST(ecpp_static_vector, capacity_capacity) {
    ecpp::static_vector<int, Capacity> temp1;
    EXPECT_EQ(temp1.capacity(), Capacity);

    ecpp::static_vector<int, Capacity + 200> temp2;
    EXPECT_EQ(temp2.capacity(), Capacity + 200);
}


TEST(ecpp_static_vector, capacity_shrink_to_fit) {
    ecpp::static_vector<int, Capacity> temp1;
    EXPECT_EQ(temp1.size(), 0);
    EXPECT_EQ(temp1.capacity(), Capacity);

    temp1.shrink_to_fit();

    EXPECT_EQ(temp1.size(), 0);
    EXPECT_LE(temp1.capacity(), Capacity);

    auto                               iList = initializer_sequence<int, Capacity - 1>()();
    ecpp::static_vector<int, Capacity> temp2(iList);
    EXPECT_EQ(temp2.size(), Capacity - 1);
    EXPECT_EQ(temp2.capacity(), Capacity);

    temp2.shrink_to_fit();

    EXPECT_EQ(temp2.size(), Capacity - 1);
    EXPECT_LE(temp2.capacity(), Capacity);
}
