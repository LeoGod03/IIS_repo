#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
Nota: Se cambiaron los nombres de las funciones para separar palabras con "_"
*/

//****Estructuras****
typedef struct{
    char calle[50];
    int cp;
    int numExt;
    char alcaldia[50];
}Direccion;

typedef struct {
    char nombre[50];
    int telefono[8];
    char correo[50];
    Direccion direc;
} Contacto;

//***prototipos***
void guardar_archivo(Contacto * arreglo, int indice, char * nombre_archivo);
Contacto * cargar_archivo(int * indice, int * tam, char * nombre_archivo);
void limpiar_buffer();
void agregar_contacto(Contacto *, int *, int *);
void imprimir_contacto(Contacto);
void imprimir_direccion(Direccion);
void imprimir_arreglo_contactos(Contacto *, int);
Contacto * leer_contacto();  

/*
**Función main**
declaración de variables importantes, función principal del programa
*/
void main(){
 
  int tam = 10;
  int indice = 0;
  Contacto * contactos = NULL;
  contactos = cargar_archivo(&indice, &tam, "agenda.dat");
  if(contactos == NULL){
    printf("Creando arreglo nuevo\n");
    tam = 10;
    indice = 0;
    contactos = (Contacto *) malloc(tam * sizeof(Contacto));
    if(contactos == NULL){
      printf("No hay memoria\n");
      return;
    }

  }
  //for(int i = 0; i < 2; i++)
    //agregar_contacto(contactos, &indice, &tam);
  
  imprimir_arreglo_contactos(contactos, indice);

  //guardar_archivo(contactos, indice, "agenda.dat");
  free(contactos);
 

}
/*Función agregar_contacto
Agrega un nuevo contacto en el arreglo y cambia el tamaño si es necesario*/
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
    free(nuevoContacto);
    (*indice) ++;
}
/* función que limpia el salto de línea o fin de archivo del buffer para evitar problemas con fgets*/
void limpiar_buffer(){
  int c;
  while((c = getchar()) != '\n' && c != EOF);
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
/*Función que llena un nuevo contacto mediante teclado, dicho contacto es creado mediante memoria dínamica*/
Contacto * leer_contacto(){
    /*
    Regla para "limpiar_buffer"
    scanf() <- algo que no sea un string
    fgets <- leer una cadena

    con limpiar_buffer queda
    scanf() <- algo que no sea un string
    limpiar_buffer() <- después del scanf y antes del fgets
    fgets <- leer una cadena

    y también cuando la función termina con un scanf que no sea un string
    usar "limpiar_buffer()" 
    */
    int i;
    Contacto *c=malloc(sizeof(Contacto));
    if(c == NULL){
      printf("No se pudo asignar memoria para el contacto\n");
      return NULL;
    }
    printf("----Ingresa los datos del contacto ----\n");
    printf("nombre:"); 
    fgets(c->nombre, 50, stdin);
    printf("correo:"); 
    fgets(c->correo, 50, stdin);
    printf("Telefono (ingresa los 8 digitos separados por espacio):");
    for(i=0;i<8;i++) {
      scanf("%d",&c->telefono[i]);
    }
    limpiar_buffer();
    printf("---Direccion ---- \n");
    printf("calle:"); 
    fgets(c->direc.calle, 50, stdin);
    printf("numero:"); 
    scanf("%d",&c->direc.numExt);
    printf("cp:");
    scanf("%d",&c->direc.cp);
    limpiar_buffer();
    printf("alcadia:"); 
    fgets(c->direc.alcaldia, 50, stdin);
  
   return c;
}

void guardar_archivo(Contacto * arreglo, int indice, char * nombre_archivo){
  FILE * archivo = fopen(nombre_archivo, "wb");
  if(archivo == NULL){
    printf("Error al abrir el archivo\n");
    return;
  }
  fwrite(&indice, sizeof(int), 1, archivo);
  if(indice > 0){
    fwrite(arreglo, sizeof(Contacto), indice, archivo);
  }
  fclose(archivo);
  printf("Se guardaron correctamente los datos\n");
}

Contacto * cargar_archivo(int * indice, int * tam, char * nombre_archivo){
  FILE * archivo = fopen(nombre_archivo, "rb");
  if(archivo == NULL){
    printf("Error al abrir el archivo\n");
    return NULL;
  }
  int cantidad = 0;
  fread(&cantidad, sizeof(int), 1, archivo);
  *tam = cantidad + cantidad / 2;
  Contacto * nuevo_arreglo = (Contacto *) malloc((*tam) * sizeof(Contacto));
  if(nuevo_arreglo == NULL){
    printf("Error al asignar memoria \n");
    fclose(archivo);
    return NULL;
  }
  fread(nuevo_arreglo, sizeof(Contacto), cantidad, archivo);
  *indice = cantidad;
  fclose(archivo);
  printf("Se cargaron los datos correctamente\n");
  return nuevo_arreglo;
  
}




