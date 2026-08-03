#ifndef TDA_UBICACION_H
#define TDA_UBICACION_H

#include <string>
#include <iostream>
#include <sstream>
#include "../constantes.h"

class Ubicacion {
private:
    int id;
    std::string nombre;
    bool tieneBomberos;
    bool tienePolicia;
    bool tieneAmbulancia;

public:
    Ubicacion() {
        id = -1;
        nombre = "";
        tieneBomberos = false;
        tienePolicia = false;
        tieneAmbulancia = false;
    }

    Ubicacion(int _id, std::string _nombre) {
        id = _id;
        nombre = _nombre;
        tieneBomberos = false;
        tienePolicia = false;
        tieneAmbulancia = false;
    }

    static std::string getNombreEstatico(int _id) {
        if (_id >= 0 && _id < 20) return UBICACIONES[_id];
        std::stringstream ss;
        ss << "Ubicacion " << _id;
        return ss.str();
    }

    int getId() const {
        return this->id;
    }

    std::string getNombre() const {
        return this->nombre;
    }

    bool getTieneBomberos() const {
        return this->tieneBomberos;
    }

    bool getTienePolicia() const {
        return this->tienePolicia;
    }

    bool getTieneAmbulancia() const {
        return this->tieneAmbulancia;
    }

    std::string getEquiposTexto() const {
        std::string res = "";
        if (this->tieneBomberos) res += " [BOMBEROS]";
        if (this->tienePolicia) res += " [POLICIA]";
        if (this->tieneAmbulancia) res += " [AMBULANCIA]";
        return res;
    }

    void setId(int _id) {
        this->id = _id;
    }

    void setNombre(std::string _nombre) {
        this->nombre = _nombre;
    }

    void setTieneBomberos(bool v) {
        this->tieneBomberos = v;
    }

    void setTienePolicia(bool v) {
        this->tienePolicia = v;
    }

    void setTieneAmbulancia(bool v) {
        this->tieneAmbulancia = v;
    }
};

#endif // TDA_UBICACION_H
