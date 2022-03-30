#include "ecpp/static_vector.hpp"
#include "initializer_list_helper.hpp"

#include <gtest/gtest.h>

#include <vector>


using namespace ecpp::testing;

constexpr std::size_t Capacity{10};

TEST(ecpp_static_vector, modifier_clear) {
    auto iList = initializer_sequence<int, Capacity>()();

    ecpp::static_vector<int, Capacity> temp(iList);
    EXPECT_EQ(temp.size(), Capacity);
    EXPECT_FALSE(temp.empty());

    temp.clear();
    EXPECT_EQ(temp.size(), 0);
    EXPECT_TRUE(temp.empty());
}

TEST(ecpp_static_vector, modifier_insert_copy_single) {
    static_assert(Capacity >= 4);

    ecpp::static_vector<int, Capacity> temp;
    EXPECT_TRUE(temp.empty());

    // Insert at the beginning in empty vector
    int  v1   = 42;
    auto pos1 = temp.insert(temp.begin(), v1);
    EXPECT_FALSE(temp.empty());
    EXPECT_EQ(temp.size(), 1);
    EXPECT_EQ(pos1, temp.begin());
    EXPECT_EQ(*pos1, v1);

    // Insert at the end
    int  v2   = 44;
    auto pos2 = temp.insert(temp.end(), v2);
    EXPECT_EQ(temp.size(), 2);
    EXPECT_EQ(pos2, temp.begin() + 1);
    EXPECT_EQ(*pos2, v2);

    // Insert in between
    int  v3   = 43;
    auto pos3 = temp.insert(pos2, v3);
    EXPECT_EQ(temp.size(), 3);
    EXPECT_EQ(pos3, temp.begin() + 1);
    EXPECT_EQ(*pos3, v3);
    EXPECT_EQ(temp.back(), v2);
    EXPECT_EQ(temp.front(), v1);
    for (auto i : temp) {
        std::cout << i << ' ';
    }

    // Insert at the beginning in non-empty vector
    int  v4   = 41;
    auto pos4 = temp.insert(temp.begin(), v4);
    EXPECT_FALSE(temp.empty());
    EXPECT_EQ(temp.size(), 4);
    EXPECT_EQ(pos4, temp.begin());
    EXPECT_EQ(temp.back(), v2);
    EXPECT_EQ(temp.front(), v4);
    EXPECT_EQ(*pos4, v4);

    int x{};
    // Fill untill full
    while (temp.size() < temp.max_size()) {
        temp.insert(temp.end(), x);
    }
    EXPECT_EQ(temp.size(), temp.max_size());

#ifdef __cpp_exceptions
    EXPECT_THROW(temp.insert(temp.end(), x), std::length_error);
    EXPECT_THROW(temp.insert(temp.begin(), x), std::length_error);
#else
    EXPECT_DEATH(temp.insert(temp.end(), x), "");
    EXPECT_DEATH(temp.insert(temp.begin(), x), "");
#endif
}


TEST(ecpp_static_vector, modifier_insert_move_single) {
    //                 constexpr iterator insert(const_iterator pos, T&& value) ==  LengthError
}


TEST(ecpp_static_vector, modifier_insert_move_count) {
    // constexpr iterator insert(const_iterator pos, size_type count, T const& value) {  LengthError
}

TEST(ecpp_static_vector, modifier_insert_range) {
    //        template<class InputIt> constexpr iterator insert(const_iterator pos, InputIt first, InputIt last) {  LengthError
}


TEST(ecpp_static_vector, modifier_insert_from_initializer_list) {
    //  constexpr iterator insert(const_iterator pos, std::initializer_list<T> ilist) { LengthError
}
