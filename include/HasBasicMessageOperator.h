#include <type_traits>

template <typename T>
struct has_cast_operator {
    template <typename U>
    static std::true_type test(decltype(static_cast<U>(std::declval<T>()))*);

    template <typename U>
    static std::false_type test(...);

    static constexpr bool value = decltype(test<T>(nullptr))::value;
};