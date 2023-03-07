#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "werte.h"

int readWerte(tEnergiewert* data, unsigned amount) {
	FILE* inp = NULL;
	char* puffer = (char*)calloc(80, sizeof(char));
	int check = 0;
	if (puffer) {
		inp = fopen("Energiewerte.txt", "rt");
		if (inp) {
			puffer = fgets(puffer, 80, inp);
			for (unsigned i = 0; i < amount; i++)
			{
				puffer = fgets(puffer, 80, inp);
				check = sscanf(puffer, "%u.%u.%u %u:%u;%lf;%lf;%lf", &data[i].datum.tag, &data[i].datum.monat, &data[i].datum.jahr, &data[i].datum.stunden, &data[i].datum.minuten, &data[i].last, &data[i].erzeugung, &data[i].importe);
				if (check != 8) {
					printf("Fehler beim Einlesen der Zeile %d", i);
				}
			}
		}
		else {
			printf("Fehler beim lesen der Datei");
			if (puffer) {
				free(puffer);
			}

			if (inp) {
				fclose(inp);
			}
			return -1;
		}
	}

	if (puffer) {
		free(puffer);
	}
	if (inp) {
		flcose(inp);
	}
	return 0;
}

tEnergiewert getMittelWert(tEnergiewert* data, unsigned amount) {
	tEnergiewert mittelWert = { 0,0,0,0,0,0,0,0 };
	for (unsigned i = 0; i < amount; i++)
	{
		if (i == (amount - 1)) {
			mittelWert.datum = data[i].datum;
		}
		mittelWert.erzeugung += data[i].erzeugung;
		mittelWert.importe += data[i].importe;
		mittelWert.last += data[i].last;
	}
	mittelWert.erzeugung /= amount;
	mittelWert.importe /= amount;
	mittelWert.last /= amount;
	return mittelWert;
}