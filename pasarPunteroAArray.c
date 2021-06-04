#include <stdio.h>

int main()
{
    char cadena[20];
    char *cadenaInicio = "Hola Mundo";
    for (int i = 0; i < 10; i++)
    {
        cadena[i] = *cadenaInicio + i;
    }

    printf("'%s' da como resultado '%s'", cadenaInicio, cadena);
}