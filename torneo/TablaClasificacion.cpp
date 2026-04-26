#include "TablaClasificacion.h"

using namespace std;

TablaClasificacion::TablaClasificacion()
    : entradas(4) {}

TablaClasificacion::TablaClasificacion(const TablaClasificacion& otra)
    : entradas(otra.entradas) {}

TablaClasificacion& TablaClasificacion::operator=(const TablaClasificacion& otra) {
    if (this == &otra) return *this;
    entradas = otra.entradas;
    return *this;
}

void TablaClasificacion::agregar(const EntradaTabla& entrada) {
    entradas.agregar(entrada);
}

void TablaClasificacion::ordenar() {
    for (int i = 1; i < entradas.getTamanio(); i++) {
        EntradaTabla clave = entradas[i];
        int j = i - 1;
        while (j >= 0 && clave > entradas[j]) {
            entradas[j + 1] = entradas[j];
            j--;
            contarIteracion();
        }
        entradas[j + 1] = clave;
        contarIteracion();
    }
}

void TablaClasificacion::construir() {
    ordenar();
}

EntradaTabla& TablaClasificacion::getEntrada(int i) {
    return entradas[i];
}

const EntradaTabla& TablaClasificacion::getEntrada(int i) const {
    return entradas[i];
}

int TablaClasificacion::getTamanio() const {
    return entradas.getTamanio();
}

ostream& operator<<(ostream& os, const TablaClasificacion& t) {
    for (int i = 0; i < t.entradas.getTamanio(); i++)
        os << (i + 1) << ". " << t.entradas[i] << "\n";
    return os;
}
