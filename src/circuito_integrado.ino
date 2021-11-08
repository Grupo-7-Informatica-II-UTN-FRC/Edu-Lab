//programa para comprobar funcionamiento de compuertas logicas AND, OR, NAND entre otras en circuitos inetgrados
//de 2 entradas y 1 salida.
//Grupo 7.
//Edu_Lab -> modo_test.


char option = ' ';
int salida_A = 12, salida_B = 11, salida_led = 3, entrada_Y = 2;

void setup(){
  pinMode(entrada_Y, INPUT);    //salida de señal de compuerta logica a entrada pin digital 2.
  pinMode(salida_led, OUTPUT);  //salida de señal comprobada a catodo del led.
  pinMode(salida_A, OUTPUT);    //salida señal de pin digital 12 a pulsador mecanico A.
  pinMode(salida_B, OUTPUT);    //salida señal de pin digital 11 a pulsador mecanico B.
}

void loop()
{
  digitalWrite(salida_A, HIGH); //establecer salidas a pulsadores en alto (1).
  digitalWrite(salida_B, HIGH); //establecer salidas a pulsadores en alto (1).
  
  if (digitalRead(entrada_Y) == HIGH){ //condicion de verificacion de estado de la salida de la compuerta logica proveniente del integrado.
  digitalWrite(salida_led, HIGH); //de ser 1, envia señal de encendido a led.
  }
  else{
  digitalWrite(salida_led, LOW); //de ser 0, no envia ninguna señal de activacion.
  }
  delay(10);
}
