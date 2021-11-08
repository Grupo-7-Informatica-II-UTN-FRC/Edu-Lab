/*En modo miniab, el usuario tendrá un laboratorio*/


#include <stdio.h>
#include <stdio_ext.h> 										/*para la funcion __fpurge*/
#include <stdlib.h>
#include "edulab.h"
#include <string.h>
#include "termset.h"										/*para configurar el puerto serie*/
#include <ctype.h>
#include <fcntl.h>											/*funciones de archivos de bajo nivel*/
#include <unistd.h>

#define	GUARDAR 1
#define	LEER 2
#define SALIR 3


//-------------------------------FUNCION	GUARDAR-----------------------------------------------//


void guardarDatos(user_data datos_1){ 				 		//guarda los datos leidos

int temp;


system("clear");
printf("\n\n\tHaz Seleccionado la opcion Guardar");
printf("\n\tEl controlador dispone de 4 entradas y dos salidas");
printf("\n\tPara continuar sera necesario indicar el estado que desea tener en las entradas");
printf("\n\tUna vez configurada las entradas guardaremos los datos recolectados");


do												//configurando entrada 1
{
	printf("\n\n\t(Estados: \"0\" o \"1\")");
	printf("\n\tEntrada Nº 1:");

	while(getchar()!='\n');
	scanf("%d",&temp);							

	if ((temp<0)||(temp>1))			//impide que carguen valores erroneos
	{
		printf("valor de temp = %d",temp);
		printf("\n\tSolo puedes elegir los valores \"0\" o \"1\"");
	}else{
		printf("\n\tCargando valor en in_0\n");
		datos_1.in_out.in_0=temp;
	}
} while ((temp<0)||(temp>1));			//impide que carguen valores erroneos





do												//configurando entrada 2
{
	printf("\n\n\t(Estados: \"0\" o \"1\")");
	printf("\n\tEntrada Nº 2:");

	while(getchar()!='\n');
	scanf("%d",&temp);							

	if ((temp<0)||(temp>1))			//impide que carguen valores erroneos
	{
		printf("valor de temp = %d",temp);
		printf("\n\tSolo puedes elegir los valores \"0\" o \"1\"");
	}else{
		printf("\n\tCargando valor en in_1\n");
		datos_1.in_out.in_1=temp;
	}
} while ((temp<0)||(temp>1));			//impide que carguen valores erroneos





do												//configurando entrada 3
{
	printf("\n\n\t(Estados: \"0\" o \"1\")");
	printf("\n\tEntrada Nº 3:");

	while(getchar()!='\n');
	scanf("%d",&temp);							

	if ((temp<0)||(temp>1))			//impide que carguen valores erroneos
	{
		printf("valor de temp = %d",temp);
		printf("\n\tSolo puedes elegir los valores \"0\" o \"1\"");
	}else{
		printf("\n\tCargando valor en in_2\n");
		datos_1.in_out.in_2=temp;
	}
} while ((temp<0)||(temp>1));			//impide que carguen valores erroneos





do												//configurando entrada 4
{
	printf("\n\n\t(Estados: \"0\" o \"1\")");
	printf("\n\tEntrada Nº 4:");

	while(getchar()!='\n');
	scanf("%d",&temp);							

	if ((temp<0)||(temp>1))			//impide que carguen valores erroneos
	{
		printf("valor de temp = %d",temp);
		printf("\n\tSolo puedes elegir los valores \"0\" o \"1\"");
	}else{
		printf("\n\tCargando valor en in_3\n");
		datos_1.in_out.in_3=temp;
	}
} while ((temp<0)||(temp>1));			//impide que carguen valores erroneos


//datos_1.in_out.puerto_completo=21;  // testing union
printf("\ndatos puerto completo:%d",datos_1.in_out.puerto_completo);
printf("\ndatos puerto in_0:%d",datos_1.in_out.in_0);
printf("\ndatos puerto in_1:%d",datos_1.in_out.in_1);
printf("\ndatos puerto in_2:%d",datos_1.in_out.in_2);
printf("\ndatos puerto in_3:%d",datos_1.in_out.in_3);
printf("\ndatos puerto out_0:%d",datos_1.in_out.out_0);
printf("\ndatos puerto out_1:%d",datos_1.in_out.out_1);
printf("\ndatos puerto padin:%d",datos_1.in_out.padin);


int fd;														//descriptor de archivo para el puerto serie 
fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_SYNC);		// esto abre y configura el puerto como de escritura y lectura
termset(fd, BAUDRATE, &ttyold, &ttynew);					// puerto serie
         
if(fd==-1){
	printf
	("\n\n\t ERROR AL ABRIR EL PUERTO ttyACM0");
}


write(fd,&datos_1.in_out.puerto_completo,1);
printf("\n\tEnviando datos al arduino..");

//system("sleep 1");

read(fd,&datos_1.in_out.puerto_completo,1);
printf("\n\tRecibiendo datos del arduino..");

//system("sleep 1");

time(&datos_1.data_time);

	//---------------------IMPRIME LOS VALORES QUE INGRESARON AL ARCHIVO-------------------//
	printf("\n\n%-12s%-7s%-7s%-7s%-7s%-7s%-7s%-25s\n", "Usuario", "IN 1", "IN 2", "IN 3", "IN 4", "out 1", "out 2","Fecha");
	printf("%-12s%-7d%-7d%-7d%-7d%-7d%-7d%-25s\n", datos_1.user_name, datos_1.in_out.in_0, datos_1.in_out.in_1, datos_1.in_out.in_2, datos_1.in_out.in_3, datos_1.in_out.out_0, datos_1.in_out.out_1, ctime(&datos_1.data_time) );


