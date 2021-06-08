#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "crearDirectorio.h"

int createDirectory();

int createDirectory(char * direccion)
{
    if (mkdir(direccion) == 0)
        return EXIT_SUCCESS;
    else
        return errno;
}