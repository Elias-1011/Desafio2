#ifndef TABLACLASIFICACION_H
#define TABLACLASIFICACION_H

#include <iostream>
#include "../utils/Lista.h"
#include "../utils/MedidorRecursos.h"
#include "EntradaTabla.h"

using namespace std;

class TablaClasificacion {
private:
    Lista<EntradaTabla> entradas;

    void ordenar();

public:
    TablaClasificacion();
    TablaClasificacion(const TablaClasificacion& otra);
    TablaClasificacion& operator=(const TablaClasificacion& otra);

    void agregar(const EntradaTabla& entrada);
    void construir();

    EntradaTabla&       getEntrada(int i);
    const EntradaTabla& getEntrada(int i) const;
    int                 getTamanio()      const;

    friend ostream& operator<<(ostream& os, const TablaClasificacion& t);
};

#endif
