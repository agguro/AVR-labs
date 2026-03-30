[Home](../../README.md)  -  [Docs index](../index/README.md) <br>
[🇬🇧](README.md)  -  [🇳🇱](README.nl.md)  -  [🇨🇴](README.es-co.md)  -  [🇵🇹](README.pt.md)

# Rutas de aprendizaje

Este repositorio ofrece múltiples rutas de aprendizaje, según los conocimientos previos, las herramientas disponibles y los objetivos de aprendizaje.  
Todas las rutas conducen, en última instancia, al mismo objetivo: comprender cómo funcionan realmente los microcontroladores.

No todas las personas comienzan desde el mismo punto, y esto es una decisión de diseño consciente.

---

## 🟢 Ruta 1 — Entrada guiada (Puente Arduino)

**Para quién:**  
- principiantes  
- estudiantes más jóvenes  
- personas sin una toolchain completa  
- primer contacto con microcontroladores  

**Herramientas:**  
- Arduino IDE  
- sketches de Arduino (en el directorio `arduino/`)  

**Enfoque:**  
- entrada y salida básicas  
- observación del comportamiento  
- experimentos sencillos  

**Qué se hace en esta ruta:**  
- abrir un sketch proporcionado  
- cargarlo en una placa Arduino  
- observar LEDs, botones y temporización  

**Qué se aprende:**  
- que el código controla el hardware  
- que los pines tienen significado  
- que el tiempo es importante  

**Nota importante:**  
Esta ruta es un punto de entrada, no el destino final.  
Se anima a los estudiantes a avanzar hacia la Ruta 2 cuando se sientan preparados.

---

## 🟡 Ruta 2 — Simulación primero (Ruta principal)

**Para quién:**  
- estudiantes que quieren entender qué ocurre realmente  
- entornos sin hardware físico  
- aulas con recursos limitados  

**Herramientas:**  
- `virt-atmega328p`  
- un programa `simulate` por laboratorio  
- sistema de construcción Meson  

**Enfoque:**  
- comportamiento interno del microcontrolador  
- registros y puertos  
- temporización y ejecución  

**Qué se hace en esta ruta:**  
- construir firmware como archivos `.elf`  
- ejecutar el firmware en simulación  
- interactuar con componentes virtuales  

**Qué se aprende:**  
- cómo se ejecuta el firmware  
- cómo funcionan realmente los puertos  
- la diferencia entre simulación y hardware real  

👉 **Esta es la ruta de aprendizaje recomendada.**

---

## 🔵 Ruta 3 — Firmware y grabación en flash (Con hardware)

**Para quién:**  
- estudiantes listos para trabajar con hardware real  
- personas curiosas por entender qué significa realmente “cargar”  

**Herramientas:**  
- archivos de firmware `.hex`  
- herramienta `flash`  
- hardware ATmega328P (con o sin placa Arduino)  

**Enfoque:**  
- grabación en flash frente a “upload”  
- estructura de memoria  
- comunicación serial  

**Qué se hace en esta ruta:**  
- grabar firmware directamente en el microcontrolador  
- configurar la velocidad en baudios y los puertos  
- observar el comportamiento en hardware real  

**Qué se aprende:**  
- cómo el código llega al microcontrolador  
- qué función cumple un bootloader  
- cómo las herramientas de software se comunican con el hardware  

---

## 🔴 Ruta 4 — Exploración avanzada (Más allá de Arduino)

**Para quién:**  
- estudiantes avanzados  
- personas autodidactas  
- quienes se interesan por el diseño de sistemas embebidos  

**Herramientas:**  
- extensiones de `virt-atmega328p`  
- componentes virtuales  
- depuración de bajo nivel  

**Enfoque:**  
- diseño de sistemas  
- periféricos  
- arquitectura  

**Qué se hace en esta ruta:**  
- ampliar el microcontrolador virtual  
- diseñar hardware virtual propio  
- explorar temporización, interrupciones y memoria  

**Qué se aprende:**  
- cómo se estructuran los sistemas embebidos  
- cómo interactúan el hardware y el software  
- cómo se crean las abstracciones  

---

## 🔁 Las rutas no son estrictamente separadas

Los estudiantes pueden moverse libremente entre rutas.  
Alguien puede empezar con Arduino, pasar a la simulación y luego volver al hardware con una comprensión más profunda.

El objetivo es el progreso, no la limitación.

---

## 🎯 Objetivo compartido

No solo lograr que algo funcione,  
sino entender **por qué** funciona.

---

## Nota para docentes

Estas rutas de aprendizaje están diseñadas intencionalmente para funcionar sin hardware físico obligatorio.  
Permiten un acceso equitativo al aprendizaje en contextos donde los recursos son limitados, sin sacrificar profundidad técnica.

