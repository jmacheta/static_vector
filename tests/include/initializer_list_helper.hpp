#include <cstddef>
#include <utility>

namespace ecpp::testing {

    template<class T, std::size_t N> struct initializer_sequence {
        std::initializer_list<T> value;
        template<T... Values> constexpr initializer_sequence(std::integer_sequence<T, Values...>) : value{Values...} {};
        constexpr initializer_sequence() : initializer_sequence(std::make_integer_sequence<T, N>{}){};
        std::initializer_list<T> operator()() {
            return value;
        }
    };


} // namespace ecpp::testing