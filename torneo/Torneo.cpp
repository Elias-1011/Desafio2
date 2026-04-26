#include "Torneo.h"
#include <fstream>

using namespace std;

Torneo::Torneo()
    : equipos(48), grupos(12), etapas(6),
    datosCargados(false), gruposConformados(false),
    faseGruposSimulada(false), transicionR16Hecha(false),
    eliminatoriasSimuladas(false) {
    srand((unsigned int)time(nullptr));
}

Partido Torneo::crearPartido(Equipo* eq1, Equipo* eq2) const {
    return Partido("10/07/2026", "00:00", "nombreSede", eq1, eq2,
                   "codArbitro1", "codArbitro2", "codArbitro3");
}

void Torneo::construirEtapaDesdePares(const Etapa& anterior,
                                      const string& nombre,
                                      int capacidad) {
    Etapa nueva(nombre, capacidad);
    for (int i = 0; i < anterior.getCantPartidos(); i += 2) {
        Equipo* a = anterior.getPartido(i).getGanador();
        Equipo* b = anterior.getPartido(i + 1).getGanador();
        nueva.agregarPartido(crearPartido(a, b));
        contarIteracion();
    }
    nueva.simular();
    nueva.imprimir();
    etapas.agregar(nueva);
}

void Torneo::ordenarPorRanking(Equipo** arreglo, char n) {
    size_t bytesLocales = sizeof(Equipo**) + sizeof(char)
    + sizeof(Equipo*)  + sizeof(char) * 2;
    sumarMemoria(bytesLocales);

    for (int i = 1; i < (int)n; i++) {
        Equipo* clave = arreglo[i];
        int j = i - 1;
        while (j >= 0 &&
               arreglo[j]->getRankingFIFA() > clave->getRankingFIFA()) {
            arreglo[j + 1] = arreglo[j];
            j--;
            contarIteracion();
        }
        arreglo[j + 1] = clave;
        contarIteracion();
    }

    restarMemoria(bytesLocales);
}

void Torneo::mezclar(Equipo** arreglo, char n) {
    size_t bytesLocales = sizeof(Equipo**) + sizeof(char) * 3
                          + sizeof(Equipo*);
    sumarMemoria(bytesLocales);

    for (int i = (int)n - 1; i > 0; i--) {
        int j        = rand() % (i + 1);
        Equipo* temp = arreglo[i];
        arreglo[i]   = arreglo[j];
        arreglo[j]   = temp;
        contarIteracion();
    }

    restarMemoria(bytesLocales);
}

void Torneo::armarBombos(Equipo** bombo1, Equipo** bombo2,
                         Equipo** bombo3, Equipo** bombo4) {
    size_t bytesLocales = sizeof(Equipo**) * 4
                          + sizeof(Equipo*)  * 48
                          + sizeof(char) * 2
                          + sizeof(Equipo*);
    sumarMemoria(bytesLocales);

    Equipo* ordenados[48];
    for (int i = 0; i < 48; i++) {
        ordenados[i] = &equipos[i];
        contarIteracion();
    }
    ordenarPorRanking(ordenados, 48);

    int posUSA = 0;
    for (int i = 0; i < 48; i++) {
        if (ordenados[i]->getPais() == "United States") {
            posUSA = i;
            break;
        }
        contarIteracion();
    }

    Equipo* usa = ordenados[posUSA];
    for (int i = posUSA; i < 47; i++) {
        ordenados[i] = ordenados[i + 1];
        contarIteracion();
    }

    bombo1[0] = usa;
    for (int i = 0; i < 11; i++) {
        bombo1[i + 1] = ordenados[i];
        contarIteracion();
    }
    for (int i = 0; i < 12; i++) {
        bombo2[i] = ordenados[11 + i];
        bombo3[i] = ordenados[23 + i];
        bombo4[i] = ordenados[35 + i];
        contarIteracion();
    }

    restarMemoria(bytesLocales);
}

