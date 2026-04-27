#include "EstPartidoEquipo.h"

using namespace std;

EstPartidoEquipo::EstPartidoEquipo()
    : golesFavor(0), golesContra(0),
    posesion(0.0f), convocados(11) {}

EstPartidoEquipo::EstPartidoEquipo(const EstPartidoEquipo& otro)
    : golesFavor(otro.golesFavor), golesContra(otro.golesContra),
    posesion(otro.posesion), convocados(otro.convocados) {}

EstPartidoEquipo& EstPartidoEquipo::operator=(const EstPartidoEquipo& otro) {
    if (this == &otro) return *this;
    golesFavor  = otro.golesFavor;
    golesContra = otro.golesContra;
    posesion    = otro.posesion;
    convocados  = otro.convocados;
    return *this;
}

short EstPartidoEquipo::getGolesFavor()  const { return golesFavor; }
short EstPartidoEquipo::getGolesContra() const { return golesContra; }
short EstPartidoEquipo::getPosesion() const { return posesion; }

Lista<JugadorConvocado>& EstPartidoEquipo::getConvocados() {
    return convocados;
}
const Lista<JugadorConvocado>& EstPartidoEquipo::getConvocados() const {
    return convocados;
}

void EstPartidoEquipo::setGolesFavor(short g)  { golesFavor = g; }
void EstPartidoEquipo::setGolesContra(short g) { golesContra = g; }
void EstPartidoEquipo::setPosesion(short p) { posesion = p; }

void EstPartidoEquipo::agregarConvocado(const JugadorConvocado& jc) {
    convocados.agregar(jc);
}

void EstPartidoEquipo::actualizarHistoricos() {
    for (int i = 0; i < convocados.getTamanio(); i++) {
        convocados[i].actualizarHistorico();
    }
}

ostream& operator<<(ostream& os, const EstPartidoEquipo& e) {
    os << "Goles: " << e.golesFavor
       << " | Posesion: " << e.posesion << "%";
    return os;
}
