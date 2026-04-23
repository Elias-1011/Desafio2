#include "EstadisticasEquipo.h"

using namespace std;

EstadisticasEquipo::EstadisticasEquipo()
    : golesFavor(0), golesContra(0), ganados(0),
    empatados(0), perdidos(0), tarjetasAmarillas(0),
    tarjetasRojas(0), faltas(0) {}

EstadisticasEquipo::EstadisticasEquipo(short golesFavor, short golesContra,
                                       short ganados, short empatados, short perdidos,
                                       short amarillas, short rojas, short faltas)
    : golesFavor(golesFavor), golesContra(golesContra), ganados(ganados),
    empatados(empatados), perdidos(perdidos), tarjetasAmarillas(amarillas),
    tarjetasRojas(rojas), faltas(faltas) {}

short EstadisticasEquipo::getGolesFavor() const        { return golesFavor; }
short EstadisticasEquipo::getGolesContra() const       { return golesContra; }
short EstadisticasEquipo::getGanados() const           { return ganados; }
short EstadisticasEquipo::getEmpatados() const         { return empatados; }
short EstadisticasEquipo::getPerdidos() const          { return perdidos; }
short EstadisticasEquipo::getTarjetasAmarillas() const { return tarjetasAmarillas; }
short EstadisticasEquipo::getTarjetasRojas() const     { return tarjetasRojas; }
short EstadisticasEquipo::getFaltas() const            { return faltas; }

float EstadisticasEquipo::getPromGolesFavor() const {
    short partidos = ganados + empatados + perdidos;
    if (partidos == 0) return 0.0f;
    return (float)golesFavor / partidos;
}

float EstadisticasEquipo::getPromGolesContra() const {
    short partidos = ganados + empatados + perdidos;
    if (partidos == 0) return 0.0f;
    return (float)golesContra / partidos;
}

EstadisticasEquipo& EstadisticasEquipo::operator+=(const EstadisticasEquipo& otro) {
    golesFavor        += otro.golesFavor;
    golesContra       += otro.golesContra;
    ganados           += otro.ganados;
    empatados         += otro.empatados;
    perdidos          += otro.perdidos;
    tarjetasAmarillas += otro.tarjetasAmarillas;
    tarjetasRojas     += otro.tarjetasRojas;
    faltas            += otro.faltas;
    return *this;
}

ostream& operator<<(ostream& os, const EstadisticasEquipo& e) {
    os << "GF: "           << e.golesFavor
       << " | GC: "        << e.golesContra
       << " | G: "         << e.ganados
       << " | E: "         << e.empatados
       << " | P: "         << e.perdidos
       << " | Amarillas: " << e.tarjetasAmarillas
       << " | Rojas: "     << e.tarjetasRojas
       << " | Faltas: "    << e.faltas;
    return os;
}
