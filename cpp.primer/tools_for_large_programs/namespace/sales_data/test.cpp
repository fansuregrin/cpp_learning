#include "sales_data.hpp"

int main() {
    cpp_primer::SalesData item1, item2, sum;
    std::cout << "enter item1([isbn] [units_sold] [price]):";
    std::cin >> item1;
    std::cout << "enter item2([isbn] [units_sold] [price]):";
    std::cin >> item2;
    try {
        sum = item1 + item2;
        std::cout << sum << std::endl;
    } catch (const isbn_mismatch &e) {
        std::cerr << e.what() << ": left isbn(" << e.left
                    << "), right isbn(" << e.right << ")" << std::endl;
    }
}