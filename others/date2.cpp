#include <iostream>

std::string months[12] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

int days_per_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int get_year(int);          //accept a year, error check it, return valid year
int get_month(int);         //accept a month, error check it, return valid month
int get_day(int, int);      //accept a day and month, error check day, return

class date{
    public:
        date();
        date(int);
        date(int, int);
        date(int, int, int);
        void print_date();
    private:
        int year;           //DOMAIN 0 to whatever
        int month;          //DOMAIN 1 - 12
        int day;            //DOMAIN depends on month
};

int get_year(int y){
    if(y < 0){
        int tempy = y;
        while(tempy < 0){
            std::cout << "Year " << tempy << " is invalid " << std::endl;
            std::cout << "Please enter a year great than 0: ";
            std::cin >> tempy;
        }
        std::cout << "Valid y of " << tempy << " accepted" << std::endl;
        y = tempy;
    }
    return y;
}

int get_month(int mon){
    if(mon < 1 || mon > 12){
        int tempm = mon;
        while(tempm < 1 || tempm > 12){
            std::cout << "Month " << tempm << " is invalid " << std::endl;
            std::cout << "Please enter a month between 1 from 12: ";
            std::cin >> tempm;
        }
        std::cout << "Valid mon of " << tempm << " accepted" << std::endl;
        mon = tempm;
    }
    return mon;
}

int get_day(int d, int mon){
    if(d < 1 || d > days_per_month[mon-1]){
        int tempd = d;
        while(tempd < 1 || tempd > days_per_month[mon-1]){
            std::cout << "Day " << tempd << " is invalid " << std::endl;
            std::cout << "Please enter a day in the range 1 - " 
                      << days_per_month[mon-1] << ": ";
            std::cin >> tempd;
        }
        std::cout << "Valid d of " << tempd << " accepted " << std::endl;
        d = tempd;
    }
    return d;
}

//return type               void
//complete function name    date::print_date
//argument list             () 
void date::print_date(){
    std::cout 
    << "date is " << this->year << " " 
    <<  months[this->month-1] << " "
    <<  this->day << std::endl; 
}

date::date(){
    std::cout << "Welcome to the no arg constructor " << std::endl;
    year = 1970;
    month = 1;
    day = 1;
}

date::date(int y){
    std::cout << "The one argument constructor has been called " << std::endl;
    year = get_year(y);
    month = 1;
    day = 1;
}

date::date(int y, int mon){
    std::cout << "The two arguments constructor has been called " << std::endl;
    year = get_year(y);
    month = get_month(mon);
    day = 1;
}

date::date(int y, int mon, int d){
    std::cout << "The three arguments constructor has been called " << std::endl; 
    year = get_year(y);
    month = get_month(mon);
    day = get_day(d, month);
}

int main(){
    date d1;
    d1.print_date();

    date d2(2018);
    d2.print_date();

    date d3(2019, 7);
    d3.print_date();

    date d4(2021, 3, 52);
    d4.print_date();

    return 0;
}