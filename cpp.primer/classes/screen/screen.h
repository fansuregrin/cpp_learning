#ifndef SCREEN
#define SCREEN

#include <string>
#include <iostream>

using namespace std;

class Screen {
public:
    typedef string::size_type index;

    Screen(index height_, index width_);

    char get() const;
    
    char get(index row, index col) const;

    index get_cursor() const;

    Screen& move(index pos);

    Screen& move(index row, index col);

    Screen& set(char ch);

    Screen& set(index row, index col, char ch);

    const Screen& display(ostream& out) const;

    Screen& display(ostream& out);
private:
    string contents;
    index cursor;
    index height, width;

    void do_display(ostream& out) const;
};

Screen::Screen(index height_, index width_) {
    height = height_;
    width = width_;
    cursor = 0;
    contents.append(height*width, ' ');
}

char Screen::get() const {
    return contents[cursor];
}

char Screen::get(index row, index col) const {
    return contents[row * width + col];
}

Screen::index Screen::get_cursor() const {
    return cursor;
}

Screen& Screen::move(index pos) {
    cursor = pos;
    return *this;
}

Screen& Screen::move(index row, index col) {
    cursor = row*width + col;
    return *this;
}

Screen& Screen::set(char ch) {
    contents[cursor] = ch;
    return *this;
}

Screen& Screen::set(index row, index col, char ch) {
    contents[row*width+col] = ch;
    return *this;
}

const Screen& Screen::display(ostream& out) const {
    do_display(out);
    return *this;
}

Screen& Screen::display(ostream& out) {
    do_display(out);
    return *this;
}

void Screen::do_display(ostream& out) const {
    for (index i=0; i<height; ++i) {
        for (index j=0; j<width; ++j) {
            out << contents[i*width+j];
        }
        out << endl;
    }
}

#endif