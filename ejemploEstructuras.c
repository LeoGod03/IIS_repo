#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    char calle[50];
    int cp;
    int numExt;
    char alcaldia[50];
}Direccion;

typedef struct {
    char nombre[15];
    int telefono[8];
    char correo[15];
    Direccion direc;
} Contacto;


struct Datos{
   int num;
   char letra;
   double valor;  
   char palabra[10];  

};

void imprimir_datos(struct Datos d){
    
     printf("num:%d\nletra:%c\nvalor:%f\npalabra:%s",d.num,d.letra,d.valor,d.palabra); 
}

void imprimir_contacto(Contacto c){

     

}

Contacto * leer_contacto(){
    int i;
   //Contacto *c=malloc(sizeof(Contacto));
    Contacto c;
    printf("Ingresa los datos del contacto:\n");
    printf("nombre:"); scanf("%s",c.nombre);
    printf("correo:"); scanf("%s",c.correo);
    printf("Telefono (ingresa los 8 digitos separados por espacio):");
    for(i=0;i<8;i++) {
      scanf("%d",&c.telefono[i]);
    }
    printf("Direccion:\n,");
    printf("calle:"); scanf("%s",c.direc.calle);
    printf("numero:"); scanf("%d",&c.direc.numExt);
    printf("cp:"); scanf("%d",&c.direc.cp);
    printf("alcadia:"); scanf("%s",c.direc.alcaldia);
  
   return &c;
}
       


void main(){

  struct Datos d1;

  Contacto contacto1;


       d1.letra='n';
       d1.num=20;
       d1.valor=7.56;

      
       strcpy(d1.palabra,"palabra");

       

       imprimir_datos(d1);
   
    strcpy(contacto1.correo,"sf@dfsf");
    strcpy(contacto1.nombre,"Sandra");
    
    contacto1.telefono[0]=5;
    contacto1.telefono[1]=5;
    contacto1.telefono[2]=4;
    contacto1.telefono[3]=5;
    contacto1.telefono[4]=5;
    contacto1.telefono[5]=5;
    contacto1.telefono[6]=4;
    contacto1.telefono[7]=5;

    strcpy(contacto1.direc.calle,"Av del Arbol");

    printf("calle:%s",contacto1.direc.calle);
    

}



