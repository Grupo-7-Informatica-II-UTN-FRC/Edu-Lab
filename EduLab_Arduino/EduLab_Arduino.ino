//----------------------------------headers----------------------------------------
#include <Wire.h>      // libreria de comunicacion por I2C
#include <LCD.h>      // libreria para funciones de LCD
#include <LiquidCrystal_I2C.h>    // libreria para LCD por I2C


//-------------------------constantes simbolicas------------------------------------

#define PIN_5 5
#define PIN_9 9
#define EN_ESPERA 0 //es un espacio en blanco literal de caracter: el 32 es ascii.
#define COLUMNAS 16
#define FILAS 2
#define EDU_LAB 1
#define TEST 2
#define MINILAB 3
#define GREEN 'g'
#define RED 'r'

//------------------------------declaracion de la union------------------------------
typedef union serial_port
{
   unsigned char puerto_completo;/*Un byte entero para recibir todo el puerto*/
   struct
   {
      unsigned char in_0 : 1;    /*bit a bit para manipular el puerto*/
      unsigned char in_1 : 1;
      unsigned char in_2 : 1;
      unsigned char in_3 : 1;
      unsigned char out_0: 1;
      unsigned char out_1: 1;
      unsigned char modes: 2;    /*modo que envia el byte*/
   };
}byte_recibido;


//-----------------------------defino variables globales----------------------------

int red = PIN_9, green = PIN_5; //asocia los led con los pines.
int entrada_1 = 10, entrada_2 = 11, entrada_3 = 12, entrada_4 = 13, salida_1 = 2, salida_2 = 3;
char flag = 0; /*bandera para limpliar el dysplay cuando sale del modo*/
unsigned char mode; /*este char se va usar para entrar al swich segun el modo enviado por el puerto serie*/
byte_recibido option = {EN_ESPERA}; //define una variable de tipo union serial_port y la inicializa en cero.

LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7); // DIR, E, RW, RS, D4, D5, D6, D7

 
//-------------------------------setup----------------------------------------------
void setup()
{
   lcd.setBacklightPin(3,POSITIVE);  // puerto P3 de PCF8574 como positivo
   lcd.setBacklight(HIGH);   // habilita iluminacion posterior de LCD
   lcd.begin(COLUMNAS, FILAS);     // 16 columnas por 2 lineas para LCD 1602A
   lcd.clear();      // limpia pantalla lcd
   
   Serial.begin(9600);
   
   pinMode(red, OUTPUT);  //configura los pines de los leds como salidas.
   pinMode(green, OUTPUT);
   digitalWrite(red, HIGH);// apaga ambos leds rojo y verde porque es logica negativa.
   digitalWrite(green, HIGH);
   pinMode(entrada_1, OUTPUT);
   pinMode(entrada_2, OUTPUT);
   pinMode(entrada_3, OUTPUT);
   pinMode(entrada_4, OUTPUT);
   pinMode(salida_1, INPUT);
   pinMode(salida_2, INPUT);
}


