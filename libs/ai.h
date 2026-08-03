#ifndef AI_H
#define AI_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include "levenshtein.h"

struct Tool {
    std::string name;
    int toolId;
    std::function<void()> action;
};

class AI {
private:
    std::map<int, Tool> tools;

public:
    AI() = default;

    AI(const std::vector<Tool>& toolList) {
        for (const auto& t : toolList) {
            tools[t.toolId] = t;
        }
    }

    void registerTool(const Tool& tool) {
        tools[tool.toolId] = tool;
    }

    void mostrarHerramientas() const {
        std::cout << "\n================ HERRAMIENTAS Y OPCIONES DISPONIBLES ================\n";
        for (const auto& pair : tools) {
            std::cout << "* " << pair.second.name << "\n";
        }
        std::cout << "=====================================================================\n";
    }

    std::string getAIResponse(const std::string& prompt, int maxDistancia = 7) {
        std::string rawResponse = getLevenshteinResponse(prompt, maxDistancia);

        if (rawResponse.empty()) {
            return "No encontre lo que buscabas.";
        }

        // Buscar T=
        size_t tPos = rawResponse.find("T=");
        if (tPos != std::string::npos) {
            int toolId = std::stoi(rawResponse.substr(tPos + 2));
            if (tools.count(toolId)) {
                std::cout << "\nEjecutando accion: " << tools[toolId].name << "...\n";
                tools[toolId].action();
                return "Ejecutada tool: " + tools[toolId].name;
            }
            return "No encontre lo que buscabas.";
        }

        // Buscar R=
        size_t rPos = rawResponse.find("R=");
        if (rPos != std::string::npos) {
            return rawResponse.substr(rPos + 2);
        }

        return rawResponse;
    }
};

#endif // AI_H
