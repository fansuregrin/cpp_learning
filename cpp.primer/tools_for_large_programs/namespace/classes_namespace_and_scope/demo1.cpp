// topic: name lookup for names used inside a namespace

// Name lookup for names used inside a namespace follows the normal lookup rules: The
// search looks **outward** through the enclosing scopes. An enclosing scope might be one
// or more nested namespaces, ending in the all-encompassing global namespace. 
// Only names that have been declared before the point of use that are in blocks that are still
// open are considered.

namespace A {
    int i;
    namespace B {
        int i;  // hides A::i within B
        int j;
        int f1() {
            int j;  // j is local to f1 and hides A::B::j
            return i;  // returns B::i
        }
    } // namespace B is closed and names in it are no longer visible

    // int f2() {
    //     // error: ‘j’ was not declared in this scope; did you mean ‘A::B::j’?
    //     return j;
    // }

    int j = i;  // initialized from A::i
}