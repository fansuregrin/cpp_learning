// topic: Argument-Dependent Lookup and Overloading

namespace NS {
    class Quote { /* ... */ };

    void display(const Quote&) { /*...*/ }
}

class BulkItem: public NS::Quote { /*...*/ };

int main() {
    BulkItem b;

    // The candidate functions for the call to display are not only the functions with declarations
    // that are in scope where display is called, but also the functions in the namespace where
    // Bulk_item and its base class, Quote, are declared. The function display(const Quote&)
    // declared in namespace NS is added to the set of candidate functions.
    display(b);
}