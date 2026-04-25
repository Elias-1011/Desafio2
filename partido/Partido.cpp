#include "Partido.h"

using namespace std;

static const float ALFA = 0.6f;
static const float BETA = 0.4f;
static const float MU   = 1.35f;

Partido::Partido()
    : fecha(""), hora(""), sede(""),
    equipo1(nullptr), equipo2(nullptr),
    prorroga(false), simulado(false), bytesReportados(0) {
    arbitros[0] = arbitros[1] = arbitros[2] = "";
    bytesReportados = fecha.capacity()       +
                      hora.capacity()        +
                      sede.capacity()        +
                      arbitros[0].capacity() +
                      arbitros[1].capacity() +
                      arbitros[2].capacity();
    MedidorRecursos::getInstancia().sumarMemoria(bytesReportados);
}

Partido::Partido(const string& fecha, const string& hora,
                 const string& sede, Equipo* equipo1, Equipo* equipo2,
                 const string& arb1, const string& arb2,
                 const string& arb3)
    : fecha(fecha), hora(hora), sede(sede),
    equipo1(equipo1), equipo2(equipo2),
    prorroga(false), simulado(false), bytesReportados(0) {
    arbitros[0] = arb1;
    arbitros[1] = arb2;
    arbitros[2] = arb3;
    bytesReportados = this->fecha.capacity()  +
                      this->hora.capacity()   +
                      this->sede.capacity()   +
                      arbitros[0].capacity()  +
                      arbitros[1].capacity()  +
                      arbitros[2].capacity();
    MedidorRecursos::getInstancia().sumarMemoria(bytesReportados);
}

Partido::Partido(const Partido& otro)
    : fecha(otro.fecha), hora(otro.hora), sede(otro.sede),
    equipo1(otro.equipo1), equipo2(otro.equipo2),
    statsEq1(otro.statsEq1), statsEq2(otro.statsEq2),
    prorroga(otro.prorroga), simulado(otro.simulado),
    bytesReportados(0) {
    arbitros[0] = otro.arbitros[0];
    arbitros[1] = otro.arbitros[1];
    arbitros[2] = otro.arbitros[2];
    bytesReportados = fecha.capacity()       +
                      hora.capacity()        +
                      sede.capacity()        +
                      arbitros[0].capacity() +
                      arbitros[1].capacity() +
                      arbitros[2].capacity();
    MedidorRecursos::getInstancia().sumarMemoria(bytesReportados);
}

Partido& Partido::operator=(const Partido& otro) {
    if (this == &otro) return *this;
    MedidorRecursos::getInstancia().restarMemoria(bytesReportados);
    fecha    = otro.fecha;
    hora     = otro.hora;
    sede     = otro.sede;
    equipo1  = otro.equipo1;
    equipo2  = otro.equipo2;
    statsEq1 = otro.statsEq1;
    statsEq2 = otro.statsEq2;
    prorroga = otro.prorroga;
    simulado = otro.simulado;
    arbitros[0] = otro.arbitros[0];
    arbitros[1] = otro.arbitros[1];
    arbitros[2] = otro.arbitros[2];
    bytesReportados = fecha.capacity()       +
                      hora.capacity()        +
                      sede.capacity()        +
                      arbitros[0].capacity() +
                      arbitros[1].capacity() +
                      arbitros[2].capacity();
    MedidorRecursos::getInstancia().sumarMemoria(bytesReportados);
    return *this;
}

Partido::~Partido() {
    MedidorRecursos::getInstancia().restarMemoria(bytesReportados);
}

float Partido::aleatorio() const {
    return (float)rand() / (float)RAND_MAX;
}

float Partido::calcularLambda(float promGF, float promGC) const {
    if (promGF <= 0.0f) promGF = 0.01f;
    if (promGC <= 0.0f) promGC = 0.01f;
    return MU * pow(promGF / MU, ALFA) * pow(promGC / MU, BETA);
}

float Partido::calcularPosesion(short rankingA, short rankingB) const {
    float total = (float)(rankingA + rankingB);
    if (total == 0.0f) return 50.0f;
    return ((float)rankingB / total) * 100.0f;
}

