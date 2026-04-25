#ifndef JUGADORCONVOCADO_H
#define JUGADORCONVOCADO_H

#include <iostream>
#include "../entidades/Jugador.h"

using namespace std;

class JugadorConvocado {
private:
    Jugador* jugador;
    short    goles;
    short    tarjetasAmarillas;
    short    tarjetasRojas;
    short    faltas;
    int      minutosJugados;

public:
    JugadorConvocado();
    JugadorConvocado(Jugador* jugador, int minutos);
    JugadorConvocado(const JugadorConvocado& otro);
    JugadorConvocado& operator=(const JugadorConvocado& otro);

    Jugador* getJugador()           const;
    short    getGoles()             const;
    short    getTarjetasAmarillas() const;
    short    getTarjetasRojas()     const;
    short    getFaltas()            const;
    int      getMinutosJugados()    const;

    void agregarGol();
    void agregarAmarilla();
    void agregarRoja();
    void agregarFalta();
    void extenderAProrroga();

    void actualizarHistorico();

    friend ostream& operator<<(ostream& os, const JugadorConvocado& jc);
};

#endif
