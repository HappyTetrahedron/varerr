#include <iostream>
#include "unit.h"
#include "varerr.h"

int
main(int argc, char **argv) {
    Unit u = 5*bu::N;
    std::cout << u.toString() << "\n";
    Varerr ve = u<<0.1;
    std::cout << ve.toString() << "\n";
    Varerr ve1 = (5*bu::N)<<(1*bu::N);
    std::cout << ve1.toString() << "\n";
    return 0;
}
