// the `tuple` type

#include <tuple>
#include <vector>
#include <list>
#include <string>

using namespace std;

int main() {
    /* Defining and Initializing `tuple`s */
    tuple<size_t, size_t, size_t> threeD;  // all three members set to 0
    tuple<int, double, string> tp = {1, 0.3, "hi"};  // Is the contructor of `tuple` explicit? 
    tuple<int, double, string> tp2{1, 0.3, "hi"};
    tuple<string, vector<double>, int, list<int>> 
        someVal("constants", {3.14, 2.718}, 42, {0,1,2,3,4,5});
    // tuple that represents a bookstore transaction: ISBN, count, price per book
    auto item = make_tuple("0-999-78345-X", 3, 20.00);
    
    /* Accessing the Members of a tuple */
    auto book = get<0>(item);  // returns the first member of `item`
    auto cnt = get<1>(item);   // returns the second member of `item`
    auto price = get<2>(item); // returns the last member of item

    get<2>(item) *= 0.8;  // apply 20% discount

    typedef decltype(item) trans;  // trans is the type of item
    // returns the number of members in object's of type trans
    size_t sz = tuple_size<trans>::value;  // returns 3
    // count has the same type as the second member in item
    tuple_element<1, trans>::type count = get<1>(item); // count is an int

    /* Relational and Equality Operators */
    tuple<string, string> duo("1", "2");
    tuple<size_t, size_t> twoD(1, 2);
    // duo == twoD; // error: can't compare a size_t and a string
    tuple<size_t, size_t, size_t> threeD_(1, 2, 3);
    // twoD == threeD_; // error: static assertion failed: tuple objects can only be compared if they have equal sizes
    // twoD < threeD_; // error!
    tuple<size_t, size_t> origin(0, 0);
    origin < twoD; // true

    return 0;
}