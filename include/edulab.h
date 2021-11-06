/*
 * ============================================================================
 *
 * NOMBRE       : edulab.h
 * AUTOR        : José Blanco 83621
 * Version      : 1.0
 * Descripción  : archivo cabecera de la biblioteca edulab
 * FECHA        : 30 08 21
 *
 * ============================================================================
 */




#include<time.h> /* Me ayuda con la estructura time_t*/

#define TAM_NAME 15
#define MODO_EDULAB '1'
#define MODO_TEST '2'
#define MODO_MINILAB '3'
#define SALIR_DEL_PROGRAMA '4'






        /*++++++++++++++++++ DECLARACION DE VARIABLES Y STRUCTS +++++++++++++++*/



                    /*Estructura para guardar datos del usuario*/
struct USUARIO {
   time_t data_time;                /*Estructura definida en time.h: guarda la fecha*/
   char user_name[TAM_NAME];        /*Un arreglo de char para guardar el user name*/
   union{                           /*Una union de */
      unsigned char puerto_completo;/*Un byte entero para manejar todo el puerto*/
      struct{
         unsigned char in_1 : 1;    /*bit a bit para manipular el puerto*/
         unsigned char in_2 : 1;
         unsigned char in_3 : 1;
         unsigned char in_4 : 1;
         unsigned char out_1: 1;
         unsigned char out_2: 1;
         unsigned char padin: 2;    /*Rellena los espacios vacios para alinear datos: padding*/
       };
    }in_out;
};

typedef struct USUARIO user_data;



      /*------------------ FIN DE LAS DECLARACIONES DE VARABLES Y STRUCTS ------------------*/




         /*++++++++++++++++ PROTOTIPADO DE FUNCIONES +++++++++++++++++++++++++++*/

void bienvenida(void);
void despedida(void);
void modo_edulab(user_data *);
void modo_test(user_data *);
void modo_minilab(user_data *);

        /*------------- FIN DEL PROTOTIPADO DE FUNCIONES -----------------------*/
