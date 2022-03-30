#include "ecpp/static_vector.hpp"
#include "initializer_list_helper.hpp"

#include <gtest/gtest.h>

#include <vector>

using namespace ecpp::testing;

constexpr std::size_t Capacity{10};


TEST(ecpp_static_vector, assignment_with_copy_assignment_operator) {
    auto                               iList = initializer_sequence<int, Capacity>()();
    ecpp::static_vector<int, Capacity> temp_src(iList);

    // Case when destination is empty
    ecpp::static_vector<int, Capacity> temp_dst1;
    EXPECT_EQ(temp_dst1.size(), 0);

    temp_dst1 = temp_src;

    EXPECT_EQ(temp_dst1.size(), Capacity);
    EXPECT_EQ(temp_dst1, temp_src);

    // Case when destination is non-empty
    ecpp::static_vector<int, Capacity> temp_dst2(1);
    EXPECT_EQ(temp_dst2.size(), 1);

    temp_dst2 = temp_src;

    EXPECT_EQ(temp_dst2.size(), Capacity);
    EXPECT_EQ(temp_dst2, temp_src);
}


TEST(ecpp_static_vector, assignment_with_move_assignment_operator) {
    auto                               iList = initializer_sequence<int, Capacity>()();
    ecpp::static_vector<int, Capacity> temp_src1(iList);
    ecpp::static_vector<int, Capacity> temp_src2(iList);

    // Case when destination is empty
    ecpp::static_vector<int, Capacity> temp_dst1;
    EXPECT_EQ(temp_dst1.size(), 0);

    temp_dst1 = std::move(temp_src1);

    EXPECT_EQ(temp_dst1.size(), Capacity);
    EXPECT_TRUE(std::equal(temp_dst1.begin(), temp_dst1.end(), iList.begin(), iList.end()));

    // Case when destination is non-empty
    ecpp::static_vector<int, Capacity> temp_dst2(1);
    EXPECT_EQ(temp_dst2.size(), 1);

    temp_dst2 = std::move(temp_src2);

    EXPECT_EQ(temp_dst2.size(), Capacity);
    EXPECT_TRUE(std::equal(temp_dst2.begin(), temp_dst2.end(), iList.begin(), iList.end()));
}


TEST(ecpp_static_vector, assignment_with_operator_from_initializer_list) {
    auto iList = initializer_sequence<int, Capacity>()();

    // Case when destination is empty
    ecpp::static_vector<int, Capacity> temp1;
    EXPECT_EQ(temp1.size(), 0);

    temp1 = iList;

    EXPECT_EQ(temp1.size(), Capacity);
    EXPECT_TRUE(std::equal(temp1.begin(), temp1.end(), iList.begin(), iList.end()));

    // Case when destination is non-empty
    ecpp::static_vector<int, Capacity> temp2(1);
    EXPECT_EQ(temp2.size(), 1);

    temp2 = iList;

    EXPECT_EQ(temp2.size(), Capacity);
    EXPECT_TRUE(std::equal(temp2.begin(), temp2.end(), iList.begin(), iList.end()));


    auto tryAssignToLargeList = []() {
        auto                               iListTooBig = initializer_sequence<int, Capacity + 1>()();
        ecpp::static_vector<int, Capacity> _;
        _ = iListTooBig;
    };
#ifdef __cpp_exceptions
    EXPECT_THROW(tryAssignToLargeList(), std::length_error);
#else
    EXPECT_DEATH(tryAssignToLargeList(), "");
#endif
}


TEST(ecpp_static_vector, assignment_with_assign_count_copies) {
    // Case when destination is empty
    ecpp::static_vector<int, Capacity> temp1;
    EXPECT_EQ(temp1.size(), 0);

    temp1.assign(Capacity, 1);

    EXPECT_EQ(temp1.size(), Capacity);
    EXPECT_EQ(std::count(temp1.begin(), temp1.end(), 1), Capacity);

    // Case when destination is non-empty
    ecpp::static_vector<int, Capacity> temp2(1);
    EXPECT_EQ(temp2.size(), 1);

    temp2.assign(Capacity, 1);

    EXPECT_EQ(temp2.size(), Capacity);
    EXPECT_EQ(std::count(temp2.begin(), temp2.end(), 1), Capacity);


    auto tryAssignToLargeList = []() {
        ecpp::static_vector<int, Capacity> _;
        _.assign(Capacity + 1, 1);
    };
#ifdef __cpp_exceptions
    EXPECT_THROW(tryAssignToLargeList(), std::length_error);
#else
    EXPECT_DEATH(tryAssignToLargeList(), "");
#endif
}


TEST(ecpp_static_vector, assignment_with_assign_from_range) {
    auto             iList = initializer_sequence<int, Capacity>()();
    std::vector<int> temp_src(iList);

    // Case when destination is empty
    ecpp::static_vector<int, Capacity> temp_dst1;
    EXPECT_EQ(temp_dst1.size(), 0);

    temp_dst1.assign(temp_src.begin(), temp_src.end());

    EXPECT_EQ(temp_dst1.size(), Capacity);
    EXPECT_TRUE(std::equal(temp_dst1.begin(), temp_dst1.end(), temp_src.begin(), temp_src.end()));

    // Case when destination is non-empty
    ecpp::static_vector<int, Capacity> temp_dst2(1);
    EXPECT_EQ(temp_dst2.size(), 1);

    temp_dst2.assign(temp_src.begin(), temp_src.end());

    EXPECT_EQ(temp_dst2.size(), Capacity);
    EXPECT_TRUE(std::equal(temp_dst2.begin(), temp_dst2.end(), temp_src.begin(), temp_src.end()));


    auto tryAssignToLargeRange = []() {
        auto                               iListTooLarge = initializer_sequence<int, Capacity + 1>()();
        std::vector<int>                   temp_src(iListTooLarge);
        ecpp::static_vector<int, Capacity> _;
        _.assign(temp_src.begin(), temp_src.end());
    };
#ifdef __cpp_exceptions
    EXPECT_THROW(tryAssignToLargeRange(), std::length_error);
#else
    EXPECT_DEATH(tryAssignToLargeRange(), "");
#endif
}


TEST(ecpp_static_vector, assignment_with_assign_from_initializer_list) {
    auto iList = initializer_sequence<int, Capacity>()();

    // Case when destination is empty
    ecpp::static_vector<int, Capacity> temp1;
    EXPECT_EQ(temp1.size(), 0);

    temp1.assign(iList);

    EXPECT_EQ(temp1.size(), Capacity);
    EXPECT_TRUE(std::equal(temp1.begin(), temp1.end(), iList.begin(), iList.end()));

    // Case when destination is non-empty
    ecpp::static_vector<int, Capacity> temp2(1);
    EXPECT_EQ(temp2.size(), 1);

    temp2.assign(iList);

    EXPECT_EQ(temp2.size(), Capacity);
    EXPECT_TRUE(std::equal(temp2.begin(), temp2.end(), iList.begin(), iList.end()));


    auto tryAssignToLargeList = []() {
        auto                               iListTooBig = initializer_sequence<int, Capacity + 1>()();
        ecpp::static_vector<int, Capacity> _;
        _.assign(iListTooBig);
    };
#ifdef __cpp_exceptions
    EXPECT_THROW(tryAssignToLargeList(), std::length_error);
#else
    EXPECT_DEATH(tryAssignToLargeList(), "");
#endif
}
