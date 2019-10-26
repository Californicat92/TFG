all: Appinforme

Appinforme: bbdd.o informe.o

bbdd.o: bbdd.c
	rm -rf *db Captura
	gcc bbdd.c -o bbdd -lsqlite3
	./bbdd

informe.o: informe.c
	gcc informe.c -o informe -lsqlite3
	./informe

clean:
	rm -rf *o *db informe bbdd
