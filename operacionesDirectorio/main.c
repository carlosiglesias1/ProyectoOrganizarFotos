#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include "../operacionesArchivo/operacionesConArchivo.h"
#include "../creaDirectorio/crearDirectorio.h"

#define MAX_SIZE_STRING 256

char* getRootDirectory(){
    char *directory = malloc(MAX_SIZE_STRING);

    fgets(directory, MAX_SIZE_STRING, stdin);
    directory[strlen(directory) - 1] = '\0';

    return directory;
}

int realPath(char *filename){
    char pathBuffer[PATH_MAX];
    return realpath(filename, pathBuffer);
}

int main()
{
    DIR *dir;
    char *trozos[5];
    char *realFilePath;
    char *direccion = getRootDirectory();
    char currentFile[256];
    struct dirent *ent;
    struct stat status;
    int anoIni = 2000;
    int counter = 0;

    dir = opendir(direccion);

    if (dir == NULL || dir == 0x0){
        printf("No puedo abrir el directorio\n");
        return -1;
    }
    while ((ent = readdir(dir)) != NULL)
    {
        if ((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
        {
            strcpy(currentFile, ent->d_name);
            if (trocearCadena(ent->d_name, trozos) > 1)
            {
                processYear(currentFile, trozos, anoIni, direccion);
            }
            printf("%30s\n", currentFile);

            //realpath(ent->d_name, realFilePath);

            realFilePath = realPath(ent->d_name);
            printf("%30s\n", realFilePath);
            if (stat(realFilePath, &status) == 0)
                printf("%100s", (char *)ctime(&status.st_mtime));
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