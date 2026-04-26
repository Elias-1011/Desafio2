#ifndef TORNEO_H
#define TORNEO_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "../utils/Lista.h"
#include "../utils/MedidorRecursos.h"
#include "../utils/GestorArchivos.h"
#include "../entidades/Equipo.h"
#include "Grupo.h"
#include "Etapa.h"

using namespace std;

class Torneo {
private:
    Lista<Equipo> equipos;
    Lista<Grupo>  grupos;
    Lista<Etapa>  etapas;

    bool datosCargados;
    bool gruposConformados;
    bool faseGruposSimulada;
    bool transicionR16Hecha;
    bool eliminatoriasSimuladas;

    void    ordenarPorRanking(Equipo** arreglo, char n);
    void    armarBombos(Equipo** bombo1, Equipo** bombo2,
                     Equipo** bombo3, Equipo** bombo4);
    void    mezclar(Equipo** arreglo, char n);
    bool    asignarBombo(Equipo** bombo, char indice,
                      char n, char nivelBombo);
    int     buscarIndiceEquipo(const Equipo* equipo)  const;
    string  generarFecha(int dia)                     const;
    void    ordenarEntradas(EntradaTabla** arreglo, int n);
    bool    mismoGrupo(const Equipo* eq1, const Equipo* eq2) const;
    Partido crearPartido(Equipo* eq1, Equipo* eq2)    const;
    void construirEtapaDesdePares(const Etapa& anterior,
                                  const string& nombre,
                                  int capacidad);

public:
    Torneo();

    void cargarDatos(const string& rutaCSV);
    void conformarGrupos();
    void mostrarGrupos()       const;
    void simularFaseGrupos();
    void transicionR16();
    void simularEliminatorias();
    void generarEstadisticas() const;
    void mostrarMenu();
};

#endif
