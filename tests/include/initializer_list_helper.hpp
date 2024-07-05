#include <cstddef>
#include <utility>

namespace ecpp::testing {

template <class T, std::size_t N> class initializer_sequence {
  std::initializer_list<T> value;
  template <std::size_t... Args> constexpr initializer_sequence(std::index_sequence<Args...>) : value{T(Args)...} {};

public:
  constexpr initializer_sequence() : initializer_sequence(std::make_index_sequence<N>{}){};
  constexpr auto &operator()() const { return value; }
};

} // namespace ecpp::testing
