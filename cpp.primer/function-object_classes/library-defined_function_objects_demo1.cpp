/* Library-defined Funciton Objects
The standard library defines a set of classes that represent the arithmetic, relational,
and logical operators. Each class defines a call operator that applies the named
operation.

Arithmetic: plus(+), minus(-), multiplies(*), divides(/), modulus(%), negate(-)
Relational: equal_to(==), not_equal_to(!=), greater(>), greater_equal(>=), less(<), less_equal(<=)
Logical: logical_not(!), logical_and(&&), logical_or(||)
*/
#include <functional>

#include <iostream>

using namespace std;

int main() {
    // function object that can add two int values
    plus<int> int_add;
    // function object that can negate an int value
    negate<int> int_negate;
    // uses `int_add::operator(int, int)` to add 10 and 20
    cout << "sum = " << int_add(10, 20) << endl;
    // uses `int_negate::operator(int)` to negate the sum of 10 and 20
    cout << "sum = " << int_negate(int_add(10, 20)) << endl;

    return 0;
}