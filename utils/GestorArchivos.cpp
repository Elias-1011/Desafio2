#include "GestorArchivos.h"
#include "MedidorRecursos.h"

using namespace std;

static int stringToInt(const string& str) {
    int resultado = 0;
    int i = 0;

    if (str.empty()) return 0;

    while (i < (int)str.length() && str[i] == ' ') {
        i++;
    }

    for (; i < (int)str.length(); i++) {
        char c = str[i];
        if (c >= '0' && c <= '9') {
            resultado = resultado * 10 + (c - '0');
        } else {
            break;
        }
    }

    return resultado;
}

static string extraerCampoConSep(const string& linea, int& posicion, char sep) {
    size_t bytesLocales = sizeof(string);
    sumarMemoria(bytesLocales);

    string campo = "";
    while (posicion < (int)linea.size() && linea[posicion] != sep) {
        campo += linea[posicion];
        posicion++;
    }
    if (posicion < (int)linea.size() && linea[posicion] == sep) {
        posicion++;
    }

    restarMemoria(bytesLocales);
    return campo;
}

static string extraerCampo(const string& linea, int& posicion) {
    return extraerCampoConSep(linea, posicion, ';');
}

static string extraerCampoJugador(const string& linea, int& posicion) {
    return extraerCampoConSep(linea, posicion, '|');
}

static void generarJugadores(Equipo& equipo) {
    size_t bytesLocales = sizeof(short) * 5 + sizeof(string) * 2;
    sumarMemoria(bytesLocales);

    short golesTotal  = equipo.getEstadisticas().getGolesFavor();
    short golesPorJug = golesTotal / 26;
    short golesResto  = golesTotal % 26;

    for (short i = 1; i <= 26; i++) {
        string nombre   = "nombre";
        string apellido = "apellido";

        if (i >= 10) {
            nombre   += char('0' + (i / 10));
            apellido += char('0' + (i / 10));
            nombre   += char('0' + (i % 10));
            apellido += char('0' + (i % 10));
        } else {
            nombre   += char('0' + i);
            apellido += char('0' + i);
        }

        short goles = golesPorJug;
        if (i <= golesResto) {
            goles++;
        }

        EstadisticasJugador estadisticas(goles, 0, 0, 0, 0, 0, 0);
        Jugador jugador(nombre, apellido, i, estadisticas);
        equipo.agregarJugador(jugador);
        contarIteracion();
    }

    restarMemoria(bytesLocales);
}

bool cargarEquipos(const string& rutaCSV, Lista<Equipo>& equipos) {
    size_t bytesLocales = sizeof(ifstream) + sizeof(string) * 11 + sizeof(int) + sizeof(short) * 6;
    sumarMemoria(bytesLocales);

    ifstream archivo(rutaCSV.c_str());
    if (!archivo.is_open()) {
        cerr << "Error: no se pudo abrir " << rutaCSV << endl;
        restarMemoria(bytesLocales);
        return false;
    }

    string linea;

    getline(archivo, linea);

    getline(archivo, linea);

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        if (!linea.empty() && linea[linea.length() - 1] == '\r') {
            linea = linea.substr(0, linea.length() - 1);
        }

        if (linea.empty()) continue;

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

        short ranking     = (short)stringToInt(campoRanking);
        short golesFavor  = (short)stringToInt(campoGF);
        short golesContra = (short)stringToInt(campoGC);
        short ganados     = (short)stringToInt(campoGanados);
        short empatados   = (short)stringToInt(campoEmpatados);
        short perdidos    = (short)stringToInt(campoPerdidos);

        EstadisticasEquipo estadisticas(
            golesFavor, golesContra, ganados,
            empatados, perdidos, 0, 0, 0
            );

        equipos.agregar(Equipo(ranking, campoPais, campoDT,
                               campoFederacion, campoConfederacion,
                               estadisticas));
        contarIteracion();
    }

    archivo.close();

    for (int i = 0; i < equipos.getTamanio(); i++) {
        generarJugadores(equipos[i]);
        contarIteracion();
    }

    restarMemoria(bytesLocales);
    return true;
}

bool guardarJugadores(const string& rutaArchivo, const Lista<Equipo>& equipos) {
    size_t bytesLocales = sizeof(ofstream) + sizeof(int) * 2;
    sumarMemoria(bytesLocales);

    ofstream archivo(rutaArchivo.c_str());
    if (!archivo.is_open()) {
        cerr << "Error: no se pudo crear " << rutaArchivo << endl;
        restarMemoria(bytesLocales);
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
            contarIteracion();
        }
        contarIteracion();
    }

    archivo.close();
    restarMemoria(bytesLocales);
    return true;
}

bool cargarJugadores(const string& rutaArchivo, Lista<Equipo>& equipos) {
    size_t bytesLocales = sizeof(ifstream) + sizeof(string) * 11 + sizeof(int) * 2;
    sumarMemoria(bytesLocales);

    ifstream archivo(rutaArchivo.c_str());
    if (!archivo.is_open()) {
        restarMemoria(bytesLocales);
        return false;
    }

    string linea;
    int indiceEquipo = -1;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        if (!linea.empty() && linea[linea.length() - 1] == '\r') {
            linea = linea.substr(0, linea.length() - 1);
        }

        if (linea.substr(0, 7) == "EQUIPO:") {
            string nombreEquipo = linea.substr(7);
            indiceEquipo = -1;
            for (int i = 0; i < equipos.getTamanio(); i++) {
                if (equipos[i].getPais() == nombreEquipo) {
                    indiceEquipo = i;
                    equipos[i].getPlantilla().limpiar();
                    break;
                }
                contarIteracion();
            }
        } else if (indiceEquipo != -1) {
            int pos = 0;
            string campoCamiseta    = extraerCampoJugador(linea, pos);
            string campoNombre      = extraerCampoJugador(linea, pos);
            string campoApellido    = extraerCampoJugador(linea, pos);
            string campoGoles       = extraerCampoJugador(linea, pos);
            string campoPartidos    = extraerCampoJugador(linea, pos);
            string campoMinutos     = extraerCampoJugador(linea, pos);
            string campoAsistencias = extraerCampoJugador(linea, pos);
            string campoAmarillas   = extraerCampoJugador(linea, pos);
            string campoRojas       = extraerCampoJugador(linea, pos);
            string campoFaltas      = extraerCampoJugador(linea, pos);

            EstadisticasJugador estadisticas(
                (short)stringToInt(campoGoles),
                (short)stringToInt(campoPartidos),
                stringToInt(campoMinutos),
                (short)stringToInt(campoAsistencias),
                (short)stringToInt(campoAmarillas),
                (short)stringToInt(campoRojas),
                (short)stringToInt(campoFaltas)
                );

            Jugador jugador(campoNombre, campoApellido,
                            (short)stringToInt(campoCamiseta),
                            estadisticas);

            equipos[indiceEquipo].agregarJugador(jugador);
            contarIteracion();
        }
    }

    archivo.close();
    restarMemoria(bytesLocales);
    return true;
}
