#include <stdio.h>
#include <stdlib.h>

int g(){
    int p = 7;
    int q = 8;

    return q;
}

int f(){
    int x = 5;
    int y = x + 1;

    return 0;

    x = 100;
}

int main(){
    int a = 6;
    int b = a * a;
    int c = f();

    printf("%d %d\n", a, c);

    return 0;
}
