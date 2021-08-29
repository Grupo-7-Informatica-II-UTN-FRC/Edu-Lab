#include <stdio.h>
#include <stdlib.h>
#include "minilab.h"


//uso este main para probar funciones que voy a utilizar en la biblioteca
int main (int argc, char *argv[]){
datos datos_1 = {0 ,"lean",{29}};

strcpy(datos_1.name, argv[1]);
//strcpy(datos_1.inout, "5";

time(&datos_1.data_time);
//printf("\n\t%s\n",ctime(&datos_1.data_time));

guardarDatos(datos_1);
leerDatos();

	return 0;

}
