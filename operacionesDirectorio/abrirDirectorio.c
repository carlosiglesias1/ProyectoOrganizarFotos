#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int main()
{
    DIR *dir;
    struct dirent *ent;
    dir = opendir("../Fotos_de_prueba");
    int counter = 0;
    if (dir == NULL)
        printf("No puedo abrir el directorio");
    while ((ent = readdir(dir)) != NULL)
    {
        if ((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
        {
            counter++;
        }
    }
    printf("%d", counter);
    return EXIT_SUCCESS;
}