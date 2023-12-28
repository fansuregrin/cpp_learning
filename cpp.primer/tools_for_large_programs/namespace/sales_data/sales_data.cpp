#include "sales_data.hpp"

namespace cpp_primer {
    SalesData::SalesData(const std::string &s): bookNo(s) {}

    SalesData::SalesData(const std::string &s, unsigned n, double p):
    bookNo(s), units_sold(n), revenue(n*p) {}

    inline std::string SalesData::isbn() const { return bookNo; }

    bool SalesData::operator==(const SalesData &rhs) const {
        return bookNo == rhs.bookNo && units_sold == rhs.units_sold && revenue == rhs.revenue;
    }

    SalesData::SalesData(std::istream &is) {
        is >> *this;
    }

    SalesData& SalesData::operator+=(const SalesData& rhs) {
        if (bookNo != rhs.bookNo) {
            throw isbn_mismatch("wrong isbns", bookNo, rhs.bookNo);
        }
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
}


template <>
struct std::hash<cpp_primer::SalesData> {
    typedef size_t result_type;
    typedef cpp_primer::SalesData argument_type;

    size_t operator()(const cpp_primer::SalesData &) const;
};

size_t
std::hash<cpp_primer::SalesData>::operator()(const cpp_primer::SalesData & item) const {
    return hash<string>()(item.bookNo) ^
           hash<unsigned>()(item.units_sold) ^
           hash<double>()(item.revenue);
}