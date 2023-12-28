#ifndef SALES_DATA
#define SALES_DATA

#include <string>
#include <iostream>
#include <functional>


class SalesData {
    friend struct std::hash<SalesData>;
    friend SalesData add(const SalesData&, const SalesData&);
    friend std::ostream& print(std::ostream&, const SalesData&);
    friend std::istream& read(std::istream&, SalesData&);
public:
    SalesData() = default;

    SalesData(const std::string &s): bookNo(s) {}

    SalesData(const std::string &s, unsigned n, double p):
        bookNo(s), units_sold(n), revenue(n*p) {}

    SalesData(std::istream &);

    std::string isbn() const { return bookNo; }

    SalesData& combine(const SalesData&);

    bool operator==(const SalesData &rhs) const {
        return bookNo == rhs.bookNo && units_sold == rhs.units_sold && revenue == rhs.revenue;
    }
private:
    double avg_price() const;

    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

SalesData::SalesData(std::istream &is) {
    read(is, *this);
}

SalesData& SalesData::combine(const SalesData& rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

double SalesData::avg_price() const {
    return units_sold ? (revenue/units_sold) : 0.0;
}

SalesData add(const SalesData&, const SalesData&);

std::ostream& print(std::ostream&, const SalesData&);

std::istream& read(std::istream&, SalesData&);

std::istream& read(std::istream &is, SalesData &item) {
    double price = 0.0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = item.units_sold * price;
    return is;
}

std::ostream& print(std::ostream &os, const SalesData &item) {
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

SalesData add(const SalesData &lhs, const SalesData &rhs) {
    SalesData sum = lhs;
    sum.combine(rhs);
    return sum;
}


// open the std namespace so we can specialize std::hash
namespace std {

template <>
struct hash<SalesData> {
    typedef size_t result_type;
    typedef SalesData argument_type;

    size_t operator()(const SalesData &) const;
};

size_t hash<SalesData>::operator()(const SalesData & item) const {
    return hash<string>()(item.bookNo) ^
           hash<unsigned>()(item.units_sold) ^
           hash<double>()(item.revenue);
}

}

#endif