#ifndef ESTPARTIDOEQUIPO_H
#define ESTPARTIDOEQUIPO_H

#include <iostream>
#include "../utils/Lista.h"
#include "JugadorConvocado.h"

using namespace std;

class EstPartidoEquipo {
private:
    short                  golesFavor;
    short                  golesContra;
    short                  posesion;
    Lista<JugadorConvocado> convocados;

public:
    EstPartidoEquipo();
    EstPartidoEquipo(const EstPartidoEquipo& otro);
    EstPartidoEquipo& operator=(const EstPartidoEquipo& otro);

    short getGolesFavor()  const;
    short getGolesContra() const;
    short getPosesion()    const;
    Lista<JugadorConvocado>&       getConvocados();
    const Lista<JugadorConvocado>& getConvocados() const;

    void setGolesFavor(short g);
    void setGolesContra(short g);
    void setPosesion(short p);
    void agregarConvocado(const JugadorConvocado& jc);

    void actualizarHistoricos();

    friend ostream& operator<<(ostream& os, const EstPartidoEquipo& e);
};

#endif
