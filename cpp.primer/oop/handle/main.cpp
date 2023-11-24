#include "basket.h"
#include <iostream>


int main() {
    ItemBase b1("0-201-82470-1", 45.7);
    BulkItem b2("0-201-82365-2", 78.3, 5, 0.2);
    BulkItem b3("0-201-56732-5", 65.9, 10, 0.3);

    Basket bkt;

    for (int i=0; i<6; ++i) {
        bkt.add_item(SalesItem(b1));
    }
    for (int i=0; i<8; ++i) {
        bkt.add_item(SalesItem(b2));
    }
    for (int i=0; i<12; ++i) {
        bkt.add_item(SalesItem(b3));
    }

    cout << "total net price: " << bkt.total() << endl;
}