#include "Mi_Libreria.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> //diseñado para operaciones básicas con caracteres. Contiene los prototipos de las funciones y macros para clasificar caracteres.
//#include <string.h> //contiene la definición de macros, constantes, funciones y tipos y algunas operaciones de manipulación de memoria.
#include <stdbool.h> //(since C99) provides a boolean type, called _Bool. By including the header
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#define ESC       27
#define SPACE     32
#define BACKS     8
#define COMMA     44
#define PUNTO     46
#define PunDouble 58
#define PunYComma 59
#define ENTER     13


/*Objetivos
    - Aplicar los conocimientos del uso básico de punteros.
    - Trabajar con asignación dinámica de memoria.
    - Trabajar con cadenas de caracteres.
    - Trabajar con archivos.
*/

int main(void)
{
    bool salir = false;
    printf("\n\t****FUNDAMENTOS DE PROGRAMACION***\n");
    printf("\tManejo de Punteros y Cadenas de Caracteres");
    do{
        switch(imprimir_menu())
        {
            case 1:
                capturar_nombre_archivo();
                break;
            case 2:
                escribir_contenido_archivo();
                break;
            case 3:
                leer_contenido_archivo();
                break;
            case 4:
                analizar_contenido_archivo();
                break;
            case 5:
                salir = true;
            default :
                printf("Funci%cn elegida no es v%clida",162,160);
                break;
        }

    }while(!salir);

    return 0;
};