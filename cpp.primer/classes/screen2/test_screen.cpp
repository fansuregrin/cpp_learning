#include "screen.h"

int main() {
    Screen my_screen(10, 8, ' ');
    // move the cursor to a given position, and set that character
    my_screen.move(4, 0).set('#');

    my_screen.display(std::cout).set('*');
}