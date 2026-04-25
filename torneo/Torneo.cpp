#include "Torneo.h"

using namespace std;

Torneo::Torneo()
    : equipos(48), grupos(12),
    datosCargados(false), gruposConformados(false),
    faseGruposSimulada(false), transicionR16Hecha(false),
    eliminatoriasSimuladas(false) {
    srand((unsigned int)time(nullptr));
}

void Torneo::ordenarPorRanking(Equipo** arreglo, char n) {
    size_t bytesLocales = sizeof(Equipo**)
    + sizeof(char)
        + sizeof(Equipo*)
        + sizeof(char) * 2;
    MedidorRecursos::getInstancia().sumarMemoria(bytesLocales);

    for (char i = 1; i < n; i++) {
        Equipo* clave = arreglo[(int)i];
        char j = i - 1;
        while (j >= 0 &&
               arreglo[(int)j]->getRankingFIFA() > clave->getRankingFIFA()) {
            arreglo[(int)j + 1] = arreglo[(int)j];
            j--;
            MedidorRecursos::getInstancia().contarIteracion();
        }
        arreglo[(int)j + 1] = clave;
        MedidorRecursos::getInstancia().contarIteracion();
    }

    MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
}

void Torneo::mezclar(Equipo** arreglo, char n) {
    size_t bytesLocales = sizeof(Equipo**)
    + sizeof(char)
        + sizeof(char) * 2
        + sizeof(Equipo*);
    MedidorRecursos::getInstancia().sumarMemoria(bytesLocales);

    for (char i = n - 1; i > 0; i--) {
        char j = (char)(rand() % (int)(i + 1));
        Equipo* temp    = arreglo[(int)i];
        arreglo[(int)i] = arreglo[(int)j];
        arreglo[(int)j] = temp;
        MedidorRecursos::getInstancia().contarIteracion();
    }

    MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
}

void Torneo::armarBombos(Equipo** bombo1, Equipo** bombo2,
                         Equipo** bombo3, Equipo** bombo4) {
    size_t bytesLocales = sizeof(Equipo**) * 4
                          + sizeof(Equipo*) * 48
                          + sizeof(char)
                          + sizeof(Equipo*)
                          + sizeof(char);
    MedidorRecursos::getInstancia().sumarMemoria(bytesLocales);

    Equipo* ordenados[48];
    for (char i = 0; i < 48; i++) {
        ordenados[(int)i] = &equipos[(int)i];
        MedidorRecursos::getInstancia().contarIteracion();
    }
    ordenarPorRanking(ordenados, 48);

    char posUSA = 0;
    for (char i = 0; i < 48; i++) {
        if (ordenados[(int)i]->getPais() == "United States") {
            posUSA = i;
            break;
        }
        MedidorRecursos::getInstancia().contarIteracion();
    }

    Equipo* usa = ordenados[(int)posUSA];
    for (char i = posUSA; i < 47; i++) {
        ordenados[(int)i] = ordenados[(int)i + 1];
        MedidorRecursos::getInstancia().contarIteracion();
    }

    bombo1[0] = usa;
    for (char i = 0; i < 11; i++) {
        bombo1[(int)i + 1] = ordenados[(int)i];
        MedidorRecursos::getInstancia().contarIteracion();
    }
    for (char i = 0; i < 12; i++) {
        bombo2[(int)i] = ordenados[11 + (int)i];
        MedidorRecursos::getInstancia().contarIteracion();
    }
    for (char i = 0; i < 12; i++) {
        bombo3[(int)i] = ordenados[23 + (int)i];
        MedidorRecursos::getInstancia().contarIteracion();
    }
    for (char i = 0; i < 12; i++) {
        bombo4[(int)i] = ordenados[35 + (int)i];
        MedidorRecursos::getInstancia().contarIteracion();
    }

    MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
}

bool Torneo::asignarBombo(Equipo** bombo, char indice,
                          char n, char nivelBombo) {
    size_t bytesLocales = sizeof(Equipo**)
    + sizeof(char) * 3
        + sizeof(Equipo*)
        + sizeof(char);
    MedidorRecursos::getInstancia().sumarMemoria(bytesLocales);

    if (indice == n) {
        MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
        return true;
    }

    Equipo* equipo = bombo[(int)indice];

    for (char g = 0; g < grupos.getTamanio(); g++) {
        MedidorRecursos::getInstancia().contarIteracion();

        if (grupos[(int)g].getCantidadEquipos() != nivelBombo) continue;

        if (grupos[(int)g].puedeAgregar(equipo)) {
            grupos[(int)g].agregarEquipo(equipo);

            if (asignarBombo(bombo, indice + 1, n, nivelBombo)) {
                MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
                return true;
            }

            grupos[(int)g].quitarUltimoEquipo();
        }
    }

    MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
    return false;
}

