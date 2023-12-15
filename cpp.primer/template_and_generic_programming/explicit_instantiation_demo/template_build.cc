// template_build.cc

#include <vector>
#include <string>
#include "compare.hpp"

using namespace std;

// instantiation file must provide a (nonextern) definition for every
// type and function that other files declare as extern

template int compare(const int&, const int&);
template class std::vector<string>;  // instantiates all members of the class template