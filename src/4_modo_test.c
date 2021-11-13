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

char TEST = 2; /*vendria a ser el modo EDU_TEST: 10XX-XXXX*/
const char *compuerta[] ={    /*si quiero cambiar el nombre de las compuertas aqui es donde*/
                          "Circuito integrado #1 -> Compuerta logica AND",
                          "Circuito integrado #2 -> Compuerta logica OR ",
                          "Circuito integrado #3 -> Compuerta logica~AND",
                          "Circuito integrado #4 -> Compuerta logica XOR"
                         }; /*esto es un arreglo de punteros a char donde se guardan los nombres de las compuertas*/
char user_election;/*aqui se va guardar el dispositivo que desea testear el usuario*/
int fd; /*file descriptor para el puerto serie /dev/ttyACM0*/


  /*-----------------------------------------FUNCION DEL MODO_TEST---------------------------------------*/


 void modo_test(ptr_user_data new_user) /*fijate como uso el alias ptr_user_data que defino en el edulab.h*/
 {
    enum device componente; /*enumeracion definida en edulab.h puede valer de '1' a '4' con cada componente*/

    do
    {

       system("clear");

       printf("\n ###########################################################");
       printf("\n #                                                         #");
       printf("\n #                     MODO TEST                           #");
       printf("\n #                                                         #");
       printf("\n #           ELEGI UNA OPCION PARA CONTINUAR               #");
       printf("\n #                                                         #");
       for(componente = COMPONENT_1 ; componente <= COMPONENT_4 ; componente++)
       {
          printf("\n #  %-40s          #", compuerta[componente - '1']); /*tengo que restarle '1'(en aski) porque el arreglo va de 0 a 3 nomas*/
       }
       printf("\n #                                                         #");
       printf("\n ###########################################################\n\n ? -> ");

       do
       {
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



    fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);/*esto abre y configura el puerto como de escritura y lectura*/
    termset(fd, BAUDRATE, &ttyold, &ttynew);
    __fpurge(stdin); /* tira la cadena del stdin para que no joda el getchar*/
    
    switch(user_election)/*va a navegar por los 4 tipos diferentes de compuertas a testear*/
    {
       case COMPONENT_1:
          system("xdg-open ./conf/componente_1.pdf &"); /*dispara el apunte 1 en el lector de pdf predeterminado & para ejecucuin en segundo plano*/
          instruccionesTest(user_election); /*indica por pantalla como proceder*/
          instruccionesTest_2(user_election);
          testiando(user_election, new_user, fd); // ejecuta la prueba de circuito integrado elegido.
       break;


       case COMPONENT_2:
          system("xdg-open ./conf/componente_2.pdf &"); /*dispara el apunte 2 en el lector de pdf predeterminado - & en segundo plano*/
          instruccionesTest(user_election);
          instruccionesTest_2(user_election);
          testiando(user_election, new_user, fd); // ejecuta la prueba de circuito integrado
       break;


       case COMPONENT_3:
          system("xdg-open ./conf/componente_3.pdf &"); /*dispara el apunte 3 en el lector de pdf predeterminado*/
          instruccionesTest(user_election);
          instruccionesTest_2(user_election);
          testiando(user_election, new_user, fd); // ejecuta la prueba de circuito integrado
       break;


       case COMPONENT_4:
          system("xdg-open ./conf/componente_4.pdf &"); /*dispara el apunte 4 en el lector de pdf predeterminado*/
          instruccionesTest(user_election);
          instruccionesTest_2(user_election);
          testiando(user_election, new_user, fd); // ejecuta la prueba de circuito integrado
       break;

    }
 }
 
/*--------------------------------FIN DE LA FUNCION MODO_TEST--------------------------------------*/



/*---------------------------------IMPLEMETACION DE LA FUNCION testiando-----------------------------------*/


 void testiando(char circuit, ptr_user_data new_user, int fd)
 {
    
    int estimulo = 0;/*contador para el for de los estimulos*/
    int i = 0;/*contador para  cargar el vector de respuestas al impulso predeterminada*/
    int resp_al_impulso[4] = {0};/*aqui se van a cargar las predeterminadas para luego comparar con las devueltas por la compuerta*/
    int flag_operativa = 0;/*bandera para avisar que si hay alguna falla será distinto de 4 (pruebas correctas)*/
    FILE * comp_ptr;/*puntero a la estructura de tipo FILE para abrir el archivo de configuracion de respuestas predeterminadas*/

    if(fd < -1)/*si no esta conectado el arbino va salir este error*/
    {
	    printf("\n\n\t ERROR AL ABRIR EL PUERTO ttyACM0");
    }
    else
    {
       switch(circuit)
       {
       case COMPONENT_1:
          if((comp_ptr = fopen("./conf/comportamiento_1.txt","r")) == NULL)/*en caso que no pueda abrir el archivo de las respuestas correctas*/
          {
             printf("\n ERROR AL ABRIR EL ARCHIVO DE COMPORTAMIENTO_1");
          }
          else
          {
             for(i = 0 ; i < 4 ; i++)/*este for carga uno a uno los datos del archivo de respuestas predeterminadas*/
             {
                fscanf(comp_ptr, "%lc", (resp_al_impulso + i));/*carg las respuestas del archivo de conf comportamiento_x en un arreglo de int*/

             }
          }
          fclose(comp_ptr);/*no necesito mas el archivo comportamiento_x.txt*/
              
          for(estimulo = 0; estimulo < 4; estimulo++)/*este for carga los estimulos en las entradas 3 y 4 de la union*/
          {
             new_user -> in_out . puerto_completo = estimulo << 2;/*pone en la entrada_3 y 4 de la union cada una de las combinaciones*/
                                                               /*XX-XX00-XX, XX-XX01-XX, XX-XX10-XX, XX-XX11-XX*/
                                                               /*fijate que estimulo varia desde 00 al 11*/
                                                               
             new_user -> in_out . modes = TEST ;/*me configura el byte a enviar con key MODO_TEST = 10XX-XXXX* see line 18*/
                                                /*es una operacion a nivel de bit. solo configura los bits de modos*/
          
             write(fd, &new_user -> in_out . puerto_completo, 1);/*fijate que apunta con operador flecha pero despues entra con
                                                                operador punto. esta linea escribe en el ttyACM0*/
                                                                
             if(estimulo==0)printf("\nSe enviaron los estimulos al arduino...");

             read(fd, &new_user -> in_out . puerto_completo, 1);
             if (estimulo==0)printf("\n\nAhora se estan recibiendo las respuestas a los impulsos enviados...");

             if(estimulo==0)printf("\n\n%-7s%-7s%-7s%-20s", "IN 1", "IN 2", "out 1", "COMPONENTE");
             printf("\n%-7d%-7d%-7d%-20s", new_user -> in_out.in_3, new_user -> in_out . in_2, new_user -> in_out.out_1, compuerta[atoi(&user_election)-1]);/*me va listar los estimulos y las respuestas a medida que las procese*/

             if(resp_al_impulso[estimulo] - '0' == new_user -> in_out . out_1 )/*compara el vector de respuestas predeterminadas*/
             {                                                                 /*con la respuesta al estímulo enviado y en caso de*/
                flag_operativa++;                                              /*ser verdadero, acumula las pruebas correctas*/
             }
          }/*fin del for*/

          flag_operativa == 4 ? printf("\n COMPONENTE OPERATIVO") : printf("\n COMPONENTE DEFECTUOSO O MAL CONECTADO");/*en caso de*/
                                                                                         /*completar las 4 pruebas, sera defectuoso*/
       break;


       case COMPONENT_2:

          if((comp_ptr = fopen("./conf/comportamiento_2.txt","r")) == NULL)/*en caso que no pueda abrir el archivo de las respuestas correctas*/
          {
             printf("\n ERROR AL ABRIR EL ARCHIVO DE COMPORTAMIENTO_2");
          }
          else
          {
             for(i = 0 ; i < 4 ; i++)/*este for carga uno a uno los datos del archivo de respuestas predeterminadas*/
             {
                fscanf(comp_ptr, "%lc", (resp_al_impulso + i));/*carg las respuestas del archivo de conf comportamiento_x en un arreglo de int*/

             }
          }
          fclose(comp_ptr);/*no necesito mas el archivo comportamiento_x.txt*/
              
          for(estimulo = 0; estimulo < 4; estimulo++)/*este for carga los estimulos en las entradas 3 y 4 de la union*/
          {
             new_user -> in_out . puerto_completo = estimulo << 2;/*pone en la entrada_3 y 4 de la union cada una de las combinaciones*/
                                                               /*XX-XX00-XX, XX-XX01-XX, XX-XX10-XX, XX-XX11-XX*/
                                                               /*fijate que estimulo varia desde 00 al 11*/
                                                               
             new_user -> in_out . modes = TEST ;/*me configura el byte a enviar con key MODO_TEST = 10XX-XXXX* see line 18*/
                                                /*es una operacion a nivel de bit. solo configura los bits de modos*/
          
             write(fd, &new_user -> in_out . puerto_completo, 1);/*fijate que apunta con operador flecha pero despues entra con
                                                                operador punto. esta linea escribe en el ttyACM0*/
                                                                
             if(estimulo==0)printf("\nSe enviaron los estimulos al arduino...");

             read(fd, &new_user -> in_out . puerto_completo, 1);
             if(estimulo==0)printf("\n\nAhora se estan recibiendo las respuestas a los impulsos enviados...");

             if(estimulo==0)printf("\n\n%-7s%-7s%-7s%-20s", "IN 1", "IN 2", "out 1", "COMPONENTE");
             printf("\n%-7d%-7d%-7d%-20s", new_user -> in_out.in_3, new_user -> in_out . in_2, new_user -> in_out.out_1, compuerta[atoi(&user_election)-1]);/*me va listar los estimulos y las respuestas a medida que las procese*/

             if(resp_al_impulso[estimulo] - '0' == new_user -> in_out . out_1 )/*compara el vector de respuestas predeterminadas*/
             {                                                                 /*con la respuesta al estímulo enviado y en caso de*/
                flag_operativa++;                                              /*ser verdadero, acumula las pruebas correctas*/
             }
          }/*fin del for*/

          flag_operativa == 4 ? printf("\n COMPONENTE OPERATIVO") : printf("\n COMPONENTE DEFECTUOSO O MAL CONECTADO");/*en caso de*/
                                                                                         /*completar las 4 pruebas, sera defectuoso*/

       break;


       case COMPONENT_3:

          if((comp_ptr = fopen("./conf/comportamiento_3.txt","r")) == NULL)/*en caso que no pueda abrir el archivo de las respuestas correctas*/
          {
             printf("\n ERROR AL ABRIR EL ARCHIVO DE COMPORTAMIENTO_3");
          }
          else
          {
             for(i = 0 ; i < 4 ; i++)/*este for carga uno a uno los datos del archivo de respuestas predeterminadas*/
             {
                fscanf(comp_ptr, "%lc", (resp_al_impulso + i));/*carg las respuestas del archivo de conf comportamiento_x en un arreglo de int*/

             }
          }
          fclose(comp_ptr);/*no necesito mas el archivo comportamiento_x.txt*/
              
          for(estimulo = 0; estimulo < 4; estimulo++)/*este for carga los estimulos en las entradas 3 y 4 de la union*/
          {
             new_user -> in_out . puerto_completo = estimulo << 2;/*pone en la entrada_3 y 4 de la union cada una de las combinaciones*/
                                                               /*XX-XX00-XX, XX-XX01-XX, XX-XX10-XX, XX-XX11-XX*/
                                                               /*fijate que estimulo varia desde 00 al 11*/
                                                               
             new_user -> in_out . modes = TEST ;/*me configura el byte a enviar con key MODO_TEST = 10XX-XXXX* see line 18*/
                                                /*es una operacion a nivel de bit. solo configura los bits de modos*/
          
             write(fd, &new_user -> in_out . puerto_completo, 1);/*fijate que apunta con operador flecha pero despues entra con
                                                                operador punto. esta linea escribe en el ttyACM0*/
                                                                
             if(estimulo==0)printf("\nSe enviaron los estimulos al arduino...");

             read(fd, &new_user -> in_out . puerto_completo, 1);
             if(estimulo==0)printf("\n\nAhora se estan recibiendo las respuestas a los impulsos enviados...");

             if(estimulo==0)printf("\n\n%-7s%-7s%-7s%-20s", "IN 1", "IN 2", "out 1", "COMPONENTE");
             printf("\n%-7d%-7d%-7d%-20s", new_user -> in_out.in_3, new_user -> in_out . in_2, new_user -> in_out.out_1, compuerta[atoi(&user_election)-1]);/*me va listar los estimulos y las respuestas a medida que las procese*/

             if(resp_al_impulso[estimulo] - '0' == new_user -> in_out . out_1 )/*compara el vector de respuestas predeterminadas*/
             {                                                                 /*con la respuesta al estímulo enviado y en caso de*/
                flag_operativa++;                                              /*ser verdadero, acumula las pruebas correctas*/
             }
          }/*fin del for*/

          flag_operativa == 4 ? printf("\n COMPONENTE OPERATIVO") : printf("\n COMPONENTE DEFECTUOSO O MAL CONECTADO");/*en caso de*/
                                                                                         /*completar las 4 pruebas, sera defectuoso*/
       break;
       
       
       case COMPONENT_4:

          if((comp_ptr = fopen("./conf/comportamiento_4.txt","r")) == NULL)/*en caso que no pueda abrir el archivo de las respuestas correctas*/
          {
             printf("\n ERROR AL ABRIR EL ARCHIVO DE COMPORTAMIENTO_4");
          }
          else
          {
             for(i = 0 ; i < 4 ; i++)/*este for carga uno a uno los datos del archivo de respuestas predeterminadas*/
             {
                fscanf(comp_ptr, "%lc", (resp_al_impulso + i));/*carg las respuestas del archivo de conf comportamiento_x en un arreglo de int*/
             }
          }
          fclose(comp_ptr);/*no necesito mas el archivo comportamiento_x.txt*/
              
          for(estimulo = 0; estimulo < 4; estimulo++)/*este for carga los estimulos en las entradas 3 y 4 de la union*/
          {
             new_user -> in_out . puerto_completo = estimulo << 2;/*pone en la entrada_3 y 4 de la union cada una de las combinaciones*/
                                                               /*XX-XX00-XX, XX-XX01-XX, XX-XX10-XX, XX-XX11-XX*/
                                                               /*fijate que estimulo varia desde 00 al 11*/
                                                               
             new_user -> in_out . modes = TEST ;/*me configura el byte a enviar con key MODO_TEST = 10XX-XXXX* see line 18*/
                                                /*es una operacion a nivel de bit. solo configura los bits de modos*/
          
             write(fd, &new_user -> in_out . puerto_completo, 1);/*fijate que apunta con operador flecha pero despues entra con
                                                                operador punto. esta linea escribe en el ttyACM0*/
                                                                
             if(estimulo==0)printf("\nSe enviaron los estimulos al arduino...");

             read(fd, &new_user -> in_out . puerto_completo, 1);
             if(estimulo==0)printf("\n\nAhora se estan recibiendo las respuestas a los impulsos enviados...");

             if(estimulo==0)printf("\n\n%-7s%-7s%-7s%-20s", "IN 1", "IN 2", "out 1", "COMPONENTE");
             printf("\n%-7d%-7d%-7d%-20s", new_user -> in_out.in_3, new_user -> in_out . in_2, new_user -> in_out.out_1, compuerta[atoi(&user_election)-1]);/*me va listar los estimulos y las respuestas a medida que las procese*/

             if(resp_al_impulso[estimulo] - '0' == new_user -> in_out . out_1 )/*compara el vector de respuestas predeterminadas*/
             {                                                                 /*con la respuesta al estímulo enviado y en caso de*/
                flag_operativa++;                                              /*ser verdadero, acumula las pruebas correctas*/
             }
          }/*fin del for*/

          flag_operativa == 4 ? printf("\n COMPONENTE OPERATIVO") : printf("\n COMPONENTE DEFECTUOSO O MAL CONECTADO");/*en caso de*/
                                                                                         /*completar las 4 pruebas, sera defectuoso*/
       break;
       }/*fin del switch*/                                                               
    }/*fin del else*/
    close(fd);/*ya no necesito enviar ni recibir mas por el puerto serie*/
       
    printf("\n enter para salir");
    getchar();        /*si no pongo esto, no me muestra los resultados finales*/
 }/*fin de la funcion testiando*/
 
 
 /*------------------------FIN DE LA FUNCION TESTIANDO-------------------------------*/
