#include "JugadorConvocado.h"

using namespace std;

JugadorConvocado::JugadorConvocado()
    : jugador(nullptr), goles(0), tarjetasAmarillas(0),
    tarjetasRojas(0), faltas(0), minutosJugados(0) {}

JugadorConvocado::JugadorConvocado(Jugador* jugador, int minutos)
    : jugador(jugador), goles(0), tarjetasAmarillas(0),
    tarjetasRojas(0), faltas(0), minutosJugados(minutos) {}

JugadorConvocado::JugadorConvocado(const JugadorConvocado& otro)
    : jugador(otro.jugador), goles(otro.goles),
    tarjetasAmarillas(otro.tarjetasAmarillas),
    tarjetasRojas(otro.tarjetasRojas),
    faltas(otro.faltas), minutosJugados(otro.minutosJugados) {}

JugadorConvocado& JugadorConvocado::operator=(const JugadorConvocado& otro) {
    if (this == &otro) return *this;
    jugador           = otro.jugador;
    goles             = otro.goles;
    tarjetasAmarillas = otro.tarjetasAmarillas;
    tarjetasRojas     = otro.tarjetasRojas;
    faltas            = otro.faltas;
    minutosJugados    = otro.minutosJugados;
    return *this;
}

Jugador* JugadorConvocado::getJugador()           const { return jugador; }
short    JugadorConvocado::getGoles()              const { return goles; }
short    JugadorConvocado::getTarjetasAmarillas()  const { return tarjetasAmarillas; }
short    JugadorConvocado::getTarjetasRojas()      const { return tarjetasRojas; }
short    JugadorConvocado::getFaltas()             const { return faltas; }
int      JugadorConvocado::getMinutosJugados()     const { return minutosJugados; }

void JugadorConvocado::agregarGol()      { goles++; }
void JugadorConvocado::agregarAmarilla() { tarjetasAmarillas++; }
void JugadorConvocado::agregarRoja()     { tarjetasRojas++; }
void JugadorConvocado::agregarFalta()    { faltas++; }
void JugadorConvocado::extenderAProrroga() { minutosJugados = 120; }

void JugadorConvocado::actualizarHistorico() {
    if (jugador == nullptr) return;
    EstadisticasJugador delta(
        goles, 1, minutosJugados, 0,
        tarjetasAmarillas, tarjetasRojas, faltas
        );
    jugador->getEstadisticas() += delta;
}

ostream& operator<<(ostream& os, const JugadorConvocado& jc) {
    if (jc.jugador == nullptr) return os;
    os << "#" << jc.jugador->getNumeroCamiseta()
       << " " << jc.jugador->getNombre()
       << " " << jc.jugador->getApellido()
       << " | Goles: "     << jc.goles
       << " | Amarillas: " << jc.tarjetasAmarillas
       << " | Rojas: "     << jc.tarjetasRojas
       << " | Faltas: "    << jc.faltas
       << " | Minutos: "   << jc.minutosJugados;
    return os;
}
