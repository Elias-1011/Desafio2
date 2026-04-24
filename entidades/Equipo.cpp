#include "Equipo.h"

using namespace std;

Equipo::Equipo()
    : rankingFIFA(0), pais(""), directorTecnico(""),
    federacion(""), confederacion(""),
    plantilla(26), estadisticas(), bytesReportados(0) {
    bytesReportados = pais.capacity()            +
                      directorTecnico.capacity() +
                      federacion.capacity()      +
                      confederacion.capacity();
    MedidorRecursos::getInstancia().sumarMemoria(bytesReportados);
}

Equipo::Equipo(short rankingFIFA, const string& pais,
               const string& directorTecnico, const string& federacion,
               const string& confederacion, const EstadisticasEquipo& estadisticas)
    : rankingFIFA(rankingFIFA), pais(pais),
    directorTecnico(directorTecnico), federacion(federacion),
    confederacion(confederacion), plantilla(26),
    estadisticas(estadisticas), bytesReportados(0) {
    bytesReportados = this->pais.capacity()            +
                      this->directorTecnico.capacity() +
                      this->federacion.capacity()      +
                      this->confederacion.capacity();
    MedidorRecursos::getInstancia().sumarMemoria(bytesReportados);
}

Equipo::Equipo(const Equipo& otro)
    : rankingFIFA(otro.rankingFIFA), pais(otro.pais),
    directorTecnico(otro.directorTecnico), federacion(otro.federacion),
    confederacion(otro.confederacion), plantilla(otro.plantilla),
    estadisticas(otro.estadisticas), bytesReportados(0) {
    bytesReportados = pais.capacity()            +
                      directorTecnico.capacity() +
                      federacion.capacity()      +
                      confederacion.capacity();
    MedidorRecursos::getInstancia().sumarMemoria(bytesReportados);
}

Equipo& Equipo::operator=(const Equipo& otro) {
    if (this == &otro) return *this;
    MedidorRecursos::getInstancia().restarMemoria(bytesReportados);
    rankingFIFA     = otro.rankingFIFA;
    pais            = otro.pais;
    directorTecnico = otro.directorTecnico;
    federacion      = otro.federacion;
    confederacion   = otro.confederacion;
    plantilla       = otro.plantilla;
    estadisticas    = otro.estadisticas;
    bytesReportados = pais.capacity()            +
                      directorTecnico.capacity() +
                      federacion.capacity()      +
                      confederacion.capacity();
    MedidorRecursos::getInstancia().sumarMemoria(bytesReportados);
    return *this;
}

Equipo::~Equipo() {
    MedidorRecursos::getInstancia().restarMemoria(bytesReportados);
}

short         Equipo::getRankingFIFA()     const { return rankingFIFA; }
const string& Equipo::getPais()            const { return pais; }
const string& Equipo::getDirectorTecnico() const { return directorTecnico; }
const string& Equipo::getFederacion()      const { return federacion; }
const string& Equipo::getConfederacion()   const { return confederacion; }

Lista<Jugador>&       Equipo::getPlantilla()       { return plantilla; }
const Lista<Jugador>& Equipo::getPlantilla() const { return plantilla; }

EstadisticasEquipo&       Equipo::getEstadisticas()       { return estadisticas; }
const EstadisticasEquipo& Equipo::getEstadisticas() const { return estadisticas; }

void Equipo::agregarJugador(const Jugador& jugador) {
    plantilla.agregar(jugador);
}

bool Equipo::operator<(const Equipo& otro) const {
    return rankingFIFA < otro.rankingFIFA;
}

bool Equipo::operator==(const Equipo& otro) const {
    return pais == otro.pais;
}

ostream& operator<<(ostream& os, const Equipo& e) {
    os << "[" << e.rankingFIFA << "] "
       << e.pais
       << " | " << e.confederacion
       << " | DT: " << e.directorTecnico
       << "\n  " << e.estadisticas;
    return os;
}
