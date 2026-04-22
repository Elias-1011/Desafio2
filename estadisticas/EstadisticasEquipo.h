#ifndef ESTADISTICASEQUIPO_H
#define ESTADISTICASEQUIPO_H

#include <iostream>

using namespace std;

class EstadisticasEquipo {
private:
    short golesFavor;
    short golesContra;
    short ganados;
    short empatados;
    short perdidos;
    short tarjetasAmarillas;
    short tarjetasRojas;
    short faltas;

public:
    EstadisticasEquipo();
    EstadisticasEquipo(short gf, short gc, short gan,
                       short emp, short per, short amarillas,
                       short rojas, short faltas);

    short getGolesFavor() const;
    short getGolesContra() const;
    short getGanados() const;
    short getEmpatados() const;
    short getPerdidos() const;
    short getTarjetasAmarillas() const;
    short getTarjetasRojas() const;
    short getFaltas() const;

    float getPromGolesFavor() const;
    float getPromGolesContra() const;

    EstadisticasEquipo& operator+=(const EstadisticasEquipo& otro);

    long getTamanioBytes() const;

    friend ostream& operator<<(ostream& os, const EstadisticasEquipo& e);
};

#endif
