#ifndef SALES_DATA
#define SALES_DATA

#include <string>
#include <iostream>

using namespace std;

class SalesData {
    friend SalesData add(const SalesData&, const SalesData&);
    friend ostream& print(ostream&, const SalesData&);
    friend istream& read(istream&, SalesData&);
public:
    SalesData() = default;

    SalesData(const string &s): bookNo(s) {}

    SalesData(const string &s, unsigned n, double p):
        bookNo(s), units_sold(n), revenue(n*p) {}

    SalesData(istream &);

    string isbn() const { return bookNo; }

    SalesData& combine(const SalesData&);

private:
    double avg_price() const;

    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

SalesData::SalesData(istream &is) {
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

ostream& print(ostream&, const SalesData&);

istream& read(istream&, SalesData&);

istream& read(istream &is, SalesData &item) {
    double price = 0.0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = item.units_sold * price;
    return is;
}

ostream& print(ostream &os, const SalesData &item) {
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

SalesData add(const SalesData &lhs, const SalesData &rhs) {
    SalesData sum = lhs;
    sum.combine(rhs);
    return sum;
}

#endif