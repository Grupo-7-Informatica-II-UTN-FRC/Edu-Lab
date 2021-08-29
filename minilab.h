#include <stdlib.h>
#include <string.h>
#include <time.h> 

/* 
MODO Mini-Lab el usuario podrá configurar los estímulos de manera
manual, cada estímulo enviado y cada respuesta recibida, tendrá 
opción de quedar documentada en un archivo que se almacenará en 
un archivo de texto (.txt) en el ordenador o PC. El Mini-Lab 
trabajará en este modo como un asistente de ensayos, facilitando 
las pruebas que el usuario realice en el circuito.
*/
struct DATOS {     		//Estructura para guardar datos IO
	time_t data_time;
	char name[15];
		union{
			unsigned int io_6 : 6;
			struct{
				unsigned int in_1 : 1;
				unsigned int in_2 : 1;
				unsigned int in_3 : 1;
				unsigned int in_4 : 1;
				unsigned int out_1: 1;
				unsigned int out_2: 1;
			};
		}inout;
};

typedef struct DATOS datos; 							//simplificacion para declarar "DATOS"

void guardarDatos(datos datos_1){ 				 //guarda los datos leidos

FILE *ptrf;

if (( ptrf = fopen ("datos.dat","ab"))==NULL){

	printf("/n/tEl archivo no existe o no pudo abrirse");
}
else{

	fseek(ptrf,0,SEEK_END);									//posiciona el puntero al final
	fwrite(&datos_1,sizeof(datos),1,ptrf);	//escribe datos en un archivo

	fclose (ptrf);													//cierra archivo

}
}



void leerDatos(){											//lee los datos guardados

char usuario[15] ;										//usuario a buscar
datos datos_1 = {0, "", {0}};					//estructura donde se guarda el archivo

FILE *ptrf;

if (( ptrf = fopen ("datos.dat","rb"))==NULL){

	printf("/n/tEl archivo no existe o no pudo abrirse");
}
else{

	printf("\n\t Ingrese su usuario: ");	
	scanf("%[^\n]s", usuario);					//usuario a buscar
	system("clear");
//	printf(" --->%s<---\n\n",usuario);	
//	printf(" --->%s<---\n\n",datos_1.name);

	while(getchar()!='\n');		


	printf("%-12s%-7s%-7s%-7s%-7s%-7s%-7s%-25s\n", "Usuario", "IN 1", "IN 2", "IN 3", "IN 4", "out 1", "out 2","Fecha");

	while(!feof(ptrf)){
	
		fread( &datos_1,sizeof(datos),1,ptrf);
//printf("\n\n --->%s<---\n\n",datos_1.name);	
		if((strcmp(usuario,datos_1.name))==0){
			printf("%-12s%-7d%-7d%-7d%-7d%-7d%-7d%-25s", datos_1.name, datos_1.inout.in_1, datos_1.inout.in_2, datos_1.inout.in_3, datos_1.inout.in_4, datos_1.inout.out_1, datos_1.inout.out_2, ctime(&datos_1.data_time) );

		}
	}
	fclose (ptrf);

}
}