void Partido::seleccionarConvocados(Equipo* equipo,
                                    EstPartidoEquipo& stats,
                                    int minutos) {
    size_t bytesLocales = sizeof(char) * 26
                          + sizeof(char) * 2
                          + sizeof(int);
    MedidorRecursos::getInstancia().sumarMemoria(bytesLocales);

    char indices[26];
    for (char i = 0; i < 26; i++) {
        indices[(int)i] = i;
        MedidorRecursos::getInstancia().contarIteracion();
    }
    for (char i = 0; i < 11; i++) {
        char j = (char)(i + rand() % (26 - (int)i));
        char temp       = indices[(int)i];
        indices[(int)i] = indices[(int)j];
        indices[(int)j] = temp;
        MedidorRecursos::getInstancia().contarIteracion();
    }
    for (char i = 0; i < 11; i++) {
        Jugador* jug = &equipo->getPlantilla()[(int)indices[(int)i]];
        stats.agregarConvocado(JugadorConvocado(jug, minutos));
        MedidorRecursos::getInstancia().contarIteracion();
    }

    MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
}

void Partido::simularConvocados(EstPartidoEquipo& stats, float lambda) {
    size_t bytesLocales = sizeof(float)
                          + sizeof(short)
                          + sizeof(short)
                          + sizeof(float)
                          + sizeof(int);
    MedidorRecursos::getInstancia().sumarMemoria(bytesLocales);

    short metaGoles      = (short)round(lambda);
    short golesAsignados = 0;

    Lista<JugadorConvocado>& convocados = stats.getConvocados();

    for (int i = 0; i < convocados.getTamanio(); i++) {
        JugadorConvocado& jc = convocados[i];
        MedidorRecursos::getInstancia().contarIteracion();

        if (golesAsignados < metaGoles && aleatorio() < 0.04f) {
            jc.agregarGol();
            golesAsignados++;
        }

        if (aleatorio() < 0.06f) {
            jc.agregarAmarilla();
            if (aleatorio() < 0.0115f) {
                jc.agregarAmarilla();
                jc.agregarRoja();
            }
        }

        if (aleatorio() < 0.13f) {
            jc.agregarFalta();
            if (aleatorio() < 0.0275f) {
                jc.agregarFalta();
                if (aleatorio() < 0.007f)
                    jc.agregarFalta();
            }
        }
    }

    stats.setGolesFavor(golesAsignados);
    MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
}

