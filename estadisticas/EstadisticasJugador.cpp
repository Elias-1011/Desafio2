#include "EstadisticasJugador.h"

using namespace std;

EstadisticasJugador::EstadisticasJugador()
    : goles(0), partidosJugados(0), minutosJugados(0),
    asistencias(0), tarjetasAmarillas(0),
    tarjetasRojas(0), faltas(0) {}

EstadisticasJugador::EstadisticasJugador(short goles, short partidos,
                                         int minutos, short asistencias, short amarillas,
                                         short rojas, short faltas)
    : goles(goles), partidosJugados(partidos), minutosJugados(minutos),
    asistencias(asistencias), tarjetasAmarillas(amarillas),
    tarjetasRojas(rojas), faltas(faltas) {}

short EstadisticasJugador::getGoles() const             { return goles; }
short EstadisticasJugador::getPartidosJugados() const   { return partidosJugados; }
int   EstadisticasJugador::getMinutosJugados() const    { return minutosJugados; }
short EstadisticasJugador::getAsistencias() const       { return asistencias; }
short EstadisticasJugador::getTarjetasAmarillas() const { return tarjetasAmarillas; }
short EstadisticasJugador::getTarjetasRojas() const     { return tarjetasRojas; }
short EstadisticasJugador::getFaltas() const            { return faltas; }

EstadisticasJugador& EstadisticasJugador::operator+=(const EstadisticasJugador& otro) {
    goles             += otro.goles;
    partidosJugados   += otro.partidosJugados;
    minutosJugados    += otro.minutosJugados;
    asistencias       += otro.asistencias;
    tarjetasAmarillas += otro.tarjetasAmarillas;
    tarjetasRojas     += otro.tarjetasRojas;
    faltas            += otro.faltas;
    return *this;
}

ostream& operator<<(ostream& os, const EstadisticasJugador& e) {
    os << "Goles: "        << e.goles
       << " | Partidos: "  << e.partidosJugados
       << " | Minutos: "   << e.minutosJugados
       << " | Asist: "     << e.asistencias
       << " | Amarillas: " << e.tarjetasAmarillas
       << " | Rojas: "     << e.tarjetasRojas
       << " | Faltas: "    << e.faltas;
    return os;
}
