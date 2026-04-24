#ifndef GESTORARCHIVOS_H
#define GESTORARCHIVOS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../utils/Lista.h"
#include "../entidades/Equipo.h"

using namespace std;

class GestorArchivos {
private:
    string extraerCampo(const string& linea, int& posicion);
    void   generarJugadores(Equipo& equipo);

public:
    GestorArchivos();

    bool cargarEquipos(const string& rutaCSV, Lista<Equipo>& equipos);
    bool guardarJugadores(const string& rutaArchivo, const Lista<Equipo>& equipos);
    bool cargarJugadores(const string& rutaArchivo, Lista<Equipo>& equipos);
};

#endif
