#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct autoMobiel {
	char merk[32];
	int aantalWielen;
	int aantalDeuren;
};

struct vliegtuig {
	char type[32];
	int spanwijdte;
};
union voertuig{
	struct autoMobiel autoStruct;
	struct vliegtuig vliegStruct;
};
struct vehicle {
	int keuze;
	union voertuig voertuig;
};


void readVehicle(struct vehicle*);
void printVehicle(struct vehicle*);

int main(void) {
	struct vehicle voertuig;
	readVehicle(&voertuig);
	printVehicle(&voertuig);

	return 0;
}

void readVehicle(struct vehicle* voertuig) {
	int keuze;

	printf("Type 1 voor een auto en 2 voor een vliegtuig: ");
	do {
		scanf("%d", &keuze);
	}while(keuze != 1 && keuze != 2);
	voertuig->keuze = keuze;
	if(keuze == 1) {
		printf("U heeft gekozen voor een auto.\n");
		printf("Geef het automerk in: ");
		scanf(" %s", voertuig->voertuig.autoStruct.merk);
		printf("Geef het aantal wielen in: ");
		scanf("%d", &voertuig->voertuig.autoStruct.aantalWielen);
		printf("Geef het aantal deuren in: ");
		scanf("%d", &voertuig->voertuig.autoStruct.aantalDeuren);
	}
	else if(keuze == 2) {
		printf("U heeft gekozen voor een vliegtuig.\n");
		printf("Geef het type in: ");
		scanf(" %s", voertuig->voertuig.vliegStruct.type);
		printf("Geef de spanwijdte: ");
		scanf("%d", &voertuig->voertuig.vliegStruct.spanwijdte);
	}
}
void printVehicle(struct vehicle* voertuig) {
	if(voertuig->keuze == 1) {
		printf("Een auto van het merk %s, met %d deuren en %d wielen.\n", voertuig->voertuig.autoStruct.merk, voertuig->voertuig.autoStruct.aantalDeuren, voertuig->voertuig.autoStruct.aantalWielen);
	}
	else if(voertuig->keuze == 2) {
		printf("Een vliegtuig van type %s met een spanwijdte van %d\n", voertuig->voertuig.vliegStruct.type, voertuig->voertuig.vliegStruct.spanwijdte);
	}

}