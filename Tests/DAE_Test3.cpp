#include <iostream>

int dodaj2(int i, int j) {
    return i + 2;
}

void g(int x, int y, int z) {
    int br1 = x + z;
    int br2 = dodaj2(x, x - z);
}

void f(int a, int b, int c) {
    g(b - c, b, c);
}

int main () {
    int a, b;
    a = 10;
    b = 2;
    f(a + b, a, b);
}