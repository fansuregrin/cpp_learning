#ifndef PRINT_TUPLE_HPP
#define PRINT_TUPLE_HPP

#include <iostream>
#include <tuple>


template <size_t Index, size_t N, typename... Args>
struct print_tuple {
    static void print(std::ostream &os, const std::tuple<Args...> &t) {
        os << std::get<Index>(t) << (Index+1 == N ? "" : ",");
        print_tuple<Index+1, N, Args...>::print(os, t);
    }
};

template <size_t N, typename... Args>
struct print_tuple<N, N, Args...> {
    static void print(std::ostream &os, const std::tuple<Args...> &t) {}
};

template <typename... Args>
std::ostream& operator<<(std::ostream &os, const std::tuple<Args...> &t) {
    os << '[';
    print_tuple<0, sizeof...(Args), Args...>::print(os, t);
    return os << ']';
}

#endif