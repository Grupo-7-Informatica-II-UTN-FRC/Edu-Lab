char option = ' ';
int red = 9, green = 8, entrada_1 = 2, entrada_2 = 3, entrada_3 = 4, entrada_4 = 5, salida_1 = 11, salida_2 = 12;
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

void setup()

{
   // put your setup code here, to run once:
   Serial.begin(9600);
   pinMode(red, OUTPUT);
   pinMode(green, OUTPUT);
   digitalWrite(red, HIGH);
   digitalWrite(green, HIGH);

    pinMode(entrada_1, OUTPUT);
    pinMode(entrada_2, OUTPUT);
    pinMode(entrada_3, OUTPUT);
    pinMode(entrada_4, OUTPUT);
    
    pinMode(salida_1, INPUT);
    pinMode(salida_2, INPUT);
}

void loop()
{
  
  // put your main code here, to run repeatedly:
  
   if(Serial.available() != 0)
   {
     
     option = Serial.read();
          
     
     if((option!='g')&&(option!='r')){
     
       
      in_out.puerto_completo = option;    
          
          digitalWrite(entrada_1,in_out.in_0);
          digitalWrite(entrada_2,in_out.in_1);
          digitalWrite(entrada_3,in_out.in_2);
          digitalWrite(entrada_4,in_out.in_3);
          in_out.out_0 = digitalRead(salida_1);
          in_out.out_1 = digitalRead(salida_2);
  
  
    option = in_out.puerto_completo;  
    Serial.write(option);
    
     }
     
     
    if(option == 'r')
    {
      for(int i = 0 ; i < 1 ; i++)
      {
         digitalWrite(red, LOW);
         delay(1000);
         digitalWrite(red, HIGH);
         delay(1000);
      }
    }

    else if(option == 'g')
    {
      for(int i = 0 ; i < 6 ; i++)
      {
         digitalWrite(green, LOW);
         delay(70);
         digitalWrite(green, HIGH);
         delay(70);
      }
    }else {
     
     
  
  }
  
   delay(10);
   }
}
