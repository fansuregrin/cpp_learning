// topic: understanding `std::move`

#include <string>
#include <type_traits>
#include <utility>


// The definiton of `std::move` may like this:
//
// template <typename T>
// typename remove_reference<T>::type&& move(T&& t)
// {
//     // static_cast covered in § 4.11.3 (p. 163)
//     return static_cast<typename remove_reference<T>::type&&>(t);
// }

int main() {
    std::string s1("hi!"), s2;

    s2 = std::move(std::string("bye!"));  // ok: moving from an rvalue
    /* 1) the argument to `move` is the rvalue result of the `string` constructor, `string("bye")`.
        - The deduced type of `T` is `string`.
        - Therefore, `remove_reference` is instantiated with `string`.
        - The `type` member of `remove_reference<string>` is `string`.
        - The return type of `move` is `string&&`.
        - `move`’s function parameter, `t`, has type `string&&`.
      this call instantiates move<string>, which is the function `string&& move(string &&t)`
    */

    s2 = std::move(s1);  // ok: but after the assigment s1 has indeterminate value
    /* 2) the argument to `move` is an lvalue.
        - The deduced type of `T` is `string&` (reference to `string`, not plain `string`).
        - Therefore, `remove_reference` is instantiated with `string&`.
        - The `type` member of `remove_reference<string&>` is `string`,
        - The return type of `move` is still `string&&`.
        - `move`’s function parameter, `t`, instantiates as `string& &&`, which collapses to `string&`.
       this call instantiates `move<string&>`, which is `string&& move(string &t)`.
    */

    return 0;
}