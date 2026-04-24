#include "Grupo.h"

using namespace std;

Grupo::Grupo()
    : letra(' '), cantidadEquipos(0) {
    for (int i = 0; i < 4; i++) equipos[i] = nullptr;
}

Grupo::Grupo(char letra)
    : letra(letra), cantidadEquipos(0) {
    for (int i = 0; i < 4; i++) equipos[i] = nullptr;
}

Grupo::Grupo(const Grupo& otro)
    : letra(otro.letra), cantidadEquipos(otro.cantidadEquipos) {
    for (int i = 0; i < 4; i++) equipos[i] = otro.equipos[i];
}

Grupo& Grupo::operator=(const Grupo& otro) {
    if (this == &otro) return *this;
    letra           = otro.letra;
    cantidadEquipos = otro.cantidadEquipos;
    for (int i = 0; i < 4; i++) equipos[i] = otro.equipos[i];
    return *this;
}

char    Grupo::getLetra()           const { return letra; }
char    Grupo::getCantidadEquipos() const { return cantidadEquipos; }
Equipo* Grupo::getEquipo(int i)     const { return equipos[i]; }

int Grupo::contarConfederacion(const string& confederacion) const {
    size_t bytesLocales = sizeof(int) + sizeof(char);
    MedidorRecursos::getInstancia().sumarMemoria(bytesLocales);

    int cuenta = 0;
    for (char i = 0; i < cantidadEquipos; i++) {
        if (equipos[(int)i]->getConfederacion() == confederacion)
            cuenta++;
        MedidorRecursos::getInstancia().contarIteracion();
    }

    MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
    return cuenta;
}

bool Grupo::puedeAgregar(const Equipo* equipo) const {
    size_t bytesLocales = sizeof(Equipo*) + sizeof(int);
    MedidorRecursos::getInstancia().sumarMemoria(bytesLocales);

    if (cantidadEquipos >= 4) {
        MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
        return false;
    }
    const string& conf = equipo->getConfederacion();
    int cantidad = contarConfederacion(conf);
    bool resultado = (conf == "UEFA") ? cantidad < 2 : cantidad < 1;

    MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
    return resultado;
}

void Grupo::agregarEquipo(Equipo* equipo) {
    if (cantidadEquipos < 4)
        equipos[(int)cantidadEquipos++] = equipo;
}

void Grupo::quitarUltimoEquipo() {
    if (cantidadEquipos > 0)
        equipos[(int)--cantidadEquipos] = nullptr;
}

ostream& operator<<(ostream& os, const Grupo& g) {
    os << "Grupo " << g.letra << ":\n";
    for (char i = 0; i < g.cantidadEquipos; i++) {
        os << "  " << g.equipos[(int)i]->getPais()
        << " (" << g.equipos[(int)i]->getConfederacion() << ")"
        << " [FIFA: " << g.equipos[(int)i]->getRankingFIFA() << "]\n";
    }
    return os;
}
