#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "werte.h"

int main(int argc, char* argv[]) {
	unsigned amount = 0;
	FILE* inp = NULL;
	tEnergiewert* data = NULL;

	if (argc == 2) {
		amount = atoi(argv[1]);
		if (amount) {
			data = (tEnergiewert*)calloc(amount, sizeof(tEnergiewert));
			if (data) {
				if (!readWerte(data, amount)) {
					tEnergiewert mittelWert = getMittelWert(data, amount);
					printf("DD.MM.YYYY HH:MM: Last (MW):  Erzeugung(MW):  Importe (MW):\n%.2u.%.2u.%.4u %.2u:%.2u %11.3lf  %14.3lf  %13.3lf\n", mittelWert.datum.tag, mittelWert.datum.monat, mittelWert.datum.jahr, mittelWert.datum.stunden, mittelWert.datum.minuten, mittelWert.last, mittelWert.erzeugung, mittelWert.importe);
				}
				else {
					printf("Fehler beim Einlesen der Daten!");
				}
			}
			else {
				printf("Fehler beim allokieren des Speichers für die Energiewert Daten.");
			}
		}
		else {
			printf("Die eingegebene Zahl war 0.");
		}
	}
	else {
		printf("Falsche Anzahl an Parametern übergeben.");
	}
	if (data) {
		free(data);
	}

	return 0;
}
