// topic: `biset` type

#include <bitset>
#include <iostream>
#include <string>

using namespace std;

int main() {
    bitset<32> bitvec(1U);  // 32 bits; low-order bit is 1, remaining bits are 0

    /// Initializing a `bitset` from an `unsigned` Value

    // bitvec1 is smaller than the initializer; high-order bits from the initializer are discarded
    bitset<13> bitvec1(0xbeef);  // 1111011101111
    // bitvec2 is larger than the initializer; high-order bits in bitvec2 are set to zero
    bitset<20> bitvec2(0xbeef); // 00001011111011101111
    // on machines with 64-bit long long 0ULL is 64 bits of 0, so ~0ULL is 64 ones
    bitset<128> bitvec3(~0ULL); // bits 0 ... 63 are one; 63 ... 127 are zero

    cout << "bitvec1: " << bitvec1 << endl;
    cout << "bitvec2: " << bitvec2 << endl;
    cout << "bitvec3: " << bitvec3 << endl;

    /// Initializing a `bitset` from a `string`

    bitset<8> bitvec4("1100"); // 00001100
    string str("1111111000000011001101");
    bitset<8> bitvec5(str, 5, 4);  // four bits starting at str[5], 1100
    bitset<8> bitvec6(str, str.size()-4);  // use last four characters

    cout << "bitvec4: " << bitvec4 << endl;
    cout << "bitvec5: " << bitvec5 << endl;
    cout << "bitvec6: " << bitvec6 << endl;

    /// Operations on `bitset`s

    bool is_set = bitvec.any();  // true, one bit is set
    bool is_not_set = bitvec.none();  // false, one bit is set
    bool all_set = bitvec.all();  // false, only one bit is set
    size_t on_bits = bitvec.count(); // 1
    size_t sz = bitvec.size(); // 32
    
    cout << "flip all bits: " << bitvec;
    bitvec.flip();  // reverses the value of all the bits in bitvec
    cout <<  " -> " << bitvec << endl;

    cout << "flip 0th bit: " << bitvec;
    bitvec.flip(0);  // reverses the value of the 0th bit in bitvec
    cout <<  " -> " << bitvec << endl;

    cout << "reset 31st bit: " << bitvec;
    bitvec.reset(31);  // resets the value of the 31st the bits in bitvec
    cout <<  " -> " << bitvec << endl;

    cout << "reset all bits: " << bitvec;
    bitvec.reset();  // resets the value of all the bits in bitvec
    cout <<  " -> " << bitvec << endl;

    cout << "set 5th bit to 1: " << bitvec;
    bitvec.set(5);
    cout <<  " -> " << bitvec << endl;

    cout << "set 5th bit to 0: " << bitvec;
    bitvec.set(5, false);
    cout <<  " -> " << bitvec << endl;

    cout << "set all bits: " << bitvec;
    bitvec.set();
    cout <<  " -> " << bitvec << endl;

    bitvec.test(0); // returns true because the first bit is on

    bitvec[0] = 0; // turn off the bit at position 0
    bitvec[31] = bitvec[0]; // set the last bit to the same value as the first bit
    bitvec[0].flip(); // flip the value of the bit at position 0
    ~bitvec[0]; // equivalent operation; flips the bit at position 0
    bool b = bitvec[0]; // convert the value of bitvec[0] to bool

    // Retrieving the Value of a bitset
    unsigned long v1 = bitvec.to_ulong();
    unsigned long long v2 = bitvec.to_ullong();
    string s = bitvec.to_string('0', '1');

    return 0;
}