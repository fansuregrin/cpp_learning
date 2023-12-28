// topic: `using` directives

// A using directive begins with the keyword using, followed by the keyword namespace, 
// followed by a namespace name. These directives make all the names from a specific 
// namespace visible without qualification. 

namespace blip {
    int i = 16, j = 15, k = 23;
}

int j = 0;  // ok: j inside blip is hidden inside a namespace

void manip() {
    // using directive; the names in blip are ''added'' to the global scope
    using namespace blip;  // clash between ::j and blip::j

    ++i;  // sets blip::i to 17
    // ++j;  // error: reference to ‘j’ is ambiguous

    ++::j;  // ok: sets global j to 1
    ++blip::j;  // ok: sets blip::j to 16
    int k = 97;  // local k hides blip::k
    ++k;  // sets local k to 98
}

int main() {
    
}