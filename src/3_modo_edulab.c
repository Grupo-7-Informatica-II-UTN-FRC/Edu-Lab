/*---------------implementacion del modo EduLab-----------------*/

/*En modo EduLab, el usuario tendrá una guia para practicar y aprender
conceptos basicos de las técnicas digitales, se trata de una trivia con
preguntas y respuestas y al finalizar, el usuario recibe un puntaje de
cual fue su rendimiento*/


#include <stdio.h>
#include <stdio_ext.h> /*para la funcion __fpurge*/
#include <stdlib.h> /*para la funcion atoi()*/
#include "edulab.h"

void modo_edulab(ptr_user_data new_user){ /*fijate como uso el alias ptr_user_data que defino en el edulab.h*/


   char leccion; /*aqui se va guardar la leccion que va elegir el usuario*/
   enum lexion tema; /*enumeracion definida en edulab.h puede valer de '1' a '4' con cada leccion*/


   const char *capitulos[] ={    /*si quiero cambiar el nombre de las lecciones aqui es donde*/
                             "Leccion #1 -> Bases Numericas.",
                             "Leccion #2 -> Compuertas Logicas.",
                             "Leccion #3 -> Algebra Booleana.",
                             "Leccion #4 -> Circuitos Combinaionales."
                            }; /*esto es un arreglo de punteros a char donde se guardan los nombres de las lecciones*/

   do{

      system("clear");

      printf("\n ###########################################################");
      printf("\n #                                                         #");
      printf("\n #                     MODO EDU-LAB                        #");
      printf("\n #                                                         #");
      printf("\n #           ELEGI UNA OPCION PARA CONTINUAR               #");
      printf("\n #                                                         #");
      for(tema = LECCION_1 ; tema <= LECCION_4 ; tema++){
      printf("\n #  %-40s               #", capitulos[tema - '1']); /*tengo que restarle '1'(en aski) porque el arreglo va de 0 a 3 nomas*/
      }
      printf("\n #                                                         #");
      printf("\n ###########################################################\n\n ? -> ");

      do{
         scanf(" %c", &leccion);
      }
      while(leccion < LECCION_1 || leccion > LECCION_4);/*esto hace que no ingrese valores basura*/

      printf("\n\n* %s, elegiste: %s\n", new_user -> user_name, capitulos[leccion - '1']);
      printf("* A continuación lee los apuntes y luego vamos a las preguntas.");
      printf("\n\n* Si estas listo, presiona ENTER para continuar\n");
      printf("* Si quieres cambiar de leccion presiona la letra \"v\"\n ? -> ");

      __fpurge(stdin); /* tira la cadena del stdin para que no joda el getchar*/
   }
   while(getchar() == 'v'); /*sale del while si no elige Volver "V" "*/

   switch(leccion)
   {
      case LECCION_1:
         system("xdg-open ./conf/leccion_1.pdf &"); /*dispara el apunte 1 en el lector de pdf predeterminado & para ejecucuin en segundo plano*/
         instrucciones(leccion); /*indica por pantalla como proceder*/
         preguntero(leccion, new_user);/*ejecuta el preguntero de la leccion elegida*/
      break;


      case LECCION_2:
         system("xdg-open ./conf/leccion_2.pdf &"); /*dispara el apunte 2 en el lector de pdf predeterminado - & en segundo plano*/
         instrucciones(leccion);
         preguntero(leccion, new_user);
      break;


      case LECCION_3:
         system("xdg-open ./conf/leccion_3.pdf &"); /*dispara el apunte 3 en el lector de pdf predeterminado*/
         instrucciones(leccion);
         preguntero(leccion, new_user);
      break;

      case LECCION_4:
         system("xdg-open ./conf/leccion_4.pdf &"); /*dispara el apunte 4 en el lector de pdf predeterminado*/
         instrucciones(leccion);
         preguntero(leccion, new_user);
      break;

   }

}
