#pragma once

#include <type_traits>


// for use in a template arguments list
// template<typename T, ENABLE_IF(std::is_integral<T>::value)>

#define ENABLE_IF(e) typename = typename std::enable_if<(e)>::type
