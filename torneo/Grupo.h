#ifndef GRUPO_H
#define GRUPO_H

#include <iostream>
#include <string>
#include "../utils/MedidorRecursos.h"
#include "../entidades/Equipo.h"

using namespace std;

class Grupo {
private:
    char    letra;
    Equipo* equipos[4];
    char    cantidadEquipos;

public:
    Grupo();
    Grupo(char letra);
    Grupo(const Grupo& otro);
    Grupo& operator=(const Grupo& otro);

    char    getLetra()           const;
    char    getCantidadEquipos() const;
    Equipo* getEquipo(int i)     const;

    bool puedeAgregar(const Equipo* equipo)      const;
    void agregarEquipo(Equipo* equipo);
    void quitarUltimoEquipo();

    int contarConfederacion(const string& confederacion) const;

    friend ostream& operator<<(ostream& os, const Grupo& g);
};

#endif
