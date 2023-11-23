#include <string>

using namespace std;

class ItemBase {
public:
    ItemBase(const string& book = "", double sales_price = 0.0):
    isbn(book), price(sales_price) {}

    string book() const {
        return isbn;
    }

    // returns total sales price for a specified number of items
    // derived classes will override and apply different discount algorithms
    virtual double net_price(size_t n) const {
        return n * price;
    }

    virtual ~ItemBase() {}
protected:
    double price;  // normal, undiscounted price
private:
    string isbn;  // identifier for the item
};


// class to hold discount rate and quantity
// derived classes will implement pricing strategies using these data
class DiscItem: public ItemBase {
public:
    DiscItem(
        const string& book = "", double sales_price = 0.0,
        size_t qty = 0, double disc_rate = 0.0
    ): ItemBase(book, sales_price), quantity(qty), discount(disc_rate) {}

    double net_price(size_t) const = 0;
protected:
    double discount;  // fractional discount to apply
    size_t quantity;  // purchase size for discount to apply
};


class BulkItem: public DiscItem {
public:
    BulkItem(
        const string& book = "", double sales_price = 0.0,
        size_t qty = 0, double disc_rate = 0.0
    ): DiscItem(book, sales_price, qty, disc_rate) {}

    // redefines base version so as to implement bulk purchase discount policy
    double net_price(size_t cnt) const {
        if (cnt >= quantity) {
            return price * (1-discount) * cnt;
        } else {
            return price * cnt;
        }
    }
};

int main() {
    // error: cannot declare variable ‘d’ to be of abstract type ‘DiscItem’
    // DiscItem d;

    // ok: DiscItem subobject within BulkItem
    BulkItem bulk("7-115-13416-2", 68.9, 10, 0.2);

    return 0;
}