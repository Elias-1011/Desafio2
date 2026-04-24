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

    void ordenarPorRanking(Equipo** arreglo, char n);
    void armarBombos(Equipo** bombo1, Equipo** bombo2,
                     Equipo** bombo3, Equipo** bombo4);
    void mezclar(Equipo** arreglo, char n);
    bool asignarBombo(Equipo** bombo, char indice, char n, char nivelBombo);

public:
    Torneo();

    void cargarDatos(const string& rutaCSV);
    void conformarGrupos();
    void mostrarGrupos() const;
    void mostrarMenu();
};

#endif