bool Torneo::asignarBombo(Equipo** bombo, char indice,
                          char n, char nivelBombo) {
    size_t bytesLocales = sizeof(Equipo**) + sizeof(char) * 3
                          + sizeof(Equipo*)  + sizeof(char);
    sumarMemoria(bytesLocales);

    if (indice == n) {
        restarMemoria(bytesLocales);
        return true;
    }

    Equipo* equipo = bombo[(int)indice];
    for (int g = 0; g < grupos.getTamanio(); g++) {
        contarIteracion();
        if (grupos[g].getCantidadEquipos() != nivelBombo) continue;
        if (grupos[g].puedeAgregar(equipo)) {
            grupos[g].agregarEquipo(equipo);
            if (asignarBombo(bombo, indice + 1, n, nivelBombo)) {
                restarMemoria(bytesLocales);
                return true;
            }
            grupos[g].quitarUltimoEquipo();
        }
    }

    restarMemoria(bytesLocales);
    return false;
}

int Torneo::buscarIndiceEquipo(const Equipo* equipo) const {
    for (int i = 0; i < equipos.getTamanio(); i++) {
        contarIteracion();
        if (&equipos[i] == equipo) return i;
    }
    return -1;
}

string Torneo::generarFecha(int dia) const {
    int diaMes = 20 + dia;
    int mes    = 6;
    if (diaMes > 30) { diaMes -= 30; mes = 7; }
    return (diaMes < 10 ? "0" : "") + to_string(diaMes) + "/"
           + (mes    < 10 ? "0" : "") + to_string(mes)    + "/2026";
}

void Torneo::ordenarEntradas(EntradaTabla** arreglo, int n) {
    size_t bytesLocales = sizeof(EntradaTabla**) + sizeof(int) * 2
                          + sizeof(EntradaTabla*);
    sumarMemoria(bytesLocales);

    for (int i = 1; i < n; i++) {
        EntradaTabla* clave = arreglo[i];
        int j = i - 1;
        while (j >= 0 && *clave > *arreglo[j]) {
            arreglo[j + 1] = arreglo[j];
            j--;
            contarIteracion();
        }
        arreglo[j + 1] = clave;
        contarIteracion();
    }

    restarMemoria(bytesLocales);
}

bool Torneo::mismoGrupo(const Equipo* eq1, const Equipo* eq2) const {
    for (int g = 0; g < grupos.getTamanio(); g++) {
        const Grupo& grupo = grupos[g];
        bool tieneEq1 = false, tieneEq2 = false;
        for (int i = 0; i < (int)grupo.getCantidadEquipos(); i++) {
            if (grupo.getEquipo(i) == eq1) tieneEq1 = true;
            if (grupo.getEquipo(i) == eq2) tieneEq2 = true;
            contarIteracion();
        }
        if (tieneEq1 && tieneEq2) return true;
    }
    return false;
}
void Torneo::cargarDatos(const string& rutaCSV) {
    gruposConformados = faseGruposSimulada =
        transicionR16Hecha = eliminatoriasSimuladas = false;
    equipos.limpiar();
    grupos.limpiar();
    etapas.limpiar();

    resetIteraciones();
    if (cargarEquipos(rutaCSV, equipos)) {
        datosCargados = true;
        cout << "Equipos cargados: " << equipos.getTamanio() << endl;
    }
    ifstream prueba("jugadores_historico.txt");
    if (prueba.is_open()) {
        prueba.close();
        cargarJugadores("jugadores_historico.txt", equipos);
        cout << "Historico de jugadores cargado desde archivo." << endl;
    } else {
        cout << "Historico de jugadores generado artificialmente." << endl;
    }

    imprimirMedidor();
}

