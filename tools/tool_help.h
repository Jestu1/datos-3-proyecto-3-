#ifndef TOOL_HELP_H
#define TOOL_HELP_H

#include "../libs/ai.h"

extern AI* ptrAgente;

// EL ESTUDIANTE NO DEBE MODIFICAR ESTA FUNCION
inline void help() {
    if (ptrAgente != nullptr) {
        ptrAgente->mostrarHerramientas();
    }
}

#endif
