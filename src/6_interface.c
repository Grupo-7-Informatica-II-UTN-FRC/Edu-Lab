/*-----------Implementacion de la funcion parpadio-------------*/

      /*envia un char al arbino para prender un lep rojo o verde segun segun*/
      

 /*     REUTILIZACION DE CODIGO!!!
 * ============================================================================
 *
 * NOMBRE       : 2_send_char.c
 * AUTOR        : José Blanco 83621
 * Version      : 1.0
 * Descripción  : envia un char al arbino para prender un lep
 * FECHA        : 26 6 2021
 *
 * ============================================================================
 */

/* cuando ejecuto el programa debo indicar a la shell donde debe buscar la
   biblioteca libtermset.so para enlazarla dinamicamente: -ltermset
   lo hago agregando la ruta donde esta la biblioteca a la variable de
   entorno LD_LIBRARY_PATH. puedo verla con echo $LD_LIBRARY_PATH
   lo hago con el comando export LD_LIBRARY_PATH=$(pwd)/lib:$LD_LIBRARY_PATH

compilar con el comando:

gcc -Wall -Werror -std=c90 --pedantic-errors 2_send_char.c -I include/ -L lib/ -o send_charapp.out -ltermset

*/


#include <stdio.h> /*no hace falta la mayoria de estos jeiders*/
#include <stdlib.h>
#include <unistd.h> /* para la funcion sleep(unsigned int segundos)*/
#include <fcntl.h>  /*para las funciones de bajo nivel*/
#include "termset.h"
#include "edulab.h"


void parpadio(const char color, int fd)
{
 //  int fd;  /*descriptor de archivo*/


 /* if(argc < 4)
  {
     printf("USAR: %s <device: /dev/ttyACM0> <char: r, a, or v> <segundos: 1>",argv[0]);
     printf("\n");
     return -1;
  }
 */
  
 //  fd = open("/dev/ttyACM0", O_WRONLY | O_NOCTTY | O_SYNC); /*open device*/
   if(fd < -1)
   {
      printf("ERROR al abrir el puerto serie\n");

   }
/* 
   if(termset(fd, BAUDRATE, &ttyold, &ttynew) == -1)
   {
      printf("ERROR, no se puede configurar tty\n");
   }
*/


      /*sleep(1);*/ /*si no le pongo pausa el arduino reinicia el puerto serie y no me llega a tomar el char*/
      write(fd, &color, 1); /*dejo que me lea 1 letras para poder mandar la senial de palpadiar*/

 //  close(fd);
}



      /*------------Fin de la funcion parpadio                -------*/
