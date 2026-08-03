#ifndef TDA_ARISTA_H
#define TDA_ARISTA_H

template <typename T, typename P = int>
class Arista {
public:
    int destino;
    P peso;
    Arista<T, P>* siguiente;

    Arista(int d, P p) {
        destino = d;
        peso = p;
        siguiente = nullptr;
    }
};

#endif // TDA_ARISTA_H