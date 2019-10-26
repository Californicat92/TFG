#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
	//fprintf(stderr, "%s: ", (const char*)data);
   
   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      
   }
   
   printf("\n");
   return 0;
}

/*char getValues(char orden, char sensor){
		sqlite3 *db;
		return 0;
}
*/

int main(int argc, char* argv[]) {
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;
	const char* data = "Callback function called";

	/* Open database */
	rc = sqlite3_open("captura.db", &db);

	if( rc ) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	} else {
      fprintf(stdout, "\n\n\n");
   }
	
int orden = 0;
	for (orden = 1; orden < 6; orden++)
	{
		/*Selección de comando SQL*/
		if (orden == 1){
			sql =	"SELECT MIN(Date_time_lecture) FROM Lectures_table " \
					"WHERE 	ID = 1";
		}

		else if (orden == 2){
			sql =	"SELECT MAX(Date_time_lecture) FROM Lectures_table " \
					"WHERE 	ID = 1";
		}

		else if (orden == 3){
			sql = 	"SELECT MAX(Value) FROM Lectures_table " \
					"WHERE 	ID = 2";
		}

		else if (orden == 4){
			sql =	"SELECT MIN(Value) FROM Lectures_table " \
					"WHERE 	ID = 2";
		}

		else if (orden == 5){
			sql =	"SELECT AVG(Value) FROM Lectures_table " \
					"WHERE 	ID = 2";
		}

		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

		if( rc != SQLITE_OK ) {
		  fprintf(stderr, "SQL error: %s\n", zErrMsg);
		  sqlite3_free(zErrMsg);
		}
	}
   sqlite3_close(db);
   return 0;
}
