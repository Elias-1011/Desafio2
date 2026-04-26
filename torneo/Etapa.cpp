#include "Etapa.h"

using namespace std;

Etapa::Etapa()
    : nombre(""), partidos(8), bytesReportados(0) {
    bytesReportados = nombre.capacity();
    sumarMemoria(bytesReportados);
}

Etapa::Etapa(const string& nombre, int capacidad)
    : nombre(nombre), partidos(capacidad), bytesReportados(0) {
    bytesReportados = this->nombre.capacity();
    sumarMemoria(bytesReportados);
}

Etapa::Etapa(const Etapa& otra)
    : nombre(otra.nombre), partidos(otra.partidos),
    bytesReportados(0) {
    bytesReportados = nombre.capacity();
    sumarMemoria(bytesReportados);
}

Etapa& Etapa::operator=(const Etapa& otra) {
    if (this == &otra) return *this;
    restarMemoria(bytesReportados);
    nombre   = otra.nombre;
    partidos = otra.partidos;
    bytesReportados = nombre.capacity();
    sumarMemoria(bytesReportados);
    return *this;
}

Etapa::~Etapa() {
    restarMemoria(bytesReportados);
}

const string& Etapa::getNombre()       const { return nombre; }
int           Etapa::getCantPartidos() const { return partidos.getTamanio(); }

void Etapa::agregarPartido(const Partido& partido) {
    partidos.agregar(partido);
}

void Etapa::simular() {
    for (int i = 0; i < partidos.getTamanio(); i++) {
        partidos[i].simular(true);
        contarIteracion();
    }
}

void Etapa::imprimir() const {
    cout << "\n=== " << nombre << " ===\n";
    for (int i = 0; i < partidos.getTamanio(); i++) {
        const Partido& p = partidos[i];
        cout << p;

        const Lista<JugadorConvocado>& conv1 = p.getStatsEq1().getConvocados();
        cout << "  Goleadores " << p.getEquipo1()->getPais() << ": ";
        bool hayGoles = false;
        for (int j = 0; j < conv1.getTamanio(); j++) {
            if (conv1[j].getGoles() > 0) {
                cout << "#" << conv1[j].getJugador()->getNumeroCamiseta()
                << "(" << conv1[j].getGoles() << ") ";
                hayGoles = true;
            }
            contarIteracion();
        }
        if (!hayGoles) cout << "ninguno";
        cout << "\n";

        const Lista<JugadorConvocado>& conv2 = p.getStatsEq2().getConvocados();
        cout << "  Goleadores " << p.getEquipo2()->getPais() << ": ";
        hayGoles = false;
        for (int j = 0; j < conv2.getTamanio(); j++) {
            if (conv2[j].getGoles() > 0) {
                cout << "#" << conv2[j].getJugador()->getNumeroCamiseta()
                << "(" << conv2[j].getGoles() << ") ";
                hayGoles = true;
            }
            contarIteracion();
        }
        if (!hayGoles) cout << "ninguno";
        cout << "\n";
    }
}

Partido&       Etapa::getPartido(int i)       { return partidos[i]; }
const Partido& Etapa::getPartido(int i) const { return partidos[i]; }

ostream& operator<<(ostream& os, const Etapa& e) {
    os << "=== " << e.nombre << " ===\n";
    for (int i = 0; i < e.partidos.getTamanio(); i++)
        os << e.partidos[i];
    return os;
}
