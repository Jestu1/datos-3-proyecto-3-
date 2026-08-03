#ifndef TOOL_VER_MAPA_H
#define TOOL_VER_MAPA_H

#include <iostream>
#include <string>
#include <limits>
#include "../constantes.h"
#include "../classes/tda_ubicacion.h"
#include "../classes/grafo/tda_grafo.h"

extern Grafo<Ubicacion>* ptrMapa;

inline void tool_ver_mapa() {
    if (!ptrMapa) {
        std::cout << "\nError: El mapa no esta inicializado.\n";
        return;
    }

    std::cout << "\n=======================================================\n";
    std::cout << "                 MAPA GENERAL DE LA ISLA               \n";
    std::cout << "=======================================================\n";

    std::cout << " UBICACION ACTUAL DE LOS EQUIPOS ESPECIALES:\n";
    std::cout << "-------------------------------------------------------\n";
    
    bool hayEquipos = false;
    for (int i = 0; i < MAX_VERTICES; i++) {
        Vertice<Ubicacion>* v = ptrMapa->getVertice(i);
        if (v != nullptr) {
            std::string nombreUbicacion = v->dato.getNombre();
            
            // Filtramos para ignorar ubicaciones vacías o genéricas si las hubiera
            if (nombreUbicacion != "Desconocido" && !nombreUbicacion.empty() && nombreUbicacion.find("Ubicacion ") == std::string::npos) {
                if (v->dato.getTieneBomberos()) {
                    std::cout << " [BOMBEROS]   -> Estacion ubicada en: " << nombreUbicacion << "\n";
                    hayEquipos = true;
                }
                if (v->dato.getTienePolicia()) {
                    std::cout << " [POLICIA]    -> Comando ubicado en:  " << nombreUbicacion << "\n";
                    hayEquipos = true;
                }
                if (v->dato.getTieneAmbulancia()) {
                    std::cout << " [AMBULANCIA] -> Base ubicada en:     " << nombreUbicacion << "\n";
                    hayEquipos = true;
                }
            }
        }
    }

    if (!hayEquipos) {
        std::cout << " No hay equipos especiales registrados en el mapa actualmente.\n";
    }

    std::cout << "\n CONEXIONES Y DISTANCIAS ENTRE UBICACIONES:\n";
    std::cout << "-------------------------------------------------------\n";
    ptrMapa->mostrarListaAdyacencia();
    
    std::cout << "=======================================================\n";
    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

#endif // TOOL_VER_MAPA_H