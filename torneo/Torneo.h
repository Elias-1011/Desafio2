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

using namespace std;

class Torneo {
private:
    Lista<Equipo>  equipos;
    Lista<Grupo>   grupos;
    GestorArchivos gestor;

    bool datosCargados;
    bool gruposConformados;
    bool faseGruposSimulada;
    bool transicionR16Hecha;
    bool eliminatoriasSimuladas;

    void   ordenarPorRanking(Equipo** arreglo, char n);
    void   armarBombos(Equipo** bombo1, Equipo** bombo2,
                     Equipo** bombo3, Equipo** bombo4);
    void   mezclar(Equipo** arreglo, char n);
    bool   asignarBombo(Equipo** bombo, char indice,
                      char n, char nivelBombo);
    int    buscarIndiceEquipo(const Equipo* equipo) const;
    string generarFecha(int dia) const;

public:
    Torneo();

    void cargarDatos(const string& rutaCSV);
    void conformarGrupos();
    void mostrarGrupos() const;
    void simularFaseGrupos();
    void mostrarMenu();
};

#endif
