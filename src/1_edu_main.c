/*
 * ============================================================================
 *
 * NOMBRE       : Grupo 7 Trabajo Final Informatica 2 2021
 * AUTOR        : José Blanco 83621 - Emanuel Lopez - Leandro Muñoz
 * Version      : 1.0
 * Descripción  : main menu de entrada al programa
 * FECHA        :29 08 2021
 *
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include"edulab.h"
             /*+++++++++++++++++++++++ INICIO DEL MAIN +++++++++++++++++++++++++++++++*/


int main(void){

 user_data nuevo_usuario; /*defino una variable de tipo user_data para cargar fecha, nombre, etc (declarada en edulab.h)*/
 char modo_elegido; /*Esta variable me va almacenar el modo elegido por el usuario (modo_edulab, modo_creditos, etc)*/
 int centinela = 0; /*flag que me controla el aviso de error en el bucle del menu (que no ingresa la opcion correcta)*/
 int i = 0; /*para el wile que va poniendo en mayuscula letra por letra*/
 void (*funcion_menu[4])(ptr_user_data new_user) = {modo_edulab, modo_test, modo_minilab, modo_creditos};
                                                     /*defino un arreglo de punteros a funciones que reciben
                                                     un puntero a una estructuras user_data y no devuelven nada 
                                                     me hace funcionar el menu como lo haria un swich masomenos*/

   system("clear");   /*solo borra la pantalla nomas*/

   bienvenida(); /*llama a la funcion que imprime la bienenida al programa*/

   printf("\n\n Ingrese su Nombre o Alias: ");
   scanf(" %[^\n]s", nuevo_usuario.user_name);/*Esta expresion regular le ayuda a guardar nombres con espacios*/

   while(nuevo_usuario.user_name[i] != '\0') /*me pasa el alias todas a mayuscula hasta que llega al fin de cadena '\0'*/
   {
      nuevo_usuario.user_name[i] = toupper(nuevo_usuario.user_name[i]); /*lo hace letra por letra hasta que encuentra el fin de cadena*/
      i++;
   }

   do{/*bucle para mostrar el menu de opcion de modos a ejecutar*/

      system("clear");    /*definido en el archivo cabecera stlib.h: me limpia la pantalla*/

      printf("\n\n \t\t ¡%s Te damos la bienvenida al Edu-LAB!\n", nuevo_usuario.user_name);
      printf("\n Selecciona el numero del \"MODO DE OPERACION\" que desees ejecutar:\n\n");

      do{
         if(centinela != 0){/*para que el error de ingreso de datos solo salga la primera vez*/
            system("clear");
            printf("\n %s! INGRESA UNA OPCION VALIDA DEL MENU (del 1 al 5)\n\n", nuevo_usuario.user_name);/*enseña como usar*/
          }
         printf("\n \t #1 --> MODO Edu-LAB.\n");
         printf("\n \t #2 --> MODO TEST.\n");
         printf("\n \t #3 --> MODO Mini-LAB.\n");
         printf("\n \t #4 --> CREDITOS.\n");
         printf("\n \t #5 --> CERRAR SESION Y SALIR DEL PROGRAMA.");
         printf("\n\n Tu opcion? --> ");
         scanf(" %c", & modo_elegido); /*este scanf prermite ingresar el modo seleccionado por el usuario*/

         centinela++;
       }
      while(modo_elegido < MODO_EDULAB || modo_elegido > SALIR_DEL_PROGRAMA); /* se asegura que sea una opcion valida del 1 al 5*/

      if(modo_elegido != SALIR_DEL_PROGRAMA)
      {
         (*funcion_menu[atoi(&modo_elegido) - 1 ])(& nuevo_usuario); /*al atoi hay que pasarle la direccion de la variable o un puntero a ella*/
      }/*aqui es donde se navega por el menu de modos lo hace el arreglo de punteros a funciones*/

      centinela = 0; /*reinicia la bandera para que salte el error de como ingresar la opcion solo cuando ingresa mal*/
      }
   while(modo_elegido != SALIR_DEL_PROGRAMA);/*pregunta por el modo toda vez que el usuario no quiera salir de la aplicacion*/

   system("clear");
   despedida();/*esta funcion solo muestra una despedida*/

 return EXIT_SUCCESS; /* EXIT_SUCCESS esta definido en el header stdlib.h */
}



                /*----------------------- FIN DEL MAIN ---------------------------*/