void Torneo::conformarGrupos() {
    size_t bytesLocales = sizeof(char) * 12
                          + sizeof(Equipo*) * 48
                          + sizeof(char);
    sumarMemoria(bytesLocales);
    resetIteraciones();

    char letras[12] = {'A','B','C','D','E','F',
                       'G','H','I','J','K','L'};
    for (int i = 0; i < 12; i++) {
        grupos.agregar(Grupo(letras[i]));
        contarIteracion();
    }

    Equipo* bombo1[12], *bombo2[12], *bombo3[12], *bombo4[12];
    armarBombos(bombo1, bombo2, bombo3, bombo4);
    mezclar(bombo1, 12); mezclar(bombo2, 12);
    mezclar(bombo3, 12); mezclar(bombo4, 12);

    if (!asignarBombo(bombo1, 0, 12, 0) ||
        !asignarBombo(bombo2, 0, 12, 1) ||
        !asignarBombo(bombo3, 0, 12, 2) ||
        !asignarBombo(bombo4, 0, 12, 3)) {
        cerr << "Error conformando grupos." << endl;
        restarMemoria(bytesLocales);
        return;
    }

    gruposConformados = true;
    restarMemoria(bytesLocales);
    mostrarGrupos();
    imprimirMedidor();
}

void Torneo::mostrarGrupos() const {
    cout << "\n=== GRUPOS DEL MUNDIAL 2026 ===\n" << endl;
    for (int i = 0; i < grupos.getTamanio(); i++) {
        cout << grupos[i];
        contarIteracion();
    }
}

void Torneo::simularFaseGrupos() {
    resetIteraciones();

    size_t bytesLocales = sizeof(int) * 48
                          + sizeof(int) * 19
                          + sizeof(char) * 12
                          + sizeof(int) * 5;
    sumarMemoria(bytesLocales);

    int ultimoDia[48];
    for (int i = 0; i < 48; i++) ultimoDia[i] = -3;

    int partidosPorDia[19];
    for (int i = 0; i < 19; i++) partidosPorDia[i] = 0;

    char pares[6][2] = {{0,3},{1,2},{0,1},{2,3},{0,2},{1,3}};

    for (int g = 0; g < grupos.getTamanio(); g++) {
        Grupo& grupo = grupos[g];
        for (int p = 0; p < 6; p++) {
            Equipo* eq1 = grupo.getEquipo((int)pares[p][0]);
            Equipo* eq2 = grupo.getEquipo((int)pares[p][1]);
            int idx1    = buscarIndiceEquipo(eq1);
            int idx2    = buscarIndiceEquipo(eq2);

            int dia = -1;
            for (int d = 0; d < 19; d++) {
                if (partidosPorDia[d] < 4 &&
                    d - ultimoDia[idx1] >= 3 &&
                    d - ultimoDia[idx2] >= 3) {
                    dia = d;
                    break;
                }
                contarIteracion();
            }
            if (dia == -1) {
                cerr << "Sin fecha valida para partido." << endl;
                continue;
            }
            Partido partido(generarFecha(dia), "00:00", "nombreSede",
                            eq1, eq2,
                            "codArbitro1", "codArbitro2", "codArbitro3");
            grupo.agregarPartido(partido);
            partidosPorDia[dia]++;
            ultimoDia[idx1] = ultimoDia[idx2] = dia;
            contarIteracion();
        }
    }
    cout << "\n=== RESULTADOS FASE DE GRUPOS ===\n";
    for (int g = 0; g < grupos.getTamanio(); g++) {
        grupos[g].simularPartidos();
        grupos[g].construirTabla();
        grupos[g].imprimirPartidos();
        cout << "Tabla Grupo " << grupos[g].getLetra() << ":\n";
        cout << grupos[g].getTabla() << "\n";
        contarIteracion();
    }
    faseGruposSimulada = true;
    restarMemoria(bytesLocales);
    imprimirMedidor();
}

