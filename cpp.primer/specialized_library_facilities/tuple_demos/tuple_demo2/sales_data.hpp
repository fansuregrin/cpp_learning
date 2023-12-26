#ifndef SALES_DATA
#define SALES_DATA

#include <string>
#include <iostream>

using namespace std;

class SalesData {
    friend ostream& operator<<(ostream&, const SalesData&);
    friend istream& operator>>(istream&, SalesData&);
    friend SalesData operator+(const SalesData&, const SalesData&);
public:
    SalesData() = default;

    SalesData(const string &s): bookNo(s) {}

    SalesData(const string &s, unsigned n, double p):
        bookNo(s), units_sold(n), revenue(n*p) {}

    SalesData(istream &);

    string isbn() const { return bookNo; }

    SalesData& operator+=(const SalesData&);

    bool operator==(const SalesData &rhs) const {
        return bookNo == rhs.bookNo && units_sold == rhs.units_sold && revenue == rhs.revenue;
    }
private:
    double avg_price() const;

    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

SalesData::SalesData(istream &is) {
    is >> *this;
}

SalesData& SalesData::operator+=(const SalesData& rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

double SalesData::avg_price() const {
    return units_sold ? (revenue/units_sold) : 0.0;
}

istream& operator>>(istream &is, SalesData &item) {
    double price = 0.0;
    is >> item.bookNo >> item.units_sold >> price;
    if (is) {
        item.revenue = item.units_sold * price;
    } else {
        item = SalesData();
    }
    return is;
}

ostream& operator<<(ostream &os, const SalesData &item) {
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

SalesData operator+(const SalesData &lhs, const SalesData &rhs) {
    SalesData sum = lhs;
    sum += rhs;
    return sum;
}

bool compareIsbn(const SalesData &lhs, const SalesData &rhs) {
    return lhs.isbn() < rhs.isbn();
}

#endif