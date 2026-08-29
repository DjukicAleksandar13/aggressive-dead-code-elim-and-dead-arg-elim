#include <iostream>

int main() {
    bool thisIsTrue, thisIsFalse, thisIsSomething;
    thisIsTrue = true;
    thisIsFalse = false;
    bool thisIsNotNothing = thisIsFalse;
    bool thisIsNothing = thisIsSomething; // novi bool dobija vrednost nekoriscene bool vrednosti
    if (thisIsNothing) {
        bool trigger = true; // nigde se ne koristi
    }
    return 0;
}