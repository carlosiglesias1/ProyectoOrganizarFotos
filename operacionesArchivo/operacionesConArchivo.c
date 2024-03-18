#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../creaDirectorio/crearDirectorio.h"

/**
 * HEADER
 */

int trocearCadena(char *cadena, char *trozos[]);

int calcularAno(char *cadena);

void moverArchivo(char *filename, char archivo[], char directorioDestino[]);

void processYear(char *filename, char *trozos[], int contador, char *directorioOperacion);

/**
 * BODY
 */

int trocearCadena(char *cadena, char *trozos[])
{
    int i = 1;
    
    //se trocea la cadena utilizando como delimitador el guion medio
    if ((trozos[0] = strtok(cadena, "-")) == NULL)
        return 0;
    while ((trozos[i] = strtok(NULL, "-")) != NULL)
        i++;
    return i;
}

int calcularAno(char *cadena)
{
    char ano[8];
    
    strcpy(ano, cadena);
    ano[strlen(ano) - 4] = '\0';
    return atoi(ano);
}

void processYear(char *filename, char *trozos[], int contador, char *directorioOperacion)
{
    char yearBuffer[5];
    char destino[255];
    char origen[100];
    int ano = calcularAno(trozos[1]);

    printf("%30d\n", ano);
    
    sprintf(yearBuffer, "%d", ano);
    strcpy(origen, directorioOperacion);
    strcat(origen, "/");
    strcat(origen, filename);

    strcpy(destino, directorioOperacion);
    strcat(destino, "/");
    strcat(destino, yearBuffer);

    printf("\tMovemos desde %s a %s/%s\n", origen, destino, filename);

    if (ano >= contador)
    {
        contador = ano;
        printf("%d\n", contador);
        if (createDirectory(destino) != 0)
        {
            if (errno == 17)
                moverArchivo(filename, origen, destino);
            else
                perror("Operation failed: ");
        }
        else
            moverArchivo(filename, origen, destino);
    }
    else {
        moverArchivo(filename, origen, destino);
    }
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