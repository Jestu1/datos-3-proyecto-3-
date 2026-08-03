#ifndef TDA_VERTICE_H
#define TDA_VERTICE_H

#include "tda_arista.h"

template <typename T, typename P = int>
class Vertice {
public:
    int id;
    T dato;
    Arista<T, P>* listaAdyacencia;

    Vertice(int i, T d) {
        id = i;
        dato = d;
        listaAdyacencia = nullptr;
    }

    void agregarArista(int destino, P peso) {
        Arista<T, P>* nueva = new Arista<T, P>(destino, peso);
        
        if (listaAdyacencia == nullptr) {
            listaAdyacencia = nueva;
        } else {
            Arista<T, P>* actual = listaAdyacencia;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nueva;
        }
    }
};

#endif // TDA_VERTICE_H