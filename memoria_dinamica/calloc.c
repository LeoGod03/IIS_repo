#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    int *ptr; 


    printf("Cuantos enteros deseas alojar? ");
    scanf("%d", &n);

    // hacemos un "cast" (int*) porque calloc devuelve void*
    ptr = (int*) calloc(n, sizeof(int));

    /// verificar que el apuntador tenga memoria asignada
    if (ptr == NULL) {
        printf("Error: No se pudo alojar la memoria (calloc devolvio NULL).\n");
        return 1;
    }

    //mostrar inicialización de calloc
    printf("Valores iniciales:\n");
    for (int i = 0; i < n; i++) {
        printf("ptr[%d] = %d\n", i, *(ptr + i)); 
    }

    // llenar el arreglo
    for (int i = 0; i < n; i++) {
        ptr[i] = i + 5;
    }
    
    // volvar a imprimir el arreglo
    printf("Valores nuevos:\n");
    for (int i = 0; i < n; i++) {
        printf("ptr[%d] = %d\n", i, ptr[i]);
    }


    //liberar memoria
    free(ptr);
    ptr = NULL;
    return 0;
}