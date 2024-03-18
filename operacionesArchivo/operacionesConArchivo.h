#ifndef operacionesConArchivo

#define operacionesConArchivo

//crea varios trozos de la cadena utilizando como delimitador el guion medio
int trocearCadena(char *cadena, char *trozos[]);
/*Mueve el archivo*/
void moverArchivo(char *filename,char archivo[], char directorioDestino[]);
//operamos segun el año del archivo
//Usamos
int calcularAno(char *cadena);
void processYear(char *filename, char *trozos[], int contador, char *directorioOperacion);

#include "operacionesConArchivo.c"

#endif