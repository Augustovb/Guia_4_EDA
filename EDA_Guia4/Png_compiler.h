#ifndef PNG_COMPILER__H
#define PNG_COMPILER__H
/****************
*	Definiciones*
*****************/

#define ERROR -1


#define ROJO	0
#define VERDE	1
#define AZUL	2


/****************
*  TIPOS		*
****************/

typedef struct{
	int x;
	int y;

}PUNTO;		//vendria a representar la ubicacion de un pixel


typedef struct{
	PUNTO inicio;

	int largo;		//este largo hace referencia a la cantidad de pixeles que ocupara cada lado

}CUADRADO;



typedef struct {
	char * nombreArchivo;	//se debe hacer con malloc en el parser
	unsigned int umbral;		//umbral significa la "precision" en la diferencia de colores a medir

} dataUsuario;

/*Esta estructura sera util para "devolverle" la infomacion del decoder*/

typedef struct{
	unsigned int ancho;
	unsigned int alto;
	unsigned char* imagen;

} IMAGEN;



/****************
*   Funciones	*
****************/


/*	Analiza que sea una imagen cuadrada y luego que cada uno de los lados sea una potencia de 2
*
* Retorna un 0 si todo anduvo bien y otra constante si hubo un error (como que no se puede guardar la imagen comprimida)
*/

int analizarImagen (IMAGEN* imagen);


/*chequea si el numero recibido es una potencia de dos o no
*	devuelve un 0 en caso de que el numero recibido no sea potencia de dos, y un 1, si lo es
*
*/
int isThisAPowerOf2  (int number);




/*	Funcion recursiva encargada de la escritura del arhivo creado y la compresion de la imagen en el mismo
*
*	Retornara siempre 0 ya que no hay error posible.
*
*/

int analizarPNGConQuadTree (FILE* archivoEscritura, IMAGEN png,CUADRADO seccion,dataUsuario data);


/*
*		De una estructura cuadrado va cheueando los colores de los pixeles y realiza el promedio especificado
*
*
*/

unsigned int analizarColoresEnCuadrado(unsigned char* arregloDePixeles, CUADRADO seccion, unsigned int largoFoto);


/*retornan el minimo/maximo entre los dos caracteres enviados*/
unsigned char maxBetween (unsigned char c1, unsigned char c2);

unsigned char minBetween (unsigned char c1, unsigned char c2);

#endif