void Torneo::transicionR16() {
    resetIteraciones();

    size_t bytesLocales = sizeof(Equipo*)      * 12 * 2
                          + sizeof(EntradaTabla*) * 12 * 2
                          + sizeof(bool)         * 12 * 3
                          + sizeof(int)          * 4;
    sumarMemoria(bytesLocales);

    Equipo* primeros[12], *segundos[12];
    EntradaTabla* entTerceros[12], *entSegundos[12];
    bool primeroCruzado[12] = {}, segundoCruzado[12] = {},
        terceroCruzado[8]  = {}, esPeorSegundo[12]  = {};

    for (int g = 0; g < 12; g++) {
        TablaClasificacion& tabla = grupos[g].getTabla();
        primeros[g]    = tabla.getEntrada(0).getEquipo();
        segundos[g]    = tabla.getEntrada(1).getEquipo();
        entTerceros[g] = &tabla.getEntrada(2);
        entSegundos[g] = &tabla.getEntrada(1);
        contarIteracion();
    }
    ordenarEntradas(entTerceros, 12);
    ordenarEntradas(entSegundos, 12);

    Equipo* mejoresTerceros[8];
    for (int i = 0; i < 8; i++) {
        mejoresTerceros[i] = entTerceros[i]->getEquipo();
        contarIteracion();
    }
    for (int i = 8; i < 12; i++) {
        for (int g = 0; g < 12; g++) {
            if (segundos[g] == entSegundos[i]->getEquipo()) {
                esPeorSegundo[g] = true;
                break;
            }
            contarIteracion();
        }
    }
    cout << "\n=== TABLAS DE CLASIFICACION ===\n";
    for (int g = 0; g < 12; g++) {
        cout << "Grupo " << grupos[g].getLetra() << ":\n"
             << grupos[g].getTabla() << "\n";
        contarIteracion();
    }
    cout << "\nMejores 8 terceros:\n";
    for (int i = 0; i < 8; i++) {
        cout << "  " << mejoresTerceros[i]->getPais() << "\n";
        contarIteracion();
    }
    Etapa r16("R16 - Dieciseisavos de Final", 16);
    for (int i = 0; i < 12; i++) {
        if (primeroCruzado[i]) continue;
        for (int j = 0; j < 8; j++) {
            if (terceroCruzado[j]) continue;
            if (!mismoGrupo(primeros[i], mejoresTerceros[j])) {
                r16.agregarPartido(crearPartido(primeros[i], mejoresTerceros[j]));
                primeroCruzado[i] = terceroCruzado[j] = true;
                break;
            }
            contarIteracion();
        }
        contarIteracion();
    }
    for (int i = 0; i < 12; i++) {
        if (primeroCruzado[i]) continue;
        for (int j = 0; j < 12; j++) {
            if (segundoCruzado[j] || !esPeorSegundo[j]) continue;
            if (!mismoGrupo(primeros[i], segundos[j])) {
                r16.agregarPartido(crearPartido(primeros[i], segundos[j]));
                primeroCruzado[i] = segundoCruzado[j] = true;
                break;
            }
            contarIteracion();
        }
        contarIteracion();
    }
    for (int i = 0; i < 12; i++) {
        if (segundoCruzado[i]) continue;
        for (int j = i + 1; j < 12; j++) {
            if (segundoCruzado[j]) continue;
            if (!mismoGrupo(segundos[i], segundos[j])) {
                r16.agregarPartido(crearPartido(segundos[i], segundos[j]));
                segundoCruzado[i] = segundoCruzado[j] = true;
                break;
            }
            contarIteracion();
        }
        contarIteracion();
    }
    etapas.agregar(r16);
    cout << "\n=== CRUCES R16 ===\n";
    for (int i = 0; i < r16.getCantPartidos(); i++) {
        cout << r16.getPartido(i).getEquipo1()->getPais()
        << " vs "
        << r16.getPartido(i).getEquipo2()->getPais() << "\n";
        contarIteracion();
    }

    transicionR16Hecha = true;
    restarMemoria(bytesLocales);
    imprimirMedidor();
}

