🌍 **Languages**  
- 🇬🇧 [English](reverse-engineering.md)  
- 🇳🇱 [Nederlands](reverse-engineering.nl.md)  
- 🇨🇴 [Español (Colombia)](reverse-engineering.es-co.md)  
- 🇵🇹 [Português (Portugal)](reverse-engineering.pt.md)

# Estudio de firmware compilado (avanzado)

Este documento introduce el estudio de firmware compilado con fines educativos.  
Está dirigido a estudiantes avanzados que desean comprender qué queda de un programa cuando el código fuente no está disponible.

Este tema es opcional y no es necesario para completar las rutas de aprendizaje principales.

---

## Qué se entiende aquí por “ingeniería inversa”

En este contexto, la ingeniería inversa se refiere al análisis del firmware compilado para comprender su estructura, comportamiento y limitaciones.  
El objetivo **no** es reconstruir el código fuente ni eludir protecciones.

El enfoque está en entender cómo un microcontrolador ejecuta instrucciones a nivel de máquina.

---

## Qué puede analizarse

Los estudiantes pueden analizar, entre otros:

- archivos `.elf`, con o sin símbolos de depuración  
- archivos `.hex` que representan imágenes de firmware  

Estos archivos pueden provenir de:
- firmware creado dentro de este repositorio  
- ejemplos de libre acceso  
- proyectos propios del estudiante  

---

## Objetivos educativos

Al analizar firmware compilado, los estudiantes pueden:

- observar cómo el código de alto nivel se traduce en instrucciones  
- comprender la disposición de la memoria y el flujo de ejecución  
- identificar el impacto de las optimizaciones del compilador  
- valorar la importancia de los símbolos de depuración  

---

## Preguntas para explorar

Ejemplos de preguntas adecuadas para este tema:

- ¿Es posible identificar bucles o retardos?  
- ¿Se pueden reconocer operaciones de entrada y salida?  
- ¿Qué información se pierde al eliminar los símbolos de depuración?  
- ¿Por qué es difícil reconstruir el código fuente a partir del firmware?  

---

## Herramientas y enfoque

Para este estudio pueden utilizarse diversas herramientas, como:

- desensambladores  
- herramientas de inspección de símbolos  
- simuladores  
- scripts de análisis propios  

El énfasis está en la **observación y la interpretación**, no en la automatización.

---

## Alcance y limitaciones

Esta actividad se centra en la comprensión, no en la reconstrucción.  
En general, no es posible recuperar el código fuente original a partir del firmware.

Las conclusiones deben considerarse interpretaciones fundamentadas.

---

## Nota ética y legal

Este tema está destinado exclusivamente a fines educativos.  
Los estudiantes deben trabajar con su propio firmware o con ejemplos de libre acceso, y respetar siempre las licencias de software.

---

## Cuándo abordar este tema

Se recomienda explorar este tema:

- después de completar las rutas de aprendizaje principales  
- con conocimientos previos de ensamblador y arquitectura de microcontroladores  
- con acompañamiento en contextos educativos  

Esta sección existe para profundizar el conocimiento y fomentar la curiosidad.

