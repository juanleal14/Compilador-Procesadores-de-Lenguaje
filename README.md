# PL-Final-Project

Proyecto de traducción en varias etapas que transforma un subconjunto de C en código Lisp intermedio y, finalmente, en código Forth. El objetivo es disponer de un **frontend** que acepte construcciones imperativas familiares y un **backend** que genere un lenguaje de pila apto para su ejecución en intérpretes Forth.

## Estructura del repositorio

- `Frontend`: gramática de Bison que implementa el analizador sintáctico/semántico del frontend. Lee código C estilizado y produce expresiones Lisp (`defun`, `setf`, `loop`, etc.).
- `Backend`: gramática de Bison para el backend. Consume el Lisp intermedio y lo reescribe en Forth, generando definiciones `:`/`;`, `cells allot`, `loop while`, entre otras construcciones propias de Forth.
- `Tryouts`: breve recordatorio del pipeline (`cat test.c | ./trad4 | clisp`).
- `test1_frontend.c`: programa de ejemplo que cubre variables globales/locales, `if`, `for`, `while`, llamadas a funciones y `printf`/`puts`.

## Requisitos previos

- [GNU Bison](https://www.gnu.org/software/bison/) 3.x o compatible.
- Compilador C estándar (por ejemplo, `gcc`).
- Un intérprete Common Lisp (se sugiere `clisp`) para ejecutar la salida intermedia, y un entorno Forth si se desea ejecutar el resultado final.

## Generar los traductores

1. Compilar el frontend (C → Lisp):
   ```bash
   bison -d -o frontend.c Frontend
   gcc frontend.c -o trad_frontend
   ```
2. Compilar el backend (Lisp → Forth):
   ```bash
   bison -d -o backend.c Backend
   gcc backend.c -o trad_backend
   ```

> **Nota:** Los archivos `Frontend` y `Backend` ya incluyen un analizador léxico manual (`yylex`), por lo que no es necesario `flex`/`lex`.

## Flujo de traducción

1. Traducir el código C de entrada a Lisp:
   ```bash
   ./trad_frontend < test1_frontend.c > programa.lisp
   ```
2. Opcional: ejecutar el Lisp resultante en `clisp` para validar la semántica intermedia.
   ```bash
   clisp programa.lisp
   ```
3. Traducir el Lisp a Forth:
   ```bash
   ./trad_backend < programa.lisp > programa.fth
   ```

El fichero `programa.fth` contendrá definiciones Forth con declaraciones de variables (`variable`, `cells allot`), funciones (`:` ... `;`) y bucles `begin ... while ... repeat` que reflejan el flujo de control original.

## Características soportadas

### Frontend (C → Lisp)
- Declaración y asignación de variables `int`, incluidas reservas de arreglos vía `[]`.
- Definición de funciones con parámetros, variables locales y retorno mediante `return`.
- Estructuras de control `if/else`, `while` y `for`.
- Operadores aritméticos y relacionales (`+`, `-`, `*`, `/`, `%`, `&&`, `||`, `!`, `==`, `!=`, `<=`, `>=`, `<`, `>`).
- Llamadas a funciones y acceso a arreglos (`identificador[expresión]`).
- Salidas estándar con `puts` y `printf` (incluyendo secuencias de parámetros).
- Inserción de código Lisp en línea mediante comentarios `//@ ...` que se copian literalmente a la salida.

### Backend (Lisp → Forth)
- Traducción de definiciones `defun` y `main` a palabras Forth (`:` ... `;`).
- Declaración de variables Forth (`variable`, `cells allot`) y almacenamiento con `!`/`@`.
- Soporte para `setf`, `setq`, `make-array`, `aref` y `return-from` del código intermedio.
- Conversión de expresiones lógicas y aritméticas (`+`, `-`, `*`, `/`, `mod`, `and`, `or`, comparadores, `not`).
- Mapeo de estructuras `loop while`, `if`/`else` y bloques `progn` a sus equivalentes en Forth.
- Impresión con `print`/`prin1` traducida a las palabras Forth correspondientes.

## Ejecución de prueba rápida

Para revisar el pipeline completo con el ejemplo incluido:

```bash
./trad_frontend < test1_frontend.c | tee programa.lisp
./trad_backend < programa.lisp > programa.fth
cat programa.fth
```

Los archivos intermedios (`programa.lisp`, `programa.fth`) pueden eliminarse tras la prueba. Ajusta los nombres según tus fuentes. Recuerda limpiar los artefactos generados por Bison/GCC (`frontend.c`, `frontend.h`, `backend.c`, `backend.h`, ejecutables) cuando ya no sean necesarios.

## Estado y próximos pasos

El proyecto sirve como base académica para explorar compilación por etapas. Posibles mejoras incluyen:
- Automatizar la construcción con un `Makefile`.
- Ampliar la gramática a más tipos de datos y estructuras de control.
- Generar pruebas automáticas que validen la equivalencia entre cada etapa de traducción.
