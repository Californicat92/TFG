// PARA COMPILAR: gcc bbdd.c -o bbdd -lsqlite3

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;

   /* Open database */
   rc = sqlite3_open("Captura.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }
//-----------------------------------------------------------------------------
   /* Create SQL statement */
   sql = "CREATE TABLE Sensors_table("  \
      "ID				INT," \
      "Type				CHAR(10)," \
      "Description		CHAR(50));";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
   
   /* Create SQL statement */
   sql = "INSERT INTO Sensors_table (ID,Type,Description) "  \
         "VALUES (1, 'Voltaje', 'Tension en bornes de la placa solar'); " \
         "INSERT INTO Sensors_table (ID,Type,Description)  "  \
         "VALUES (2, 'Intensidad', 'Intensidad de carga de la placa solar'); ";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Records created successfully\n");
   }
//-----------------------------------------------------------------------------
   /* Create SQL statement */
   sql = "CREATE TABLE Lectures_table("  \
      "Date_time_lecture	DATE," \
      "ID					INT," \
      "Value				INT);";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }   
   
   /* Create SQL statement */
   sql = 	"INSERT INTO Lectures_table (Date_time_lecture,ID,Value) "	\
			"VALUES (20191023,1,1023); "								\
			"INSERT INTO Lectures_table (Date_time_lecture,ID,Value) "	\
			"VALUES (20191023,2,512); "									\
			"INSERT INTO Lectures_table (Date_time_lecture,ID,Value) "	\
			"VALUES (20191024,1,256); "									\
			"INSERT INTO Lectures_table (Date_time_lecture,ID,Value) "	\
			"VALUES (20191024,2,128); ";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Records created successfully\n");
   }
//-----------------------------------------------------------------------------
   /* Create SQL statement */
   sql = "CREATE TABLE Alarms_table("  \
      "Date_time_alarm		DATE," \
      "Alarm_description	CHAR(50));";
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
      
   /* Create SQL statement */
   sql = "INSERT INTO Alarms_table (Date_time_alarm,Alarm_description) "  \
         "VALUES (20191023, 'Se ha desconectado la placa solar'); " \
         "INSERT INTO Alarms_table (Date_time_alarm,Alarm_description)  "  \
         "VALUES (20191024, 'La bateria esta por encima de su voltaje'); ";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Records created successfully\n");
	}
//-----------------------------------------------------------------------------

   sqlite3_close(db);
   return 0;
}

