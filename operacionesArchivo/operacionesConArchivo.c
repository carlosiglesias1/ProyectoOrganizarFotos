#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "../creaDirectorio/crearDirectorio.h"
//crea varios trozos de la cadena utilizando como delimitador el guion medio
int trocearCadena(char *cadena, char *trozos[]);
/*Mueve el archivo*/
void moverArchivo(char *filename, char archivo[], char directorioDestino[]);
//operamos segun el año del archivo
//Usamos
int calcularAno(char *cadena);
void operarAno(char *filename, char *trozos[], int contador, char *directorioOperacion);

int trocearCadena(char *cadena, char *trozos[])
{
    int i = 1;

    if ((trozos[0] = strtok(cadena, "-")) == NULL) //se trocea la cadena utilizando como delimitador el guion medio
        return 0;
    while ((trozos[i] = strtok(NULL, "-")) != NULL)
        i++;
    return i;
}

void moverArchivo(char *filename, char rutaArchivo[], char directorioDestino[])
{
    char destination[250];
    strcpy(destination, directorioDestino);
    strcat(destination, "/");
    strcat(destination, filename);
    printf("%s\n", rutaArchivo);
    printf("%s\n", destination);
    if (rename(rutaArchivo, destination) != -1)
    {
        printf("Success\n");
    }
    else
    {
        perror("Rename Fail ");
        printf("%d", errno);
    }
}

int calcularAno(char *cadena)
{
    char ano[8];
    strcpy(ano, cadena);
    ano[strlen(ano) - 4] = '\0';
    return atoi(ano);
}

void operarAno(char *filename, char *trozos[], int contador, char *directorioOperacion)
{
    char anoStr[strlen(trozos[1])];
    char folder[255] = "";
    char origen[100] = "";
    int ano = calcularAno(trozos[1]);
    printf("%30d\n", ano);
    strcpy(origen, directorioOperacion);
    strcat(origen, "/");
    strcat(origen, filename);
    strcpy(folder, directorioOperacion);
    strcat(folder, "/");
    strcat(folder, itoa(ano, anoStr, 10));
    printf("\tMovemos desde %s a %s/%s\n", origen, folder, filename);
    if (ano >= contador)
    {
        contador = ano;
        printf("%d\n", contador);
        if (createDirectory(folder) != 0)
        {
            if (errno == 17)
                moverArchivo(filename, origen, folder);
            else
                perror("Operation failed\n");
        }
        else
            moverArchivo(filename, origen, folder);
    }
    else
        moverArchivo(filename, origen, folder);
    printf("JODER\n");
}