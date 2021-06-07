#include <stdio.h>

int main (){
    int res = rename ("escaner_prueba.png", "C:/Users/carlo/Desktop/ProyectoOrganizarFotos/2021/escaner_prueba.png");
    if (res == 0){
        printf("Succes");
    }else{
        printf("Fail");
    }
    return 0;
}