#include "../include/comandos.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

/*
Valor arbitrário.
*/
#define MAX_SIZE 100

/*
Variáveis globais.
*/
extern char **environ;


void recebe_comando(char *comando)
{
    char c;
    scanf("%[^\n]", comando);
    while ((c = getchar() != '\n') && c != EOF); // limpa stdin
}


void quebra_string(char *str, char **arrayStr, char *delimitador)
{
    char *token;
    int i = 0;

    token = strtok(str, delimitador);
    while(token != NULL)
    {
        arrayStr[i] = token;
        token = strtok(NULL, delimitador);
        i++;
    }
}


void executa_comando(char **args)
{

    if(strcmp(args[0], "ajuda") == 0)
    {
        ajuda();
    }
    else if(strcmp(args[0], "amb") == 0)
    {
        gerencia_amb(args);
    }
    else if(strcmp(args[0], "cd") == 0)
    {
        cd(args);
    }
    else if(strcmp(args[0], "limpa") == 0)
    {
        system("clear");
    }
    else if(strcmp(args[0], "sair") == 0)
    {
        exit(EXIT_SUCCESS);
    }
    else if(strcmp(args[0], "leia") == 0)
    {
        executa_arquivo(args);
    }
    else if(strcmp(args[0], "historico") == 0)
    {
        print_historico();
    }
    else
    {
        executa_comando_externo(args);
    }
}


void executa_comando_externo(char **args)
{
    if(fork() == 0)
    {
        execvp(args[0], args);
        printf("Falha na execução do comando. Verifique se o comando está sendo digitado corretamente.\n");
        /*
        Quando são passados comandos inválidos, exec falha e é necessario usar exit()
        para finalizar o processo filho e não causar erros imprevisíveis na aplicação.
        */
        exit(EXIT_FAILURE);
    }else{
        wait(NULL);
    }
}


void cd(char **args)
{
    int status;
    char cwd[MAX_SIZE];

    status = chdir(args[1]);

    if(status)
    {
        printf("Diretório inválido.\n");
    }
    else
    {
        getcwd(cwd, sizeof(cwd));
        setenv("DTA", cwd, 1);
        setenv("PRONTO", cwd, 1);
    }
}


void executa_arquivo(char **args)
{
    FILE *fp;
    ssize_t len = 0;
    char *comando;
    char *file_args[MAX_SIZE];

    fp = fopen(args[1], "r");
    if(fp == NULL)
    {
        printf("Falha em abrir o arquivo. Verifique se o arquivo está no diretório atual.\n");
        return;
    }

    while(getline(&comando, &len, fp) != -1)
    {
        memset(file_args, 0, sizeof(file_args));
        // remove newline e carriage return (windows)
        remove_newline(comando);
        quebra_string(comando, file_args, " ");
        executa_comando(file_args);
    }
}


void remove_newline(char *string)
{
    for(int i=0; i<strlen(string); i++)
    {
        // 13 = carriage return e 10 = newline
        if(string[i] == 13 || string[i] == 10)
        {
            string[i] = '\0';
            return;
        }
    }
}


void adiciona_historico(char *comando)
{
    FILE *fp;
    static char ultimo_comando[MAX_SIZE] = "";
    static char filepath[MAX_SIZE];

    if(strlen(filepath) == 0)
    {
        realpath("./arquivos_de_programa/.meushell.hst", filepath);
    }
    // evita repetiçao do ultimo comando
    if(strcmp(ultimo_comando, comando) == 0)
    {
        return;
    }

    fp = fopen(filepath, "a");
    if(fp == NULL)
    {
        return;
    }

    fputs(comando, fp);
    fputs("\n", fp);

    fclose(fp);
}


void print_historico()
{
    FILE *fp;
    int i;
    char linha[MAX_SIZE];
    static char filepath[MAX_SIZE];

    if(strlen(filepath) == 0)
    {
        realpath("./arquivos_de_programa/.meushell.hst", filepath);
    }

    fp = fopen(filepath, "r");
    i = 0;
    if(fp == NULL)
    {
        printf("Não foi possível abrir o histórico.\n");
        return;
    }

    printf("Histórico de comandos:\n");
    while(fgets(linha, MAX_SIZE, fp) != NULL)
    {
        printf("%d - %s\n", i, linha);
        i++;
    }
}


void gerencia_amb(char **args)
{
    if(args[1] == 0)
    {
        print_amb(NULL);
    }
    else if(args[1][0] == '$')
    {
        print_amb(args);
    }
    else
    {
        set_amb(args);
    }
}


void print_amb(char **args)
{
    if(args == 0)
    {
        char **aux = environ;

        while(*aux)
        {
            printf("%s\n", *aux);
            aux++;        
        }        
    }
    else
    {
        printf("%s\n", getenv(&(args[1][1]))); // ignora o caractere $ na primeira posiçao
    }
}


void set_amb(char **args)
{
    char *ambv[2]; // nome, valor

    quebra_string(args[1], ambv, "=");
    if(ambv[1][0] == '$')
    {
        setenv(ambv[0], getenv(&ambv[1][1]), 1); // PRONTO=$DTA
        return;
    }
    else
    {
        setenv(ambv[0], ambv[1], 1);
        return;
    }

    printf("Falha em configurar variável de ambiente.");
}


void init_amb()
{
    FILE *fp;
    char linha[MAX_SIZE];
    char *ambv[2];
    char filepath[MAX_SIZE];
    ssize_t len = 0;

    setenv("DTA", getenv("PWD"), 1);
    setenv("PRONTO", getenv("PWD"), 1);

    // extensao .rec dá problemas na compilação no windows
    fp = fopen("./arquivos_de_programa/.meushell.txt", "r");
    if(fp == NULL)
    {
        return;
    }

    while(fgets(linha, MAX_SIZE, fp) != NULL)
    {    
        remove_newline(linha);
        quebra_string(linha, ambv, "=");

        if(ambv[1][0] == '$') // PRONTO=$DTA
        {
            setenv(ambv[0], getenv(&ambv[1][1]), 1);
        }
        else
        {
            setenv(ambv[0], ambv[1], 1);            
        }
    }
}


void ajuda()
{
    FILE *fp;
    char linha[MAX_SIZE];
    static char filepath[MAX_SIZE];

    if(strlen(filepath) == 0)
    {
        realpath("./arquivos_de_programa/ajuda.txt", filepath);
    }

    fp = fopen(filepath, "r");
    if(fp == NULL)
    {
        printf("Não foi possível abrir ajuda.\n");
        return;
    }

    while(fgets(linha, MAX_SIZE, fp) != NULL)
    {
        printf("%s\n", linha);
    }

    fclose(fp);
}