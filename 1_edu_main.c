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

#include<stdio.h>
#include<stdlib.h>
#include"edulab.h"

             /*+++++++++++++++++++++++ INICIO DEL MAIN +++++++++++++++++++++++++++++++*/


int main(void){

 user_data nuevo_usuario; /*defino una variable de tipo user_data para cargar fecha, nombre, etc*/
 unsigned char modo_elegido; /*Esta variable me va almacenar el modo elegido por el usuario*/
 int centinela = 0; /*flag que me controla el aviso de error en el bucle del menu*/
 void (*funcion_menu[3])(user_data * new_user) = {modo_edulab, modo_test, modo_minilab};
                                                     /*defino un arreglo de punteros a funciones que reciben
                                                     un puntero a una estructuras user_data y no devuelven nada */

   system("clear");   /*solo borra la pantalla nomas*/

   bienvenida(); /*llama a la funcion que imprime la bienenida al programa*/

   printf("\n\n Ingrese su Nombre o Alias: ");
   scanf(" %[^\n]s", nuevo_usuario.user_name);/*Esta expresion regular le ayuda a guardar nombres con espacios*/


   do{

      system("clear");    /*definido en el archivo cabecera stlib.h: me limpia la pantalla*/

      printf("\n\n \t\t ¡Te damos la bienvenida al Edu-LAB!\n");
      printf("\n %s, selecciona el numero del \"MODO DE OPERACION\" que desees ejecutar:\n\n", nuevo_usuario.user_name);

      do{
         if(centinela != 0){/*para que el error de ingreso de datos solo salga la primera vez*/
            system("clear");
            printf("\n %s! INGRESA UNA OPCION VALIDA DEL MENU (del 1 al 4)\n\n", nuevo_usuario.user_name);
          }
         printf("\n \t #1 --> MODO Edu-LAB.\n");
         printf("\n \t #2 --> MODO TEST.\n");
         printf("\n \t #3 --> MODO Mini-LAB.\n");
         printf("\n \t #4 --> CERRAR SESION Y SALIR DEL PROGRAMA.");
         printf("\n\n Tu opcion? --> ");
         scanf(" %c", & modo_elegido); /*este scanf prermite ingresar el modo seleccionado por el usuario*/
         /*printf("\n El usuario eligió el modo: %c \n", modo_elegido); /*printf de prueba: (debe comentarse luego de debbugiar)*/
         centinela++;
       }
      while(modo_elegido < MODO_EDULAB || modo_elegido > SALIR_DEL_PROGRAMA); /* se asegura que sea una opcion valida del 1 al 4*/

      (*funcion_menu[atoi((& modo_elegido) - 1)])(& nuevo_usuario);

         centinela = 0; /*baja la bandera para que no salte el error siempre*/
       }
   while(modo_elegido != SALIR_DEL_PROGRAMA);

   system("clear");
   despedida();/*esta funcion solo muestra una despedida*/

 return EXIT_SUCCESS; /* EXIT_SUCCESS esta definido en el header stdlib.h */
}



                /*----------------------- FIN DEL MAIN ---------------------------*/
