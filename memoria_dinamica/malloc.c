#include <stdio.h>
#include <stdlib.h> 

int main() {
    int n;
    int *ptr;
    printf("Cuantos enteros deseas alojar? ");
    scanf("%d", &n);

    // hacemos un "cast" (int*) porque malloc devuelve void*
    ptr = (int*) malloc(n * sizeof(int));

    
    // verificar que el apuntador tenga memoria asignada
    if (ptr == NULL) {
        printf("Error: No se pudo alojar la memoria (malloc devolvio NULL).\n");
        return 1;
    }

    //mostrar que se inicializó con basura
    printf("Valores del arreglo con los que se inicializaron:\n");
    for (int i = 0; i < n; i++) {
        printf("ptr[%d] = %d\n", i, *(ptr + i));
    }

    // llenar el arreglo
    for (int i = 0; i < n; i++) {
        *(ptr + i) = i * 10;
    }

    // imprimir arreglo
    printf("Valores almacenados:\n");
    for (int i = 0; i < n; i++) {
        printf("ptr[%d] = %d\n", i, *(ptr + i));
    }

    // liberar memoria
    free(ptr); 
    ptr = NULL;

    return 0;
}