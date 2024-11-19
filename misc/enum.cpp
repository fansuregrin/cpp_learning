//Fansure Grin
//Supplementary example on overloading operator

#include <iostream>
#include <cstdint>

using namespace std;

enum class days:std::int8_t{
    SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
};

ostream& operator<<(ostream& out, const days& d){
    std:string day_str;
    switch(d){
        case days::SUNDAY: day_str = "SUN"; break;
        case days::MONDAY: day_str = "MON"; break;
        case days::TUESDAY: day_str = "TUE"; break;
        case days::WEDNESDAY: day_str = "WED"; break;
        case days::THURSDAY: day_str = "THUR"; break;
        case days::FRIDAY: day_str = "FRI"; break;
        case days::SATURDAY: day_str = "SAT"; break;
    }
    out << day_str;
    return out;
}

//Prefix Operator
days operator++(days& d){
    d = static_cast<days>((static_cast<int>(d) + 1) % 7);
    return d;
}

//Postfix Operator
days operator++(days& d, int){
    days temp = d;
    d = static_cast<days>((static_cast<int>(d) + 1) % 7);
    return temp;
}

int main(){
    //days today{days::MONDAY};
    days today = days::FRIDAY;
    std::cout << "Demonstrate class enum" << std::endl;
    std::cout << "TODAY IS " << today << std::endl;       //maybe MONDAY
    std::cout << "TOMORROW IS " << ++today << std::endl;  //maybe TUE
    std::cout << "TOMORROW IS " << today++ << std::endl;  //TUE
    std::cout << "THE DAY AFTER TOMORROW IS " << today << std::endl;
    return 0;
}