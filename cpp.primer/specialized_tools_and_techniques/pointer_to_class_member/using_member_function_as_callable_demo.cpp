// topic: Using Member Functions as Callable Objects

#include <vector>
#include <string>
#include <algorithm>
#include <functional>

int main() {
    std::vector<std::string> svec = {"a", "", "bc"};
    std::vector<std::string *> pvec;

    /// Problem: we cannot directly pass a pointer to a member function to an algorithm.
    auto fp = &std::string::empty;  // fp points to the string empty function
    // error: must use ‘.*’ or ‘->*’ to call pointer-to-member function
    // std::find_if(svec.begin(), svec.end(), fp);

    /// Using `function` to Generate a Callable
    std::function<bool (const std::string&)> fcn = &std::string::empty;
    std::find_if(svec.begin(), svec.end(), fcn);
    std::function<bool (std::string *)> fp2 = &std::string::empty;
    std::find_if(pvec.begin(), pvec.end(), fp2);

    /// Using `mem_fn` to Generate a Callable
    // `mem_fn` will deduce the type of the callable from the type of the pointer to member
    std::find_if(svec.begin(), svec.end(), std::mem_fn(&std::string::empty));
    auto f = std::mem_fn(&std::string::empty);  // f takes a string or a string*
    f(*svec.begin());  // ok: passes a string object; f uses .* to call empty
    f(&svec[0]);  // ok: passes a pointer to string; f uses .-> to call empty

    /// Using `bind` to Generate a Callable
    using namespace std::placeholders;
    // bind each string in the range to the implicit first argument to empty
    std::find_if(svec.begin(), svec.end(), std::bind(&std::string::empty, _1));
    auto f2 = std::bind(&std::string::empty, _1);
    f2(*svec.begin());  // ok: passes a string object; f2 uses .* to call empty
    f2(&svec[0]);  // ok: passes a pointer to string; f2 uses .-> to call empty
}