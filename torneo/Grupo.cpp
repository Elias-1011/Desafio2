#include "Grupo.h"

using namespace std;

Grupo::Grupo()
    : letra(' '), cantidadEquipos(0),
    partidos(6), tabla() {
    for (int i = 0; i < 4; i++) equipos[i] = nullptr;
}

Grupo::Grupo(char letra)
    : letra(letra), cantidadEquipos(0),
    partidos(6), tabla() {
    for (int i = 0; i < 4; i++) equipos[i] = nullptr;
}

Grupo::Grupo(const Grupo& otro)
    : letra(otro.letra), cantidadEquipos(otro.cantidadEquipos),
    partidos(otro.partidos), tabla(otro.tabla) {
    for (int i = 0; i < 4; i++) equipos[i] = otro.equipos[i];
}

Grupo& Grupo::operator=(const Grupo& otro) {
    if (this == &otro) return *this;
    letra           = otro.letra;
    cantidadEquipos = otro.cantidadEquipos;
    partidos        = otro.partidos;
    tabla           = otro.tabla;
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

void Grupo::agregarPartido(const Partido& partido) {
    partidos.agregar(partido);
}

void Grupo::simularPartidos() {
    for (int p = 0; p < partidos.getTamanio(); p++) {
        partidos[p].simular(false);
        MedidorRecursos::getInstancia().contarIteracion();
    }
}

void Grupo::construirTabla() {
    for (char i = 0; i < cantidadEquipos; i++) {
        tabla.agregar(EntradaTabla(equipos[(int)i]));
        MedidorRecursos::getInstancia().contarIteracion();
    }

    for (int p = 0; p < partidos.getTamanio(); p++) {
        const Partido& partido = partidos[p];
        if (!partido.isSimulado()) continue;

        short   gf1 = partido.getStatsEq1().getGolesFavor();
        short   gf2 = partido.getStatsEq2().getGolesFavor();
        Equipo* eq1 = partido.getEquipo1();
        Equipo* eq2 = partido.getEquipo2();

        for (int i = 0; i < tabla.getTamanio(); i++) {
            EntradaTabla& entrada = tabla.getEntrada(i);
            if (entrada.getEquipo() == eq1) {
                if      (gf1 > gf2) entrada.sumarVictoria(gf1, gf2);
                else if (gf1 == gf2) entrada.sumarEmpate(gf1, gf2);
                else                 entrada.sumarDerrota(gf1, gf2);
            }
            if (entrada.getEquipo() == eq2) {
                if      (gf2 > gf1) entrada.sumarVictoria(gf2, gf1);
                else if (gf2 == gf1) entrada.sumarEmpate(gf2, gf1);
                else                 entrada.sumarDerrota(gf2, gf1);
            }
            MedidorRecursos::getInstancia().contarIteracion();
        }
        MedidorRecursos::getInstancia().contarIteracion();
    }

    tabla.construir();
}

void Grupo::imprimirPartidos() const {
    cout << "\n--- Partidos Grupo " << letra << " ---\n";
    for (int p = 0; p < partidos.getTamanio(); p++) {
        const Partido& partido = partidos[p];
        cout << partido;

        cout << "  Goleadores " << partido.getEquipo1()->getPais() << ": ";
        const Lista<JugadorConvocado>& conv1 =
            partido.getStatsEq1().getConvocados();
        bool hayGoles = false;
        for (int i = 0; i < conv1.getTamanio(); i++) {
            if (conv1[i].getGoles() > 0) {
                cout << "#" << conv1[i].getJugador()->getNumeroCamiseta() << " ";
                hayGoles = true;
            }
            MedidorRecursos::getInstancia().contarIteracion();
        }
        if (!hayGoles) cout << "ninguno";
        cout << "\n";

        cout << "  Goleadores " << partido.getEquipo2()->getPais() << ": ";
        const Lista<JugadorConvocado>& conv2 =
            partido.getStatsEq2().getConvocados();
        hayGoles = false;
        for (int i = 0; i < conv2.getTamanio(); i++) {
            if (conv2[i].getGoles() > 0) {
                cout << "#" << conv2[i].getJugador()->getNumeroCamiseta() << " ";
                hayGoles = true;
            }
            MedidorRecursos::getInstancia().contarIteracion();
        }
        if (!hayGoles) cout << "ninguno";
        cout << "\n\n";
    }
}

const TablaClasificacion& Grupo::getTabla() const {
    return tabla;
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
