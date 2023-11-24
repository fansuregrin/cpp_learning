#ifndef BASKET_H
#define BASKET_H

#include "handle.h"
#include <set>

class Basket {
    // type of the comparison function used to order the multiset
    typedef bool (*Comp) (const SalesItem&, const SalesItem&);
public:
    // make it easier to type the type of our set
    typedef multiset<SalesItem, Comp> set_type;

    // typedefs modeled after corresponding container types
    typedef set_type::size_type size_type;
    typedef set_type::const_iterator const_iter;

    Basket(): items(compare) {}

    void add_item(const SalesItem& item) {
        items.insert(item);
    }
    
    size_type size(const SalesItem& item) const {
        return items.count(item);
    }

    double total() const;
private:
    multiset<SalesItem, Comp> items;
};

double Basket::total() const {
    double sum = 0.0;

    for (const_iter it=items.begin();
    it!=items.end(); it=items.upper_bound(*it)) {
        sum += (*it)->net_price(items.count(*it));
    }

    return sum;
}

#endif