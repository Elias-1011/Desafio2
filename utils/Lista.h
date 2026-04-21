#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Lista {
private:
    T*  datos;
    int capacidad;
    int tamanio;

    void redimensionar() {
        capacidad *= 2;
        T* nuevo = new T[capacidad];
        for (int i = 0; i < tamanio; i++)
            nuevo[i] = datos[i];
        delete[] datos;
        datos = nuevo;
    }

public:
    Lista(int capInicial = 8)
        : capacidad(capInicial), tamanio(0) {
        datos = new T[capacidad];
    }

    Lista(const Lista<T>& otra)
        : capacidad(otra.capacidad), tamanio(otra.tamanio) {
        datos = new T[capacidad];
        for (int i = 0; i < tamanio; i++)
            datos[i] = otra.datos[i];
    }

    Lista<T>& operator=(const Lista<T>& otra) {
        if (this == &otra) return *this;
        delete[] datos;
        capacidad = otra.capacidad;
        tamanio   = otra.tamanio;
        datos     = new T[capacidad];
        for (int i = 0; i < tamanio; i++)
            datos[i] = otra.datos[i];
        return *this;
    }

    ~Lista() {
        delete[] datos;
    }

    void agregar(const T& elemento) {
        if (tamanio == capacidad)
            redimensionar();
        datos[tamanio++] = elemento;
    }

    T& operator[](int i) {
        if (i < 0 || i >= tamanio)
            throw out_of_range("Lista: indice fuera de rango");
        return datos[i];
    }

    const T& operator[](int i) const {
        if (i < 0 || i >= tamanio)
            throw out_of_range("Lista: indice fuera de rango");
        return datos[i];
    }

    int getTamanio() const { return tamanio; }

    bool estaVacia() const { return tamanio == 0; }

    void limpiar() { tamanio = 0; }

    long getTamanioBytes() const {
        return sizeof(*this) + sizeof(T) * capacidad;
    }
};
#endif