void Torneo::cargarDatos(const string& rutaCSV) {
    // Limpiar estado si se recarga
    gruposConformados      = false;
    faseGruposSimulada     = false;
    transicionR16Hecha     = false;
    eliminatoriasSimuladas = false;
    equipos.limpiar();
    grupos.limpiar();

    MedidorRecursos::getInstancia().resetIteraciones();
    if (gestor.cargarEquipos(rutaCSV, equipos)) {
        datosCargados = true;
        cout << "Datos cargados correctamente. "
             << equipos.getTamanio() << " equipos." << endl;
    }
    MedidorRecursos::getInstancia().imprimir();
}
int Torneo::buscarIndiceEquipo(const Equipo* equipo) const {
    for (int i = 0; i < equipos.getTamanio(); i++) {
        MedidorRecursos::getInstancia().contarIteracion();
        if (&equipos[i] == equipo) return i;
    }
    return -1;
}

string Torneo::generarFecha(int dia) const {
    // Base: 20 junio 2026, rango: 19 dias
    int diaMes = 20 + dia;
    int mes    = 6;
    if (diaMes > 30) { diaMes -= 30; mes = 7; }
    string fecha = "";
    if (diaMes < 10) fecha += "0";
    fecha += to_string(diaMes) + "/";
    if (mes < 10) fecha += "0";
    fecha += to_string(mes) + "/2026";
    return fecha;
}

void Torneo::simularFaseGrupos() {
    MedidorRecursos::getInstancia().resetIteraciones();

    size_t bytesLocales = sizeof(int) * 48   // ultimoDia[48]
                          + sizeof(int) * 19   // partidosPorDia[19]
                          + sizeof(char) * 12  // pares[6][2]
                          + sizeof(int) * 5;   // dia, idx1, idx2, g, p
    MedidorRecursos::getInstancia().sumarMemoria(bytesLocales);

    int ultimoDia[48];
    for (int i = 0; i < 48; i++) ultimoDia[i] = -3;

    int partidosPorDia[19];
    for (int i = 0; i < 19; i++) partidosPorDia[i] = 0;

    // Pares balanceados round-robin: 3 rondas de 2 partidos cada una
    char pares[6][2] = {{0,3},{1,2},{0,1},{2,3},{0,2},{1,3}};

    // Configurar partidos con fechas validas
    for (char g = 0; g < grupos.getTamanio(); g++) {
        Grupo& grupo = grupos[(int)g];
        for (char p = 0; p < 6; p++) {
            Equipo* eq1 = grupo.getEquipo((int)pares[(int)p][0]);
            Equipo* eq2 = grupo.getEquipo((int)pares[(int)p][1]);
            int idx1    = buscarIndiceEquipo(eq1);
            int idx2    = buscarIndiceEquipo(eq2);

            // Buscar el dia mas temprano disponible
            int dia = -1;
            for (int d = 0; d < 19; d++) {
                if (partidosPorDia[d] < 4 &&
                    d - ultimoDia[idx1] >= 3 &&
                    d - ultimoDia[idx2] >= 3) {
                    dia = d;
                    break;
                }
                MedidorRecursos::getInstancia().contarIteracion();
            }

            if (dia == -1) {
                cerr << "No se encontro fecha valida." << endl;
                continue;
            }

            string fecha = generarFecha(dia);
            Partido partido(fecha, "00:00", "nombreSede", eq1, eq2,
                            "codArbitro1", "codArbitro2", "codArbitro3");
            grupo.agregarPartido(partido);

            partidosPorDia[dia]++;
            ultimoDia[idx1] = dia;
            ultimoDia[idx2] = dia;

            MedidorRecursos::getInstancia().contarIteracion();
        }
    }

    // Simular todos los partidos
    for (char g = 0; g < grupos.getTamanio(); g++) {
        grupos[(int)g].simularPartidos();
        MedidorRecursos::getInstancia().contarIteracion();
    }

    // Construir tablas e imprimir resultados
    cout << "\n=== RESULTADOS FASE DE GRUPOS ===\n";
    for (char g = 0; g < grupos.getTamanio(); g++) {
        grupos[(int)g].construirTabla();
        grupos[(int)g].imprimirPartidos();
        cout << "Tabla Grupo " << grupos[(int)g].getLetra() << ":\n";
        cout << grupos[(int)g].getTabla() << "\n";
        MedidorRecursos::getInstancia().contarIteracion();
    }

    faseGruposSimulada = true;
    MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
    MedidorRecursos::getInstancia().imprimir();
}

