#ifndef HANDLE_H
#define HANDLE_H

#include "book.h"
#include <stdexcept>

// use counted handle class for the ItemBase hierarchy
class SalesItem {
public:
    // default constructor: unbound handle
    SalesItem(): p(nullptr), use(new size_t(1)) {}

    // attaches a handle to a copy of the ItemBase object
    SalesItem(const ItemBase&);

    SalesItem(const SalesItem& other): p(other.p), use(other.use) {
        ++*use;
    }

    SalesItem& operator=(const SalesItem&);

    ~SalesItem() { desc_use(); }

    const ItemBase* operator->() const {
        if (p) {
            return p;
        } else {
            throw logic_error("unbound SalesItem");
        }
    }

    const ItemBase& operator*() const {
        if (p) {
            return *p;
        } else {
            throw logic_error("unbound SalesItem");
        }
    }
private:
    ItemBase * p;  // pointer to shared item
    size_t * use;  // pointer to shared use count

    // called by both destructor and assignment operator to free pointers
    void desc_use() {
        if (--*use == 0) {
            delete p;
            delete use;
        }
    }
};

SalesItem::SalesItem(const ItemBase& item):
p(item.clone()), use(new size_t(1)) { }

SalesItem& SalesItem::operator=(const SalesItem& rhs) {
    ++*rhs.use;
    desc_use();
    use = rhs.use;
    p = rhs.p;
    return *this;
}

inline bool compare(const SalesItem& lhs, const SalesItem& rhs) {
    return lhs->book() < rhs->book();
}

#endif