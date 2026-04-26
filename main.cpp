#include <iostream>
#include <cstdlib>
#include <ctime>
#include "torneo/Torneo.h"
using namespace std;

int main() {
    srand(time(0));
    Torneo torneo;
    torneo.mostrarMenu();
    return 0;
}
