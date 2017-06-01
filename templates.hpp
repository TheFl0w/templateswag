#pragma once

// <constants>
template<class T, T v>
struct integral_constant {
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant;
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

template<bool b>
using bool_constant = integral_constant<bool, b>;

struct true_type : integral_constant<bool, true> {};
struct false_type : integral_constant<bool, false> {};

using nullptr_t = decltype(nullptr);
// </constants>

// <conditionals>
template<class T, class U>
struct is_same : false_type {};

template<class T>
struct is_same<T, T> : true_type {};

template<class T, class U>
constexpr bool is_same_v = is_same<T, U>::value;

template<bool p, class T, class F>
struct conditional { using type = F; };

template<class T, class F>
struct conditional<true, T, F> { using type = T; };

template<bool p, class T, class F>
using conditional_t = typename conditional<p, T, F>::type;
// </conditionals>

// <cv qualifiers>
template<class T>
struct remove_const { using type = T; };

template<class T>
struct remove_const<const T> { using type = T; };

template<class T>
using remove_const_t = typename remove_const<T>::type;

template<class T>
struct remove_volatile { using type = T; };

template<class T>
struct remove_volatile<volatile T> { using type = T; };

template<class T>
using remove_volatile_t = typename remove_volatile<T>::type;

template<class T>
struct remove_cv { using type = remove_const_t<remove_volatile_t<T>>; };

template<class T>
using remove_cv_t = typename remove_cv<T>::type;
// </cv qualifiers>

// <type categories>
template<class T>
struct is_void : is_same<remove_cv_t<T>, void> {};

template<class T>
constexpr bool is_void_v = is_void<T>::value;

template<class T>
struct is_null_pointer : is_same<remove_cv_t<T>, nullptr_t> {};

template<class T>
constexpr bool is_null_pointer_v = is_null_pointer<T>::value;

namespace details {
template<class T>
struct is_integral_impl;
} // namespace details

template<class T>
struct is_integral : details::is_integral_impl<remove_cv_t<T>> {};

template<class T>
constexpr bool is_integral_v = is_integral<T>::value;

namespace details {
template<class T>
struct is_integral_impl : false_type {};
template<>
struct is_integral_impl<bool> : true_type {};
template<>
struct is_integral_impl<char> : true_type {};
template<>
struct is_integral_impl<signed char> : true_type {};
template<>
struct is_integral_impl<short> : true_type {};
template<>
struct is_integral_impl<int> : true_type {};
template<>
struct is_integral_impl<long> : true_type {};
template<>
struct is_integral_impl<long long> : true_type {};
template<>
struct is_integral_impl<unsigned char> : true_type {};
template<>
struct is_integral_impl<unsigned short> : true_type {};
template<>
struct is_integral_impl<unsigned int> : true_type {};
template<>
struct is_integral_impl<unsigned long> : true_type {};
template<>
struct is_integral_impl<unsigned long long> : true_type {};
} // namespace details

// </type categories>

// <tests>
static_assert(integral_constant<bool, true>::value == true, "");
static_assert(is_same_v<integral_constant<bool, true>::value_type, bool>, "");
static_assert(is_same_v<integral_constant<bool, true>::type, integral_constant<bool, true>>, "");
static_assert(integral_constant<bool, true>() == true, "");
static_assert(integral_constant<bool, true>()() == true, "");

static_assert(bool_constant<true>::value == true, "");
static_assert(bool_constant<false>::value == false, "");

static_assert(true_type::value == true, "");
static_assert(false_type::value == false, "");

static_assert(is_same_v<void, void> == true, "");
static_assert(is_same_v<void, int> == false, "");

static_assert(is_same_v<conditional_t<true, true_type, false_type>, true_type>, "");
static_assert(is_same_v<conditional_t<false, true_type, false_type>, false_type>, "");
static_assert(is_void_v<int> == false, "");
static_assert(is_void_v<void> == true, "");

static_assert(is_same_v<remove_const_t<int>, int>, "");
static_assert(is_same_v<remove_const_t<const int>, int>, "");
static_assert(is_same_v<remove_volatile_t<int>, int>, "");
static_assert(is_same_v<remove_volatile_t<volatile int>, int>, "");
static_assert(is_same_v<remove_cv_t<const volatile int>, int>, "");

static_assert(is_void_v<void>, "");
static_assert(is_void_v<const volatile void>, "");
static_assert(!is_void_v<const volatile int>, "");

static_assert(is_null_pointer_v<nullptr_t>, "");
static_assert(is_null_pointer_v<const volatile nullptr_t>, "");
static_assert(!is_null_pointer_v<const volatile int>, "");

static_assert(is_integral_v<const volatile bool>, "");
static_assert(!is_integral_v<nullptr_t>, "");

// </tests>
