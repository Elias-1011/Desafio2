#include "EntradaTabla.h"

using namespace std;

EntradaTabla::EntradaTabla()
    : equipo(nullptr), puntos(0), pj(0),
    pg(0), pe(0), pp(0), gf(0), gc(0) {}

EntradaTabla::EntradaTabla(Equipo* equipo)
    : equipo(equipo), puntos(0), pj(0),
    pg(0), pe(0), pp(0), gf(0), gc(0) {}

EntradaTabla::EntradaTabla(const EntradaTabla& otro)
    : equipo(otro.equipo), puntos(otro.puntos), pj(otro.pj),
    pg(otro.pg), pe(otro.pe), pp(otro.pp),
    gf(otro.gf), gc(otro.gc) {}

EntradaTabla& EntradaTabla::operator=(const EntradaTabla& otro) {
    if (this == &otro) return *this;
    equipo = otro.equipo;
    puntos = otro.puntos;
    pj     = otro.pj;
    pg     = otro.pg;
    pe     = otro.pe;
    pp     = otro.pp;
    gf     = otro.gf;
    gc     = otro.gc;
    return *this;
}

Equipo* EntradaTabla::getEquipo()     const { return equipo; }
short   EntradaTabla::getPuntos()     const { return puntos; }
short   EntradaTabla::getPJ()         const { return pj; }
short   EntradaTabla::getPG()         const { return pg; }
short   EntradaTabla::getPE()         const { return pe; }
short   EntradaTabla::getPP()         const { return pp; }
short   EntradaTabla::getGF()         const { return gf; }
short   EntradaTabla::getGC()         const { return gc; }
short   EntradaTabla::getDiferencia() const { return gf - gc; }

void EntradaTabla::sumarVictoria(short golesFavor, short golesContra) {
    pj++; pg++; puntos += 3;
    gf += golesFavor;
    gc += golesContra;
}

void EntradaTabla::sumarEmpate(short golesFavor, short golesContra) {
    pj++; pe++; puntos += 1;
    gf += golesFavor;
    gc += golesContra;
}

void EntradaTabla::sumarDerrota(short golesFavor, short golesContra) {
    pj++; pp++;
    gf += golesFavor;
    gc += golesContra;
}

bool EntradaTabla::operator>(const EntradaTabla& otro) const {
    if (puntos != otro.puntos)
        return puntos > otro.puntos;
    short dif     = gf - gc;
    short difOtro = otro.gf - otro.gc;
    if (dif != difOtro)
        return dif > difOtro;
    return gf > otro.gf;
}

ostream& operator<<(ostream& os, const EntradaTabla& e) {
    os << e.equipo->getPais()
    << " | PJ:" << e.pj
    << " PG:" << e.pg
    << " PE:" << e.pe
    << " PP:" << e.pp
    << " GF:" << e.gf
    << " GC:" << e.gc
    << " DG:" << (e.gf - e.gc)
    << " PTS:" << e.puntos;
    return os;
}
