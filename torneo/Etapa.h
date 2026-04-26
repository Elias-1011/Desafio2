#ifndef ETAPA_H
#define ETAPA_H

#include <iostream>
#include <string>
#include "../utils/Lista.h"
#include "../utils/MedidorRecursos.h"
#include "../partido/Partido.h"

using namespace std;

class Etapa {
private:
    string         nombre;
    Lista<Partido> partidos;
    size_t         bytesReportados;

public:
    Etapa();
    Etapa(const string& nombre, int capacidad);
    Etapa(const Etapa& otra);
    Etapa& operator=(const Etapa& otra);
    ~Etapa();

    const string& getNombre()      const;
    int           getCantPartidos() const;

    void agregarPartido(const Partido& partido);
    void simular();
    void imprimir()                const;

    Partido&       getPartido(int i);
    const Partido& getPartido(int i) const;

    friend ostream& operator<<(ostream& os, const Etapa& e);
};

#endif
