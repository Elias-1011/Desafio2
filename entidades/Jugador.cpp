#include "Jugador.h"

using namespace std;

Jugador::Jugador()
    : nombre(""), apellido(""), numeroCamiseta(0), estadisticas() {
    MedidorRecursos::getInstancia().sumarMemoria(
        nombre.capacity() + apellido.capacity()
        );
}

Jugador::Jugador(const string& nombre, const string& apellido,
                 short numeroCamiseta, const EstadisticasJugador& estadisticas)
    : nombre(nombre), apellido(apellido),
    numeroCamiseta(numeroCamiseta), estadisticas(estadisticas) {
    MedidorRecursos::getInstancia().sumarMemoria(
        nombre.capacity() + apellido.capacity()
        );
}

Jugador::Jugador(const Jugador& otro)
    : nombre(otro.nombre), apellido(otro.apellido),
    numeroCamiseta(otro.numeroCamiseta), estadisticas(otro.estadisticas) {
    MedidorRecursos::getInstancia().sumarMemoria(
        nombre.capacity() + apellido.capacity()
        );
}

Jugador::~Jugador() {
    MedidorRecursos::getInstancia().restarMemoria(
        nombre.capacity() + apellido.capacity()
        );
}

const string& Jugador::getNombre()        const { return nombre; }
const string& Jugador::getApellido()      const { return apellido; }
short         Jugador::getNumeroCamiseta() const { return numeroCamiseta; }

EstadisticasJugador& Jugador::getEstadisticas()             { return estadisticas; }
const EstadisticasJugador& Jugador::getEstadisticas() const { return estadisticas; }

ostream& operator<<(ostream& os, const Jugador& j) {
    os << "#" << j.numeroCamiseta
       << " " << j.nombre
       << " " << j.apellido
       << " | " << j.estadisticas;
    return os;
}
