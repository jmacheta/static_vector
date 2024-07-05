#ifndef TEST_TYPES_HPP_
#define TEST_TYPES_HPP_

#include <gtest/gtest.h>
#include <type_traits>
namespace ecpp::testing {
struct Base {
  int value;
  constexpr operator int() const { return value; }
};

struct NonDefaultConstructible : public Base {
  constexpr NonDefaultConstructible(int v) : Base{v} {}
};

struct NonMovable : public Base {
  constexpr NonMovable() : Base{11} {};
  constexpr NonMovable(int v) : Base{v} {}
  constexpr NonMovable(NonMovable const &) = default;
  constexpr NonMovable &operator=(NonMovable const &) = default;
  constexpr NonMovable(NonMovable &&) = delete;
  constexpr NonMovable &operator=(NonMovable &&) = delete;
  ~NonMovable() = default;
};

using Types = ::testing::Types<Base, NonDefaultConstructible, NonMovable>;

} // namespace ecpp::testing

template <typename T> struct StaticVector : public testing::Test {};

TYPED_TEST_SUITE(StaticVector, ecpp::testing::Types);

#endif
