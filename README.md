# Shell simplificada

Aluno: Enzo Cunha
Matrícula: 201802676

Esse projeto consiste na criação de um programa com as funcionalidades básicas de um interpretador de linhas de comando (Shell).

## Instalação

A partir do arquivo Makefile, o programa será compilado e irá ser automaticamente executado.

```bash
make
```

## Códigos fonte

Os headers com a documentação das funções se encontra na pasta include enquanto os códigos-fonte estão na pasta src. A pasta arquivos_de_programa contém os arquivos gerados na execução do programa.

## Funcionalidades

### Comandos internos

Lista as variáveis de ambiente:
```bash
amb
```

Exibe o conteúdo de uma variável de ambiente:
```bash
amb $VAR
```

Configura uma variável de ambiente.
```bash
amb VAR=Valor
```

Exibe o manual de uso interno.
```bash
ajuda
```

Limpa a tela
```bash
limpa
```

Muda o diretório atual e atualiza o valor da variável de ambiente PWD.
```bash
cd diretório
```

Executa comandos fornecidos por um arquivo de entrada.
```bash
leia arquivo
```

Mostra o histórico de uso da shell.
```bash
historico
```

Sai da shell.
```bash
sair
```

### Comandos externos

Também é possível utilizar comandos externos, por exemplo:
```bash
ls -l
```

## Build status

O arquivo em que as variáveis de ambiente são configuráveis é .meushell.txt, pois a programação em Linux a partir de um computador Windows apresenta algumas limitações quanto às extensões dos arquivos.