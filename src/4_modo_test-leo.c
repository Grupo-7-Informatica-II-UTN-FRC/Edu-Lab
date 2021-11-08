/*En modo test el usuario tendrá un banco de trabajo*/


#include <stdio.h>
#include <stdio_ext.h> /*para la funcion __fpurge*/
#include <stdlib.h> /*para la funcion atoi()*/
#include "edulab.h"

void modo_test(ptr_user_data new_user){ /*fijate como uso el alias ptr_user_data que defino en el edulab.h*/


   char prueba; /*aqui se va guardar la leccion que va elegir el usuario*/
   enum lexion tema; /*enumeracion definida en edulab.h puede valer de '1' a '4' con cada leccion*/

   const char *capitulos[] ={    /*si quiero cambiar el nombre de las lecciones aqui es donde*/
                             "Leccion #1 -> Compuerta logica AND.",
                             "Leccion #2 -> Compuerta logica OR.",
                             "Leccion #3 -> Compuerta logica NAND.",
                             "Leccion #4 -> Compuerta logica XOR."
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
         scanf(" %c", &prueba);
      }
      while(prueba < LECCION_1 || prueba > LECCION_4);/*esto hace que no ingrese valores basura*/

      printf("\n\n* %s, elegiste: %s\n", new_user -> user_name, capitulos[prueba - '1']);
      printf("* A continuación observa el diagrama de coneccion y vamos a trabajar!.");
      printf("\n\n* Si estas listo, presiona ENTER para continuar\n");
      printf("* Si quieres cambiar de prueba presiona la letra \"v\"\n ? -> ");

      __fpurge(stdin); /* tira la cadena del stdin para que no joda el getchar*/
   }
   while(getchar() == 'v'); /*sale del while si no elige Volver "V" "*/

   switch(prueba)
   {
      case LECCION_1:
         system("xdg-open ./conf/compuerta_and.pdf &"); /*dispara el apunte 1 en el lector de pdf predeterminado & para ejecucuin en segundo plano*/
         instruccionesTest(prueba); /*indica por pantalla como proceder*/
         instruccionesTest_2(prueba);
        // test (prueba, new_user); // ejecuta la prueba de circuito integrado
      break;


      case LECCION_2:
         system("xdg-open ./conf/compuerta_or.pdf &"); /*dispara el apunte 2 en el lector de pdf predeterminado - & en segundo plano*/
         instruccionesTest(prueba);
         instruccionesTest_2(prueba);
         //test (prueba, new_user); // ejecuta la prueba de circuito integrado
      break;


      case LECCION_3:
         system("xdg-open ./conf/ &"); /*dispara el apunte 3 en el lector de pdf predeterminado*/
         instruccionesTest(prueba);
         instruccionesTest_2(prueba);
         //test (prueba, new_user); // ejecuta la prueba de circuito integrado
      break;

      case LECCION_4:
         system("xdg-open ./conf/ &"); /*dispara el apunte 4 en el lector de pdf predeterminado*/
         instruccionesTest(prueba);
         instruccionesTest_2(prueba);
        // test (prueba, new_user); // ejecuta la prueba de circuito integrado
      break;

   }

}
