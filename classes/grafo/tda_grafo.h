#ifndef TDA_GRAFO_H
#define TDA_GRAFO_H

#include <iostream>
#include "tda_vertice.h"

const int MAX_VERTICES = 50;

// typename T: Es un comodín (un marcador de posición) para el tipo de dato del vértice.
// typename P = int: Es un comodín para el tipo de dato del peso, por defecto es int (entero).

template <typename T, typename P = int>
class Grafo {
private:
    bool esPonderado;
    bool esDirigido;
    Vertice<T, P>* vertices[MAX_VERTICES];
    int numVertices;

public:
    Grafo(bool _esPonderado = false, bool _esDirigido = false) {
        esPonderado = _esPonderado;
        esDirigido = _esDirigido;
        numVertices = 0;
        for (int i = 0; i < MAX_VERTICES; i++) {
            vertices[i] = nullptr;
        }
    }

    bool getEsPonderado() {
        return esPonderado;
    }

    bool getEsDirigido() {
        return esDirigido;
    }

    int getNumVertices() {
        return numVertices;
    }

    void agregarVertice(int id, T dato) {
        if (id >= 0 && id < MAX_VERTICES) {
            if (vertices[id] == nullptr) {
                vertices[id] = new Vertice<T, P>(id, dato);
                numVertices = numVertices + 1;
            } else {
                vertices[id]->dato = dato;
            }
        }
    }

    void agregarArista(int origen, int destino, P peso = P(1)) {
        if (origen < 0 || origen >= MAX_VERTICES || destino < 0 || destino >= MAX_VERTICES) {
            return;
        }
        if (vertices[origen] == nullptr || vertices[destino] == nullptr) {
            return;
        }

        P pesoFinal;
        if (esPonderado) {
            pesoFinal = peso;
        } else {
            pesoFinal = P(1);
        }

        vertices[origen]->agregarArista(destino, pesoFinal);
        if (!esDirigido) {
            vertices[destino]->agregarArista(origen, pesoFinal);
        }
    }

    Vertice<T, P>* getVertice(int id) {
        if (id >= 0 && id < MAX_VERTICES) {
            return vertices[id];
        }
        return nullptr;
    }

    void mostrarListaAdyacencia() {
        for (int i = 0; i < MAX_VERTICES; i++) {
            if (vertices[i] != nullptr) {
                // Se asume que el objeto T tiene un método getNombre(), según el pseudocódigo
                std::cout << "[" << vertices[i]->id << "] " << vertices[i]->dato.getNombre() << ": ";
                
                Arista<T, P>* actual = vertices[i]->listaAdyacencia;
                while (actual != nullptr) {
                    if (vertices[actual->destino] != nullptr) {
                        std::cout << vertices[actual->destino]->dato.getNombre();
                        if (esPonderado) {
                            std::cout << " (" << actual->peso << ")";
                        }
                    }
                    if (actual->siguiente != nullptr) {
                        std::cout << " -> ";
                    }
                    actual = actual->siguiente;
                }
                std::cout << "\n";
            }
        }
    }

    void dijkstra(int origen, int destino, int* previo, P* dist) {
        const P INF = 1000000;
        bool visitado[MAX_VERTICES];

        for (int i = 0; i < MAX_VERTICES; i++) {
            dist[i] = INF;
            previo[i] = -1;
            visitado[i] = false;
        }

        if (origen < 0 || origen >= MAX_VERTICES || vertices[origen] == nullptr) {
            return;
        }

        dist[origen] = 0;

        for (int count = 0; count < MAX_VERTICES; count++) {
            int u = -1;
            P minDist = INF;

            // Encontrar el vértice con la distancia mínima no visitado
            for (int i = 0; i < MAX_VERTICES; i++) {
                if (vertices[i] != nullptr && !visitado[i] && dist[i] < minDist) {
                    minDist = dist[i];
                    u = i;
                }
            }

            // Si no se encuentra un vértice accesible o llegamos al destino, terminamos
            if (u == -1 || u == destino) {
                break;
            }

            visitado[u] = true;
            Arista<T, P>* actual = vertices[u]->listaAdyacencia;

            // Actualizar las distancias de los vértices adyacentes
            while (actual != nullptr) {
                int v = actual->destino;
                P peso = actual->peso;

                if (!visitado[v] && dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                    previo[v] = u;
                }
                actual = actual->siguiente;
            }
        }
    }
};

#endif // TDA_GRAFO_H