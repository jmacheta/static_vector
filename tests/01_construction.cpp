#include "ecpp/static_vector.hpp"
#include "initializer_list_helper.hpp"
#include "test_types.hpp"
#include <vector>

using namespace ecpp::testing;
using ecpp::static_vector;

constexpr std::size_t Capacity{10U};

TYPED_TEST(StaticVector, construction_default) {
  static_vector<TypeParam, Capacity> v;
  EXPECT_EQ(v.max_size(), Capacity);
  EXPECT_EQ(v.capacity(), Capacity);
  EXPECT_EQ(v.size(), 0);
}

TYPED_TEST(StaticVector, construction_n_copies) {
  static_vector<TypeParam, Capacity> v(Capacity, TypeParam(-1));
  EXPECT_EQ(v.max_size(), Capacity);
  EXPECT_EQ(v.capacity(), Capacity);
  EXPECT_EQ(v.size(), Capacity);

  for(auto const &i : v) {
    EXPECT_EQ(i, -1);
  }

  auto construct_invalid_element_count = []() { static_vector<TypeParam, Capacity> _(Capacity + 1, TypeParam(-1)); };
#ifdef __cpp_exceptions
  EXPECT_THROW(construct_invalid_element_count(), std::length_error);
#else
  EXPECT_DEATH(construct_invalid_element_count(), "");
#endif
}

TYPED_TEST(StaticVector, construction_n_default_inserted_instances) {

  if constexpr(std::is_default_constructible_v<TypeParam>) {
    static_vector<TypeParam, Capacity> v(Capacity);
    EXPECT_EQ(v.max_size(), Capacity);
    EXPECT_EQ(v.capacity(), Capacity);
    EXPECT_EQ(v.size(), Capacity);
    auto construct_invalid_element_count = []() { static_vector<TypeParam, Capacity> _(Capacity + 1); };
#ifdef __cpp_exceptions
    EXPECT_THROW(construct_invalid_element_count(), std::length_error);
#else
    EXPECT_DEATH(construct_invalid_element_count(), "");
#endif
  } else {
    EXPECT_FALSE((std::is_constructible_v<static_vector<TypeParam, Capacity>, std::size_t>));
  }
}

TYPED_TEST(StaticVector, construction_from_range) {
  static_vector<TypeParam, Capacity> src(Capacity, TypeParam(-1));
  static_vector<TypeParam, Capacity> v(src.begin(), src.end());

  EXPECT_EQ(v.max_size(), Capacity);
  EXPECT_EQ(v.capacity(), Capacity);
  EXPECT_EQ(v.size(), src.size());

  EXPECT_TRUE(std::equal(src.begin(), src.end(), v.begin(), v.end()));

  auto construct_from_too_big_range = []() {
    static_vector<TypeParam, Capacity + 1> too_big(Capacity + 1, TypeParam(-1));
    static_vector<TypeParam, Capacity> _(too_big.begin(), too_big.end());
  };
#ifdef __cpp_exceptions
  EXPECT_THROW(construct_from_too_big_range(), std::length_error);
#else
  EXPECT_DEATH(construct_from_too_big_range(), "");
#endif
}

TYPED_TEST(StaticVector, construction_copy) {
  static_vector<TypeParam, Capacity> src(Capacity, TypeParam(-1));
  static_vector<TypeParam, Capacity> dst(src);

  EXPECT_EQ(dst.max_size(), src.max_size());
  EXPECT_EQ(dst.capacity(), src.capacity());
  EXPECT_EQ(dst.size(), src.size());

  EXPECT_EQ(src, dst);
}

TYPED_TEST(StaticVector, construction_move) {
  static_vector<TypeParam, Capacity> src(Capacity, TypeParam(-1));
  // will fallback to copy if move is not allowed
  static_vector<TypeParam, Capacity> dst(std::move(src));

  EXPECT_EQ(dst.max_size(), Capacity);
  EXPECT_EQ(dst.capacity(), Capacity);
  EXPECT_EQ(dst.size(), Capacity);

  for(auto const &i : dst) {
    EXPECT_EQ(i, TypeParam(-1));
  }
}

TYPED_TEST(StaticVector, construction_from_initializer_list) {
  auto iList = std::initializer_list<TypeParam>{TypeParam(-1), TypeParam(0), TypeParam(1), TypeParam(2), TypeParam(3),
                                                TypeParam(4),  TypeParam(5), TypeParam(6), TypeParam(7), TypeParam(8)};
  if(Capacity < iList.size()) {
    GTEST_SKIP();
  }
  static_vector<TypeParam, Capacity> v(iList);
  EXPECT_EQ(v.max_size(), Capacity);
  EXPECT_EQ(v.capacity(), Capacity);
  EXPECT_EQ(v.size(), Capacity);

  EXPECT_TRUE(std::equal(v.begin(), v.end(), iList.begin(), iList.end()));

  auto construct_from_too_large_ilist = []() {
    auto iListTooBig = initializer_sequence<TypeParam, Capacity + 1>()();
    static_vector<TypeParam, Capacity> _(iListTooBig);
  };
#ifdef __cpp_exceptions
  EXPECT_THROW(construct_from_too_large_ilist(), std::length_error);
#else
  EXPECT_DEATH(construct_from_too_large_ilist(), "");
#endif
}
