// topic: copy constructor
//
// Copy initialization *ordinarily* uses the copy constructor.
// Copy initialization happens when:
//   1) Define variables using an `=`
//   2) Pass an object as an argument to a parameter of nonreference type
//   3) Return an object from a function that has a nonreference return type
//   4) Brace initialize the elements in an array or the members of an aggregate class

#include <iostream>
#include <vector>

using namespace std;

class Point {
public:
    Point() {
        cout << "calling default constructor" << endl;
    }

    Point(const Point & other) {
        cout << "calling copy constructor" << endl;
    }

    Point& operator=(const Point& rhs) {
        cout << "calling copy assignment operator" << endl;
        return *this;
    }
};

Point global; // calling default constructor

Point foo_bar(Point arg) {  // using an argument to initialize a non-reference parameter calls the copy-constructor
    // using `arg` to initialize `local` calls the copy constructor
    // using `global` to initialize the newly allocated `Point` calls the copy constructor
    Point local = arg, *heap = new Point(global);
    
    // calling copy assignment operator
    *heap = local;

    // using `local` and `*heap` to initialize the first two elements in the array `pa`
    // calls the copy constructor twice
    // calling default constructor twice to initialize the last two elements in the array
    Point pa[4] = {local, *heap};

    return *heap;
}

int main() {
    Point a;  // calling default constructor

    cout << "---------------" << endl;
    // returning a non-reference value from a function to initialize the variable
    // at the call site calls the copy constructor
    Point b = foo_bar(a);

    cout << "---------------" << endl;
    vector<Point> vec{Point(), Point()};
    cout << "capacity of vec: " << vec.capacity() << endl;  // 2
    cout << "---------------" << endl;
    vec.push_back(a);  // calls copy constructor 3 times, maybe move from old place to new place in the memory
    cout << "capacity of vec: " << vec.capacity() << endl;  // 4
    // calls copy constructor only once because the space allocated 
    // to the container can also accommodate a new element
    vec.push_back(b);

    return 0;
}