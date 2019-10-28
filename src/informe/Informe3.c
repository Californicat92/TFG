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

//gcc informe.c -o informe -lsqlite3
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   char val[80];

	//fprintf(stderr, "%s: ", (const char*)data);
   
   for(nSen = 0; nSen<argc; nSen++){
		//~ printf("\n%s\n", argv[i] ? argv[i] : "NULL");
		//~ fprintf(fp,"\n%s\n", argv[i] ? argv[i] : "NULL");
		sprintf(val, "\n%s\n", argv[nSen] ? argv[nSen] : "NULL");
		printf(val);
		fprintf(fp, val);
   }
   return 0;
}

char getValues(char orden, char id){
}

int main(int argc, char **argv)
{
	char sensor = "01";
	char inicio[30] ;
	char final[30];	
	float max[30];
	float min[30];
	float med[30];
	sprintf(val, getValues("SELECT MIN(Date_time_lecture) FROM Lectures_table WHERE ID = %d", sensor))
	getValues("Final", sensor)
	getValues("Maximo", sensor)
	getValues("Minimo", sensor)
	getValues("Media", sensor)
	return 0;
}