void Torneo::simularEliminatorias() {
    resetIteraciones();

    size_t bytesLocales = sizeof(int) * 3;
    sumarMemoria(bytesLocales);

    etapas[0].simular();
    etapas[0].imprimir();

    {
        Etapa anterior = etapas[0];
        construirEtapaDesdePares(anterior, "R8 - Octavos de Final", 8);
    }
    {
        Etapa anterior = etapas[1];
        construirEtapaDesdePares(anterior, "QF - Cuartos de Final", 4);
    }
    {
        Etapa anterior = etapas[2];
        construirEtapaDesdePares(anterior, "SF - Semifinales", 2);
    }

    {
        const Partido& sf1 = etapas[3].getPartido(0);
        const Partido& sf2 = etapas[3].getPartido(1);
        Equipo* p1 = (sf1.getGanador() == sf1.getEquipo1())
                         ? sf1.getEquipo2() : sf1.getEquipo1();
        Equipo* p2 = (sf2.getGanador() == sf2.getEquipo1())
                         ? sf2.getEquipo2() : sf2.getEquipo1();
        Etapa tercerPuesto("Tercer Puesto", 1);
        tercerPuesto.agregarPartido(crearPartido(p1, p2));
        tercerPuesto.simular();
        tercerPuesto.imprimir();
        etapas.agregar(tercerPuesto);
    }
    {
        Equipo* finalistA = etapas[3].getPartido(0).getGanador();
        Equipo* finalistB = etapas[3].getPartido(1).getGanador();
        Etapa finalEtapa("Final", 1);
        finalEtapa.agregarPartido(crearPartido(finalistA, finalistB));
        finalEtapa.simular();
        finalEtapa.imprimir();
        etapas.agregar(finalEtapa);
    }
    guardarJugadores("jugadores_historico.txt", equipos);
    cout << "Historico de jugadores guardado en jugadores_historico.txt" << endl;

    eliminatoriasSimuladas = true;
    restarMemoria(bytesLocales);
    imprimirMedidor();
}

void Torneo::generarEstadisticas() const {
    resetIteraciones();

    size_t bytesLocales = sizeof(int)     * 4
                          + sizeof(Equipo*) * 2
                          + sizeof(short)   * 2;
    sumarMemoria(bytesLocales);

    const Etapa& finalEtapa   = etapas[5];
    const Etapa& tercerPuesto = etapas[4];

    Equipo* campeon    = finalEtapa.getPartido(0).getGanador();
    Equipo* subcampeon = (finalEtapa.getPartido(0).getEquipo1() == campeon)
                             ? finalEtapa.getPartido(0).getEquipo2()
                             : finalEtapa.getPartido(0).getEquipo1();
    Equipo* tercero    = tercerPuesto.getPartido(0).getGanador();
    Equipo* cuarto     = (tercerPuesto.getPartido(0).getEquipo1() == tercero)
                         ? tercerPuesto.getPartido(0).getEquipo2()
                         : tercerPuesto.getPartido(0).getEquipo1();

    cout << "\n=== ESTADISTICAS FINALES ===\n"
         << "\nTop 4:\n"
         << "  1. " << campeon->getPais()    << "\n"
         << "  2. " << subcampeon->getPais() << "\n"
         << "  3. " << tercero->getPais()    << "\n"
         << "  4. " << cuarto->getPais()     << "\n";

    const Lista<Jugador>& plantilla = campeon->getPlantilla();
    Jugador* maxGoleador = nullptr;
    short    maxGoles    = -1;
    for (int i = 0; i < plantilla.getTamanio(); i++) {
        short g = plantilla[i].getEstadisticas().getGoles();
        if (g > maxGoles) {
            maxGoles    = g;
            maxGoleador = const_cast<Jugador*>(&plantilla[i]);
        }
        contarIteracion();
    }
    cout << "\nMaximo goleador del campeon (" << campeon->getPais() << "):\n";
    if (maxGoleador) cout << "  " << *maxGoleador << "\n";

    Jugador* topGoleadores[3] = {nullptr, nullptr, nullptr};
    short    topGoles[3]      = {-1, -1, -1};
    for (int e = 0; e < equipos.getTamanio(); e++) {
        const Lista<Jugador>& plant = equipos[e].getPlantilla();
        for (int j = 0; j < plant.getTamanio(); j++) {
            short g = plant[j].getEstadisticas().getGoles();
            for (int k = 0; k < 3; k++) {
                if (g > topGoles[k]) {
                    for (int m = 2; m > k; m--) {
                        topGoleadores[m] = topGoleadores[m - 1];
                        topGoles[m]      = topGoles[m - 1];
                    }
                    topGoleadores[k] = const_cast<Jugador*>(&plant[j]);
                    topGoles[k]      = g;
                    break;
                }
            }
            contarIteracion();
        }
        contarIteracion();
    }
    cout << "\nTop 3 goleadores:\n";
    for (int k = 0; k < 3; k++)
        if (topGoleadores[k])
            cout << "  " << (k + 1) << ". " << *topGoleadores[k] << "\n";

    Equipo* maxGolesEq   = nullptr;
    short   maxGolesHist = -1;
    for (int e = 0; e < equipos.getTamanio(); e++) {
        short g = equipos[e].getEstadisticas().getGolesFavor();
        if (g > maxGolesHist) {
            maxGolesHist = g;
            maxGolesEq   = const_cast<Equipo*>(&equipos[e]);
        }
        contarIteracion();
    }
    cout << "\nEquipo con mas goles historicos:\n"
         << "  " << maxGolesEq->getPais()
         << " (" << maxGolesHist << " goles)\n";

    const char* confs[]     = {"UEFA","CONMEBOL","Concacaf","CAF","AFC","OFC"};
    const char* nombresEt[] = {"R16", "R8", "QF"};
    int         indicesEt[] = {0, 1, 2};

    for (int e = 0; e < 3; e++) {
        int cuenta[6] = {};
        const Etapa& etapa = etapas[indicesEt[e]];
        for (int p = 0; p < etapa.getCantPartidos(); p++) {
            const string& c1 = etapa.getPartido(p).getEquipo1()->getConfederacion();
            const string& c2 = etapa.getPartido(p).getEquipo2()->getConfederacion();
            for (int c = 0; c < 6; c++) {
                if (c1 == confs[c]) cuenta[c]++;
                if (c2 == confs[c]) cuenta[c]++;
                contarIteracion();
            }
        }
        int maxIdx = 0;
        for (int c = 1; c < 6; c++)
            if (cuenta[c] > cuenta[maxIdx]) maxIdx = c;
        cout << "\nConfederacion dominante en " << nombresEt[e]
             << ": " << confs[maxIdx]
             << " (" << cuenta[maxIdx] << " equipos)\n";
        contarIteracion();
    }

    restarMemoria(bytesLocales);
    imprimirMedidor();
}

