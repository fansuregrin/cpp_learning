// topic: enumerations

// C++ has two kinds of enumerations: scoped and unscoped.The new standard
// introduced scoped enumerations. We define a scoped enumeration using the
// keywords enum class (or, equivalently, enum struct), followed by the
// enumeration name and a comma-separated list of enumerators enclosed in curly
// braces. A semicolon follows the close curly.

// scoped enumeration

enum class day {
    Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday
};

// unscoped enumeration

enum color {
    red, yellow, green
};

// unnamed, unscoped enumeration

enum {
    floatPrec = 6, doublePrec = 10, double_doublePrec = 10
};


/// The enumerator names in an unscoped enumeration are placed into 
/// the same scope as the enumeration itself.
// error: ‘red’ conflicts with a previous declaratio
// error: ‘yellow’ conflicts with a previous declaration
// error: ‘green’ conflicts with a previous declaration
// enum stoplight { red, yellow, green };

enum class peppers {
    // ok: enumerators are hidden
    red, yellow, green
};

// By default, enumerator values start at 0 and each enumerator has a value 1 greater
// than the preceding one. However, we can also supply initializers for one or more
// enumerators.

// An enumerator value need not be unique.
// Enumerators are const and, if initialized, their initializers must be constant expressions.

enum class intTypes {
    charTyp = 8, shortTyp = 16, intTyp = 16,
    longTyp = 32, longlongTyp = 64
};

/// Specifying the Size of an enum
// Under the new standard, we may specify that type by following the
// enum name with a colon and the name of the type we want to use.
// If we do not specify the underlying type, then by default scoped enums have **int** as
// the underlying type.

enum intValues : unsigned long long {
    charTyp = 255, shortTyp = 65535, intTyp = 65535,
    longTyp = 4294967295UL,
    long_longTyp = 18446744073709551615ULL
};

/// Forward Declarations for Enumerations
// Under the new standard, we can forward declare an enum. An enum forward
// declaration must specify (implicitly or explicitly) the underlying size of the enum.

// forward declaration of unscoped enum named flag
enum flag: unsigned long;  // unscoped, must specify a type
enum class open_mods;  // scoped enums can use int by default

// the size of the enum must be the same across all declarations and the enum definition. 
// Moreover, we cannot declare a name as an unscoped enum in one context and redeclare it as a
// scoped enum later.

/// Parameter Matching and Enumerations
// An integral value that happens to have the same value as an enumerator cannot be used to call a function
// expecting an enum argument.
// Although we cannot pass an integral value to an enum parameter, we can pass an
// object or enumerator of an unscoped enumeration to a parameter of integral type.

// unscoped enumeration; the underlying type is machine dependent
enum Tokens {INLINE = 128, VIRTUAL = 129};

void ff(Tokens t) {}
void ff(int i) {}
void newf(unsigned char ch) {}
void newf(int i) {}

int main() {
    color eyes = green;  // ok: enumerators are in scope for an unscoped enumeration

    // error: enumerators from peppers are not in scope
    // color::green is in scope but has the wrong type
    // error: cannot convert ‘color’ to ‘peppers’ in initialization
    // peppers p = green;

    color hair = color::red;  // ok: we can explicitly access the enumerators
    peppers p2 = peppers::red; // ok: using red from peppers

    /// Like Classes, Enumerations Define New Types
    // An enum object may be initialized or assigned only by one of its enumerators or by
    // another object of the same enum type
    // color c = 2;  // error: invalid conversion from ‘int’ to ‘color’

    // Objects or enumerators of an unscoped enumeration type are automatically
    // converted to an integral type.
    int i = color::red; // ok: unscoped enumerator implicitly converted to int
    // int j = peppers::red;  // error: cannot convert ‘peppers’ to ‘int’ in initialization

    Tokens curTok = INLINE;
    ff(128);  // exactly matches `ff(int)`
    ff(INLINE);  // exactly matches `ff(Tokens)`
    ff(curTok);  // exactly matches `ff(Tokens)`
    newf(VIRTUAL);  // calls `newf(int)`
    unsigned char uc = VIRTUAL;
    newf(uc);  // calls `newf(unsigned char)`
}