FILE *ptrf;

if (( ptrf = fopen ("datos.dat","ab"))==NULL){

	printf("/n/tEl archivo no pudo abrirse");
}
else{

	printf("\n\tGuardando datos..");
	fseek(ptrf,0,SEEK_END);									//posiciona el puntero al final
	fwrite(&datos_1,sizeof(user_data),1,ptrf);				//escribe datos en un archivo

	printf("\n\tCerrando archivo..");
	fclose (ptrf);											//cierra archivo

}

close(fd);													//Cerrando puerto serie


	printf("\n\n Presione enter para continuar");
    __fpurge(stdin);
    getchar();
	system("clear");
	
}








//-----------------------		FUNCION		LEER	--------------------------------------------//




void leerDatos(){											//lee los datos guardados

system("clear");

int i = 0;
char usuario_1[15] ;										//usuario a buscar
user_data datos_1 = {0, "pepe", {0}};							//estructura donde se guarda el archivo

printf("\n\n\tHaz seleccionado la opcion Leer");
printf("\n\tEn esta opcion podras ver los datos almacenados previamente");


FILE *ptrf;


/*
//----TEST----//
printf("\nhi 3\n");
system("sleep 1");
*/



if (( ptrf = fopen ("datos.dat","rb"))==NULL){
	printf("\n\n/tEl archivo no existe o no pudo abrirse");
}
else{
	
	printf("\n\tIngrese el nombre del usuario que desea ver: ");	
	while(getchar()!='\n');
	scanf("%[^\n]s", usuario_1);					//usuario a buscar
	

	
	
	while(usuario_1[i] != '\0') /*me pasa el alias todas a mayuscula hasta que llega al fin de cadena '\0'*/
   {
      usuario_1[i] = toupper(usuario_1[i]); /*lo hace letra por letra hasta que encuentra el fin de cadena*/
      i++;
   }




/*
	//----TEST----//
	printf("\nusuario --->%s<---\n\n",usuario_1);	
	printf("\ndato --->%s<---\n\n",datos_1.user_name);
*/




	while(getchar()!='\n');		


	printf("\n%-12s%-7s%-7s%-7s%-7s%-7s%-7s%-25s\n", "Usuario", "IN 1", "IN 2", "IN 3", "IN 4", "out 1", "out 2","Fecha");

	while(!feof(ptrf)){
	
		fread( &datos_1,sizeof(user_data),1,ptrf);


/*
//---- TEST ----//
printf("\n\nuser after reading --->%s<---\n",datos_1.user_name);	
printf("valor del strcmp:%d\n\n",(strcmp(usuario_1,datos_1.user_name))==0);
system("sleep 2");
*/


		if(((strcmp(usuario_1,datos_1.user_name))==0)){
			printf("%-12s%-7d%-7d%-7d%-7d%-7d%-7d%-25s", datos_1.user_name, datos_1.in_out.in_0, datos_1.in_out.in_1, datos_1.in_out.in_2, datos_1.in_out.in_3, datos_1.in_out.out_0, datos_1.in_out.out_1, ctime(&datos_1.data_time) );
		}
	}

	fclose (ptrf);

}


	printf("\n\n Presione enter para continuar");
    __fpurge(stdin);
    getchar();
	system("clear");
}







//---------------------------MODO MINILAB-----------------------------------------------------//

void modo_minilab(ptr_user_data new_user){
	int option =0;
	user_data datos_1;


//strcpy(new_user->user_name, "Test");


strcpy(datos_1.user_name, new_user->user_name);



   system("clear");


   printf("\n ###########################################################");
   printf("\n #                  MODO MINI-LAB       (MANU)             #");
   printf("\n #                                                         #");
   printf("\n #                                                         #");
   printf("\n #           ELIJA UNA OPCION PARA CONTINUAR               #");
   printf("\n #                                                         #");
   printf("\n ###########################################################");



    //printf("\n\n Presione enter para continuar");
    //__fpurge(stdin);
    //getchar();






//datos_1.in_out.puerto_completo=15;  // testing union
printf("\ndatos puerto completo:%d",datos_1.in_out.puerto_completo);
printf("\ndatos puerto in_0:%d",datos_1.in_out.in_0);
printf("\ndatos puerto in_1:%d",datos_1.in_out.in_1);
printf("\ndatos puerto in_2:%d",datos_1.in_out.in_2);
printf("\ndatos puerto in_3:%d",datos_1.in_out.in_3);
printf("\ndatos puerto out_0:%d",datos_1.in_out.out_0);
printf("\ndatos puerto out_1:%d",datos_1.in_out.out_1);
printf("\ndatos puerto padin:%d",datos_1.in_out.padin);





do{
printf("\n\n%-20s%-30s ","Opciones","Descripcion");

printf("\n%-20s%-30s ","1. Guardar","Guarda los datos obtenidos de la placa de desaarrollo");

printf("\n%-20s%-30s ","2. Leer","Lee Los datos previamente guardados");

printf("\n%-20s%-30s ","3. Salir","Volver al menu principar");

printf("\n\n\t--> ");
scanf("%d",&option);





if(option==GUARDAR){
guardarDatos(datos_1);
};


if(option==LEER){
leerDatos();
};



}while(option!=SALIR);

}