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

#include<stdio.h> /*para los printf, scanf, etc*/
#include"edulab.h" /*para conocer los prototipos de funciones bienvenida, etc*/



         /*+++++++++++++++++++ FUNCION DE BIENVENIDA ++++++++++++++++++++++++*/


 void bienvenida(void){

    printf("\n ###########################################################");
    printf("\n #                                                         #");
    printf("\n #                        EDU-LAB                          #");
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


/* estas implementaciones siguientes hay que comentarlas una vez que
   esten los correspondientes archivos.c de cada implementacion, por
   el momento no los comento para que funcione el menu de bienvenida*/


 void modo_edulab(user_data * new_user){
  }






 void modo_test(user_data * new_user){} /*esta la hace el lean*/






 void modo_minilab(user_data * new_user){} /*esta la hace el ema*/
