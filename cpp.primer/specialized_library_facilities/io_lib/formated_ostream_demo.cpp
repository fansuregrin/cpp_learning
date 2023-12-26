// topic: format control of IO

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

int main() {
    /// Controlling the Format of Boolean Values
    cout << "default bool values: " << true << " " << false
         << "\nalpha bool values: " << boolalpha  // sets the internal state of coust
         << true << " " << false << noboolalpha  // resets the internal state to default formatting
         << '\n' << endl;

    /// Specifying the Base for Integral Values
    cout << "default(decimal): " << 20 << " " << 8415 << endl;
    cout << "octal: " << oct << 20 << " " << 8415 << endl;
    cout << "hex: " << hex << 20 << " " << 8415 << endl;
    cout << "decimal: " << dec << 20 << " " << 8415 << '\n' << endl;
    // Note:
    // The hex, oct, and dec manipulators affect only integral operands; the
    // representation of floating-point values is unaffected.

    /// Indicating Base on the Output
    cout << showbase;  // show the base when printing integral values
    cout << "default(decimal): " << 20 << " " << 8415 << endl;
    cout << "in octal: " << oct << 20 << " " << 8415 << endl;
    cout << "in hex: " << hex << 20 << " " << 8415 << endl;
    cout << "in decimal: " << dec << 20 << " " << 8415 << endl;
    cout << noshowbase;  // reset the state of the stream

    // display the X and the hex digits a–f as uppercase by applying the uppercase
    cout << uppercase
         << showbase << "in hex: " << hex << 20 << " " << 8415 << '\n' << endl
         << noshowbase << nouppercase << dec;

    /// Controlling the Format of Floating-Point Values
    //
    // default format for output float-point values
    // By default, floating-point values are printed using six digits of precision; the decimal
    // point is omitted if the value has no fractional part; and they are printed in either fixed
    // decimal or scientific notation depending on the value of the number. 
    // Very large and very small values are printed using scientific notation
    cout << "very small float-point value [0.000000000000104]: " << 0.000000000000104 << endl;
    cout << "very large float-point value [303550448045.3456]: " << 303550448045.3456 << endl;
    // Other values are printed in fixed decimal
    cout << "no fractinal part [5.00]: " << 5.00 << endl;
    cout << "other float-point values [34.567]: " << 34.567 << '\n' << endl;
    //
    // Specifying How Much Precision to Print
    // precision controls the total number of digits that are printed (rounded, not truncated)
    // We can change the precision by calling the precision member of an IO object or
    // by using the setprecision manipulator.
    cout << "Precison: " << cout.precision() << ", Value: " << sqrt(2.0) << endl;
    cout.precision(12);
    cout << "Precison: " << cout.precision() << ", Value: " << sqrt(2.0) << endl;
    cout << setprecision(3) << "Precison: " << cout.precision() << ", Value: " << sqrt(2.0)
         << setprecision(6) << '\n' << endl;
    //
    // Specifying the Notation of Floating-Point Numbers
    cout << "default format: " << 100 * sqrt(2.0) << "\n"
         << "scientific: " << scientific << 100 * sqrt(2.0) << "\n"
         << "fixed decimal: " << fixed << 100 * sqrt(2.0) << "\n"
         << "hexadecimal: " << hexfloat << 100 * sqrt(2.0) << "\n"
         << defaultfloat;
    //
    // Printing the Decimal Point
    cout << showpoint << 10.00 << noshowpoint << '\n' << endl;

    /// Padding the Output
    // setw, setfill, left, internal, right
    cout << string(18, '=') << '\n'
         << left << setw(8) << "Name" << setw(1) << ' '
         << left << setw(4) << "Sex" << setw(1) << ' '
         << setw(4) << "Age" << '\n' << string(18, '-') << endl;
    auto print_row = [](const string &name, bool is_male, unsigned age) {
        cout << left << setw(8) << name;
        cout << setw(1) << ' ' << left << setw(4) << (is_male?'M':'F');
        cout << setw(1) << ' ' << setw(4) << age << endl;
    };
    print_row("Bob", true, 24);
    print_row("Florence", false, 19);
    cout << string(18, '=') << endl;
}