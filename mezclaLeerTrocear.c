#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

int abrirDirectorio();
void procesoArchivo();
char *trocearCadena();

int main()
{
    if (abrirDirectorio() == -1)
        printf("Algo no ha ido como debería");
}

int abrirDirectorio()
{
    /* Con un puntero a DIR abriremos el directorio */
    DIR *dir;
    /* en *ent habrá información sobre el archivo que se está "sacando" a cada momento */
    //struct dirent *ent;

    /* Empezaremos a leer en el directorio actual */
    dir = opendir(".");

    /* Miramos que no haya error */
    if (dir == NULL)
    {
        perror("No puedo abrir el directorio");
        return -1;
    }
    procesoArchivo("leerDirectorio.c");
    closedir(dir);
    return 1;
}
void procesoArchivo(char *archivo)
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
        printf("%s", trocearCadena(archivo));
    }
    else
    {
        /* Si ha pasado algo, sólo decimos el nombre */
        printf("%30s (No info.)\n", archivo);
        printf("%s", trocearCadena(archivo));
    }
}

char *trocearCadena(char *archivo)
{
    /*Copio el nombre del archivo, ya que no puedo cortarlo directamente*/
    char archivoCorte[strlen(archivo)];
    strcpy(archivoCorte, archivo); 
    /*Establezco un delimitador*/
    char delimitador[] = "D";
    /*Corto la cadena hasta el delimitador*/
    char *resultado = strtok(archivoCorte, delimitador);
    /*Despues de cortar, asigno el valor de fin de cadena*/
    archivoCorte[strlen(archivoCorte)+1] = '\0'; 
    printf("%s", resultado);
    return resultado;
}
