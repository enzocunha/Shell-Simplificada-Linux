#include "../include/comandos.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Valor arbitrário.
*/
#define MAX_SIZE 100

void shell_loop()
{
    char comando[MAX_SIZE];
    char *args[MAX_SIZE];

    init_amb();

    while(1)
    {
        memset(args, 0, sizeof(args)); // limpa lixo do comando anterior
        printf("%s$ ", getenv("PRONTO"));
        recebe_comando(comando);
        adiciona_historico(comando);
        quebra_string(comando, args, " ");
        executa_comando(args);
    }    
}

int main()
{
    printf("Shell simplificada - Enzo Cunha\n");
    shell_loop();
    return 0;
}