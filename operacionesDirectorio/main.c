#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "../operacionesArchivo/operacionesConArchivo.h"
#include "../creaDirectorio/crearDirectorio.h"

//set directory to open here
char *direccion = "C:/Users/carlo/Desktop/DAM1";

int main()
{
    DIR *dir;
    struct dirent *ent;
    char *trozos[5];
    int anoIni = 2000;
    dir = opendir(direccion);
    struct stat status;
    int counter = 0;
    if (dir == NULL)
        printf("No puedo abrir el directorio\n");
    while ((ent = readdir(dir)) != NULL)
    {
        if ((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
        {
            char archivo[strlen(ent->d_name)];
            strcpy(archivo, ent->d_name);
            if (trocearCadena(ent->d_name, trozos) > 1)
            {
                operarAno(archivo, trozos, anoIni, direccion);
            }
            printf("%30s\n", archivo);
            char *bigPath = _fullpath(NULL, ent->d_name, PATH_MAX);
            printf("%30s\n", bigPath);
            if (stat(bigPath, &status) == 0)
                printf((char *)ctime(&status.st_mtime));
            else
            {
                perror("Algo ha ocurrido: ");
            }
        }
        counter++;
    }
    closedir(dir);
    printf("%d\n", counter);
    return EXIT_SUCCESS;
}