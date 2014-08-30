#include <stdio.h>
#include "Png_compiler.h"


int analizarImagen (IMAGEN* imagen){
	unsigned int width=0;
	unsigned int height=0;
	height=imagen->alto;
	width=imagen->ancho;
	if(width==height){
		if(isThisAPowerOf2(width)){
				return 0;
		} else {return ERROR;}


	} else {return ERROR;}
}





int isThisAPowerOf2  (int number){
	
	while((number%2)==0){
		number/=2;
	}
	if(number==1){
			return 1;
	} else {
			return 0;
		
	}
}



int analizarPNGConQuadTree (FILE* archivoEscritura, IMAGEN png,CUADRADO seccion,dataUsuario data){
	unsigned int promedio;
	CUADRADO seccion1=seccion;
	CUADRADO seccion2=seccion;
	CUADRADO seccion3=seccion;
	CUADRADO seccion4=seccion;
	promedio=analizarColoresEnCuadrado(png.imagen,seccion,png.ancho);
	if(promedio<data.umbral){
		fprintf(archivoEscritura,"(%d,%d,%d)",*(png.imagen+(seccion.inicio.x)*4+(seccion.inicio.y)*4*(png.ancho)+ROJO),*(png.imagen+(seccion.inicio.x)*4+(seccion.inicio.y)*4*(png.ancho)+VERDE),*(png.imagen+(seccion.inicio.x)*4+(seccion.inicio.y)*4*(png.ancho)+AZUL));		//escribo el color de cualquier parte del cuadrado (en 1 2 3 tengo que usar la tecnica sobre como escribir, y como separar, que use en la funcion de sacar el promedio)
		return 0;
	}
	else {
		fprintf(archivoEscritura,"R");
		seccion1.largo=(seccion1.largo)/2;		//si fuese ya un solo pixel, no hubiese entrado aca

		seccion2.largo=(seccion2.largo)/2;			//la seccion dos comienza (si fuese un cadrado) desde (L/2,0) siendo L el largo del cuadrado original
		seccion2.inicio.x+=(seccion2.largo)/2;

		seccion3.largo=(seccion3.largo)/2;			//comienza desde (0,L/2)
		seccion3.inicio.y+=(seccion3.largo)/2;

		seccion4.largo=(seccion4.largo)/2;			//desde (L/2,L/2)
		seccion4.inicio.x+=(seccion4.largo)/2;
		seccion4.inicio.y+=(seccion4.largo)/2;

		analizarPNGConQuadTree(archivoEscritura,png,seccion1,data);
		analizarPNGConQuadTree(archivoEscritura,png,seccion2,data);
		analizarPNGConQuadTree(archivoEscritura,png,seccion3,data);
		analizarPNGConQuadTree(archivoEscritura,png,seccion4,data);


	}
}





unsigned int analizarColoresEnCuadrado(unsigned char* arregloDePixeles, CUADRADO seccion, unsigned int largoFoto){
	unsigned char maxRed=0;
	unsigned char minRed=255;
	unsigned char maxGreen=0;
	unsigned char minGreen=255;
	unsigned char maxBlue=0;
	unsigned char minBlue=255;
	unsigned int i=0,j=0;

	for(i=0; i<(seccion.largo);++i){	//el por 4 es porque tengo que 

	for(j=0; j<(seccion.largo);++j){

		maxRed=maxBetween(maxRed,*(arregloDePixeles+(seccion.inicio.x)*4+(seccion.inicio.y)*4*largoFoto+i*(largoFoto)*4+j*4+ROJO));
		minRed=minBetween(minRed,*(arregloDePixeles+(seccion.inicio.x)*4+(seccion.inicio.y)*4*largoFoto+i*(largoFoto)*4+j*4+ROJO));
		maxGreen=maxBetween(maxGreen,*(arregloDePixeles+(seccion.inicio.x)*4+(seccion.inicio.y)*4*largoFoto+i*(largoFoto)*4+j*4+VERDE));
		minGreen=minBetween(minGreen,*(arregloDePixeles+(seccion.inicio.x)*4+(seccion.inicio.y)*4*largoFoto+i*(largoFoto)*4+j*4+VERDE));
		maxBlue=maxBetween(maxBlue,*(arregloDePixeles+(seccion.inicio.x)*4+(seccion.inicio.y)*4*largoFoto+i*(largoFoto)*4+j*4+AZUL));
		minBlue=minBetween(minBlue,*(arregloDePixeles+(seccion.inicio.x)*4+(seccion.inicio.y)*4*largoFoto+i*(largoFoto)*4+j*4+AZUL));
	}
// como voy barriendo? se que tengo una seccion con su inicio y largo
//el inicio lo tomare como un offset. el offset de y lo obtengo sumando este valor (que es el pixel) multiplicandolo por 4
//( ya que un pixel en el arreglo son 4 chars) y por el largo de la foto.
// el de x, simplemente sumandolo multiplicado por pixel. al igual, cmo cuando aanzo con i y j, i representa Y, y j X

}
	return ((int)(maxRed-minRed+maxGreen-minGreen+maxBlue-minBlue));
}



unsigned char maxBetween (unsigned char c1, unsigned char c2){
	int comparacion;
	comparacion= (int)(c1-c2);

	if(comparacion<=0){
		return c2;
	} else {
		return c1;
	}

}


unsigned char minBetween (unsigned char c1, unsigned char c2){

	int comparacion;
	comparacion= (int)(c1-c2);

	if(comparacion<=0){
		return c1;
	} else {
		return c2;
	}


}