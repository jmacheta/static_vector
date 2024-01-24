#include "ecpp/static_vector.hpp"
#include "initializer_list_helper.hpp"

#include <gtest/gtest.h>

#include <vector>

using namespace ecpp::testing;

constexpr std::size_t Capacity{10};
TEST(ecpp_static_vector, construction_default) {
  ecpp::static_vector<int, Capacity> temp;
  EXPECT_EQ(temp.max_size(), Capacity);
  EXPECT_EQ(temp.capacity(), Capacity);
  EXPECT_EQ(temp.size(), 0);
}

TEST(ecpp_static_vector, construction_with_count_copies) {
  ecpp::static_vector<int, Capacity> temp(Capacity, -1);
  EXPECT_EQ(temp.max_size(), Capacity);
  EXPECT_EQ(temp.capacity(), Capacity);
  EXPECT_EQ(temp.size(), Capacity);

  for(auto i : temp) {
    EXPECT_EQ(i, -1);
  }

  auto tryConstructInvalidVector = []() { ecpp::static_vector<int, Capacity> _(Capacity + 1, {42}); };
#ifdef __cpp_exceptions
  EXPECT_THROW(tryConstructInvalidVector(), std::length_error);
#else
  EXPECT_DEATH(tryConstructInvalidVector(), "");
#endif
}

TEST(ecpp_static_vector, construction_with_count_default_inserted_instances) {
  ecpp::static_vector<int, Capacity> temp(Capacity);
  EXPECT_EQ(temp.max_size(), Capacity);
  EXPECT_EQ(temp.capacity(), Capacity);
  EXPECT_EQ(temp.size(), Capacity);

  auto tryConstructInvalidVector = []() { ecpp::static_vector<int, Capacity> _(Capacity + 1); };
#ifdef __cpp_exceptions
  EXPECT_THROW(tryConstructInvalidVector(), std::length_error);
#else
  EXPECT_DEATH(tryConstructInvalidVector(), "");
#endif
}

TEST(ecpp_static_vector, construction_from_range) {
  auto iList = initializer_sequence<int, Capacity>()();
  std::vector<int> temp_src(iList);

  ecpp::static_vector<int, Capacity> temp_dst(temp_src.begin(), temp_src.end());

  EXPECT_EQ(temp_dst.max_size(), Capacity);
  EXPECT_EQ(temp_dst.capacity(), Capacity);
  EXPECT_EQ(temp_dst.size(), temp_src.size());

  EXPECT_TRUE(std::equal(temp_src.begin(), temp_src.end(), temp_dst.begin(), temp_dst.end()));

  auto tryConstructInvalidVector = []() {
    auto iListTooBig = initializer_sequence<int, Capacity + 1>()();
    std::vector<int> temp_src(iListTooBig);
    ecpp::static_vector<int, Capacity> _(temp_src.begin(), temp_src.end());
  };
#ifdef __cpp_exceptions
  EXPECT_THROW(tryConstructInvalidVector(), std::length_error);
#else
  EXPECT_DEATH(tryConstructInvalidVector(), "");
#endif
}

TEST(ecpp_static_vector, construction_copy) {
  ecpp::static_vector<int, Capacity> temp_src(Capacity, -1);

  ecpp::static_vector<int, Capacity> temp_dst(temp_src);

  EXPECT_EQ(temp_dst.max_size(), temp_src.max_size());
  EXPECT_EQ(temp_dst.capacity(), temp_src.capacity());
  EXPECT_EQ(temp_dst.size(), temp_src.size());

  EXPECT_EQ(temp_src, temp_dst);
}

TEST(ecpp_static_vector, construction_move) {
  ecpp::static_vector<int, Capacity> temp_src(Capacity, -1);
  ecpp::static_vector<int, Capacity> temp_dst(std::move(temp_src));

  EXPECT_EQ(temp_dst.max_size(), temp_src.max_size());
  EXPECT_EQ(temp_dst.capacity(), temp_src.capacity());
  EXPECT_EQ(temp_dst.size(), temp_src.size());

  for(auto i : temp_dst) {
    EXPECT_EQ(i, -1);
  }

  // The equality of elements of both vectors MAY not be met when elements are not trivial
}

// TEST(ecpp_static_vector, construction_from_initializer_list) {
//     auto iList = initializer_sequence<int, Capacity>()();

//     ecpp::static_vector<int, Capacity> temp(iList);
//     EXPECT_EQ(temp.max_size(), Capacity);
//     EXPECT_EQ(temp.capacity(), Capacity);
//     EXPECT_EQ(temp.size(), Capacity);

//     EXPECT_TRUE(std::equal(temp.begin(), temp.end(), iList.begin(), iList.end()));

//     auto tryConstructInvalidVector = []() {
//         auto                               iListTooBig = initializer_sequence<int, Capacity + 1>()();
//         ecpp::static_vector<int, Capacity> _(iListTooBig);
//     };
// #ifdef __cpp_exceptions
//     EXPECT_THROW(tryConstructInvalidVector(), std::length_error);
// #else
//     EXPECT_DEATH(tryConstructInvalidVector(), "");
// #endif
// }
