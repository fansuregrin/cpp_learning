#ifndef BOOK_H
#define BOOK_H

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

    virtual ItemBase* clone() const {
        return new ItemBase(*this);
    }
protected:
    double price;  // normal, undiscounted price
private:
    string isbn;  // identifier for the item
};


class BulkItem: public ItemBase {
public:
    BulkItem(
        const string& book = "", double sales_price = 0.0,
        size_t qty = 0, double disc_rate = 0.0
    ): ItemBase(book, sales_price), quantity(qty), discount(disc_rate) {}

    // redefines base version so as to implement bulk purchase discount policy
    double net_price(size_t cnt) const {
        if (cnt >= quantity) {
            return price * (1-discount) * cnt;
        } else {
            return price * cnt;
        }
    }

    BulkItem* clone() const {
        return new BulkItem(*this);
    }

private:
    size_t quantity;
    double discount;
};

#endif