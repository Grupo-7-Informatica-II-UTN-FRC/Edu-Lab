/*En modo test el usuario tendrá un banco de pruebas
  el usuario elegirá el circuito integrado a probar y 
  el programa indicará como conectarlo y luego enviará
  estimulos para poner a prueba dicho dispositivo*/



#include <stdio.h>
#include <stdio_ext.h> /*para la funcion __fpurge*/
#include <stdlib.h>
#include "edulab.h"
#include <string.h>
#include "termset.h" /*para configurar el puerto serie*/
#include <ctype.h>
#include <fcntl.h> /*funciones de archivos de bajo nivel*/
#include <unistd.h>

char TEST = 2; /*vendria a ser el modo 10XX-XXXX*/
const char *compuerta[] ={    /*si quiero cambiar el nombre de las compuertas aqui es donde*/
                          "Circuito integrado #1 -> Compuerta logica AND",
                          "Circuito integrado #2 -> Compuerta logica OR ",
                          "Circuito integrado #3 -> Compuerta logica~AND",
                          "Circuito integrado #4 -> Compuerta logica XOR"
                         }; /*esto es un arreglo de punteros a char donde se guardan los nombres de las compuertas*/
char user_election;/*aqui se va guardar el dispositivo que desea testear el usuario*/
int fd;//file descriotor


void modo_test(ptr_user_data new_user){ /*fijate como uso el alias ptr_user_data que defino en el edulab.h*/



   enum device componente; /*enumeracion definida en edulab.h puede valer de '1' a '4' con cada componente*/


   do{

      system("clear");

      printf("\n ###########################################################");
      printf("\n #                                                         #");
      printf("\n #                     MODO TEST                           #");
      printf("\n #                                                         #");
      printf("\n #           ELEGI UNA OPCION PARA CONTINUAR               #");
      printf("\n #                                                         #");
      for(componente = COMPONENT_1 ; componente <= COMPONENT_4 ; componente++){
      printf("\n #  %-40s          #", compuerta[componente - '1']); /*tengo que restarle '1'(en aski) porque el arreglo va de 0 a 3 nomas*/
      }
      printf("\n #                                                         #");
      printf("\n ###########################################################\n\n ? -> ");

      do{
         scanf(" %c", &user_election);
      }
      while(user_election < COMPONENT_1 || user_election > COMPONENT_4);/*esto hace que no ingrese valores basura*/
      

      printf("\n\n* %s, elegiste: %s\n", new_user -> user_name, compuerta[user_election - '1']);
      printf("* A continuación observa el diagrama de coneccion y vamos a trabajar!!");
      printf("\n\n* Si estas listo, presiona ENTER para continuar\n");
      printf("* Si quieres cambiar de componente a probar, presiona la letra \"v\"\n ? -> ");

      __fpurge(stdin); /* tira la cadena del stdin para que no joda el getchar*/
   }
   while(getchar() == 'v'); /*sale del while si no elige Volver "V" "*/


      // int fd;	//descriptor de archivo de bajo nivel para el puerto serie. 

    fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);// esto abre y configura el puerto como de escritura y lectura
    termset(fd, BAUDRATE, &ttyold, &ttynew);// configura el puerto serie
    __fpurge(stdin); /* tira la cadena del stdin para que no joda el getchar*/
    fflush(stdin);
    getchar();
    
    
   switch(user_election)
   {
      case COMPONENT_1:
         system("xdg-open ./conf/componente_1.pdf &"); /*dispara el apunte 1 en el lector de pdf predeterminado & para ejecucuin en segundo plano*/
         instruccionesTest(user_election); /*indica por pantalla como proceder*/
         instruccionesTest_2(user_election);
         
    __fpurge(stdin); /* tira la cadena del stdin para que no joda el getchar*/
    fflush(stdin);         
         
         test(user_election, new_user, fd); // ejecuta la prueba de circuito integrado elegido.
      break;


      case COMPONENT_2:
         system("xdg-open ./conf/componente_2.pdf &"); /*dispara el apunte 2 en el lector de pdf predeterminado - & en segundo plano*/
         instruccionesTest(user_election);
         instruccionesTest_2(user_election);
         test(user_election, new_user, fd); // ejecuta la prueba de circuito integrado
      break;


      case COMPONENT_3:
         system("xdg-open ./conf/componente_3.pdf &"); /*dispara el apunte 3 en el lector de pdf predeterminado*/
         instruccionesTest(user_election);
         instruccionesTest_2(user_election);
         test(user_election, new_user, fd); // ejecuta la prueba de circuito integrado
      break;

      case COMPONENT_4:
         system("xdg-open ./conf/componente_4.pdf &"); /*dispara el apunte 4 en el lector de pdf predeterminado*/
         instruccionesTest(user_election);
         instruccionesTest_2(user_election);
         test(user_election, new_user, fd); // ejecuta la prueba de circuito integrado
      break;

   }
}









