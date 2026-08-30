#include <iostream>

int g;

void f(int *x) {
    *x = 5;
}

void use(int *a, int b) {
    *a = 10;
};

void usage(int x, int useless) {
    int y = x;
    use(&y, 9);
}

int main () {
    f(&g);
    usage(5, 10);
    return 0;
}