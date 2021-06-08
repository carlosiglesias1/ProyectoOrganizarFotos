#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "../creaDirectorio/crearDirectorio.h"
//crea varios trozos de la cadena utilizando como delimitador el guion medio
int trocearCadena(char *cadena, char *trozos[]);
/*Mueve el archivo*/
void moverArchivo(char archivo[], char directorioDestino[]);
//operamos segun el año del archivo
//Usamos
int calcularAno(char *cadena);
void operarAno(char *trozos[], int contador);

int main()
{
    char cadena[] = "IMG-20180303-WA0005.jpg";
    char *trozos[5];
    trocearCadena(cadena, trozos);
    printf("%s ---> %s\n", trozos[0], trozos[1]);
    operarAno(trozos, 2015);
}

int trocearCadena(char *cadena, char *trozos[])
{
    int i = 1;

    if ((trozos[0] = strtok(cadena, "-")) == NULL) //se trocea la cadena utilizando como delimitador el guion medio
        return 0;
    while ((trozos[i] = strtok(NULL, "-")) != NULL)
        i++;
    return i;
}

void moverArchivo(char archivo[], char directorioDestino[])
{
    char destination[250];
    strcpy(destination, directorioDestino);
    strcat(destination, "/");
    strcat(destination, archivo);
    printf("%s\n", destination);
    if (rename(archivo, destination) != -1)
    {
        printf("Success");
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

void operarAno(char *trozos[], int contador)
{
    char * folder;
    int ano = calcularAno(trozos[1]);
    printf("%d\n", ano);
    if (ano > contador)
    {
        itoa(ano, folder, 10);
        if (createDirectory(folder) != 0)
        {
            if (errno == 17)
                moverArchivo("IMG-20180303-WA0005.jpg", folder);
            else
                perror("Operation failed");
        }
        else
            moverArchivo("IMG-20180303-WA0005.jpg", folder);
    }
    else
        printf("El año es menor");
    printf("JODER");
}