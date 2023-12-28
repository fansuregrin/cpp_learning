#ifndef SALES_DATA
#define SALES_DATA

#include <string>
#include <iostream>


class SalesData {
    friend std::ostream& operator<<(std::ostream&, const SalesData&);
    friend std::istream& operator>>(std::istream&, SalesData&);
    friend SalesData operator+(const SalesData&, const SalesData&);
public:
    SalesData() = default;

    SalesData(const std::string &s): bookNo(s) {}

    SalesData(const std::string &s, unsigned n, double p):
        bookNo(s), units_sold(n), revenue(n*p) {}

    SalesData(std::istream &);

    std::string isbn() const { return bookNo; }

    SalesData& operator+=(const SalesData&);

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

std::istream& operator>>(std::istream &is, SalesData &item) {
    double price = 0.0;
    is >> item.bookNo >> item.units_sold >> price;
    if (is) {
        item.revenue = item.units_sold * price;
    } else {
        item = SalesData();
    }
    return is;
}

std::ostream& operator<<(std::ostream &os, const SalesData &item) {
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