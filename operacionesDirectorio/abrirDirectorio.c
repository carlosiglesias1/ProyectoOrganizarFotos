#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "../operacionesArchivo/operacionesConArchivo.h"
#include "../creaDirectorio/crearDirectorio.h"

//set directory to open here
char * direccion = "F:/Fotos/WhatsApp Images/Private";

int main()
{
    DIR *dir;
    struct dirent *ent;
    char *trozos[5];
    int anoIni = 2000;
    dir = opendir(direccion);
    int counter = 0;
    if (dir == NULL)
        printf("No puedo abrir el directorio");
    while ((ent = readdir(dir)) != NULL)
    {
        if ((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
        {
            char archivo[strlen(ent->d_name)];
            strcpy(archivo, ent->d_name);
            printf("%30s\n", archivo);
            if (trocearCadena(ent->d_name, trozos) > 0)
            {
                operarAno(archivo, trozos, anoIni, direccion);
            }

            counter++;
        }
    }
    closedir(dir);
    printf("%d\n", counter);
    return EXIT_SUCCESS;
}