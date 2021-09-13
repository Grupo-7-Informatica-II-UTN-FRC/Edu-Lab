#include <stdlib.h>
#include <string.h>
#include <time.h> 
#define nombre 15

/* 
MODO Mini-Lab el usuario podrá configurar los estímulos de manera
manual, cada estímulo enviado y cada respuesta recibida, tendrá 
opción de quedar documentada en un archivo que se almacenará en 
un archivo de texto (.txt) en el ordenador o PC. El Mini-Lab 
trabajará en este modo como un asistente de ensayos, facilitando 
las pruebas que el usuario realice en el circuito.
*/

void guardarDatos(user_data * datos_1){ //guarda los datos leidos

FILE *ptrf;

if (( ptrf = fopen ("datos.dat","ab"))==NULL){

	printf("/n/tEl archivo no pudo abrirse");
}
else{

	fseek(ptrf,0,SEEK_END);									//posiciona el puntero al final
	fwrite(&datos_1,sizeof(user_data),1,ptrf);	//escribe datos en un archivo

	fclose (ptrf);													//cierra archivo

}
}



void leerDatos(){											//lee los datos guardados

char usuario_1[TAM_NAME] ;										//usuario a buscar
datos_usuario datos_1 = {0, "", {0}};					//estructura donde se guarda el archivo

FILE *ptrf;

if (( ptrf = fopen ("datos.dat","rb"))==NULL){

	printf("/n/tEl archivo no existe o no pudo abrirse");
}
else{

	printf("\n\t Ingrese su usuario: ");	
	scanf("%[^\n]s", usuario_1);					//usuario a buscar
	system("clear");
//	printf(" --->%s<---\n\n",usuario);	
//	printf(" --->%s<---\n\n",datos_1.name);

	while(getchar()!='\n');		


	printf("%-12s%-7s%-7s%-7s%-7s%-7s%-7s%-25s\n", "Usuario", "IN 1", "IN 2", "IN 3", "IN 4", "out 1", "out 2","Fecha");

	while(!feof(ptrf)){
	
		fread( &datos_1,sizeof(user_data),1,ptrf);
//printf("\n\n --->%s<---\n\n",datos_1.name);	
		if(((strcmp(usuario_1,datos_1.user_name))==0)||((strcmp(usuario_1,"todos"))==0)){
			printf("%-12s%-7d%-7d%-7d%-7d%-7d%-7d%-25s", datos_1.user_name, datos_1.inout.in_1, datos_1.inout.in_2, datos_1.inout.in_3, datos_1.inout.in_4, datos_1.inout.out_1, datos_1.inout.out_2, ctime(&datos_1.data_time) );

		}
	}
	fclose (ptrf);

}
}

