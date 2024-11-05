#include <stdio.h>

int main(){

  /*
  Este programa imprime un rombo usando caracteres concéntricos
  '@', '.' y 'o' dada una longitud por el usuario.
  La longitud del lado más externo del rombo no será mayor de 20 caracteres.
  */

  int longitud, vez;

  printf("Introduzca la longitud del lado más externo del rombo\n");
  scanf("%d", &longitud);
  printf("\n");

  if (longitud>20 || longitud<=0) {
    printf("El dato introducido excede de la longitud permitida o no es correcto\n");
    printf("%2d", longitud);

  }else{
    // Imprimir parte superior del rombo
        for (int linea = 0; linea < longitud; linea++) {
            // Imprimir espacios en blanco
            for (int nespaciosblanco = 0; nespaciosblanco < (longitud - linea - 1); nespaciosblanco++) {
                printf(" ");
            }

            // Imprimir caracteres superiores izquierdos
            for (int posicion = 0; posicion <= linea; posicion++) {
                vez = posicion % 4;
                if(vez==0){
                    printf("@");
                }else if(vez==1){
                    printf(".");
                } else if(vez==2){
                    printf("o");
                }else{
                    printf(".");
                }
            }

            // Imprimir caracteres superiores derechos
            for (int posicion = 0; posicion < linea; posicion++) {
                vez = (linea-(posicion+1))% 4;
               if(vez==0){
                    printf("@");
                }else if(vez==1){
                    printf(".");
                } else if(vez==2){
                    printf("o");
                }else{
                    printf(".");
                }
            }
            printf("\n");
        }

        // Imprimir parte inferior del rombo
        for (int linea = longitud - 2; linea >= 0; linea--) {
            // Imprimir espacios en blanco
            for (int nespaciosblanco = 0; nespaciosblanco < (longitud - linea - 1); nespaciosblanco++) {
                printf(" ");
            }

            // Imprimir caracteres inferiores izquierdos
            for (int posicion = 0; posicion <= linea; posicion++) {
                vez = posicion % 4;
                if(vez==0){
                    printf("@");
                }else if(vez==1){
                    printf(".");
                } else if(vez==2){
                    printf("o");
                }else{
                    printf(".");
                }
            }

            // Imprimir caracteres inferiores derechos
            for (int posicion = 0; posicion < linea; posicion++) {
                vez = (linea-(posicion+1))% 4;
                if(vez==0){
                    printf("@");
                }else if(vez==1){
                    printf(".");
                } else if(vez==2){
                    printf("o");
                }else{
                    printf(".");
                }
            }
            printf("\n");
        }
  }
  return 0;
}
