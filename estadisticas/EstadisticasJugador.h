#ifndef ESTADISTICASJUGADOR_H
#define ESTADISTICASJUGADOR_H

#include <iostream>

using namespace std;

class EstadisticasJugador {
private:
    short goles;
    short partidosJugados;
    int   minutosJugados;
    short asistencias;
    short tarjetasAmarillas;
    short tarjetasRojas;
    short faltas;

public:
    EstadisticasJugador();
    EstadisticasJugador(short goles, short partidos, int minutos,
                        short asistencias, short amarillas,
                        short rojas, short faltas);

    short getGoles() const;
    short getPartidosJugados() const;
    int   getMinutosJugados() const;
    short getAsistencias() const;
    short getTarjetasAmarillas() const;
    short getTarjetasRojas() const;
    short getFaltas() const;

    EstadisticasJugador& operator+=(const EstadisticasJugador& otro);

    long getTamanioBytes() const;

    friend ostream& operator<<(ostream& os, const EstadisticasJugador& e);
};

#endif
