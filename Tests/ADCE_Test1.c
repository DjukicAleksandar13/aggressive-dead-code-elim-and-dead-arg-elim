#include <stdio.h>

void f();

int main() {
    int x, y, z;
    x = 21; // promenljiva x se nigde ne koristi, pa se alloc i store instrukcije brisu
    z = 42;
    y = z - 21;
    printf("%d", y + z);

    if (z < 42) {
        printf("Hello");
    } else {
        printf("Bye");
    }

    f();

    return 0;
}

void f() {   
    int j, i;
    i = 12;
    j = 13;
    printf("%d\n", j + i);
    int k = 25; // promenljiva k se nigde ne koristi
}