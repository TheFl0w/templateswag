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
// </constants>

// <conditionals>
template<class T, class U>
struct is_same : false_type {};

template<class T>
struct is_same<T, T> : true_type {};

template<class T, class U>
static constexpr bool is_same_v = is_same<T, U>::value;

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
static constexpr bool is_void_v = is_void<T>::value;
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
// </tests>
