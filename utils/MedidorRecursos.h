#ifndef MEDIDORRECURSOS_H
#define MEDIDORRECURSOS_H

#include <iostream>

using namespace std;

class MedidorRecursos {
private:
    size_t memoriaBytes;
    long   iteraciones;

    MedidorRecursos();

public:
    static MedidorRecursos& getInstancia();

    void sumarMemoria(size_t bytes);
    void restarMemoria(size_t bytes);
    void contarIteracion(int n = 1);

    size_t getMemoriaBytes() const;
    long   getIteraciones() const;

    void resetIteraciones();
    void imprimir() const;

    MedidorRecursos(const MedidorRecursos&)            = delete;
    MedidorRecursos& operator=(const MedidorRecursos&) = delete;
};

#endif