void Partido::simular(bool conProrroga) {
    if (simulado || equipo1 == nullptr || equipo2 == nullptr) return;

    size_t bytesLocales = sizeof(bool)
                          + sizeof(float) * 4
                          + sizeof(short) * 6
                          + sizeof(int);
    MedidorRecursos::getInstancia().sumarMemoria(bytesLocales);

    int minutos = 90;

    float lambdaA = calcularLambda(
        equipo1->getEstadisticas().getPromGolesFavor(),
        equipo2->getEstadisticas().getPromGolesContra()
        );
    float lambdaB = calcularLambda(
        equipo2->getEstadisticas().getPromGolesFavor(),
        equipo1->getEstadisticas().getPromGolesContra()
        );
    float posA = calcularPosesion(equipo1->getRankingFIFA(),
                                  equipo2->getRankingFIFA());
    statsEq1.setPosesion(posA);
    statsEq2.setPosesion(100.0f - posA);

    seleccionarConvocados(equipo1, statsEq1, minutos);
    seleccionarConvocados(equipo2, statsEq2, minutos);
    simularConvocados(statsEq1, lambdaA);
    simularConvocados(statsEq2, lambdaB);

    statsEq1.setGolesContra(statsEq2.getGolesFavor());
    statsEq2.setGolesContra(statsEq1.getGolesFavor());

    if (conProrroga &&
        statsEq1.getGolesFavor() == statsEq2.getGolesFavor()) {
        prorroga = true;

        Lista<JugadorConvocado>& conv1 = statsEq1.getConvocados();
        Lista<JugadorConvocado>& conv2 = statsEq2.getConvocados();
        for (int i = 0; i < conv1.getTamanio(); i++) {
            conv1[i].extenderAProrroga();
            MedidorRecursos::getInstancia().contarIteracion();
        }
        for (int i = 0; i < conv2.getTamanio(); i++) {
            conv2[i].extenderAProrroga();
            MedidorRecursos::getInstancia().contarIteracion();
        }

        short r1 = equipo1->getRankingFIFA();
        short r2 = equipo2->getRankingFIFA();
        float probEq1 = (float)r2 / (float)(r1 + r2);
        if (aleatorio() < probEq1) {
            statsEq1.setGolesFavor(statsEq1.getGolesFavor() + 1);
            statsEq2.setGolesContra(statsEq2.getGolesContra() + 1);
        } else {
            statsEq2.setGolesFavor(statsEq2.getGolesFavor() + 1);
            statsEq1.setGolesContra(statsEq1.getGolesContra() + 1);
        }
    }

    short amarillasEq1 = 0, rojasEq1 = 0, faltasEq1 = 0;
    short amarillasEq2 = 0, rojasEq2 = 0, faltasEq2 = 0;
    Lista<JugadorConvocado>& conv1 = statsEq1.getConvocados();
    Lista<JugadorConvocado>& conv2 = statsEq2.getConvocados();
    for (int i = 0; i < conv1.getTamanio(); i++) {
        amarillasEq1 += conv1[i].getTarjetasAmarillas();
        rojasEq1     += conv1[i].getTarjetasRojas();
        faltasEq1    += conv1[i].getFaltas();
        MedidorRecursos::getInstancia().contarIteracion();
    }
    for (int i = 0; i < conv2.getTamanio(); i++) {
        amarillasEq2 += conv2[i].getTarjetasAmarillas();
        rojasEq2     += conv2[i].getTarjetasRojas();
        faltasEq2    += conv2[i].getFaltas();
        MedidorRecursos::getInstancia().contarIteracion();
    }

    statsEq1.actualizarHistoricos();
    statsEq2.actualizarHistoricos();

    short gf1 = statsEq1.getGolesFavor();
    short gf2 = statsEq2.getGolesFavor();

    EstadisticasEquipo deltaEq1(
        gf1, gf2,
        gf1 > gf2 ? 1 : 0,
        gf1 == gf2 ? 1 : 0,
        gf1 < gf2 ? 1 : 0,
        amarillasEq1, rojasEq1, faltasEq1
        );
    equipo1->getEstadisticas() += deltaEq1;

    EstadisticasEquipo deltaEq2(
        gf2, gf1,
        gf2 > gf1 ? 1 : 0,
        gf2 == gf1 ? 1 : 0,
        gf2 < gf1 ? 1 : 0,
        amarillasEq2, rojasEq2, faltasEq2
        );
    equipo2->getEstadisticas() += deltaEq2;

    simulado = true;
    MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
}

Equipo* Partido::getEquipo1()  const { return equipo1; }
Equipo* Partido::getEquipo2()  const { return equipo2; }
bool    Partido::isProrroga()  const { return prorroga; }
bool    Partido::isSimulado()  const { return simulado; }
const string& Partido::getFecha() const { return fecha; }

EstPartidoEquipo&       Partido::getStatsEq1()       { return statsEq1; }
EstPartidoEquipo&       Partido::getStatsEq2()       { return statsEq2; }
const EstPartidoEquipo& Partido::getStatsEq1() const { return statsEq1; }
const EstPartidoEquipo& Partido::getStatsEq2() const { return statsEq2; }

Equipo* Partido::getGanador() const {
    if (!simulado) return nullptr;
    if (statsEq1.getGolesFavor() > statsEq2.getGolesFavor()) return equipo1;
    if (statsEq2.getGolesFavor() > statsEq1.getGolesFavor()) return equipo2;
    return nullptr;
}

ostream& operator<<(ostream& os, const Partido& p) {
    os << "Partido: " << p.equipo1->getPais()
    << " vs "      << p.equipo2->getPais()
    << " | Fecha: "<< p.fecha
    << " | Hora: " << p.hora
    << (p.prorroga ? " | PRORROGA" : "") << "\n"
    << "  Resultado: "
    << p.statsEq1.getGolesFavor() << " - "
    << p.statsEq2.getGolesFavor() << "\n"
    << "  " << p.equipo1->getPais()
    << " posesion: " << p.statsEq1.getPosesion() << "%\n"
    << "  " << p.equipo2->getPais()
    << " posesion: " << p.statsEq2.getPosesion() << "%\n";
    return os;
}
