/*
 * Informe.c
 * 
 * Copyright 2019 alumne <alumne@L20xx>
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

//gcc Informe.c -o Informe -lsqlite3

#include <stdio.h>

char getValues(char orden, char sensor){
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;
	const char* data = "Callback function called";
	
	/*Selección de comando SQL*/
	if (orden == "Inicio"){
		sql = 	"SELECT MIN(Date_time_lecture) FROM Lectures_table.db " \
				"WHERE 	ID = sensor";
	}
	
	else if (orden == "Final"){
		sql = 	"SELECT MAX(Date_time_lecture) FROM Lectures_table.db " \
				"WHERE 	ID = sensor";
	}
	
	else if (orden == "Maximo"){
		sql = 	"SELECT MAX(Value) FROM Lectures_table.db " \
				"WHERE 	ID = sensor";
	}
	
	else if (orden == "Minimo"){
		sql = 	"SELECT MIN(Value) FROM Lectures_table.db " \
				"WHERE 	ID = sensor";
	}
	
	else if (orden == "Media"){
		sql = 	"SELECT AVG(Value) FROM Lectures_table.db " \
				"WHERE 	ID = sensor";
		
	}

	/* Open database */
	rc = sqlite3_open("Captura.db", &db);

	if( rc ) {
	  fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	  return(0);
	} else {
	  fprintf(stderr, "Opened database successfully\n");
	}

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

	if( rc != SQLITE_OK ) {
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	} else {
	  fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(db);
	
	return 0;
}

int main(int argc, char **argv){
	char sensor = "01";
	char inicio = getValues("Inicio", sensor);
	char final = getValues("Final", sensor);	
	float max = getValues("Maximo", sensor);
	float min = getValues("Minimo", sensor);
	float med = getValues("Media", sensor);
	
	int nSen = 1 sens = 1;
	for (int nSen = 1; nSen <= sens; nSen++){
		fprintf(("%s\n"\
				"		Data/hora inici: 	%s\n"\
				"		Data/hora final: 	%s\n"\
				"		Valor Máxim: 		%.2f\n"\
				"		Valor Mínim: 		%.2f\n"\
				"		Valor Mitjà: 		%.2f\n"),
				sensor, inicio, final, max, min, med);
	}
	return 0;
}

