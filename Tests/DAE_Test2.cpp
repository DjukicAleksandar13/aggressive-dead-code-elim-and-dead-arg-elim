#include <iostream>

bool odaberi(int a, int b, int c, double x, double y, bool nothingHere) {
    if (a > c) { return true; }
    return nothingHere;
}

int main () {
    double i, j;
    i = 2.1;
    j = 3.3;
    odaberi(13, 5, 2003, i, j, true);
    odaberi(99, 100, 101, j, i, false);
    odaberi(1000, 1000, 1000, j, 3.14, true);
}