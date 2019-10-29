/*
 * Informe3.c
 * 
 * Copyright 2019  <pi@raspberrypi>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
 
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

//gcc Informe3.c -o informe -lsqlite3
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

static int getValues(void *data, int argc, char **argv, char **azColName){
	int i;
	
	for (i = 0; i < argc; i++){
		sprintf(data, "%s", argv[i] ? argv[i] : "NULL");
		printf("%s", (char *)data);
	}
	return 0;
}

int main(int argc, char* argv[]){
	sqlite3 *db;
	char sql[80];
	char *zErrMsg = 0;
	int rc;
	FILE * fp;
	int nSen;
	char data[100];
	char texto[200];
	
	/* Open database */
	rc = sqlite3_open("captura.db", &db);

	if( rc ) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	}
	else {
      fprintf(stdout, "\n\n\n");
   }
	/* Open document */
	fp = fopen("informe.txt", "w"); 
    if (fp == NULL){ 
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
	
	int n;
	for (n = 1; n <= nSen; n++){
		//Sensor
		sprintf(texto, "Informe de sensor: %d\n", n);
		fprintf(fp,"%s", texto);
		memset(texto,'\0', 200);
		
		//Fecha/hora inicial
		sprintf(sql, "SELECT MIN(Date_time_lecture) FROM Lectures_table WHERE ID = %d", n);
		rc = sqlite3_exec(db, sql, getValues, (void*)data, &zErrMsg);
		sprintf(texto, "Fecha/hora inicio: %s\n", data);
		fprintf(fp,"%s",texto);
		memset(texto,'\0', 200);
		
		//~ //Fecha/hora final
		//~ sprintf(sql, "SELECT MIN(Date_time_lecture) FROM Lectures_table WHERE ID = %d", sensor);
		//~ sqlite3_exec(db, sql, getValues, (void*)data, &zErrMsg);
		//~ sprintf(texto, "Fecha/hora inicio: %s", value);
		//~ fprintf(fp, texto);
		
		//~ //Valor máximo
		//~ sprintf(sql, "SELECT MIN(Date_time_lecture) FROM Lectures_table WHERE ID = %d", sensor);
		//~ sqlite3_exec(db, sql, getValues, (void*)data, &zErrMsg);
		//~ sprintf(texto, "Fecha/hora inicio: %s", value);
		//~ fprintf(fp, texto);
		
		//~ //Valor mínimo
		//~ sprintf(sql, "SELECT MIN(Date_time_lecture) FROM Lectures_table WHERE ID = %d", sensor);
		//~ sqlite3_exec(db, sql, getValues, (void*)data, &zErrMsg);
		//~ sprintf(texto, "Fecha/hora inicio: %s", value);
		//~ fprintf(fp, texto);
		
		//~ //Valor medio
		//~ sprintf(sql, "SELECT MIN(Date_time_lecture) FROM Lectures_table WHERE ID = %d", sensor);
		//~ sqlite3_exec(db, sql, getValues, (void*)data, &zErrMsg);
		//~ sprintf(texto, "Fecha/hora inicio: %s", value);
		//~ fprintf(fp, texto);
	}
	fclose(fp);
	sqlite3_close(db);
	return 0;
}
