#ifndef SALES_DATA
#define SALES_DATA

#include <string>
#include <iostream>
#include "custom_exception.hpp"

namespace cpp_primer {
    class SalesData;
    std::ostream& operator<<(std::ostream&, const SalesData&);
    std::istream& operator>>(std::istream&, SalesData&);
    SalesData operator+(const SalesData&, const SalesData&);

    class SalesData {
        friend struct std::hash<SalesData>;
        friend std::ostream& operator<<(std::ostream&, const SalesData&);
        friend std::istream& operator>>(std::istream&, SalesData&);
        friend SalesData operator+(const SalesData&, const SalesData&);
    public:
        SalesData() = default;

        SalesData(const std::string &s);

        SalesData(const std::string &s, unsigned n, double p);

        SalesData(std::istream &);

        inline std::string isbn() const;

        SalesData& operator+=(const SalesData&);

        bool operator==(const SalesData &rhs) const;
    private:
        double avg_price() const;

        std::string bookNo;
        unsigned units_sold = 0;
        double revenue = 0.0;
    };
}

namespace std {
    template <> struct hash<cpp_primer::SalesData>;
}

#endif