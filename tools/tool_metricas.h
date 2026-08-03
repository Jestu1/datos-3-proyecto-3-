#ifndef TOOL_METRICAS_H
#define TOOL_METRICAS_H

#include <iostream>
#include <list>
#include <string>
#include <limits>
#include "../constantes.h"
#include "../classes/tda_emergencia.h"
#include "../classes/tda_ubicacion.h"
#include "../classes/grafo/tda_grafo.h"

extern std::list<Emergencia> listaEmergencias;
extern Grafo<Ubicacion>* ptrMapa;

inline void tool_metricas() {
    std::cout << "\n=======================================================\n";
    std::cout << "             METRICAS Y ESTADISTICAS DEL SISTEMA       \n";
    std::cout << "=======================================================\n";

    // Contadores de emergencias
    int totalEmergencias = listaEmergencias.size();
    int atendidas = 0;
    int pendientes = 0;
    
    // Contadores por tipo de equipo requerido
    int totalBomberos = 0;
    int totalPolicia = 0;
    int totalAmbulancia = 0;

    for (auto it = listaEmergencias.begin(); it != listaEmergencias.end(); ++it) {
        if (it->getAtendida()) {
            atendidas++;
        } else {
            pendientes++;
        }

        int tipo = it->getTipo();
        if (tipo == BOMBEROS) totalBomberos++;
        else if (tipo == POLICIA) totalPolicia++;
        else if (tipo == AMBULANCIA) totalAmbulancia++;
    }

    // Contadores de unidades operativas en el mapa actual
    int mapasBomberos = 0;
    int mapasPolicia = 0;
    int mapasAmbulancia = 0;

    if (ptrMapa != nullptr) {
        for (int i = 0; i < MAX_VERTICES; i++) {
            Vertice<Ubicacion>* v = ptrMapa->getVertice(i);
            if (v != nullptr) {
                if (v->dato.getTieneBomberos()) mapasBomberos++;
                if (v->dato.getTienePolicia()) mapasPolicia++;
                if (v->dato.getTieneAmbulancia()) mapasAmbulancia++;
            }
        }
    }

    // Mostrar reporte estadístico
    std::cout << " [1] ESTADO DE EMERGENCIAS:\n";
    std::cout << "     - Total registradas : " << totalEmergencias << "\n";
    std::cout << "     - Atendidas         : " << atendidas << "\n";
    std::cout << "     - Pendientes        : " << pendientes << "\n\n";

    std::cout << " [2] DISTRIBUCION POR TIPO REQUERIDO:\n";
    std::cout << "     - Bomberos          : " << totalBomberos << "\n";
    std::cout << "     - Policia           : " << totalPolicia << "\n";
    std::cout << "     - Ambulancia        : " << totalAmbulancia << "\n\n";

    std::cout << " [3] POSICION ACTUAL DE UNIDADES EN EL MAPA:\n";
    std::cout << "     - Unidades de Bomberos  : " << mapasBomberos << " activas\n";
    std::cout << "     - Unidades de Policia   : " << mapasPolicia << " activas\n";
    std::cout << "     - Unidades de Ambulancia: " << mapasAmbulancia << " activas\n";

    std::cout << "=======================================================\n";
    
    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

#endif // TOOL_METRICAS_H