#pragma once
#include <stdlib.h>

struct sDatum {
	unsigned minuten;
	unsigned stunden;
	unsigned tag;
	unsigned monat;
	unsigned jahr;
};

typedef struct sEnergiewert {
	struct sDatum datum;
	double last;
	double erzeugung;
	double importe;
}tEnergiewert;

int readWerte(tEnergiewert* data, unsigned amount);
tEnergiewert getMittelWert(tEnergiewert* data, unsigned amount);