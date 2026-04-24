#include "GestorArchivos.h"

using namespace std;

GestorArchivos::GestorArchivos() {}

string GestorArchivos::extraerCampo(const string& linea, int& posicion) {
    size_t bytesLocales = sizeof(string);
    MedidorRecursos::getInstancia().sumarMemoria(bytesLocales);

    string campo = "";
    while (posicion < (int)linea.size() && linea[posicion] != ';') {
        campo += linea[posicion];
        posicion++;
    }
    posicion++;

    MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
    return campo;
}

void GestorArchivos::generarJugadores(Equipo& equipo) {
    size_t bytesLocales = sizeof(short) * 5
                          + sizeof(string) * 2;
    MedidorRecursos::getInstancia().sumarMemoria(bytesLocales);

    short golesTotal  = equipo.getEstadisticas().getGolesFavor();
    short golesPorJug = golesTotal / 26;
    short golesResto  = golesTotal % 26;

    for (short i = 1; i <= 26; i++) {
        string nombre   = "nombre"   + to_string(i);
        string apellido = "apellido" + to_string(i);
        short goles = golesPorJug + (i <= golesResto ? 1 : 0);
        EstadisticasJugador estadisticas(goles, 0, 0, 0, 0, 0, 0);
        Jugador jugador(nombre, apellido, i, estadisticas);
        equipo.agregarJugador(jugador);
        MedidorRecursos::getInstancia().contarIteracion();
    }

    MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
}

bool GestorArchivos::cargarEquipos(const string& rutaCSV,
                                   Lista<Equipo>& equipos) {
    size_t bytesLocales = sizeof(ifstream)
                          + sizeof(string) * 11
                          + sizeof(int)
                          + sizeof(short) * 6;
    MedidorRecursos::getInstancia().sumarMemoria(bytesLocales);

    ifstream archivo(rutaCSV);
    if (!archivo.is_open()) {
        cerr << "Error: no se pudo abrir " << rutaCSV << endl;
        MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
        return false;
    }

    string linea;
    getline(archivo, linea);
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        if (!linea.empty() && linea.back() == '\r')
            linea.pop_back();

        int pos = 0;
        string campoRanking       = extraerCampo(linea, pos);
        string campoPais          = extraerCampo(linea, pos);
        string campoDT            = extraerCampo(linea, pos);
        string campoFederacion    = extraerCampo(linea, pos);
        string campoConfederacion = extraerCampo(linea, pos);
        string campoGF            = extraerCampo(linea, pos);
        string campoGC            = extraerCampo(linea, pos);
        string campoGanados       = extraerCampo(linea, pos);
        string campoEmpatados     = extraerCampo(linea, pos);
        string campoPerdidos      = extraerCampo(linea, pos);

        short ranking    = (short)stoi(campoRanking);
        short golesFavor = (short)stoi(campoGF);
        short golesContra= (short)stoi(campoGC);
        short ganados    = (short)stoi(campoGanados);
        short empatados  = (short)stoi(campoEmpatados);
        short perdidos   = (short)stoi(campoPerdidos);

        EstadisticasEquipo estadisticas(
            golesFavor, golesContra, ganados,
            empatados, perdidos, 0, 0, 0
            );

        equipos.agregar(Equipo(ranking, campoPais, campoDT,
                               campoFederacion, campoConfederacion,
                               estadisticas));

        generarJugadores(equipos[equipos.getTamanio() - 1]);
        MedidorRecursos::getInstancia().contarIteracion();
    }

    archivo.close();
    MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
    return true;
}

bool GestorArchivos::guardarJugadores(const string& rutaArchivo,
                                      const Lista<Equipo>& equipos) {
    size_t bytesLocales = sizeof(ofstream)
                          + sizeof(int) * 2;
    MedidorRecursos::getInstancia().sumarMemoria(bytesLocales);

    ofstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cerr << "Error: no se pudo crear " << rutaArchivo << endl;
        MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
        return false;
    }

    for (int i = 0; i < equipos.getTamanio(); i++) {
        const Equipo& equipo = equipos[i];
        archivo << "EQUIPO:" << equipo.getPais() << "\n";

        const Lista<Jugador>& plantilla = equipo.getPlantilla();
        for (int j = 0; j < plantilla.getTamanio(); j++) {
            const Jugador& jug = plantilla[j];
            const EstadisticasJugador& e = jug.getEstadisticas();
            archivo << jug.getNumeroCamiseta() << "|"
                    << jug.getNombre()          << "|"
                    << jug.getApellido()        << "|"
                    << e.getGoles()             << "|"
                    << e.getPartidosJugados()   << "|"
                    << e.getMinutosJugados()    << "|"
                    << e.getAsistencias()       << "|"
                    << e.getTarjetasAmarillas() << "|"
                    << e.getTarjetasRojas()     << "|"
                    << e.getFaltas()            << "\n";
            MedidorRecursos::getInstancia().contarIteracion();
        }
        MedidorRecursos::getInstancia().contarIteracion();
    }

    archivo.close();
    MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
    return true;
}

bool GestorArchivos::cargarJugadores(const string& rutaArchivo,
                                     Lista<Equipo>& equipos) {
    size_t bytesLocales = sizeof(ifstream)
                          + sizeof(string) * 11
                          + sizeof(int) * 2;
    MedidorRecursos::getInstancia().sumarMemoria(bytesLocales);

    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cerr << "Error: no se pudo abrir " << rutaArchivo << endl;
        MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
        return false;
    }

    string linea;
    int indiceEquipo = -1;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        if (!linea.empty() && linea.back() == '\r')
            linea.pop_back();

        if (linea.substr(0, 7) == "EQUIPO:") {
            string nombreEquipo = linea.substr(7);
            indiceEquipo = -1;
            for (int i = 0; i < equipos.getTamanio(); i++) {
                if (equipos[i].getPais() == nombreEquipo) {
                    indiceEquipo = i;
                    equipos[i].getPlantilla().limpiar();
                    break;
                }
                MedidorRecursos::getInstancia().contarIteracion();
            }
        } else if (indiceEquipo != -1) {
            int pos = 0;
            string campoCamiseta    = extraerCampo(linea, pos);
            string campoNombre      = extraerCampo(linea, pos);
            string campoApellido    = extraerCampo(linea, pos);
            string campoGoles       = extraerCampo(linea, pos);
            string campoPartidos    = extraerCampo(linea, pos);
            string campoMinutos     = extraerCampo(linea, pos);
            string campoAsistencias = extraerCampo(linea, pos);
            string campoAmarillas   = extraerCampo(linea, pos);
            string campoRojas       = extraerCampo(linea, pos);
            string campoFaltas      = extraerCampo(linea, pos);

            EstadisticasJugador estadisticas(
                (short)stoi(campoGoles),
                (short)stoi(campoPartidos),
                stoi(campoMinutos),
                (short)stoi(campoAsistencias),
                (short)stoi(campoAmarillas),
                (short)stoi(campoRojas),
                (short)stoi(campoFaltas)
                );

            Jugador jugador(campoNombre, campoApellido,
                            (short)stoi(campoCamiseta),
                            estadisticas);

            equipos[indiceEquipo].agregarJugador(jugador);
            MedidorRecursos::getInstancia().contarIteracion();
        }
    }

    archivo.close();
    MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
    return true;
}
