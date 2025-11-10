#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr;
    int *temp_ptr; 
    int tamano_inicial = 5;
    int tamano_nuevo;

    ptr = (int*) malloc(tamano_inicial * sizeof(int));

    if (ptr == NULL) {
        printf("Error: Fallo el malloc inicial.\n");
        return 1;
    }

    for (int i = 0; i < tamano_inicial; i++) {
        ptr[i] = i * 10;
        printf("ptr[%d] = %d (Dir: %p)\n", i, ptr[i], &ptr[i]);
    }

    printf("\nIntroduce el nuevo tamano del arreglo (ej. 10): ");
    scanf("%d", &tamano_nuevo);


    //uso de un apuntador temporal para evitar perder los datos
    temp_ptr = (int*) realloc(ptr, tamano_nuevo * sizeof(int));

    // se verifica el puntero temporal
    if (temp_ptr == NULL) {
        printf("Error: No se pudo realojar la memoria (realloc devolvio NULL).\n");
        free(ptr);
        return 1;
    }

    // actualizar el puntero original
    ptr = temp_ptr;
    temp_ptr = NULL; 

    // llenar el nuevo arreglo
    if (tamano_nuevo > tamano_inicial) {
        printf("Llenando la *nueva* seccion del arreglo:\n");
        for (int i = tamano_inicial; i < tamano_nuevo; i++) {
            ptr[i] = i * 100;
        }
    }

    // imprimir el arreglo nuevo
    printf("Contenido completo del arreglo realojado:\n");
    for (int i = 0; i < tamano_nuevo; i++) {
        printf("ptr[%d] = %d\n", i, ptr[i]);
    }

    // liberar memoria
    free(ptr);
    ptr = NULL;

    return 0;
}