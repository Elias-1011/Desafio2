#ifndef GRUPO_H
#define GRUPO_H

#include <iostream>
#include <string>
#include "../utils/Lista.h"
#include "../utils/MedidorRecursos.h"
#include "../entidades/Equipo.h"
#include "../partido/Partido.h"
#include "EntradaTabla.h"
#include "TablaClasificacion.h"

using namespace std;

class Grupo {
private:
    char               letra;
    Equipo*            equipos[4];
    char               cantidadEquipos;
    Lista<Partido>     partidos;
    TablaClasificacion tabla;

public:
    Grupo();
    Grupo(char letra);
    Grupo(const Grupo& otro);
    Grupo& operator=(const Grupo& otro);

    char    getLetra()           const;
    char    getCantidadEquipos() const;
    Equipo* getEquipo(int i)     const;

    bool puedeAgregar(const Equipo* equipo) const;
    void agregarEquipo(Equipo* equipo);
    void quitarUltimoEquipo();

    void agregarPartido(const Partido& partido);
    void simularPartidos();
    void construirTabla();
    void imprimirPartidos() const;

    const TablaClasificacion& getTabla() const;

    int contarConfederacion(const string& confederacion) const;

    friend ostream& operator<<(ostream& os, const Grupo& g);
};

#endif
