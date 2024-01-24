#include "ecpp/static_vector.hpp"
#include "initializer_list_helper.hpp"

#include <gtest/gtest.h>

#include <vector>

using namespace ecpp::testing;

constexpr std::size_t Capacity{10};

TEST(ecpp_static_vector, iterator_begin) {
  auto iList = initializer_sequence<int, Capacity>()();

  ecpp::static_vector<int, Capacity> temp(iList);

  auto begin = temp.begin();
  EXPECT_EQ(begin, temp.data());

  auto cbegin = temp.cbegin();
  EXPECT_EQ(cbegin, temp.data());

  ecpp::static_vector<int, Capacity> const tempC(iList);

  auto beginC = tempC.begin();
  EXPECT_EQ(beginC, tempC.data());
}

TEST(ecpp_static_vector, iterator_end) {
  auto iList = initializer_sequence<int, Capacity>()();

  ecpp::static_vector<int, Capacity> temp(iList);

  auto end = temp.end();
  EXPECT_EQ(end, temp.data() + Capacity);

  auto cend = temp.cend();
  EXPECT_EQ(cend, temp.data() + Capacity);

  ecpp::static_vector<int, Capacity> const tempC(iList);

  auto endC = tempC.end();
  EXPECT_EQ(endC, tempC.data() + Capacity);
}

TEST(ecpp_static_vector, iterator_rbegin) {
  auto iList = initializer_sequence<int, Capacity>()();

  ecpp::static_vector<int, Capacity> temp(iList);

  auto rbegin = temp.rbegin();
  EXPECT_EQ(rbegin.base(), temp.data() + Capacity);

  ecpp::static_vector<int, Capacity> const tempC(iList);

  auto rbeginC = tempC.rbegin();
  EXPECT_EQ(rbeginC.base(), tempC.data() + Capacity);
}

TEST(ecpp_static_vector, iterator_rend) {
  auto iList = initializer_sequence<int, Capacity>()();

  ecpp::static_vector<int, Capacity> temp(iList);

  auto rend = temp.rend();
  EXPECT_EQ(rend.base(), temp.data());

  ecpp::static_vector<int, Capacity> const tempC(iList);

  auto rendC = tempC.rend();
  EXPECT_EQ(rendC.base(), tempC.data());
}