/*----------------IMPLEMETACION DE LA FUNCION test-----------------------------------*/


 void test(char prueba, ptr_user_data new_user, int fd)
 {
    
    int estimulo = 0;/*contador para el for de los estimulos*/
    int i = 0;
    int resp_al_impulso[4] = {0};
    int flag_operativa = 0;
   // int fd;	//descriptor de archivo de bajo nivel para el puerto serie. 
    FILE * comp_ptr;

    //fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_SYNC);// esto abre y configura el puerto como de escritura y lectura
   // termset(fd, BAUDRATE, &ttyold, &ttynew);// configura el puerto serie
         
    if(fd < -1){
	    printf("\n\n\t ERROR AL ABRIR EL PUERTO ttyACM0");
    }
    else
    {
       /*aqui iria el suich para cada comportamiento*/
       if((comp_ptr = fopen("./conf/comportamiento_2.txt","r")) == NULL)/*en caso que no pueda abrir el archivo de las respuestas correctas*/
       {
          printf("\n ERROR AL ABRIR EL ARCHIVO DE COMPORTAMIENTO 1");
       }
       else
       {
          for(i = 0 ; i < 4 ; i++)
          {
             fscanf(comp_ptr, "%lc", (resp_al_impulso + i));/*carg las respuestas del archivo de conf comportamiento_x en un arreglo de int*/
             printf("\nresp al inp: %ls", resp_al_impulso + i);
          }
       }
       fclose(comp_ptr);
       
       
       for(estimulo = 0; estimulo < 4; estimulo++)
       {
          new_user -> in_out . puerto_completo = estimulo << 2;/*pone en la entrada_3 y 4 de la union cada una de las combinaciones*/
                                                               /*XX-XX00-XX, XX-XX01-XX, XX-XX10-XX, XX-XX11-XX*/
          new_user -> in_out . modes = TEST ;/*me configura el byte a enviar con key MODO_TEST = 10XX-XXXX* see line 18*/
          
          write(fd, &new_user -> in_out . puerto_completo, 1);/*fijate que apunta con operador flecha pero despues entra con
                                                                operador punto. esta linea escribe en el ttyACM0*/
          printf("\n\tEnviando datos al arduino..");
/* no se si aqui hara falta un delay o no!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
          read(fd, &new_user -> in_out . puerto_completo, 1);
          printf("\n\tRecibiendo datos del arduino..");

          printf("\n\n%-20s%-7s%-7s%-7s", "COMPONENTE", "IN 1", "IN 2", "out 1");
          printf("\n%-20s%-7d%-7d%-7d", compuerta[atoi(&user_election)], new_user -> in_out.in_2, new_user -> in_out . in_3, new_user -> in_out.out_1);
          
          
          if(resp_al_impulso[estimulo] - '0' == new_user -> in_out . out_1 )
             flag_operativa++;
       }
       printf("flag_operativa es: %d", flag_operativa);/*para debuhigar*/
       flag_operativa == 4 ? printf("\n COMPONENTE OPERATIVO") : printf("\n COMPONENTE DEFECTUOSO O MAL CONECTADO");
    }
       close(fd);
       
       printf("\n enter para salir");
       getchar();
 }
