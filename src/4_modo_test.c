/*En modo test el usuario tendrá un banco de trabajo*/


#include <stdio.h>
#include <stdio_ext.h> /*para la funcion __fpurge*/
#include <stdlib.h>
#include "edulab.h"

void modo_test(ptr_user_data new_user){

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

}