void Torneo::mostrarMenu() {
    int opcion = 0;
    do {
        cout << "\n=== UdeAWorldCup ===\n"
             << "Estado:\n"
             << "  Datos cargados:       " << (datosCargados         ? "SI":"NO") << "\n"
             << "  Grupos conformados:   " << (gruposConformados      ? "SI":"NO") << "\n"
             << "  Fase grupos simulada: " << (faseGruposSimulada     ? "SI":"NO") << "\n"
             << "  Transicion R16:       " << (transicionR16Hecha     ? "SI":"NO") << "\n"
             << "  Eliminatorias:        " << (eliminatoriasSimuladas ? "SI":"NO") << "\n\n"
             << "1. Cargar datos\n"
             << "2. Conformar grupos\n"
             << "3. Simular fase de grupos\n"
             << "4. Transicion a R16\n"
             << "5. Simular etapas eliminatorias\n"
             << "6. Estadisticas del torneo\n"
             << "0. Salir\n"
             << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: cargarDatos("selecciones_clasificadas_mundial.csv"); break;
        case 2:
            if (!datosCargados)
                cerr << "Primero cargue los datos (1).\n";
            else conformarGrupos();
            break;
        case 3:
            if (!gruposConformados)
                cerr << "Primero conforme los grupos (2).\n";
            else simularFaseGrupos();
            break;
        case 4:
            if (!faseGruposSimulada)
                cerr << "Primero simule la fase de grupos (3).\n";
            else transicionR16();
            break;
        case 5:
            if (!transicionR16Hecha)
                cerr << "Primero haga la transicion R16 (4).\n";
            else simularEliminatorias();
            break;
        case 6:
            if (!eliminatoriasSimuladas)
                cerr << "Primero simule las eliminatorias (5).\n";
            else generarEstadisticas();
            break;
        case 0: cout << "Saliendo...\n"; break;
        default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}
