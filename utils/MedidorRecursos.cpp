#include "MedidorRecursos.h"

using namespace std;

MedidorRecursos::MedidorRecursos()
    : memoriaBytes(0), iteraciones(0) {}

MedidorRecursos& MedidorRecursos::getInstancia() {
    static MedidorRecursos instancia;
    return instancia;
}

void MedidorRecursos::sumarMemoria(size_t bytes)  { memoriaBytes += bytes; }
void MedidorRecursos::restarMemoria(size_t bytes) { memoriaBytes -= bytes; }
void MedidorRecursos::contarIteracion(int n)      { iteraciones  += n; }

size_t MedidorRecursos::getMemoriaBytes() const { return memoriaBytes; }
long   MedidorRecursos::getIteraciones()  const { return iteraciones; }

void MedidorRecursos::resetIteraciones() { iteraciones = 0; }

void MedidorRecursos::imprimir() const {
    cout << "\n--- Medicion de recursos ---" << endl;
    cout << "Memoria en uso: " << memoriaBytes << " bytes" << endl;
    cout << "Iteraciones:    " << iteraciones  << endl;
    cout << "----------------------------\n" << endl;
}
