#include <stdio.h>
#include <stdlib.h> // Necesario para malloc
#include <string.h> // Necesario para strcspn (quitar el enter)

// Definición de estructuras (Asumida para el ejemplo)
typedef struct {
    char calle[50];
    int numExt;
    int cp;
    char alcaldia[50];
} Direccion;

typedef struct {
    char nombre[50];
    char correo[50];
    int telefono[8];
    Direccion direc;
} Contacto;

void guardar_archivo(Contacto * arreglo, int indice, const char * nombre_archivo);
Contacto * cargar_archivo(int * indice, int * tam, const char * nombre_archivo);
void limpiar_buffer();
void agregar_contacto(Contacto *, int *, int *);
void imprimir_contacto(Contacto);
void imprimir_direccion(Direccion);
void imprimir_arreglo_contactos(Contacto *, int);
Contacto * leer_contacto();  

int main() {
    int tam = 10;
    int indice = 0;
    Contacto * contactos = NULL;

    contactos = cargar_archivo(&indice, &tam, "agenda.dat");

    if (contactos == NULL) {
        printf("Iniciando agenda nueva...\n");
        tam = 10;
        indice = 0;
        contactos = (Contacto* ) malloc(tam * sizeof(Contacto));
        if(contactos == NULL){
            printf("No hay memoria.\n");
            return 0;
        }
    }
    for(int i = 0; i < 3; i++)
        agregar_contacto(contactos, &indice, &tam);

    imprimir_arreglo_contactos(contactos, indice);

    guardar_archivo(contactos, indice, "agenda.dat");
    
    free(contactos);
    return 0;
}


/* Función para GUARDAR en TXT*/
void guardar_archivo_txt(Contacto * arreglo, int indice, const char * nombre_archivo){
    FILE * archivo = fopen(nombre_archivo, "w");
    
    if(archivo == NULL){
        printf("Error: No se pudo crear el archivo txt.\n");
        return;
    }

    // guardamos la cantidad de contactos registrados
    fprintf(archivo, "%d\n", indice);

    // guardar la lista de contactos
    for(int i = 0; i < indice; i++){
        fprintf(archivo, "%s\n", arreglo[i].nombre);
        fprintf(archivo, "%s\n", arreglo[i].correo);
        
        // se guarda el telefono
        for(int j = 0; j < 8; j++){
            fprintf(archivo, "%d ", arreglo[i].telefono[j]);
        }
        fprintf(archivo, "\n"); // salto de línea al terminar los telefonos

        // datos de la dirección del contacto
        fprintf(archivo, "%s\n", arreglo[i].direc.calle);
        fprintf(archivo, "%d\n", arreglo[i].direc.numExt);
        fprintf(archivo, "%d\n", arreglo[i].direc.cp);
        fprintf(archivo, "%s\n", arreglo[i].direc.alcaldia);
    }

    fclose(archivo);
    printf("Datos guardados en texto plano en %s\n", nombre_archivo);
}

/* Función para CARGAR desde TXT*/
Contacto * cargar_archivo_txt(int * indice, int * tam, const char * nombre_archivo){
    FILE * archivo = fopen(nombre_archivo, "r");
    
    if(archivo == NULL){
        printf("No se encontro archivo de texto previo.\n");
        return NULL;
    }

    int cantidad_guardada = 0;

    // leer la cantidad total
    fscanf(archivo, "%d", &cantidad_guardada);
    
    // se limpia el buffer como se vio en clase
    int c; while((c = fgetc(archivo)) != '\n' && c != EOF); 

    *tam = cantidad_guardada + 5; 
    Contacto * nuevo_arreglo = (Contacto *) malloc((*tam) * sizeof(Contacto));

    if(nuevo_arreglo == NULL){ 
        return NULL; 
    }
    for(int i = 0; i < cantidad_guardada; i++){
        
        // por cada cadena se quita el salto de línea

        fgets(nuevo_arreglo[i].nombre, 50, archivo);
        nuevo_arreglo[i].nombre[strcspn(nuevo_arreglo[i].nombre, "\n")] = 0;

        fgets(nuevo_arreglo[i].correo, 50, archivo);
        nuevo_arreglo[i].correo[strcspn(nuevo_arreglo[i].correo, "\n")] = 0;

        for(int j = 0; j < 8; j++){
            fscanf(archivo, "%d", &nuevo_arreglo[i].telefono[j]);
        }

        // se limpia el buffer (DEL ARCHIVO)
        while((c = fgetc(archivo)) != '\n' && c != EOF);


        fgets(nuevo_arreglo[i].direc.calle, 50, archivo);
        nuevo_arreglo[i].direc.calle[strcspn(nuevo_arreglo[i].direc.calle, "\n")] = 0;

        fscanf(archivo, "%d", &nuevo_arreglo[i].direc.numExt);
        fscanf(archivo, "%d", &nuevo_arreglo[i].direc.cp);
        
        // se limpia el buffer
        while((c = fgetc(archivo)) != '\n' && c != EOF);

        fgets(nuevo_arreglo[i].direc.alcaldia, 50, archivo);
        nuevo_arreglo[i].direc.alcaldia[strcspn(nuevo_arreglo[i].direc.alcaldia, "\n")] = 0;
    }
    
    *indice = cantidad_guardada;
    fclose(archivo);
    printf("Cargados %d contactos desde TXT.\n", cantidad_guardada);
    
    return nuevo_arreglo;
}

