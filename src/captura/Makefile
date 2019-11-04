all: Appcaptura

Appcaptura: Basedades.o

Basedades.o: Basedades.c
	rm -rf Basedades
	gcc Basedades.c -o Basedades -lsqlite3
	./Basedades

clean:
	rm -rf *o *db Basedades -r doc

