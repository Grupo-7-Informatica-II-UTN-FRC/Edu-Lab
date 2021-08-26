/*
MODO Mini-Lab el usuario podrá configurar los estímulos de manera manual, cada estímulo enviado y cada respuesta recibida, tendrá opción de quedar documentada en un archivo que se almacenará en un archivo de texto (.txt) en el ordenador o PC. El Mini-Lab trabajará en este modo como un asistente de ensayos, facilitando las pruebas que el usuario realice en el circuito.
*/
struct DATOS {
char name[20];
int in_1;
int in_2;
int in_3;
int in_4;
int out_1;
int out_2;
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



void leerDatos(datos datos_1){

FILE *ptrf;

if (( ptrf = fopen ("datos.txt","rb"))==NULL){

	printf("/n/tEl archivo no existe o no pudo abrirse");
}
else{

	printf("%-15s%-5s%-5s%-5s%-5s%-5s%-5s","Usuario","IN_1","IN_2","IN_3""IN_4","out_1","out_2");

	while(!feof(ptrf)){
	
		fread( &datos_1,sizeof(datos),1,ptrf);
		printf("%-15s%-5d%-5d%-5d%-5d%-5d%-5d",datos_1.name,datos_1.in_1,datos_1.in_2,datos_1.in_3,datos_1.in_4,datos_1.out_1,datos_1.out_2);

	}
	fclose (ptrf);

}
}

