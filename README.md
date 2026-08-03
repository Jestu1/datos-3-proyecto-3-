# DATOS III - Proyecto 3 - Central de emergencias

Por algún extraño motivo, el índice de catástrofes en Margarita se ha elevado, y el estado se encuentra sumido en el caos; las líneas de emergencias están colapsadas. Para afrontar esta situación se ha desarrollado un chatbot capaz de atender estos incidentes.

La labor del chatbot es ser un asistente para la central de emergencias, debe ser capaz de recibir solicitudes de ayuda y, en base a ellas, enviar los equipos especiales necesarios para atender la emergencia. Entre dichos recursos están:

* Equipo de bomberos.
* Equipo de seguridad.
* Equipo médico.

Debido a la gran catástrofe, solo se cuenta con una única unidad de cada uno de los recursos mencionados anteriormente.

Por lo tanto, el agente debe ser capaz de recibir las solicitudes y atenderlas de manera eficiente para evitar que el caos aumente.

## Notas sobre la IA:
* El agente es un chatbot basado en el algoritmo de Levenshtein.
* El equipo de IT (Estudiantes) tiene a disposición las funciones de IA `solo deben utilizarla`.

```cpp
// libs/ai.h
std::string respuesta = agente.getAIResponse(prompt);
// Ingresa un prompt y la IA responde un string
```

## Las Tools de IA:
Cuando `getAIResponse` recibe un prompt pueden ocurrir dos cosas:
  1. Se devuelve rápidamente una respuesta string.
  2. Se llama a una tool, que no es más que una función definida por los estudiantes en el agente.

## Funciones que debe completar el estudiante:

A lo largo del código, hay varias funciones que el estudiante debe completar, su trabajo será encontrarlas y hacerlas funcionar en conjunto, dichas funciones, cuentan con comentarios para ayudar al estudiante a completarlas con éxito. Ejemplo:

`tools/tool_reportar_emergencia.h`:
* `tool_reportar_emergencia`

## Para obtener el 10: Features adicionales
* **1.5 pto**: Registrar localidad (agregar vértice): Un formulario en línea único y fluido (sin complicar al usuario con palabras técnicas) que permita conectar localidades existentes o agregar una nueva localidad (no se permite agregar localidades sin conectar).

* **2 pts**: En el contexto de la aplicación, se debe crear Una (1) `tool` original y dos (2) `respuestas` originales para la IA (que no sean tools y definidas por usted mismo). `Se evalúa creatividad` (agregar al `context.txt`, `tools/tool_adicional.h` y `main.cpp`).
