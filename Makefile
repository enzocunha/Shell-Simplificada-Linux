all:
	gcc ./src/meushell.c ./src/comandos.c -o ./arquivos_de_programa/meushell
	./arquivos_de_programa/meushell