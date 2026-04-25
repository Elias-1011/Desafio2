#ifndef ENTRADATABLA_H
#define ENTRADATABLA_H

#include <iostream>
#include "../entidades/Equipo.h"

using namespace std;

class EntradaTabla {
private:
    Equipo* equipo;
    short   puntos;
    short   pj;
    short   pg;
    short   pe;
    short   pp;
    short   gf;
    short   gc;

public:
    EntradaTabla();
    EntradaTabla(Equipo* equipo);
    EntradaTabla(const EntradaTabla& otro);
    EntradaTabla& operator=(const EntradaTabla& otro);

    Equipo* getEquipo()     const;
    short   getPuntos()     const;
    short   getPJ()         const;
    short   getPG()         const;
    short   getPE()         const;
    short   getPP()         const;
    short   getGF()         const;
    short   getGC()         const;
    short   getDiferencia() const;

    void sumarVictoria(short golesFavor, short golesContra);
    void sumarEmpate(short golesFavor, short golesContra);
    void sumarDerrota(short golesFavor, short golesContra);

    bool operator>(const EntradaTabla& otro) const;

    friend ostream& operator<<(ostream& os, const EntradaTabla& e);
};

#endif
