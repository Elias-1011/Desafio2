#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include <string>
#include "../estadisticas/EstadisticasJugador.h"
#include "../utils/MedidorRecursos.h"

using namespace std;

class Jugador {
private:
    string              nombre;
    string              apellido;
    short               numeroCamiseta;
    EstadisticasJugador estadisticas;

public:
    Jugador();
    Jugador(const string& nombre, const string& apellido,
            short numeroCamiseta, const EstadisticasJugador& estadisticas);
    Jugador(const Jugador& otro);
    ~Jugador();

    const string&       getNombre()        const;
    const string&       getApellido()      const;
    short               getNumeroCamiseta() const;
    EstadisticasJugador&       getEstadisticas();
    const EstadisticasJugador& getEstadisticas() const;

    friend ostream& operator<<(ostream& os, const Jugador& j);
};

#endif
