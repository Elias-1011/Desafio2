#include "Torneo.h"

using namespace std;

Torneo::Torneo() {
    srand((unsigned int)time(nullptr));
    MedidorRecursos::getInstancia().resetIteraciones();
    gestor.cargarEquipos("selecciones_clasificadas_mundial.csv", equipos);
    MedidorRecursos::getInstancia().imprimir();
}

void Torneo::ordenarPorRanking(Equipo** arreglo, char n) {
    // arreglo: puntero por valor — cuenta
    // n: char por valor — cuenta
    // clave: Equipo* — cuenta
    // i, j: char — cuentan
    size_t bytesLocales = sizeof(Equipo**)  // arreglo
                          + sizeof(char)      // n
                          + sizeof(Equipo*)   // clave
                          + sizeof(char) * 2; // i, j
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
    // arreglo: puntero por valor — cuenta
    // n: char por valor — cuenta
    // i, j: char — cuentan
    // temp: Equipo* — cuenta
    size_t bytesLocales = sizeof(Equipo**)
                          + sizeof(char)      // n
                          + sizeof(char) * 2  // i, j
                          + sizeof(Equipo*);  // temp
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
    // 4 punteros por valor — cuentan
    // ordenados[48]: arreglo local de punteros — cuenta
    // posUSA: char — cuenta
    // usa: Equipo* — cuenta
    // i: char — cuenta
    size_t bytesLocales = sizeof(Equipo**) * 4    // bombo1-4
                          + sizeof(Equipo*) * 48    // ordenados[48]
                          + sizeof(char)            // posUSA
                          + sizeof(Equipo*)         // usa
                          + sizeof(char);           // i
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
    // bombo: puntero por valor — cuenta
    // indice, n, nivelBombo: char por valor — cuentan
    // equipo: Equipo* — cuenta
    // g: char — cuenta
    size_t bytesLocales = sizeof(Equipo**)   // bombo
                          + sizeof(char) * 3   // indice, n, nivelBombo
                          + sizeof(Equipo*)    // equipo
                          + sizeof(char);      // g
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

void Torneo::conformarGrupos() {
    // letras[12]: char array — cuenta
    // bombo1-4[12]: arreglos de punteros — cuentan
    // exito: bool — cuenta
    // intentos: int — cuenta
    // maxIntentos: int — cuenta
    // i: char — cuenta
    size_t bytesLocales = sizeof(char) * 12       // letras[12]
                          + sizeof(Equipo*) * 12 * 4 // bombo1-4[12]
                          + sizeof(bool)             // exito
                          + sizeof(int) * 2          // intentos, maxIntentos
                          + sizeof(char);            // i
    MedidorRecursos::getInstancia().sumarMemoria(bytesLocales);
    MedidorRecursos::getInstancia().resetIteraciones();

    char letras[12] = {'A','B','C','D','E','F',
                       'G','H','I','J','K','L'};

    Equipo* bombo1[12], *bombo2[12], *bombo3[12], *bombo4[12];
    armarBombos(bombo1, bombo2, bombo3, bombo4);

    bool exito       = false;
    int  intentos    = 0;
    const int maxIntentos = 100;

    while (!exito && intentos < maxIntentos) {
        intentos++;

        grupos.limpiar();
        for (char i = 0; i < 12; i++) {
            grupos.agregar(Grupo(letras[(int)i]));
            MedidorRecursos::getInstancia().contarIteracion();
        }

        mezclar(bombo1, 12);
        mezclar(bombo2, 12);
        mezclar(bombo3, 12);
        mezclar(bombo4, 12);

        if (asignarBombo(bombo1, 0, 12, 0) &&
            asignarBombo(bombo2, 0, 12, 1) &&
            asignarBombo(bombo3, 0, 12, 2) &&
            asignarBombo(bombo4, 0, 12, 3)) {
            exito = true;
        }

        MedidorRecursos::getInstancia().contarIteracion();
    }

    if (!exito) {
        cerr << "Error: no se pudo conformar grupos tras "
             << maxIntentos << " intentos." << endl;
        MedidorRecursos::getInstancia().restarMemoria(bytesLocales);
        return;
    }

    cout << "Grupos conformados en " << intentos << " intento(s)." << endl;
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
        cout << "1. Conformar grupos"    << endl;
        cout << "0. Salir"              << endl;
        cout << "Opcion: ";
        cin  >> opcion;

        switch (opcion) {
        case 1:
            conformarGrupos();
            break;
        case 0:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opcion invalida." << endl;
        }
    } while (opcion != 0);
}
