#ifndef TOOL_ATENDER_EMERGENCIA_H
#define TOOL_ATENDER_EMERGENCIA_H

#include <iostream>
#include <list>
#include <string>
#include "../classes/tda_emergencia.h"
#include "../classes/tda_ubicacion.h"
#include "../classes/grafo/tda_grafo.h"
#include "../constantes.h"

extern std::list<Emergencia> listaEmergencias;
extern Grafo<Ubicacion>* ptrMapa;

// Auxiliar para verificar si existen emergencias pendientes
inline bool existenEmergenciasPendientes() {
    for (auto it = listaEmergencias.begin(); it != listaEmergencias.end(); ++it) {
        if (!it->getAtendida()) {
            return true;
        }
    }
    return false;
}

// Auxiliar para mostrar emergencias pendientes
inline void mostrarEmergenciasPendientes() {
    for (auto it = listaEmergencias.begin(); it != listaEmergencias.end(); ++it) {
        if (!it->getAtendida()) {
            std::cout << "[ID: " << it->getId() << "] Tipo: " << it->getTipoNombre()
                      << " | Ubicacion: " << Ubicacion::getNombreEstatico(it->getIdSector())
                      << " | " << it->getDescripcion() << "\n";
        }
    }
}

// Auxiliar para buscar el nodo donde se encuentra el equipo requerido
inline int buscarNodoEquipo(int tipoRequerido) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        Vertice<Ubicacion>* v = ptrMapa->getVertice(i);
        if (v != nullptr) {
            if (tipoRequerido == BOMBEROS && v->dato.getTieneBomberos()) return i;
            if (tipoRequerido == POLICIA && v->dato.getTienePolicia()) return i;
            if (tipoRequerido == AMBULANCIA && v->dato.getTieneAmbulancia()) return i;
        }
    }
    return -1;
}

// Auxiliar para trasladar el equipo en el grafo de un vertice a otro vertice
inline void moverEquipoEnMapa(int nodoOrigen, int nodoDestino, int tipoRequerido) {
    Vertice<Ubicacion>* vOrigen = ptrMapa->getVertice(nodoOrigen);
    Vertice<Ubicacion>* vDestino = ptrMapa->getVertice(nodoDestino);

    if (vOrigen != nullptr && vDestino != nullptr) {
        if (tipoRequerido == BOMBEROS) {
            vOrigen->dato.setTieneBomberos(false);
            vDestino->dato.setTieneBomberos(true);
        } else if (tipoRequerido == POLICIA) {
            vOrigen->dato.setTienePolicia(false);
            vDestino->dato.setTienePolicia(true);
        } else if (tipoRequerido == AMBULANCIA) {
            vOrigen->dato.setTieneAmbulancia(false);
            vDestino->dato.setTieneAmbulancia(true);
        }
    }
}

// Auxiliar para buscar una emergencia pendiente por ID
inline Emergencia* buscarEmergenciaPorId(int idBuscado) {
    for (auto it = listaEmergencias.begin(); it != listaEmergencias.end(); ++it) {
        if (!it->getAtendida() && it->getId() == idBuscado) {
            return &(*it);
        }
    }
    return nullptr;
}

// Auxiliar para mostrar la ruta calculada por Dijkstra
// EL ESTUDIANTE NO DEBE MODIFICAR ESTA FUNCION
inline void mostrarRutaCalculada(int nodoDestino, int dist[], int camino[], int tamCamino) {
    std::cout << "\n=======================================================\n";
    std::cout << "             CAMINO MAS CORTO (DIJKSTRA)               \n";
    std::cout << "=======================================================\n";
    std::cout << " Distancia Total: " << dist[nodoDestino] << " km\n";
    std::cout << " Ruta: ";
    for (int i = tamCamino - 1; i >= 0; i--) {
        Vertice<Ubicacion>* v = ptrMapa->getVertice(camino[i]);
        if (v != nullptr) {
            std::cout << "[" << v->id << "] " << v->dato.getNombre();
            if (i > 0) {
                std::cout << " -> ";
            }
        }
    }
    std::cout << "\n=======================================================\n";
}

// EL ESTUDIANTE NO DEBE MODIFICAR ESTA FUNCION: PERO DEBE REVISAR EL TDA GRAFO PARA COMPLETAR LA FUNCION DIJKSTRA
inline void tool_atender_emergencia() {
    std::cout << "\n=======================================================\n";
    std::cout << "                 ATENDER EMERGENCIA                   \n";
    std::cout << "=======================================================\n";

    if (!existenEmergenciasPendientes()) {
        std::cout << "No hay emergencias pendientes para atender.\n";
        return;
    }
    
    std::cout << "Emergencias pendientes:\n";
    mostrarEmergenciasPendientes();

    int idSelec = -1;
    std::cout << "\nIngrese el ID de la emergencia a atender: ";
    std::cin >> idSelec;

    Emergencia* emerg = buscarEmergenciaPorId(idSelec);

    if (emerg == nullptr) {
        std::cout << "ID invalido o la emergencia ya fue atendida.\n";
        std::cin.ignore(1000, '\n');
        return;
    }

    int tipoRequerido = emerg->getTipo();
    int nodoOrigen = buscarNodoEquipo(tipoRequerido);

    if (nodoOrigen == -1) {
        std::cout << "Error: No se encontro el equipo correspondiente en el mapa.\n";
        return;
    }

    int nodoDestino = emerg->getIdSector();

    int previo[MAX_VERTICES];
    int dist[MAX_VERTICES];
    ptrMapa->dijkstra(nodoOrigen, nodoDestino, previo, dist);

    if (dist[nodoDestino] >= 1000000) {
        std::cout << "No existe camino hacia el destino indicado.\n";
        return;
    }

    int camino[MAX_VERTICES];
    int tamCamino = 0;
    int actual = nodoDestino;

    while (actual != -1) {
        camino[tamCamino++] = actual;
        actual = previo[actual];
    }

    mostrarRutaCalculada(nodoDestino, dist, camino, tamCamino);
    moverEquipoEnMapa(nodoOrigen, nodoDestino, tipoRequerido);

    emerg->atenderEmergencia();

    std::cout << "\nEmergencia ATENDIDA con exito!\n";
    std::cout << "El equipo ha sido trasladado a: " << Ubicacion::getNombreEstatico(nodoDestino) << "\n";

    std::cin.ignore(1000, '\n');
}

#endif // TOOL_ATENDER_EMERGENCIA_H