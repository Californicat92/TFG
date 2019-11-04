all: Appinforme

Appinforme:
	gcc informe.c -o informe -lsqlite3
	./informe

bbdd:
	rm *db
	gcc bbdd.c -o bbdd -lsqlite3
	./bbdd

doxygen:
	doxygen Doxyfile

clean:
	rm -rf *o *db *txt informe bbdd informe3 -r doc

