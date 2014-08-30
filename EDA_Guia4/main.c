#include <stdio.h>
#include <stdlib.h>
#include "Png_compiler.h"
#include "lodepng.h"

/*	de la libreria lodepng se usaran solamente dos funciones
*	1) unsigned LodePNG_decode32_file(unsigned char** out, unsigned* w, unsigned* h,const char* filename);
*
*	2)unsigned LodePNG_encode32(unsigned char** out, size_t* outsize, const unsigned,char* image, unsigned w, unsigned h);
*/




int
main (int argc, char * agrv[]){
	CUADRADO valoresFoto;
	dataUsuario data={"foto.png",2};
	IMAGEN pngADecodificar;
	FILE* archivoAEscribir=NULL;
	int estado=0;
	

	//meter aca lo del parser para llennar data usuario chequear (como en el de los robots) que lo de la estrutura dataUsuario sea correcto

	estado=lodepng_decode32_file(&(pngADecodificar.imagen),&(pngADecodificar.ancho),&(pngADecodificar.alto),data.nombreArchivo);

	if(estado){		//luego de decodificar la imagen, chequeo si hubo errores
		printf("Hubo un error en el decodificado de la imagen. Finalizara el programa.\n");
		system ("pause");
		return ERROR;
	}

	//Debug
	printf("El ancho es %d,",pngADecodificar.ancho);
	printf("y el alto es %d.\n",pngADecodificar.alto);
	getchar();
	//End Debug
	

	//luego de la decodificacion debo verificar que sea una foto cuadrada y el tamaño de sus lados sea potencia de 2

	estado=analizarImagen(&pngADecodificar);

	if(estado){
		printf("No se analizara la imagen porque: no es cuadrada o su lado no es potencia de 2. Finalizara el programa.\n");
		system ("pause");
		return ERROR;
	}

	archivoAEscribir= fopen("CompressedPng.eda","wb");	//donde escribire mi arhivo
	if(archivoAEscribir==NULL){
		printf("Ocurrio un error en la creacion del archivo donde se comprimira la imagen. Finalizara el programa.\n");
		system ("pause");
		return ERROR;
	}

	valoresFoto.largo=pngADecodificar.alto;		//si pongo alto o ancho es lo mismo, yo quiero setear el "cuadrado inicial" al comienzo de la imagen
	valoresFoto.inicio.x=0;
	valoresFoto.inicio.y=0;


	//recursiva con la info 

	free(pngADecodificar.imagen);
	return 0;
}





