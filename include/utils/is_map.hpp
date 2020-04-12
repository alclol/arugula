#ifndef IS_MAP_H
#define IS_MAP_H

#include <map>
#include <type_traits>
#include <utility>

//specialize a type for all of the STL containers.
namespace is_map_impl {
    template <typename T>       struct is_map :std::false_type {};
    template <typename... Args> struct is_map<std::map               <Args...>> :std::true_type {};
}

//type trait to utilize the implementation type traits as well as decay the type
template <typename T> struct is_map {
    static constexpr bool const value = is_map_impl::is_map<std::decay_t<T>>::value;
};

#endif // IS_MAP_H