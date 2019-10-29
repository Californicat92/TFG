/*
 * Formato Captura.db
 * 
 * 	· Sensors_table
 * 		- ID
 * 		- Types (Magnitud)
 * 		- Description
 * 
 * 	· Lectures_table
 * 		- Date_time_lecture
 * 		- ID
 * 		- Value
 * 
 * 	· Alarms_table
 * 		- Date_time_alarm
 * 		- Alarm_description
 */

//gcc informe.c -o informe -lsqlite3
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string.h> 


sqlite3 *db;
char *zErrMsg = 0;
int rc;
FILE * fp;

static int getValues(void *data, int argc, char **argv, char **azColName){
   int i;
      
   for(i = 0; i<argc; i++){
		memset(data,'\0',100);		
		sprintf(data, "\n%s\n", argv[i] ? argv[i] : "NULL");
		printf("%s", (char *)data);
		fprintf(fp,"%s", (char *)data);
   }
   return 0;
}



int main(int argc, char* argv[]) {

	char sql[80];
	char data[100];
	int nSen=0;
	/* Open database */
	rc = sqlite3_open("captura.db", &db);

	if( rc ) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	} else {
      fprintf(stdout, "\n\n\n");
   }
	/* Open document */
	fp = fopen("informe.txt", "w"); 
    if (fp == NULL) 
    { 
        printf("Could not open file"); 
        return 0; 
    }
	  
	/* Lectura nº sensores */
	memset(data,'\0',100);
	sprintf(sql, "SELECT MAX(ID) FROM Lectures_table");
	
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, getValues, (void*)data, &zErrMsg);

	if( rc != SQLITE_OK ) {
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}
	nSen = atoi(data);
	printf("El numero de sensores es %d",nSen);
	
	    
	int orden = 0, ID=0;
	for (ID = 1; ID < 3; ID++)
	{
		printf("\n\nInforme de sensor: %d \n",ID);
		fprintf(fp,"\n\nInforme de sensor: %d \n",ID);
		for (orden = 1; orden < 7; orden++)
		{
			/*Selección de comando SQL*/
			if (orden == 1){
				sprintf(sql, "SELECT MIN(Date_time_lecture) FROM Lectures_table WHERE ID = %d", ID);
			}

			else if (orden == 2){
				sprintf(sql, "SELECT MAX(Date_time_lecture) FROM Lectures_table WHERE ID = %d", ID);
			}

			else if (orden == 3){
				sprintf(sql, "SELECT MAX(Value) FROM Lectures_table WHERE ID = %d", ID);
			}

			else if (orden == 4){
				sprintf(sql, "SELECT MIN(Value) FROM Lectures_table WHERE ID = %d", ID);
			}

			else if (orden == 5){
				sprintf(sql, "SELECT AVG(Value) FROM Lectures_table WHERE ID = %d", ID);
			}

			else if (orden == 6){
				sprintf(sql, "SELECT * FROM Alarms_table");
			}
			
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql, getValues, (void*)data, &zErrMsg);

			if( rc != SQLITE_OK ) {
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}
		}
	}
	
   fclose(fp); 
   sqlite3_close(db);
   return 0;
}
