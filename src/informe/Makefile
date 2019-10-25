all: Appinforme

Appinforme: bbdd.o

bbdd.o: bbdd.c
    gcc bbdd.c -o bbdd -lsqlite3

informe.o: informe.c
    gcc -c informe.c -o informe -lsqlite3

clean:
    rm -rf *o informe bbdd

