#ifndef PARTIDO_H
#define PARTIDO_H

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include "../utils/MedidorRecursos.h"
#include "../entidades/Equipo.h"
#include "EstPartidoEquipo.h"

using namespace std;

class Partido {
private:
    string           fecha;
    string           hora;
    string           sede;
    string           arbitros[3];
    Equipo*          equipo1;
    Equipo*          equipo2;
    EstPartidoEquipo statsEq1;
    EstPartidoEquipo statsEq2;
    bool             prorroga;
    bool             simulado;
    size_t           bytesReportados;

    void  seleccionarConvocados(Equipo* equipo,
                               EstPartidoEquipo& stats, int minutos);
    void  simularConvocados(EstPartidoEquipo& stats, float lambda);
    float calcularLambda(float promGF, float promGC)          const;
    float calcularPosesion(short rankingA, short rankingB)    const;
    float aleatorio()                                          const;

public:
    Partido();
    Partido(const string& fecha, const string& hora,
            const string& sede, Equipo* equipo1, Equipo* equipo2,
            const string& arb1, const string& arb2,
            const string& arb3);
    Partido(const Partido& otro);
    Partido& operator=(const Partido& otro);
    ~Partido();

    void simular(bool permitirProrroga = false);

    Equipo*                  getEquipo1()   const;
    Equipo*                  getEquipo2()   const;
    Equipo*                  getGanador()   const;
    bool                     isProrroga()   const;
    bool                     isSimulado()   const;
    const string&            getFecha()     const;

    EstPartidoEquipo&        getStatsEq1();
    EstPartidoEquipo&        getStatsEq2();
    const EstPartidoEquipo&  getStatsEq1() const;
    const EstPartidoEquipo&  getStatsEq2() const;

    friend ostream& operator<<(ostream& os, const Partido& p);
};

#endif
