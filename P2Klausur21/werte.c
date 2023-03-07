#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "werte.h"

int readWerte(tEnergiewert* data, unsigned amount) {
	FILE* inp = NULL;
	char* puffer = (char*)calloc(80, sizeof(char));
	if (puffer) {
		inp = fopen("Energiewerte.txt", "rt");
		if (inp) {
			puffer = fgets(puffer, 80, inp);
			for (unsigned i = 0; i < amount; i++)
			{
				puffer = fgets(puffer, 80, inp);
				if (!puffer) {
					free(puffer);
					fclose(inp);
					printf("Es stehen weniger als %u Datensätze in der Datei (nur %i). Lesen nicht erfolgreich.\n", amount, i);
					return -1;
				}
				if (sscanf(puffer, "%u.%u.%u %u:%u;%lf;%lf;%lf", &data[i].datum.tag, &data[i].datum.monat, &data[i].datum.jahr, &data[i].datum.stunden, &data[i].datum.minuten, &data[i].last, &data[i].erzeugung, &data[i].importe) != 8) {
					printf("WARNUNG: Fehler beim Einlesen der Zeile %d\n\n", i);
					free(puffer);
					fclose(inp);
					return -1;
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
	else {
		printf("Fehler beim Erstellen des Puffers.\n\n");
		return -1;
	}
	printf("%u Werte eingelesen.\n\n", amount);
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