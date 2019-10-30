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
FILE * fp;

static int getValues(void *data, int argc, char **argv, char **azColName){
	int i;
	
	memset((char *)data,'\0',200);
	
	for (i = 0; i < argc; i++){
		sprintf(data, "%s", argv[i] ? argv[i] : "NULL");
		//~ printf("%s", (char *)data);
	}
	return 0;
}
static int Alarmas(void *data, int argc, char **argv, char **azColName){
	int i;
	
	memset((char *)data,'\0',200);
	
	for(i = 0; i<argc; i++) {
		fprintf(fp,"%s\n", argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int main(int argc, char* argv[]){
	sqlite3 *db;
	char sql[80];
	char *zErrMsg = 0;
	int rc;
	int nSen;
	char data[200];
	char texto[400];
	
	/* Open database */
	rc = sqlite3_open("captura.db", &db);

	if( rc ) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	}

	/* Open document */
	fp = fopen("informe3.txt", "w"); 
    if (fp == NULL){ 
        printf("Could not open file"); 
        return 0; 
    }
    
    /* Lectura nº sensores */
	memset(data,'\0',200);
	sprintf(sql, "SELECT MAX(ID) FROM Lectures_table");
	
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, getValues, (void*)data, &zErrMsg);

	if( rc != SQLITE_OK ) {
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}
	nSen = atoi(data);
	//~ printf("\n\nEl numero de sensores es %d\n",nSen);
	
	int n;
	for (n = 1; n <= nSen; n++){
		//Sensor
		sprintf(texto, "\n\nInforme de sensor %d:\n", n);
		fprintf(fp,"%s", texto);
		memset(texto,'\0', sizeof(texto));
		
		//Fecha/hora inicial
		sprintf(sql, "SELECT MIN(Date_time_lecture) FROM Lectures_table WHERE ID = %d", n);
		rc = sqlite3_exec(db, sql, getValues, (void*)data, &zErrMsg);
		sprintf(texto, "\tFecha/hora inicio: %s\n", data);
		fprintf(fp,"%s",texto);
		memset(texto,'\0', sizeof(texto));
		
		//Fecha/hora final
		sprintf(sql, "SELECT MAX(Date_time_lecture) FROM Lectures_table WHERE ID = %d", n);
		sqlite3_exec(db, sql, getValues, (void*)data, &zErrMsg);
		sprintf(texto, "\tFecha/hora final: %s\n", data);
		fprintf(fp,"%s",texto);
		memset(texto,'\0', sizeof(texto));
		
		//Valor máximo
		sprintf(sql, "SELECT MAX(Value) FROM Lectures_table WHERE ID = %d", n);
		sqlite3_exec(db, sql, getValues, (void*)data, &zErrMsg);
		sprintf(texto, "\tEl valor máximo de tensión registrado: %s V\n", data);
		fprintf(fp,"%s",texto);
		memset(texto,'\0', sizeof(texto));
		
		//Valor mínimo
		sprintf(sql, "SELECT MIN(Value) FROM Lectures_table WHERE ID = %d", n);
		sqlite3_exec(db, sql, getValues, (void*)data, &zErrMsg);
		sprintf(texto, "\tEl valor mínimo de tensión registrado: %s V\n", data);
		fprintf(fp,"%s",texto);
		memset(texto,'\0', sizeof(texto));
		
		//Valor medio
		sprintf(sql, "SELECT AVG(Value) FROM Lectures_table WHERE ID = %d", n);
		sqlite3_exec(db, sql, getValues, (void*)data, &zErrMsg);
		sprintf(texto, "\tEl valor medio de tensión obtenido: %s V\n\n", data);
		fprintf(fp,"%s",texto);
		memset(texto,'\0', sizeof(texto));
	}
	if( rc != SQLITE_OK ) {
	fprintf(stderr, "SQL error: %s\n", zErrMsg);
	sqlite3_free(zErrMsg);
	}
	
	//Alarmas
	fprintf(fp, "\n\nLas alarmas sucedidas en las úliamas 24h han sido:\n");
	sprintf(sql, "SELECT * FROM Alarms_table");
	sqlite3_exec(db, sql, Alarmas, (void*)data, &zErrMsg);
	sprintf(texto, "\t%s", data);
	fprintf(fp,"%s",texto);
	memset(texto,'\0', sizeof(texto));

	if( rc != SQLITE_OK ) {
	fprintf(stderr, "SQL error: %s\n", zErrMsg);
	sqlite3_free(zErrMsg);
	} else {
	printf("\nEjecución correcta, revise el documento informe.txt\n\n");
	}
		
	fclose(fp);
	sqlite3_close(db);
	return 0;
}
