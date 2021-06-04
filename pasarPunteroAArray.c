#include <stdio.h>
#include <string.h>

int main()
{
    char *cadenaInicio = "Hola Mundo";
    char cadena[strlen(cadenaInicio+1)];
    strcpy(cadena, cadenaInicio);
    printf("'%s' da como resultado '%s'", cadenaInicio, cadena);
}