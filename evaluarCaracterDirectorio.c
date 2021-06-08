#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

/* Función para devolver un error en caso de que ocurra */
void error(const char *s);
/* Función que hace algo con un archivo */
void procesoArchivo(char *archivo);
/*Si es distinto en el año, creará un directorio*/
void evaluarCaracter(char nombre[]);
/*Mueve el archivo*/
void moverArchivo(char archivo[], char directorioDestino[]);
/*
    En caso de que se active moverArchivo, este moverá el archivo al nuevo directorio
*/
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
/*
Evaluamos el caracter que marcará la diferencia, en este caso el número final del año de la fecha
*/
void evaluarCaracter(char nombre[])
{
    if (nombre[11] == '1')
    {
        printf("Entra\n");
        char directorio[100];
        strcpy(directorio, "2021");
        printf("%s\n", directorio);
        if (mkdir(directorio) == -1)
        {
            if (errno == 17)
            {
                moverArchivo(nombre, directorio);
            }
            else
            {
                perror("fuck: ");
                printf("%d", errno);
            }
        }
        else
        {
            moverArchivo(nombre, directorio);
        }
    }
}

void procesoArchivo(char *archivo)
{
    char nombre[strlen(archivo)];
    strcpy(nombre, archivo);
    FILE *fich;
    long ftam;
    fich = fopen(archivo, "r");
    if (fich)
    {
        fseek(fich, 0L, SEEK_END);
        ftam = ftell(fich);
        fclose(fich);
        //Si todo va bien, decimos el tamaño
        printf("%30s (%ld bytes)\n", nombre, ftam);
        evaluarCaracter(nombre);
    }
    else
    {
        //Si ha pasado algo, sólo decimos el nombre
        printf("%30s (No info.)\n", nombre);
        evaluarCaracter(nombre);
    }
}

/*
Calculamos errores
*/
void error(const char *s)
{
    //perror() devuelve la cadena S y el error (en cadena de caracteres) que tenga errno
    perror(s);
    exit(EXIT_FAILURE);
}

void usarDirectorio(char *direccion)
{
    DIR *dir;
    struct dirent *ent;
    dir = opendir(direccion);
    if (dir == NULL)
        error("No puedo abrir el directorio");
    while ((ent = readdir(dir)) != NULL)
    {
        if ((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
        {
            procesoArchivo(ent->d_name);
        }
    }
    closedir(dir);
}

int main()
{
    char direccion[255];
    printf("Selecciona que directorio quieres procesar");
    scanf("%s", direccion);
    usarDirectorio(direccion);
    return EXIT_SUCCESS;
}