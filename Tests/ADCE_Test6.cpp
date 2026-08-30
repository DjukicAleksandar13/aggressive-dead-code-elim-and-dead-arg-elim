#include <iostream>

int g, i;

void f() {
    g = 5;
}

int h(int x) {
    int a = x + 1;
    int b = a * 2;
    return 3;
}

int main () {
    f();
    i = h(5);
    return 0;
}