/*En modo test el usuario tendrá un banco de trabajo*/


#include <stdio.h>
#include <stdio_ext.h> /*para la funcion __fpurge*/
#include <fcntl.h>/*funciones de archivos de bajo nivel*/
#include <stdlib.h>
#include "edulab.h"
#include "termset.h"/*para configurar el puerto serie*/
#include <unistd.h>

void modo_test(ptr_user_data new_user){

   int fd = open("/dev/ttyACM0", O_WRONLY | O_NOCTTY | O_SYNC); /*esto abre y configura el puerto como de escritura*/
   char bict;
   termset(fd, BAUDRATE, &ttyold, &ttynew);/*esto configura otras yerbas del puerto serie como la velocidad de transm*/

   system("clear");

   
    printf("\n ###########################################################");
    printf("\n #                                                         #");
    printf("\n #                      MODO TEST (LEAN)                   #");
    printf("\n #                                                         #");
    printf("\n #                                                         #");
    printf("\n #           ELIJA UNA OPCION PARA CONTINUAR               #");
    printf("\n #                                                         #");
    printf("\n ###########################################################");


    printf("\n\n Presione enter para continuar");
    __fpurge(stdin);
    getchar();
    bict = (1<<7);
    write(fd, &bict, 1); /*dejo que me lea 1 letras para poder mandar la senial de palpadear*/
    close(fd);/*cierra el puerto serie ttyACM0*/

}
