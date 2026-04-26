#include "Jugador.h"

using namespace std;

Jugador::Jugador()
    : nombre(""), apellido(""), numeroCamiseta(0),
    estadisticas(), bytesReportados(0) {
    bytesReportados = nombre.capacity() + apellido.capacity();
    sumarMemoria(bytesReportados);
}

Jugador::Jugador(const string& nombre, const string& apellido,
                 short numeroCamiseta, const EstadisticasJugador& estadisticas)
    : nombre(nombre), apellido(apellido),
    numeroCamiseta(numeroCamiseta), estadisticas(estadisticas),
    bytesReportados(0) {
    bytesReportados = this->nombre.capacity() + this->apellido.capacity();
    sumarMemoria(bytesReportados);
}

Jugador::Jugador(const Jugador& otro)
    : nombre(otro.nombre), apellido(otro.apellido),
    numeroCamiseta(otro.numeroCamiseta), estadisticas(otro.estadisticas),
    bytesReportados(0) {
    bytesReportados = nombre.capacity() + apellido.capacity();
    sumarMemoria(bytesReportados);
}

Jugador& Jugador::operator=(const Jugador& otro) {
    if (this == &otro) return *this;
    restarMemoria(bytesReportados);
    nombre         = otro.nombre;
    apellido       = otro.apellido;
    numeroCamiseta = otro.numeroCamiseta;
    estadisticas   = otro.estadisticas;
    bytesReportados = nombre.capacity() + apellido.capacity();
    sumarMemoria(bytesReportados);
    return *this;
}

Jugador::~Jugador() {
    restarMemoria(bytesReportados);
}

const string& Jugador::getNombre()         const { return nombre; }
const string& Jugador::getApellido()       const { return apellido; }
short         Jugador::getNumeroCamiseta() const { return numeroCamiseta; }

EstadisticasJugador&       Jugador::getEstadisticas()       { return estadisticas; }
const EstadisticasJugador& Jugador::getEstadisticas() const { return estadisticas; }

ostream& operator<<(ostream& os, const Jugador& j) {
    os << "#" << j.numeroCamiseta
       << " " << j.nombre
       << " " << j.apellido
       << " | " << j.estadisticas;
    return os;
}
