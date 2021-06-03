#include <stdio.h>
#include <string.h>
int main()
{
    char cadena [] = "Hola, Mundo";
    char delimitador [] = ",";
    char *token = strtok(cadena, delimitador);
    printf ("Encontramos un token: %s", token);
    return 0;
}