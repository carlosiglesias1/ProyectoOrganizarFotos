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
    int dir_result = mkdir(direccion, 0700);
    if (dir_result == 0 || dir_result == EEXIST)
        return EXIT_SUCCESS;
    else
        return errno;
}