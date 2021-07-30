#include "ecpp/static_vector.hpp"
#include "initializer_list_helper.hpp"

#include <gtest/gtest.h>

#include <vector>


using namespace ecpp::testing;

constexpr std::size_t Capacity{10};

TEST(ecpp_static_vector, access_at) {
    auto iList = initializer_sequence<int, Capacity>()();

    ecpp::static_vector<int, Capacity> temp(iList);

    for (std::size_t i = 0; i != Capacity; ++i) {
        auto& v = temp.at(i);
        EXPECT_EQ(std::data(iList)[i], v);
    }

    ecpp::static_vector<int, Capacity> const tempC(iList);

    for (std::size_t i = 0; i != Capacity; ++i) {
        auto const& vC = temp.at(i);
        EXPECT_EQ(std::data(iList)[i], vC);
    }

    

#ifndef ECPP_NOEXCEPT
    EXPECT_THROW(temp.at(Capacity), std::out_of_range);
    EXPECT_THROW(tempC.at(Capacity), std::out_of_range);
#else

#endif
}

TEST(ecpp_static_vector, access_operator) {
    auto iList = initializer_sequence<int, Capacity>()();

    ecpp::static_vector<int, Capacity> temp(iList);

    for (std::size_t i = 0; i != Capacity; ++i) {
        auto& v = temp[i];
        EXPECT_EQ(std::data(iList)[i], v);
    }

    ecpp::static_vector<int, Capacity> const tempC(iList);

    for (std::size_t i = 0; i != Capacity; ++i) {
        auto const& vC = temp[i];
        EXPECT_EQ(std::data(iList)[i], vC);
    }
}


TEST(ecpp_static_vector, access_front) {
    auto iList = initializer_sequence<int, Capacity>()();

    ecpp::static_vector<int, Capacity> temp(iList);
    auto& v = temp.front();
    EXPECT_EQ(0, v);


    ecpp::static_vector<int, Capacity> const tempC(iList);
    auto const& vC = temp.front();
    EXPECT_EQ(0, vC);
}


TEST(ecpp_static_vector, access_back) {
    auto iList = initializer_sequence<int, Capacity>()();

    ecpp::static_vector<int, Capacity> temp(iList);
    auto& v = temp.back();
    EXPECT_EQ(Capacity - 1, v);


    ecpp::static_vector<int, Capacity> const tempC(iList);

    auto const& vC = temp.back();
    EXPECT_EQ(Capacity - 1, vC);
}


TEST(ecpp_static_vector, access_data) {
    auto iList = initializer_sequence<int, Capacity>()();

    ecpp::static_vector<int, Capacity> temp(iList);
    auto data = temp.data();
    for (std::size_t i = 0; i != Capacity; ++i) {
        EXPECT_EQ(&temp[i], data + i);
    }


    ecpp::static_vector<int, Capacity> const tempC(iList);

    auto const dataC = temp.data();
    for (std::size_t i = 0; i != Capacity; ++i) {
        EXPECT_EQ(&temp[i], dataC + i);
    }
}
