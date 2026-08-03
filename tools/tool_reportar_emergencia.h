#ifndef TOOL_REPORTAR_EMERGENCIA_H
#define TOOL_REPORTAR_EMERGENCIA_H

#include <iostream>
#include <string>
#include <list>
#include <limits>
#include "../constantes.h"
#include "../classes/tda_emergencia.h"
#include "../classes/tda_ubicacion.h"

extern std::list<Emergencia> listaEmergencias;

// FUNCION PARA AGREGAR NUEVAS EMERGENCIAS
inline void tool_reportar_emergencia() {
    std::cout << "\n=======================================================\n";
    std::cout << "               REPORTAR NUEVA EMERGENCIA              \n";
    std::cout << "=======================================================\n";

    int idUbicacion = -1;
    bool ubicacionValida = false;
    
    // Validacion DINAMICA para la ubicacion
    do {
        std::cout << "Seleccione la ubicacion de la emergencia:\n";
        for (int i = 0; i < MAX_VERTICES; i++) { 
            std::string nombre = Ubicacion::getNombreEstatico(i);
            // Mostrar solo las ubicaciones reales
            if (nombre != "Desconocido" && !nombre.empty() && nombre.find("Ubicacion ") == std::string::npos) {
                std::cout << "[" << i << "] " << nombre << "\n";
            }
        }
        std::cout << "ID Ubicacion: ";
        std::cin >> idUbicacion;

        // Comprobar que el ID esté en rango y pertenezca a un nombre válido
        if (idUbicacion >= 0 && idUbicacion < MAX_VERTICES) {
            std::string nombreSeleccionado = Ubicacion::getNombreEstatico(idUbicacion);
            if (nombreSeleccionado != "Desconocido" && !nombreSeleccionado.empty() && nombreSeleccionado.find("Ubicacion ") == std::string::npos) {
                ubicacionValida = true; // Es valido, podemos salir del ciclo
            }
        }

        if (!ubicacionValida) {
            std::cout << "Error: Ubicacion invalida. Intente de nuevo.\n\n";
        }
    } while (!ubicacionValida);

    int tipoEquipo = -1;
    // Validacion para el tipo de equipo
    do {
        std::cout << "\nSeleccione el equipo especial requerido:\n";
        std::cout << "[" << BOMBEROS << "] Bomberos\n";
        std::cout << "[" << POLICIA << "] Policia\n";
        std::cout << "[" << AMBULANCIA << "] Ambulancia\n";
        std::cout << "Tipo de Equipo: ";
        std::cin >> tipoEquipo;

        if (tipoEquipo != BOMBEROS && tipoEquipo != POLICIA && tipoEquipo != AMBULANCIA) {
            std::cout << "Error: Opcion de equipo invalida. Intente de nuevo.\n";
        }
    } while (tipoEquipo != BOMBEROS && tipoEquipo != POLICIA && tipoEquipo != AMBULANCIA);

    // Limpiamos el buffer de entrada antes de usar getline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::string descripcion;
    std::cout << "\nIngrese una descripcion de la emergencia:\n";
    std::getline(std::cin, descripcion);

    int nuevo_id = listaEmergencias.size() + 1;
    Emergencia nuevaEmerg(nuevo_id, tipoEquipo, idUbicacion, descripcion);
    listaEmergencias.push_back(nuevaEmerg);

    std::cout << "\nEmergencia reportada exitosamente.\n";
    std::cout << "Nuevo ID: " << nuevo_id << " en ubicacion: " << Ubicacion::getNombreEstatico(idUbicacion) << "\n";
}

#endif // TOOL_REPORTAR_EMERGENCIA_H