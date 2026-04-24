#ifndef EQUIPO_H
#define EQUIPO_H

#include <iostream>
#include <string>
#include "../utils/Lista.h"
#include "../utils/MedidorRecursos.h"
#include "../estadisticas/EstadisticasEquipo.h"
#include "Jugador.h"

using namespace std;

class Equipo {
private:
    short              rankingFIFA;
    string             pais;
    string             directorTecnico;
    string             federacion;
    string             confederacion;
    Lista<Jugador>     plantilla;
    EstadisticasEquipo estadisticas;
    size_t             bytesReportados;

public:
    Equipo();
    Equipo(short rankingFIFA, const string& pais,
           const string& directorTecnico, const string& federacion,
           const string& confederacion, const EstadisticasEquipo& estadisticas);
    Equipo(const Equipo& otro);
    Equipo& operator=(const Equipo& otro);
    ~Equipo();

    short         getRankingFIFA()     const;
    const string& getPais()            const;
    const string& getDirectorTecnico() const;
    const string& getFederacion()      const;
    const string& getConfederacion()   const;

    Lista<Jugador>&       getPlantilla();
    const Lista<Jugador>& getPlantilla() const;

    EstadisticasEquipo&       getEstadisticas();
    const EstadisticasEquipo& getEstadisticas() const;

    void agregarJugador(const Jugador& jugador);

    bool operator<(const Equipo& otro)  const;
    bool operator==(const Equipo& otro) const;

    friend ostream& operator<<(ostream& os, const Equipo& e);
};

#endif
