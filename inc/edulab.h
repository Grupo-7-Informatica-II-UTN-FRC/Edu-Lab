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




#include <time.h> /* Me ayuda con la estructura time_t*/


#define TAM_NAME 15               /*notar que algunos son literal de caracter y otros son constantes normales*/
#define MODO_EDULAB '1'
#define MODO_TEST '2'
#define MODO_MINILAB '3'
#define MODO_CREDITOS '4'
#define SALIR_DEL_PROGRAMA '5'
#define RED 'r'
#define GREEN 'g'
#define BAUDRATE 9600





        /*++++++++++++++++++ DECLARACION DE VARIABLES Y STRUCTS +++++++++++++++*/



                    /*Estructura para guardar datos del usuario*/
struct usuario {
   time_t data_time;                /*Estructura definida en time.h: guarda la fecha*/
   char user_name[TAM_NAME];        /*Un arreglo de char para guardar el user name*/
   union{                           /*Una union de */
      unsigned char puerto_completo;/*Un byte entero para manejar todo el puerto*/
      struct{
         unsigned char in_0 : 1;    /*bit a bit para manipular el puerto*/
         unsigned char in_1 : 1;
         unsigned char in_2 : 1;
         unsigned char in_3 : 1;
         unsigned char out_0: 1;
         unsigned char out_1: 1;
         unsigned char padin: 2;    /*Rellena los espacios vacios para alinear datos: padding*/
       };
    }in_out;
};

typedef struct usuario user_data; /*alias a la estructura usuario*/
typedef user_data * ptr_user_data; /*alias de un puntero a la estruct usuario*/


      /*------------------ FIN DE LAS DECLARACIONES DE VARABLES Y STRUCTS ------------------*/




         /*++++++++++++++++ PROTOTIPADO DE FUNCIONES +++++++++++++++++++++++++++*/

void bienvenida(void);
void despedida(void);
void modo_edulab(ptr_user_data new_user);
void modo_test(ptr_user_data new_user);
void modo_minilab(ptr_user_data new_user);
void modo_creditos(ptr_user_data new_user);
void instrucciones(char);
void preguntero(char, user_data * new_user);
void conclusion(user_data * new_user, int calif, char lecc);
void correcta(int * const good, user_data * new_user, int file_desc); /*puntero constante a dato no constante*/
void falsa(user_data * new_user, int file_desc);
void parpadio (const char color, int file_desc);

        /*------------- FIN DEL PROTOTIPADO DE FUNCIONES -----------------------*/




        /*-----------------ENUMERACIONES UTILES-------------------------*/

enum lexion {LECCION_1 = '1', LECCION_2, LECCION_3, LECCION_4};/*recordar que aqui el literal de cadena '1' es un 49 en ascii*/
enum question {PREGUNTA_1 = 1, PREGUNTA_2, PREGUNTA_3, PREGUNTA_4, PREGUNTA_5, PREGUNTA_6, PREGUNTA_7, PREGUNTA_8, PREGUNTA_9, PREGUNTA_10};


         /*----------FIN DE LAS ENUMERACIONES-------------------*/