//-----------------------------bucle infinito------------------------------------
void loop()
{
   if(flag == 0)
   {   
      lcd.clear();// limpia pantalla lcd
      flag++;
   }
   
   lcd.setCursor(3, 0);    // ubica cursor en columna 0 y linea 0
   lcd.print("TIME LAPSED");  // escribe el texto
   lcd.setCursor(0, 1);    // ubica cursor en columna 0 y linea 1
   lcd.print(millis() / 1000);   // funcion millis() / 1000 para segundos transcurridos
   lcd.print(" seg.");     // escribe seg.

   if(Serial.available() != 0) //pregunta si hay algo para enviar
   {
      option.puerto_completo = Serial.read(); //guarda lo que envie el puerto serie en la union
      mode = option.puerto_completo;

      switch(mode >> 6) //si llega una g: 01100111 lo desplaza a la deracha 00000001 y queda en modo 01 edulab.
      {                 //si llega        10XXXXXX lo desplaza a la derecha 00000010 y queda en modo 02 test.
                        //si llega        11XXXXXX lo desplaza a la derecha 00000011 y queda en modo 03 minilab.
         case EDU_LAB:  

         if(option.puerto_completo == RED)
         {
            lcd.clear();      // limpia pantalla lcd
            lcd.setCursor(3, 0);    // ubica cursor en columna 0 y linea 0
            lcd.print(":( FALSA...");  // escribe el texto
      
            for(int i = 0 ; i < 1 ; i++)
            {
               digitalWrite(red, LOW);
               delay(1000);
               digitalWrite(red, HIGH);
               delay(1000);
            }
         }

         else if(option.puerto_completo == GREEN)
         {
            lcd.clear();      // limpia pantalla lcd
            lcd.setCursor(3, 0);    // ubica cursor en columna 0 y linea 0
            lcd.print("CORRECTA!!!");  // escribe el texto

            for(int i = 0 ; i < 6 ; i++)
            {
               digitalWrite(green, LOW);
               delay(70);
               digitalWrite(green, HIGH);
               delay(70);
            }
         }
         flag = 0; //reinicia la bandera para que se borre el display.

         break;
//---------------------------------------------------------------------------------------------------
         case TEST:

         lcd.clear();
         lcd.setCursor(0, 0);    // ubica cursor en columna 0 y linea 0
         lcd.print("   MODO TEST");  // escribe el texto 
         delay(1000);
         lcd.setCursor(0, 1);    // ubica cursor en columna 3 y linea 1
         lcd.print("Probando comp..");  // escribe el texto 
         delay(1000);

         digitalWrite(entrada_1,option.in_0);
         digitalWrite(entrada_2,option.in_1);
         digitalWrite(entrada_3,option.in_2);
         digitalWrite(entrada_4,option.in_3);
         option.out_0 = digitalRead(salida_1);
         option.out_1 = digitalRead(salida_2);

         Serial.write(option.puerto_completo);
         
         lcd.clear();
         lcd.setCursor(0, 0);    // ubica cursor en columna 0 y linea 0
         lcd.print("   MODO TEST");  // escribe el texto 
         lcd.setCursor(0, 1);    // ubica cursor en columna 0 y linea 1
         lcd.print("Transmitiendo..");  // escribe el texto 
         delay(1500);

         lcd.clear();
         lcd.setCursor(0, 0);    // ubica cursor en columna 0 y linea 0
         lcd.print("   MODO TEST");  // escribe el texto 
         lcd.setCursor(0, 1);    // ubica cursor en columna 0 y linea 1
         lcd.print("Transmitiendo..");  // escribe el texto 
         delay(1500);

         lcd.clear();
         lcd.setCursor(0, 0);    // ubica cursor en columna 0 y linea 0
         lcd.print("I1 I2 I3 I4  1 2");  // escribe el texto 
         lcd.setCursor(0, 1);    // ubica cursor en columna 0 y linea 1
         lcd.print(option.in_0); // escribe el texto
         lcd.setCursor(3, 1);    // ubica cursor en columna 3 y linea 1
         lcd.print(option.in_1); // escribe el texto         
         lcd.setCursor(6, 1);    // ubica cursor en columna 6 y linea 1
         lcd.print(option.in_2); // escribe el texto         
         lcd.setCursor(9, 1);    // ubica cursor en columna 9 y linea 1
         lcd.print(option.in_3);  // escribe el texto         
         lcd.setCursor(13, 1);    // ubica cursor en columna 13 y linea 1
         lcd.print(option.out_0);  // escribe el texto
         lcd.setCursor(15, 1);    // ubica cursor en columna 15 y linea 1
         lcd.print(option.out_1);  // escribe el texto 
         delay(6000);
                  
         flag = 0;
         
         break;
//---------------------------------------------------------------------------------------------------
         case MINILAB:
         lcd.clear();
         lcd.setCursor(0, 0);    // ubica cursor en columna 0 y linea 0
         lcd.print("   MODO MINILAB");  // escribe el texto 
         delay(1000);

         digitalWrite(entrada_1,option.in_0);
         digitalWrite(entrada_2,option.in_1);
         digitalWrite(entrada_3,option.in_2);
         digitalWrite(entrada_4,option.in_3);
         option.out_0 = digitalRead(salida_1);
         option.out_1 = digitalRead(salida_2);

         lcd.clear();
         lcd.setCursor(0, 0);    // ubica cursor en columna 0 y linea 0
         lcd.print("   MODO MINILAB");  // escribe el texto 
         //delay(1000);
         lcd.setCursor(0, 1);    // ubica cursor en columna 3 y linea 1
         lcd.print("Probando comp..");  // escribe el texto 
         delay(1500);
         
         Serial.write(option.puerto_completo);
         
         lcd.clear();
         lcd.setCursor(0, 0);    // ubica cursor en columna 0 y linea 0
         lcd.print("   MODO MINILAB");  // escribe el texto 
         lcd.setCursor(0, 1);    // ubica cursor en columna 0 y linea 1
         lcd.print("Transmitiendo..");  // escribe el texto 
         delay(1500);

         lcd.clear();
         lcd.setCursor(0, 0);    // ubica cursor en columna 0 y linea 0
         lcd.print("I1 I2 I3 I4  1 2");  // escribe el texto 
         lcd.setCursor(0, 1);    // ubica cursor en columna 0 y linea 1
         lcd.print(option.in_0); // escribe el texto
         lcd.setCursor(3, 1);    // ubica cursor en columna 3 y linea 1
         lcd.print(option.in_1); // escribe el texto         
         lcd.setCursor(6, 1);    // ubica cursor en columna 6 y linea 1
         lcd.print(option.in_2); // escribe el texto         
         lcd.setCursor(9, 1);    // ubica cursor en columna 9 y linea 1
         lcd.print(option.in_3);  // escribe el texto         
         lcd.setCursor(13, 1);    // ubica cursor en columna 13 y linea 1
         lcd.print(option.out_0);  // escribe el texto
         lcd.setCursor(15, 1);    // ubica cursor en columna 15 y linea 1
         lcd.print(option.out_1);  // escribe el texto 
         delay(5000);
                  
         flag = 0;
         digitalWrite(entrada_1,LOW);
         digitalWrite(entrada_2,LOW);
         digitalWrite(entrada_3,LOW);
         digitalWrite(entrada_4,LOW);
         break;
      }   
      delay(10);
   
   }

}
