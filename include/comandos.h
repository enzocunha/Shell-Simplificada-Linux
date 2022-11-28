#ifndef COMANDOS_H
#define COMANDOS_H


/*
Essa função espera a entrada de dados e a armazena na string passada por referência.
*/
void recebe_comando(char *comando);


/*
Essa função quebra uma string de acordo com o delimitador, 
colocando os pedaços da string em char **arrayStr.
*/
void quebra_string(char *str, char **arrayStr, char *delimitador);


/*
Essa função procura o comando na lista de comandos internos, 
e se não for encontrado ele tenta executar como um comando externo.
*/
void executa_comando(char **args);


/*
Essa função cria um processo filho para executar o comando externo passado
como argumento.
*/
void executa_comando_externo(char **args);

/*
Essa função define o comando interno de mudança de diretório de trabalho atual.
*/
void cd(char **args);


/*
Essa função lê o arquivo de entrada e executa os comandos definidos.
*/
void executa_arquivo(char **args);


/*
Essa função remove os caracteres encontrados no final da linha quando lidos de um arquivo.
Newline e Carriage Return (Windows).
*/
void remove_newline(char *string);


/*
Essa função grava os comandos utilizados na shell em um arquivo .meushell.hst
*/
void adiciona_historico(char *comando);


/*
Essa função lê o conteudo do arquivo .meushell.hst e imprime na tela o resultado.
*/
void print_historico();


/*
Essa função verifica se o usuário pede para imprimir as variáveis de ambiente,
mostrar o valor de uma variável ou setar o valor de uma variável.
*/
void gerencia_amb(char **args);


/*
Essa função imprime todas as variáveis de ambiente se é passado NULL como parâmetro,
caso contrário imprime a variável específicada.
*/
void print_amb(char **args);


/*
Essa função cria variáveis de ambiente e, se já existentes, altera o seu valor.
*/
void set_amb(char **args);

/*
Essa função seta as variáveis de ambiente com os valores especificados no arquivo.
*/
void init_amb();

/*
Essa função imprime o manual da shell na tela.
*/
void ajuda();

#endif