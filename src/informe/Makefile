all: Appinforme

Appinforme: bbdd.o

bbdd.o: bbdd.c
	gcc bbdd.c -o bbdd -lsqlite3

informe.o: informe.c
	gcc -c informe.c -o informe -lsqlite3

updateDB: bbdd.o
	rm -rf *db Captura
	sudo ./bbdd

clean:
	rm -rf *o informe bbdd