void Torneo::conformarGrupos() {
    size_t bytesLocales = sizeof(char) * 12
                          + sizeof(Equipo*) * 12 * 4
                          + sizeof(char);
    MedidorRecursos::getInstancia().sumarMemoria(bytesLocales);
    MedidorRecursos::getInstancia().resetIteraciones();

    char letras[12] = {'A','B','C','D','E','F',
                       'G','H','I','J','K','L'};

    for (char i = 0; i < 12; i++) {
        grupos.agregar(Grupo(letras[(int)i]));
        MedidorRecursos::getInstancia().contarIteracion();
    }

    Equipo* bombo1[12], *bombo2[12], *bombo3[12], *bombo4[12];
    armarBombos(bombo1, bombo2, bombo3, bombo4);

    mezclar(bombo1, 12);
    mezclar(bombo2, 12);
    mezclar(bombo3, 12);
    mezclar(bombo4, 12);

    if (!asignarBombo(bombo1, 0, 12, 0) ||
        !asignarBombo(bombo2, 0, 12, 1) ||
        !asignarBombo(bombo3, 0, 12, 2) ||
        !asignarBombo(bombo4, 0, 12, 3)) {
        cerr << "Error: no se pudo conformar los grupos." << endl;
        MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
        return;
    }
    gruposConformados = true;
    MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
    mostrarGrupos();
    MedidorRecursos::getInstancia().imprimir();
}

void Torneo::mostrarGrupos() const {
    cout << "\n=== GRUPOS DEL MUNDIAL 2026 ===\n" << endl;
    for (char i = 0; i < grupos.getTamanio(); i++) {
        cout << grupos[(int)i];
        MedidorRecursos::getInstancia().contarIteracion();
    }
}

void Torneo::mostrarMenu() {
    int opcion = 0;
    do {
        cout << "\n=== UdeAWorldCup ===" << endl;
        cout << "  Estado actual:" << endl;
        cout << "  Datos cargados:       " << (datosCargados         ? "SI" : "NO") << endl;
        cout << "  Grupos conformados:   " << (gruposConformados      ? "SI" : "NO") << endl;
        cout << "  Fase grupos simulada: " << (faseGruposSimulada     ? "SI" : "NO") << endl;
        cout << "  Transicion R16:       " << (transicionR16Hecha     ? "SI" : "NO") << endl;
        cout << "  Eliminatorias:        " << (eliminatoriasSimuladas ? "SI" : "NO") << endl;
        cout << endl;
        cout << "\n--------------------------------------"<< endl;
        cout << "1. Cargar datos"                 << endl;
        cout << "2. Conformar grupos"             << endl;
        cout << "3. Simular fase de grupos"       << endl;
        cout << "4. Transicion a R16"             << endl;
        cout << "5. Simular etapas eliminatorias" << endl;
        cout << "6. Estadisticas del torneo"      << endl;
        cout << "0. Salir"                        << endl;
        cout << "Opcion: ";
        cin  >> opcion;

        switch (opcion) {
        case 1:
            cargarDatos("selecciones_clasificadas_mundial.csv");
            break;
        case 2:
            if (!datosCargados)
                cerr << "Primero debe cargar los datos (opcion 1)." << endl;
            else
                conformarGrupos();
            break;
        case 3:
            if (!gruposConformados)
                cerr << "Primero debe conformar los grupos (opcion 2)." << endl;
            else
                simularFaseGrupos();
            break;
        case 4:
            if (!faseGruposSimulada)
                cerr << "Primero debe simular la fase de grupos (opcion 3)." << endl;
            else
                cout << "Proximamente: transicion a R16." << endl;
            break;
        case 5:
            if (!transicionR16Hecha)
                cerr << "Primero debe hacer la transicion a R16 (opcion 4)." << endl;
            else
                cout << "Proximamente: simulacion eliminatorias." << endl;
            break;
        case 6:
            if (!eliminatoriasSimuladas)
                cerr << "Primero debe simular las eliminatorias (opcion 5)." << endl;
            else
                cout << "Proximamente: estadisticas del torneo." << endl;
            break;
        case 0:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opcion invalida." << endl;
        }
    } while (opcion != 0);
}
