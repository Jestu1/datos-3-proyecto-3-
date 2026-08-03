#ifndef TOOL_LISTAR_EMERGENCIAS_H
#define TOOL_LISTAR_EMERGENCIAS_H

#include <iostream>
#include <list>
#include "../classes/tda_emergencia.h"
#include "../classes/tda_ubicacion.h"

extern std::list<Emergencia> listaEmergencias;

inline void tool_listar_emergencias() {
    std::cout << "\n=======================================================\n";
    std::cout << "           CASOS DE EMERGENCIA REGISTRADOS             \n";
    std::cout << "=======================================================\n";

    if (listaEmergencias.empty()) {
        std::cout << "No hay ninguna emergencia registrada en el sistema.\n";
    } else {
        for (auto it = listaEmergencias.begin(); it != listaEmergencias.end(); ++it) {
            std::string estado = it->getAtendida() ? "Atendida" : "Pendiente";
            std::cout << "[ID: " << it->getId() << "] Tipo: " << it->getTipoNombre() 
                      << " --> Ubicacion: " << Ubicacion::getNombreEstatico(it->getIdSector()) 
                      << " | Descripcion: " << it->getDescripcion() 
                      << " | Estado: " << estado << "\n";
        }
    }
}

#endif // TOOL_LISTAR_EMERGENCIAS_H