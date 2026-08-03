#include <iostream>
#include <string>
#include <vector>
#include "libs/ai.h"
#include "constantes.h"
#include <list>
#include "classes/tda_emergencia.h"
#include "classes/tda_ubicacion.h"
#include "classes/grafo/tda_grafo.h"

#include "helpers/inicializar_aplicacion.h"

#include "tools/tool_salir.h"
#include "tools/tool_help.h"
#include "tools/tool_listar_emergencias.h"
#include "tools/tool_reportar_emergencia.h"
#include "tools/tool_atender_emergencia.h"
#include "tools/tool_ver_mapa.h"
#include "tools/tool_metricas.h"


// Punteros globales a objetos instanciados en el main
Grafo<Ubicacion>* ptrMapa = nullptr;
AI* ptrAgente = nullptr;
std::list<Emergencia> listaEmergencias;

int main() {
    // 1. Inicializar grafo del mapa
    Grafo<Ubicacion> mapa(true, false);
    ptrMapa = &mapa;
    
    inicializarAplicacion("grafo.txt", mapa);
    
    std::vector<Tool> herramientas = {
        { "Salir", 0, salir },
        { "Ayuda", 1, help },
        { "listar emergencias", 2, tool_listar_emergencias },
        { "reportar emergencia", 3, tool_reportar_emergencia },
        { "atender emergencia", 4, tool_atender_emergencia },
        { "ver mapa", 5, tool_ver_mapa },
        {"ejecutar estadisticas", 6, tool_metricas},
    };

    AI agente(herramientas);
    ptrAgente = &agente;

    std::cout << "\n=======================================================\n";
    std::cout << "         EMERGENCIA EN MARGARITA - CHAT BOT            \n";
    std::cout << "=======================================================\n";

    while (true) {
        std::string prompt;
        std::cout << "\nCHAT-BOT: En que te puedo ayudar? (help para ver opciones)\n";
        if (!std::getline(std::cin, prompt)) {
            break;
        }

        std::string respuesta = agente.getAIResponse(prompt);
        std::cout << "\n>> " << respuesta << "\n";
    }
}
