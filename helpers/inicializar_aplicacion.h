#ifndef INICIALIZAR_APLICACION_H
#define INICIALIZAR_APLICACION_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../constantes.h"
#include "../classes/tda_ubicacion.h"
#include "../classes/grafo/tda_grafo.h"


// ESTA FUNCION NO DEBE SER MODIFICADA (A NO SER QUE ROMPA EL TDA QUE DEFINAN USTEDES)
inline bool inicializarAplicacion(const std::string& rutaArchivo, Grafo<Ubicacion>& mapa) {
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cout << "Error al abrir el archivo: " << rutaArchivo << "\n";
        return false;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        if (linea.rfind("V =", 0) == 0) {
            size_t inicio = linea.find('{');
            size_t fin = linea.find('}');
            if (inicio != std::string::npos && fin != std::string::npos) {
                std::string contenido = linea.substr(inicio + 1, fin - inicio - 1);
                std::stringstream ss(contenido);
                std::string token;
                while (std::getline(ss, token, ',')) {
                    std::stringstream st(token);
                    int id;
                    if (st >> id) {
                        std::string nombreSector = Ubicacion::getNombreEstatico(id);
                        mapa.agregarVertice(id, Ubicacion(id, nombreSector));
                    }
                }
            }
        } else if (linea.rfind("E =", 0) == 0) {
            size_t pos = 0;
            while ((pos = linea.find('(', pos)) != std::string::npos) {
                size_t finPar = linea.find(')', pos);
                if (finPar != std::string::npos) {
                    std::string trio = linea.substr(pos + 1, finPar - pos - 1);
                    std::stringstream ss(trio);
                    std::string uStr, vStr, wStr;
                    if (std::getline(ss, uStr, ',') && std::getline(ss, vStr, ',') && std::getline(ss, wStr, ',')) {
                        int u = std::stoi(uStr);
                        int v = std::stoi(vStr);
                        int w = std::stoi(wStr);
                        mapa.agregarArista(u, v, w);
                    }
                    pos = finPar + 1;
                } else {
                    break;
                }
            }
        } else if (linea.rfind("U_BOMBEROS =", 0) == 0) {
            int nodo = std::stoi(linea.substr(linea.find('=') + 1));
            Vertice<Ubicacion>* vert = mapa.getVertice(nodo);
            if (vert != nullptr) vert->dato.setTieneBomberos(true);
        } else if (linea.rfind("U_POLICIA =", 0) == 0) {
            int nodo = std::stoi(linea.substr(linea.find('=') + 1));
            Vertice<Ubicacion>* vert = mapa.getVertice(nodo);
            if (vert != nullptr) vert->dato.setTienePolicia(true);
        } else if (linea.rfind("U_AMBULANCIA =", 0) == 0) {
            int nodo = std::stoi(linea.substr(linea.find('=') + 1));
            Vertice<Ubicacion>* vert = mapa.getVertice(nodo);
            if (vert != nullptr) vert->dato.setTieneAmbulancia(true);
        }
    }

    archivo.close();
    return true;
}

#endif // INICIALIZAR_APLICACION_H
