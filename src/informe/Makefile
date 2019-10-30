all: Appinforme

Appinforme: bbdd.o informe.o informe3.o

bbdd.o: bbdd.c
	rm -rf *db Captura
	gcc bbdd.c -o bbdd -lsqlite3
	./bbdd

informe.o: informe.c
	gcc informe.c -o informe -lsqlite3
	./informe

informe3.o: Informe3.c
	gcc Informe3.c -o informe3 -lsqlite3
	./informe3

clean:
	rm -rf *o *db *txt informe bbdd
