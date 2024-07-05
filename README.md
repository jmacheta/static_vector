# Drop-in replacement for std::vector with built-in storage

This package provides single-header C++20 library that defines container with std::vector interface, which uses statically_allocated storage instead of std::allocator.

[![Build status](https://github.com/jmacheta/static_vector/actions/workflows/cpp_unit_tests.yml/badge.svg)](https://github.com/jmacheta/static_vector/actions/workflows/cpp_unit_tests.yml)

## Installation

The easiest way is to use built-in CMake FetchContent:

```cmake
include(FetchContent)
FetchContent_Declare(
    ecpp_static_vector
    GIT_REPOSITORY https://github.com/jmacheta/static_vector.git
    GIT_TAG main
)

FetchContent_MakeAvailable(ecpp_static_vector)
```

Then add a dependency to your target:

```cmake
target_link_libraries(my_target PUBLIC ecpp_static_vector)
```

## Usage

The API of the component is compatible with std::vector one. I tried to implement every method in a meaningful way.
The main difference is a class declaration - You need to provide vector's capacity that will be built into it:

```cpp
#include <ecpp/static_vector>

ecpp::static_vector<int, 20> vec; // Creates static_vector with capacity to store 20 elements of type int
```

Now you can use it as you would use a std::vector. Please note that in order to avoid UB/throwing, you should check the size before each emplace/insertion:

```cpp
if(vec.size() < vec.capacity()) {
    vec.push_back(42);
} else {
    // Well... do anything but insertion ;)
}
```

If you are not sure, whether you need statically allocated storage, you can create a type alias to switch between static_vector and std::vector as you will:

```cpp
    inline constexpr std::size_t use_dynamic_storage{std::numeric_limits<std::size_t>::max()}; ///< Token to force dynamically allocated storage, instead of static one

    /**
     * @brief vector type that may use either statically, or dynamically allocated storage
     *
     * @tparam T value type
     * @tparam capacity Storage capacity (static_vector). When use_dynamic_storage is passed, changes to std::vector with dynamic allocation
     */
    template<class T, std::size_t capacity> class maybe_static_vector : public std::type_identity<static_vector<T, capacity>> {};
    template<class T> class maybe_static_vector<T, use_dynamic_storage> : public std::type_identity<std::vector<T>> {};

    template<class T, std::size_t capacity> using maybe_static_vector_t = typename maybe_static_vector<T, capacity>::type;
```

## Limitations

- Non-member functions are NOT defined in namespace std. If you need them, use __using namespace__.
- _reserve_ method is a NO-OP (unless you exceed capacity - then it throws)
- shrink_to_fit is a NO-OP
