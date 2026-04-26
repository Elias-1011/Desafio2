#include "MedidorRecursos.h"

using namespace std;

static size_t memoriaBytes = 0;
static long   iteraciones  = 0;

void sumarMemoria(size_t bytes)  { memoriaBytes += bytes; }
void restarMemoria(size_t bytes) { memoriaBytes -= bytes; }
void contarIteracion(int n)      { iteraciones  += n; }
void resetIteraciones()          { iteraciones   = 0; }

void imprimirMedidor() {
    cout << "\n--- Medicion de recursos ---" << endl;
    cout << "Memoria en uso:        " << memoriaBytes << " bytes" << endl;
    cout << "Iteraciones:           " << iteraciones  << endl;
    cout << "Componente ext. usado: rand() [<cstdlib>] para aleatoriedad" << endl;
    cout << "----------------------------\n" << endl;
}
