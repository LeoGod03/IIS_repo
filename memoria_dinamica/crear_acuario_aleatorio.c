#include <stdio.h>
#include <stdlib.h> 
#include <time.h>   // Para time (para la semilla de rand)


int* crearAcuarioAleatorio(int);
void imprimirArreglo(int*, int);

int main() {
    // inicializar semilla
    srand(time(NULL));

    
    int tamanoDeseado = 10;
    int* miAcuario = NULL;

    printf("Creando un acuario aleatorio de %d peces...\n", tamanoDeseado);
    miAcuario = crearAcuarioAleatorio(tamanoDeseado);

    // imprimir acuario
    if (miAcuario != NULL) {
        imprimirArreglo(miAcuario, tamanoDeseado);
    } else {
        printf("No se pudo crear el acuario.\n");
        return 1;
    }

    free(miAcuario);
    miAcuario = NULL;
    return 0;
}

int* crearAcuarioAleatorio(int tamano) {
    // validar que el tamaño dado sea correcto
    if (tamano <= 0) {
        printf("Error: El tamano debe ser positivo.\n");
        return NULL;
    }
    int* acuario = (int*) malloc(tamano * sizeof(int));

    // verificar
    if (acuario == NULL) {
        printf("Error: malloc devolvio NULL. No hay memoria.\n");
        return NULL;
    }

    for (int i = 0; i < tamano; i++) {

        *(acuario + i) = (rand() % 4) + 1;
    }
    return acuario;
}


void imprimirArreglo(int* arr, int tam) {
    if (arr == NULL) return;
    
    for (int i = 0; i < tam; i++) {
        printf("%d ", *(arr+ i));
    }
    printf("\n");
}

