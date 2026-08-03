#ifndef TDA_EMERGENCIA_H
#define TDA_EMERGENCIA_H

#include <string>

// Tipos de equipos de emergencia (constantes enteras)
const int BOMBEROS   = 0;
const int POLICIA    = 1;
const int AMBULANCIA = 2;

// TDA Emergencia: representa un caso de emergencia registrado
class Emergencia {
private:
    int id;
    int tipo;                   // 0=Bomberos, 1=Policia, 2=Ambulancia
    int idSector;               // ID del sector (0-19)
    std::string descripcion;
    bool atendida;

public:
    Emergencia() {
        id = 0;
        tipo = 0;
        idSector = 0;
        descripcion = "";
        atendida = false;
    }

    Emergencia(int _id, int _tipo, int _idSector, std::string _descripcion) {
        id = _id;
        tipo = _tipo;
        idSector = _idSector;
        descripcion = _descripcion;
        atendida = false;
    }

    int getId() const {
        return id;
    }

    int getTipo() const {
        return tipo;
    }

    std::string getTipoNombre() const {
        const std::string nombres[] = {"Bomberos", "Policia", "Ambulancia"};
        if (tipo >= 0 && tipo <= 2) return nombres[tipo];
        return "Desconocido";
    }

    int getIdSector() const {
        return idSector;
    }

    std::string getDescripcion() const {
        return descripcion;
    }

    bool getAtendida() const {
        return atendida;
    }

    void atenderEmergencia() {
        atendida = true;
    }
};

#endif // TDA_EMERGENCIA_H
