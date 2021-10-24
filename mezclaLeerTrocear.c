#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

int abrirDirectorio();
void procesoArchivo();
int trocearCadena();

int main()
{
    if (abrirDirectorio() == -1)
        printf("Algo no ha ido como debería");
}

int abrirDirectorio()
{
    /*Declaro donde voy a guardar el trozo de la cadena*/
    char trozo[30];
    int count = 0;
    /* Con un puntero a DIR abriremos el directorio */
    DIR *dir;
    /* en *ent habrá información sobre el archivo que se está "sacando" a cada momento */
    //struct dirent *ent;
    struct dirent *ent;
    /* Empezaremos a leer en el directorio actual */
    dir = opendir("F:/Fotos/WhatsApp Images/Private");

    /* Miramos que no haya error */
    if (dir == NULL)
    {
        perror("No puedo abrir el directorio");
        return -1;
    }
    while ((ent = readdir(dir)) != NULL && count < 10)
    {
        /* Nos devolverá el directorio actual (.) y el anterior (..), como hace ls */
        if ((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
        {
            /* Una vez tenemos el archivo, lo pasamos a una función para procesarlo. */
            procesoArchivo(ent->d_name, trozo);
        }
        count++;
    }
    closedir(dir);
    return 1;
}
void procesoArchivo(char *archivo, char trozo[])
{
    /* Para "procesar", o al menos, hacer algo con el archivo, vamos a decir su tamaño en bytes */
    /* para ello haremos lo que vemos aquí: https://poesiabinaria.net/2010/04/tamano-de-un-fichero-en-c/ */
    FILE *fich;
    long ftam;
    fich = fopen(archivo, "r");
    if (fich)
    {
        fseek(fich, 0L, SEEK_END);
        ftam = ftell(fich);
        fclose(fich);
        /* Si todo va bien, decimos el tamaño */
        printf("%30s (%ld bytes)\n", archivo, ftam);
        printf("%30d\n", trocearCadena(archivo, trozo));
        printf("%30s\n", trozo);
    }
    else
    {
        /* Si ha pasado algo, sólo decimos el nombre */
        printf("%30s (No info.)\n", archivo);
        printf("%30d\n", trocearCadena(archivo, trozo));
        printf("%30s\n", trozo);
    }
}

int trocearCadena(char *archivo, char trozo[])
{
    /*Copio el nombre del archivo, ya que no puedo cortarlo directamente*/
    strcpy(trozo, archivo);
    /*Establezco un delimitador*/
    char delimitador[] = "D";
    /*Corto la cadena hasta el delimitador*/
    strtok(trozo, delimitador);
    return 0;
}
