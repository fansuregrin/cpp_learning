// Topic: conversions
// 
// Converting constructors and conversion operators define `class-type conversions`.
// Such conversions are also referred to as `user-defined conversions`.

#include <cstddef>
#include <stdexcept>
#include <iostream>

using namespace std;

class SmallInt {
public:
    // a non-explicit constructor that can be called with
    // one argument defines an implicit conversion.
    // Such constructors convert an object from
    // the argument’s type to the class type.

    SmallInt(int i): val(i) {
        if (i<0 || i>255) {
            throw out_of_range("Bad SmallInt value");
        }
    }

    // We can also define conversions from the class type. We define a 
    // conversion from a class type by defining a `conversion operator`.
    //
    // A conversion operator is a special kind of member function that 
    // converts a value of a class type to a value of some other type.
    // general form: `operator type() const;`, where type represents a type.
    // 
    // Conversion operators can be defined for any type (other than `void`)
    // that can be a function return type.
    // Conversions to `an array` or `a function type` are not permitted.
    // Conversions to `pointer types` — both data and function pointers
    // and to `reference types` are allowed.

    // A conversion function must be a member function;
    // may not specify a return type;
    // must have an empty parameter list.
    // The function usually should be `const`.

    // Although a conversion function does not specify a return type, each
    // conversion function must return a value of its corresponding type.

    operator int() const {
        return val;
    }
private:
    size_t val;
};

int main() {
    // implicitly converts 4(int) to `SmallInt` then calls `SmallInt::operator=`
    SmallInt si = 4;
    // implicitly converts `si` to `int` followed by integer addition
    cout << "si + 3 = " << si + 3 << endl;

    // the literal floating-point number (default as `double` type) is 
    // converted to `int` using the built-in conversion;
    // then, calls the `SmallInt(int)` constructor to convert the `int` to `SmallInt`.
    // After that, calls `SmallInt::operator=`.
    SmallInt si2 = 3.14;
    // the `SmallInt` conversion operator converts `si2` to `int`;
    // then `int` is converted to `double` using the built-in conversion
    cout << "si2 + 0.13 = " << si2 + 0.13 << endl;
}