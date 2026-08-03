#ifndef TDA_EQUIPO_H
#define TDA_EQUIPO_H

#include <string>
#include "tda_emergencia.h"

// TDA Equipo: representa un equipo de emergencia (bomberos, policia, ambulancia)
class Equipo {
private:
    int tipo;           // 0=Bomberos, 1=Policia, 2=Ambulancia
    std::string nombre;
    int sectorActual;

public:
    Equipo() {
        tipo = 0;
        nombre = "";
        sectorActual = 0;
    }

    Equipo(int _tipo, std::string _nombre, int _sectorActual) {
        tipo = _tipo;
        nombre = _nombre;
        sectorActual = _sectorActual;
    }

    int getTipo() const {
        return tipo;
    }

    std::string getNombre() const {
        return nombre;
    }

    int getSectorActual() const {
        return sectorActual;
    }

    void setSectorActual(int sectorId) {
        sectorActual = sectorId;
    }
};

#endif // TDA_EQUIPO_H
