#include <stdio.h>
#include <stdlib.h> // Necesario para malloc, free, NULL

/**
 * @brief Imprime los elementos de un arreglo de enteros.
 * @param arr El arreglo a imprimir.
 * @param tam El número de elementos en el arreglo.
 */
void imprimirArreglo(int* arr, int tam) {
    if (arr == NULL) {
        printf("Arreglo es NULL\n");
        return;
    }
    printf("[ ");
    for (int i = 0; i < tam; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

/**
 * @brief Crea y devuelve un *nuevo* arreglo en el Heap
 * que contiene solo los números pares del arreglo original.
 *
 * @param arr El arreglo de entrada.
 * @param tam El tamaño del arreglo de entrada.
 * @param tamPares Puntero a un entero donde se almacenará
 * el tamaño del nuevo arreglo de pares.
 * @return Un puntero al nuevo arreglo de pares (alojado con malloc),
 * o NULL si no hay memoria o no hay pares.
 */
int* filtrarPares(int* arr, int tam, int* tamPares) {
    
    //contar cuántos pares hay
    int contador = 0;
    for (int i = 0; i < tam; i++) {
        if (*(arr + i) % 2 == 0) {
            contador++;
        }
    }
    
    // asignamos el tamaño del nuevo arreglo
    *tamPares = contador;

    // si el tamaño es 0 no hay arreglo
    if (contador == 0) {
        return NULL;
    }

    int* arrPares = (int*) malloc(contador * sizeof(int));
    
    // verificar el apuntador
    if (arrPares == NULL) {
        printf("Error: ¡malloc falló! No hay memoria.\n");
        *tamPares = 0;
        return NULL; 
    }

    // copiar los pares al nuevo arreglo
    int j = 0; // indice del nuevo arreglo
    for (int i = 0; i < tam; i++) {
        if (*(arr + i) % 2 == 0) {
            *(arrPares + j) = *(arr + i);
            j++; 
        }
    }
    return arrPares; 
}


int main() {
    int arr_original[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int tam_original = 10;
    
    int tam_nuevo = 0; // Esta variable la llenará la función
    int* arreglo_pares = NULL; // Aquí guardaremos el puntero al nuevo arreglo

    printf("Arreglo Original: ");
    imprimirArreglo(arr_original, tam_original);

    //filtrar pares
    arreglo_pares = filtrarPares(arr_original, tam_original, &tam_nuevo);

    // verificamos
    if (arreglo_pares == NULL) {
        printf("La funcion devolvio NULL (No hay memoria o no habia pares).\n");
    } else {
        printf("Nuevo tamano: %d\n", tam_nuevo);
        printf("Arreglo de Pares: ");
        imprimirArreglo(arreglo_pares, tam_nuevo);
        
        // liberar memoria
        free(arreglo_pares);
        arreglo_pares = NULL; // Buena práctica
    }

    return 0;
}