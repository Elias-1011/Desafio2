#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include <stdexcept>
#include "MedidorRecursos.h"

using namespace std;

template <typename T>
class Lista {
private:
    char* bufer;
    int   capacidad;
    int   tamanio;

    T* apuntador(int i) {
        return reinterpret_cast<T*>(bufer) + i;
    }

    const T* apuntador(int i) const {
        return reinterpret_cast<const T*>(bufer) + i;
    }

    void redimensionar() {
        int   nuevaCap = capacidad * 2;
        char* nuevo    = static_cast<char*>(::operator new(sizeof(T) * nuevaCap));
        for (int i = 0; i < tamanio; i++) {
            new (reinterpret_cast<T*>(nuevo) + i) T(*apuntador(i));
            apuntador(i)->~T();
        }
        restarMemoria(sizeof(T) * capacidad);
        ::operator delete(bufer);
        bufer     = nuevo;
        capacidad = nuevaCap;
        sumarMemoria(sizeof(T) * capacidad);
    }

public:
    Lista(int capInicial = 8)
        : capacidad(capInicial), tamanio(0) {
        bufer = static_cast<char*>(::operator new(sizeof(T) * capacidad));
        sumarMemoria(sizeof(T) * capacidad);
    }

    Lista(const Lista<T>& otra)
        : capacidad(otra.capacidad), tamanio(otra.tamanio) {
        bufer = static_cast<char*>(::operator new(sizeof(T) * capacidad));
        for (int i = 0; i < tamanio; i++)
            new (apuntador(i)) T(*otra.apuntador(i));
        sumarMemoria(sizeof(T) * capacidad);
    }

    Lista<T>& operator=(const Lista<T>& otra) {
        if (this == &otra) return *this;
        for (int i = 0; i < tamanio; i++) apuntador(i)->~T();
        restarMemoria(sizeof(T) * capacidad);
        ::operator delete(bufer);
        capacidad = otra.capacidad;
        tamanio   = otra.tamanio;
        bufer     = static_cast<char*>(::operator new(sizeof(T) * capacidad));
        for (int i = 0; i < tamanio; i++)
            new (apuntador(i)) T(*otra.apuntador(i));
        sumarMemoria(sizeof(T) * capacidad);
        return *this;
    }

    ~Lista() {
        for (int i = 0; i < tamanio; i++) apuntador(i)->~T();
        restarMemoria(sizeof(T) * capacidad);
        ::operator delete(bufer);
    }

    void agregar(const T& elemento) {
        if (tamanio == capacidad) redimensionar();
        new (apuntador(tamanio)) T(elemento);
        tamanio++;
    }

    T& operator[](int i) {
        if (i < 0 || i >= tamanio)
            throw out_of_range("Lista: indice fuera de rango");
        return *apuntador(i);
    }

    const T& operator[](int i) const {
        if (i < 0 || i >= tamanio)
            throw out_of_range("Lista: indice fuera de rango");
        return *apuntador(i);
    }

    int  getTamanio() const { return tamanio; }
    bool estaVacia()  const { return tamanio == 0; }

    void limpiar() {
        for (int i = 0; i < tamanio; i++) apuntador(i)->~T();
        tamanio = 0;
    }
};

#endif
