#include <stdlib.h>

/* 
MODO Mini-Lab el usuario podrá configurar los estímulos de manera manual, cada estímulo enviado y cada respuesta recibida, tendrá opción de quedar documentada en un archivo que se almacenará en un archivo de texto (.txt) en el ordenador o PC. El Mini-Lab trabajará en este modo como un asistente de ensayos, facilitando las pruebas que el usuario realice en el circuito.
*/
struct DATOS {
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

typedef struct DATOS datos;

void guardarDatos(datos datos_1){

FILE *ptrf;

if (( ptrf = fopen ("datos.txt","ab"))==NULL){

	printf("/n/tEl archivo no existe o no pudo abrirse");
}
else{

	fseek(ptrf,0,SEEK_END);
	fwrite( &datos_1,sizeof(datos),1,ptrf);

	fclose (ptrf);

}
}



void leerDatos(){

char usuario[15] ;	
datos datos_1 = { "name",{13}};

FILE *ptrf;

if (( ptrf = fopen ("datos.txt","rb"))==NULL){

	printf("/n/tEl archivo no existe o no pudo abrirse");
}
else{

	printf("\n\t Ingrese su usuario: ");
	scanf("%[^\n]s", usuario);
	printf(" --->%s<---\n\n",usuario);
	
	printf("%-15s%-7s%-7s%-7s%-7s%-7s%-7s \n", "Usuario", "IN 1", "IN 2", "IN 3", "IN 4", "out 1", "out 2");

	while(!feof(ptrf)){
	
		fread( &datos_1,sizeof(datos),1,ptrf);
	
		if(usuario==datos_1.name){
			printf("%-15s%-7d%-7d%-7d%-7d%-7d%-7d\n",datos_1.name,datos_1.inout.in_1,datos_1.inout.in_2,datos_1.inout.in_3,datos_1.inout.in_4,datos_1.inout.out_1,datos_1.inout.out_2);

		}
	}
	fclose (ptrf);

}
}

