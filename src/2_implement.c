/*
 * ============================================================================
 *
 * NOMBRE       : edulab.c
 * AUTOR        : grupo 7
 * Version      : 1.0
 * Descripción  : archivo de impementacion de la biblioteca edulab
 * FECHA        : 30 8 2021
 *
 * ============================================================================
 */

#include <stdio.h> /*para los printf, scanf, etc*/
#include <stdio_ext.h> /*para que no joda el __fpurge(stdin)*/
#include <stdlib.h> /* para el rand y los clear, etc */
#include "edulab.h" /*para conocer los prototipos de funciones bienvenida, etc*/
#include "termset.h"/*para configurar el puerto serie*/
#include <fcntl.h>/*funciones de archivos de bajo nivel*/
#include <unistd.h>


#define NOTA_DE_APROBAR 6



         /*+++++++++++++++++++ FUNCION DE BIENVENIDA ++++++++++++++++++++++++*/


 void bienvenida(void){

    printf("\n ###########################################################");
    printf("\n #                                                         #");
    printf("\n #                Bienvenido a EDU-LAB                     #");
    printf("\n #    Mini laboratorio para las tecnicas digitales         #");
    printf("\n #                                                         #");
    printf("\n #    Trabajo Practico Informatica II - Version 01         #");
    printf("\n #                                                         #");
    printf("\n ###########################################################");

  }


      /*---------------- FIN DE LA FUNCION DE BIENVENIDA -------------------*/





         /*+++++++++++++++++++ FUNCION DE DESPEDIDA ++++++++++++++++++++++++*/


 void despedida(void){

    printf("\n\n   #####################################################################    ");
    printf("\n   #                                                                   #      ");
    printf("\n   #  * * * *   *     *       *           *           *       *     *  #      ");
    printf("\n   #  *         *     *      * *         * *         * *      *     *  #      ");
    printf("\n   #  *         * * * *     *   *       *   *       *   *     *     *  #      ");
    printf("\n   #  *         *     *    * * * *     * * * *     * * * *    *     *  #      ");
    printf("\n   #  * * * *   *     *   *       *   *       *   *       *   * * * *  #      ");
    printf("\n   #                                                                   #      ");
    printf("\n   #####################################################################\n\n\n");

  }


      /*---------------- FIN DE LA FUNCION DE DESPEDIDA -------------------*/





      /*--------------FUNCION INSTRUCCIONES---------------*/

           void instrucciones(char leccion)
      {
      system("clear");
      printf("\n\n * AHORA ESTUDIA LA LECCION #%c.", leccion);
      printf("\n\n * UNA VEZ LEIDO, CERRA LA VENTANA DEL APUNTE.");
      printf("\n\n * Y LUEGO, CUANDO ESTES LISTO PARA CONTINUAR, PRESIONA ENTER... ");
      getchar();
      }


      /*---------------FIN DE LA FUNCION INSTRUCCIONES----------------------------*/





      /*--------------FUNCION PREGUNTERO---------------*/

      void preguntero (char leccion, user_data *new_user){

         int num_preg = 1;/*para correr en el switch interno*/
         int i = 0; /*para copiar las respuestas del archivo de config en un arreglo de chares con un for*/
         int fd;/*descriptor de archivo para el puerto serie ttyACM0*/
         int aciertos = 0;/*va contando los aciertos para finalmente sacar el promedio*/
         char respuestas[10];/*arreglo de chares que guarda las respuestas que contesta el usuario*/
         char answers[10];/*arreglo de chares de respuestas correctas para comparar con las respuestas del usuario*/
         char salir = '0'; /*bandera para salir del preguntero*/
         FILE * answ_ptr;/*define un puntero que apunta a una estructura de tipo FILE para manejar el archivo de respuestas correctas*/

         system("clear");
                 /*"/dev/ttyUSB0"*//* tambien puede ser este otro puerto si es el arbino chino*/
         fd = open("/dev/ttyACM0", O_WRONLY | O_NOCTTY | O_SYNC); /*esto abre y configura el puerto como de escritura*/
         termset(fd, BAUDRATE, &ttyold, &ttynew);/*esto configura otras yerbas del puerto serie como la velocidad de transm*/
         

            switch(leccion)/*direcciona el tema a evaluar elegido por el usuario*/
            {
               case LECCION_1:
               
                  if((answ_ptr = fopen("./conf/answers_1.txt","r")) == NULL)/*en caso que no pueda abrir el archivo de las respuestas correctas*/
                  {
                     printf("\n ERROR AL ABRIR EL ARCHIVO DE RESPUESTAS 1");
                  }
                  else
                  {
                     for(i = 0 ; i < 10 ; i++)
                     {
                        fscanf(answ_ptr, "%c", answers + i);/*carg las respuestas del archivo de conf answers_x en un arreglo de chares*/
                     }

                     do
                     {

                        switch(num_preg) /*va seleccionando cada pregunta del tema 1*/
                        {
                           case PREGUNTA_1:
                              printf("\n");
                              system("cat ./conf/preguntero1.txt | head -n 10 | tail -n 10");/*muestra solo la 1er pregunta*/
                              __fpurge(stdin);/*tira la cadena del bufer para que ande bien el getchar()*/
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);/*utiliza el operador ternario para decidir si llama a la funcion correcta o falsa*/
                              printf("\n");/*si el usuario elige salir ahi nomas termina el bucle do wile*/
                           break;/*en esa misma linea se compara la respuesta con la correclta y ahi decide*/

                           case PREGUNTA_2:
                              printf("\n");
                              system("cat ./conf/preguntero1.txt | head -n 20 | tail -n 10");/*muestra solo la 2da pregunta*/
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_3:
                              printf("\n");
                              system("cat ./conf/preguntero1.txt | head -n 30 | tail -n 10");/*muestra solo la 3er pregunta*/
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_4:
                              printf("\n");
                              system("cat ./conf/preguntero1.txt | head -n 40 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_5:
                              printf("\n");
                              system("cat ./conf/preguntero1.txt | head -n 50 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_6:
                              printf("\n");
                              system("cat ./conf/preguntero1.txt | head -n 60 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_7:
                              printf("\n");
                              system("cat ./conf/preguntero1.txt | head -n 70 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_8:
                              printf("\n");
                              system("cat ./conf/preguntero1.txt | head -n 80 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_9:
                              printf("\n");
                              system("cat ./conf/preguntero1.txt | head -n 90 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_10:
                              printf("\n");
                              system("cat ./conf/preguntero1.txt | head -n 100 | tail -n 10");
                              __fpurge(stdin);
                              /*respuestas[num_preg] = salir = getchar(); (...asi lo habiba implementado antes...)
                              respuestas[num_preg] == answers[num_preg] ? correcta(&aciertos) : falsa(&fallas) ;*/
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              conclusion(new_user, aciertos, leccion);/*llama a la funcion para escribir en el archivo creditos.txt*/
                              printf("\n\n ENTER PARA CONTINUAR...");
                              __fpurge(stdin);
                              getchar();

                           break;

                        }/*fin del switch, no puedo hacerlo con un for porque no me anda el head y tail en el system como variable*/
                        num_preg++;/*hace que avance el preguntero*/
                        if(num_preg > 10)/*maneja la vandera para salir del bucle cuando se agota el preguntero*/
                           salir = 's';

                     }/*fin del swich interno del preguntero de la leccion_1*/
                     while(salir != 's');   /*repite el swich interno 10 veces porque son 10 preguntas o hasta salir del usuario*/
                  }/*cierra el else de la linea 130 que contempla todo el primer case externo*/
                  fclose(answ_ptr);/*cierro el archivo de las answers_1.txt porque ya no lo usa mas*/
                  
               break;/*breik de LECCION_1*/


               case LECCION_2:

                  if((answ_ptr = fopen("./conf/answers_2.txt","r")) == NULL)/*en caso que no pueda abrir el archivo de las respuestas correctas*/
                  {
                     printf("\n ERROR AL ABRIR EL ARCHIVO DE RESPUESTAS 2");
                  }
                  else
                  {
                     for(i = 0 ; i < 10 ; i++)
                     {
                        fscanf(answ_ptr, "%c", answers + i);/*carg las respuestas del archivo de conf answers_x en un arreglo de chares*/
                     }

                     do
                     {

                        switch(num_preg) /*va seleccionando cada pregunta del tema 2*/
                        {
                           case PREGUNTA_1:
                              printf("\n");
                              system("cat ./conf/preguntero2.txt | head -n 10 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_2:
                              printf("\n");
                              system("cat ./conf/preguntero2.txt | head -n 20 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_3:
                              printf("\n");
                              system("cat ./conf/preguntero2.txt | head -n 30 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_4:
                              printf("\n");
                              system("cat ./conf/preguntero2.txt | head -n 40 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_5:
                              printf("\n");
                              system("cat ./conf/preguntero2.txt | head -n 50 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_6:
                              printf("\n");
                              system("cat ./conf/preguntero2.txt | head -n 60 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_7:
                              printf("\n");
                              system("cat ./conf/preguntero2.txt | head -n 70 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_8:
                              printf("\n");
                              system("cat ./conf/preguntero2.txt | head -n 80 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_9:
                              printf("\n");
                              system("cat ./conf/preguntero2.txt | head -n 90 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_10:
                              printf("\n");
                              system("cat ./conf/preguntero2.txt | head -n 100 | tail -n 10");
                              __fpurge(stdin);
                              /*respuestas[num_preg] = salir = getchar(); (...asi lo habiba implementado antes...)
                              respuestas[num_preg] == answers[num_preg] ? correcta(&aciertos) : falsa(&fallas) ;*/
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              conclusion(new_user, aciertos, leccion);
                              printf("\n\n ENTER PARA CONTINUAR...");
                              __fpurge(stdin);
                              getchar();

                           break;

                        }/*fin del switch, no puedo hacerlo con un for porque no me anda el head en el system como variable*/
                        num_preg++;
                        if(num_preg > 10)
                           salir = 's';

                     }/*fin del swich interno del preguntero de la leccion_2*/
                     while(salir != 's');   /*repite el swich interno 10 veces porque son 10 preguntas o hasta salir del usuario*/
                  }/*cierra el else de la linea 247 que contempla todo el segundo case externo*/
                  fclose(answ_ptr);/*cierro el archivo de las answers_2.txt porque ya no lo usa mas*/
               
               break;/*break de LECCION_2*/


               case LECCION_3:

                  if((answ_ptr = fopen("./conf/answers_3.txt","r")) == NULL)/*en caso que no pueda abrir el archivo de las respuestas correctas*/
                  {
                     printf("\n ERROR AL ABRIR EL ARCHIVO DE RESPUESTAS 3");
                  }
                  else
                  {
                     for(i = 0 ; i < 10 ; i++)
                     {
                        fscanf(answ_ptr, "%c", answers + i);/*carg las respuestas del archivo de conf answers_x en un arreglo de chares*/
                     }

                     do
                     {

                        switch(num_preg) /*va seleccionando cada pregunta del tema 3*/
                        {
                           case PREGUNTA_1:
                              printf("\n");
                              system("cat ./conf/preguntero3.txt | head -n 10 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_2:
                              printf("\n");
                              system("cat ./conf/preguntero3.txt | head -n 20 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_3:
                              printf("\n");
                              system("cat ./conf/preguntero3.txt | head -n 30 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_4:
                              printf("\n");
                              system("cat ./conf/preguntero3.txt | head -n 40 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_5:
                              printf("\n");
                              system("cat ./conf/preguntero3.txt | head -n 50 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_6:
                              printf("\n");
                              system("cat ./conf/preguntero3.txt | head -n 60 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_7:
                              printf("\n");
                              system("cat ./conf/preguntero3.txt | head -n 70 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_8:
                              printf("\n");
                              system("cat ./conf/preguntero3.txt | head -n 80 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_9:
                              printf("\n");
                              system("cat ./conf/preguntero3.txt | head -n 90 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_10:
                              printf("\n");
                              system("cat ./conf/preguntero3.txt | head -n 100 | tail -n 10");
                              __fpurge(stdin);
                              /*respuestas[num_preg] = salir = getchar(); (...asi lo habiba implementado antes...)
                              respuestas[num_preg] == answers[num_preg] ? correcta(&aciertos) : falsa(&fallas) ;*/
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              conclusion(new_user, aciertos, leccion);
                              printf("\n\n ENTER PARA CONTINUAR...");
                              __fpurge(stdin);
                              getchar();

                           break;

                        }/*fin del switch, no puedo hacerlo con un for porque no me anda el head en el system como variable*/
                        num_preg++;
                        if(num_preg > 10)
                           salir = 's';

                     }/*fin del swich interno del preguntero de la leccion_2*/
                     while(salir != 's');   /*repite el swich interno 10 veces porque son 10 preguntas o hasta salir del usuario*/
                  }/*cierra el else de la linea 364 que contempla todo el tercer case externo*/
                  fclose(answ_ptr);/*cierro el archivo de las answers_2.txt porque ya no lo usa mas*/

               break; /*break de LECCION_3*/

               case LECCION_4:

                  if((answ_ptr = fopen("./conf/answers_4.txt","r")) == NULL)/*en caso que no pueda abrir el archivo de las respuestas correctas*/
                  {
                     printf("\n ERROR AL ABRIR EL ARCHIVO DE RESPUESTAS 4");
                  }
                  else
                  {
                     for(i = 0 ; i < 10 ; i++)
                     {
                        fscanf(answ_ptr, "%c", answers + i);/*carg las respuestas del archivo de conf answers_x en un arreglo de chares*/
                     }

                     do
                     {

                        switch(num_preg) /*va seleccionando cada pregunta del tema 4*/
                        {
                           case PREGUNTA_1:
                              printf("\n");
                              system("cat ./conf/preguntero4.txt | head -n 10 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_2:
                              printf("\n");
                              system("cat ./conf/preguntero4.txt | head -n 20 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_3:
                              printf("\n");
                              system("cat ./conf/preguntero4.txt | head -n 30 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_4:
                              printf("\n");
                              system("cat ./conf/preguntero4.txt | head -n 40 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_5:
                              printf("\n");
                              system("cat ./conf/preguntero4.txt | head -n 50 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_6:
                              printf("\n");
                              system("cat ./conf/preguntero4.txt | head -n 60 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_7:
                              printf("\n");
                              system("cat ./conf/preguntero4.txt | head -n 70 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_8:
                              printf("\n");
                              system("cat ./conf/preguntero4.txt | head -n 80 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_9:
                              printf("\n");
                              system("cat ./conf/preguntero4.txt | head -n 90 | tail -n 10");
                              __fpurge(stdin);
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              printf("\n");
                           break;

                           case PREGUNTA_10:
                              printf("\n");
                              system("cat ./conf/preguntero4.txt | head -n 100 | tail -n 10");
                              __fpurge(stdin);
                              /*respuestas[num_preg] = salir = getchar(); (...asi lo habiba implementado antes...)
                              respuestas[num_preg] == answers[num_preg] ? correcta(&aciertos) : falsa(&fallas) ;*/
                              (respuestas[num_preg-1] = salir = getchar()) == answers[num_preg-1] ? correcta(&aciertos, new_user, fd) : falsa(new_user, fd);
                              conclusion(new_user, aciertos, leccion);
                              printf("\n\n ENTER PARA CONTINUAR...");
                              __fpurge(stdin);
                              getchar();

                           break;

                        }/*fin del switch, no puedo hacerlo con un for porque no me anda el head en el system como variable*/
                        num_preg++;
                        if(num_preg > 10)
                           salir = 's';

                     }/*fin del swich interno del preguntero de la leccion_2*/
                     while(salir != 's');   /*repite el swich interno 10 veces porque son 10 preguntas o hasta salir del usuario*/
                  }/*cierra el else de la linea 480 que contempla todo el cuarto case externo*/
                  fclose(answ_ptr);/*cierro el archivo de las answers_2.txt porque ya no lo usa mas*/

               break;/*break de LECCION_4*/
            }/*fin del swith externo de las 4 lecciones*/

         close(fd);/*cierra el puerto serie ttyACM0*/
      }



      /*---------------FIN DE LA FUNCION PREGUNTERO----------------------------*/





      /*-----------respuestas correctas o falsas--------------*/
      
      void correcta(int * const good, user_data * new_user, int fd) /*va devolver 1 de 5 respuestas de felicitaciones aleatoriamente*/
      {
         srand(time(NULL));/*planta la semilla del rand aleatorio*/
         
         system("clear");
         
         (*good)++; /*claro porque si no incremento el contenido(*) se cambia el puntero (deberia ser puntero constante a dato no const)*/
         
         parpadio(GREEN, fd);/*llama a la funcion que escribe en el puerto serie un char que prende una luz de acierto*/
         
         switch(rand()%5)/*hay 5 variantes o 5 respuestas distintas posibles*/
         {/*cuando las respuestas son correctas, muestra la cantidad de aciertos. cuando son falsas, no lo hace*/
            case 0:
               printf(" POLEEEEENTA [%2d de 10]\n", *good);
            break;
            
            case 1:
               printf(" Jamón, %s [%2d de 10]\n", new_user -> user_name, *good);
            break;
            
            case 2:
               printf(" Ahí ta, ve? [%2d de 10]\n", *good);
            break;
            
            case 3:
               printf(" SI %s, vamo todavia [%2d de 10]\n", new_user -> user_name, *good);
            break;
            
            case 4:
               printf(" %s, %s, RA RA RAAAA... [%2d de 10]\n", new_user -> user_name, new_user -> user_name, *good);
            break;
         }

      }




      void falsa(user_data * new_user, int fd)
      {
         srand(time(NULL));/*planta la semilla del rand aleatorio*/
         
         system("clear");/*limpia la pantalla para mostrar la siguiente pregunta*/
         
         parpadio(RED, fd);/*llama a la funcion que escribe en el puerto serie una luz de error*/

         switch(rand()%5) /*hay 5 respuestas distintas posibles y salen al azar*/
         {
            case 0:
               printf(" ponele mas voluntad cullA\n\n");
            break;
            
            case 1:
               printf(" Que inutil, %s\n\n", new_user -> user_name);
            break;
            
            case 2:
               printf(" Dejaaaaaaaa...\n\n");
            break;
            
            case 3:
               printf(" NOOOO %s, piteeeee\n\n", new_user -> user_name);
            break;
            
            case 4:
               printf(" Vee VOOOOOOO\n\n");
            break;
         }

      }



      /*----------------fin de resp correctas o falsas----------------*/





      /*--------------FUNCION CONCLUSION---------------*/

       void conclusion (user_data * new_user, int calificacion, char modulo)
       {

          char date[50];
          FILE * score_ptr;
          
          new_user -> data_time = time(NULL);/*me carga la fecha y hora actualizada*/
          strftime(date, sizeof(date), "%A, %d %B %Y - %X", localtime(& new_user -> data_time));/*esto foramtea la fecha*/

          if((score_ptr = fopen("creditos.txt", "a")) == NULL)/*abre el archivo de escores en modo agregar*/
          {
             printf("\nERROR AL ABRIR EL ARCHIVO creditos.txt\n");/*en caso que no pueda abrir el archivo*/
          }
          else
          {
             if (calificacion >= NOTA_DE_APROBAR) /*en caso de que apruebe. NOTA_DE_APROBAR se #define arriba*/
             {
                printf(" FELICITACIONES %s!!! Aprobaste el módulo %c con calificacion: %.2f puntos", new_user -> user_name, modulo, calificacion*10.0);/*esto imprime en pantalla*/
                
                fprintf(score_ptr, " %s --->   %s:   %.2f puntos - Leccion %c.\n", date, new_user -> user_name, calificacion * 10.0, modulo);/*esto imprime en un arhivo .txt*/
             }
             else/*en caso que no llegue a la NOTA_DE_APROBAR*/
             {
                printf(" Todo mal %s cote tenes un %.2f puntos en el modulo %c anda a repasar el apunte bolo", new_user -> user_name, calificacion*10.0, modulo);/*esto lo muestra en pantalla*/
                
                fprintf(score_ptr, " %s --->   %s:   %.2f puntos - Leccion %c.\n", date, new_user -> user_name, calificacion * 10.0, modulo);/*esto lo imprime en un archivo .txt*/
             }
             fclose(score_ptr); /*si no cierro el archivo no me muestra los creditos hasta que salga del programa*/
          }
       }


      /*---------------FIN DE LA FUNCION CONCLUSION---------------------*/
      
      
      
      
      
      
      /*--------------FUNCIN MODO_CREDITOS-----------------------------*/
      
      
      void modo_creditos(ptr_user_data new_user){
         system("clear");/*me limpia la pantalla*/
      
         printf("\n ###########################################################");
         printf("\n #                                                         #");
         printf("\n #          Mini LAboratorio de Tecnicas Digitales         #");
         printf("\n #                                                         #");
         printf("\n #                         EDU-Lab                         #");
         printf("\n #       Trabajo Practico Informatica II - Version 01      #");
         printf("\n #                                                         #");
         printf("\n #                Año: 2021 - 2R4 - GRUPO 7                #");
         printf("\n #  ----------------------------------------------------   #");
         printf("\n #       Blanco, José: 83621                               #");
         printf("\n #       Lopez, Emanuel: 80300                             #");
         printf("\n #       Muñoz, Leandro: 83393                             #");
         printf("\n ###########################################################");
      
         printf("\n Usuario actual: %s\n", new_user -> user_name);
      
         printf("\n\n SCORES:\n\n ");
         
         system("tac ./creditos.txt");/*tac es igual que eun cat pero de abaj para arriba*/
         
         printf("\n %s, presione una tecla para volver al menu...", new_user -> user_name);
         getchar();getchar();/*si no pongo 2 el muy maldito se come el bufer*/
      
      }
      
      
      
      /*-------------FIN DE LA FUNCION MODO CREDITOS-------------------*/
      
      
      
      
      
      
/*void parpadio(const char color){} borrar cuando implemente en 6_interfase*/


/* void modo_edulab(user_data * new_user){} */ /* implementacion que pasa al archivo 3_modo_edulab.c */


/* void modo_test(user_data * new_user){} */ /* implementacion que pasa al archivo 4_modo_test.c */


/* void modo_minilab(user_data * new_user){} */ /* implementacion que pasa al archivo 5_modo_minilab.c */