void agregar_contacto(Contacto * arreglo, int *indice, int * tam){
  if(*indice == *tam){
    printf("Cambiando tamanio\n");
    int nuevoTam = (*tam / 2) + *tam;
    Contacto * aux = realloc(arreglo, nuevoTam * sizeof(Contacto));
    if(aux == NULL){
      printf("No se pudo asignar memoria \n");
      return;
    }
    arreglo = aux;
    *tam = nuevoTam;
  }
    Contacto * nuevoContacto;
    nuevoContacto = leer_contacto();
    arreglo[*indice] = *nuevoContacto;
    (*indice) ++;
}
/*Funcion que imprime la información de la estructura "Contacto"*/
void imprimir_contacto(Contacto c){

     printf("---Info del contacto ---\n");
     printf("Nombre: %s\n", c.nombre);
     for(int i = 0; i < 8; i++){
      printf("%d", c.telefono[i]);
     }
     printf("\n");
     printf("Correo: %s\n", c.correo);
     imprimir_direccion(c.direc); // aquí se muestra la información de la estructura anidada en "Contacto", es decir, "Dirección"

}
/*Función que imprime la información de la estructura "Dirección"*/
void imprimir_direccion(Direccion d){
  printf("--Imprimir dirección --\n");
  printf("Calle: %s\n", d.calle);
  printf("Alcaldia: %s\n", d.alcaldia);
  printf("Num exterior: %d\n", d.numExt);
  printf("Cp: %d\n", d.cp);
}
/*Función que imprime el arreglo de contactos usando la función "imprimir_contacto"*/
void imprimir_arreglo_contactos(Contacto * arreglo, int indice){
  for(int i = 0; i < indice; i++){
    printf("Contacto %d\n", (i + 1));
    imprimir_contacto(arreglo[i]);
  }
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Contacto* leer_contacto() {
    int i;
    
    Contacto *c = malloc(sizeof(Contacto));
    
    if (c == NULL) {
        printf("Error: No hay memoria suficiente.\n");
        return NULL;
    }

    printf("Ingresa los datos del contacto:\n");
    printf("Nombre: ");
    fgets(c->nombre, 50, stdin);
    c->nombre[strcspn(c->nombre, "\n")] = 0; 

    printf("Correo: ");
    fgets(c->correo, 50, stdin);
    c->correo[strcspn(c->correo, "\n")] = 0;

    printf("Telefono (ingresa los 8 digitos separados por espacio): ");
    for(i = 0; i < 8; i++) {
        scanf("%d", &c->telefono[i]);
    }

    
    limpiarBuffer();

    printf("\n-- Direccion --\n");
    
    printf("Calle: "); 
    fgets(c->direc.calle, 50, stdin); 
    c->direc.calle[strcspn(c->direc.calle, "\n")] = 0;

    printf("Numero: "); 
    scanf("%d", &c->direc.numExt); 

    printf("CP: "); 
    scanf("%d", &c->direc.cp);
    
    limpiarBuffer(); 

    printf("Alcaldia: "); 
    fgets(c->direc.alcaldia, 50, stdin);
    c->direc.alcaldia[strcspn(c->direc.alcaldia, "\n")] = 0;
  
    return c;
}
