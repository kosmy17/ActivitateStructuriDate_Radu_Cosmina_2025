#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<malloc.h>

//declaram  struct pantofi
typedef struct Pantofi {
	char* brand;
	float  pret;
	int marime;
}Pantofi;

//functia de creare  structura
Pantofi crearePantofi(const char* b, float pr, int m) {
	Pantofi p;
	p.brand = (char*)malloc(sizeof(char) * (strlen(b) + 1));
	strcpy(p.brand, b);
	p.pret = pr;
	p.marime = m;
	return p;
}

//afisare
Pantofi afisarePantofi(Pantofi p) {
	printf("\n Tocmai ce mi-am  cumparat 1 pereche de  pantofi marimea %d de la %s cu pretul de %5.2f ron.\n", p.marime, p.brand, p.pret);
}

//declaram nod
typedef struct nod {
	Pantofi info;
	struct nod* next;
}nod;

//functia  creare
nod* creareNod(Pantofi info, nod* next) {
	//facem o  copie la nod * nou
	nod* nou = (nod*)malloc(sizeof(nod));
	//deep  copy
	nou->info = crearePantofi(info.brand, info.pret, info.marime);
	nou->next = next;
	//returnam  nodulnou creat
	return nou;
}

//functia inserare inceput cu param  lista (nod* cap) si obiectul (Pantofi)
nod* inserareInceput(nod* cap,Pantofi p	) {
	//crem un nod nou cu unctia de  creare nod
	nod* nou = creareNod(p, NULL);
	//ne intrebam daca E lista
	if (cap) {
		//refacem legaturile
		nou->next = cap;
		//primul nod  devine nou
		cap = nou;;
	}
	else {
		//nodul nou est esingurul  din lista
		cap = nou;
	}
	//returnam  lista
	return cap;

}

nod* inserareFinal(nod* cap, Pantofi p) {
	//cream  un nod*nou
	nod* nou = creareNod(p,NULL);
	//intrebam daca E lista
	if (cap) {
	//facem o copie le prmul nod
		nod* copie = cap;
	//trebuie sa parcugem lista pana la  ultimul nod
		while (copie->next) {
			copie = copie->next;
		}
		//ajunge  pe ultimul nod
		copie->next = nou;

	}
	else {
	//nodul nou e sing din lista
	cap = nou;
	}
	return  cap;
}

//functia de  afisare lista(nod*)
nod* afisarelista(nod* cap) {
	//ori if ori memory leak
	if (cap) {
		//facem mereu o copie la  cap
		nod* copie = cap;
		while (copie) {
			//afisam informatia utila din  Pantofi
			afisarePantofi(copie->info);
			//ne  mutam pe  urmatorul nod;
			copie = copie->next;
		}
	}
}
//
//nod* dezalocarelista(nod* cap) {
//	while (cap) {
//		//cream  un nod auxiliar
//		nod* aux = (nod*)malloc(sizeof(nod));
//		//mutam capul pe nodul urm
//		cap = cap->next;
//		//dezalocam ce in spate;
//		free(aux->info.brand);
//		free(aux);
//	}
	//returnam lista
//	return  cap;
//}
//void main() {
//	nod* lista = NULL;
//	lista = inserareInceput(lista, crearePantofi("musette", 150, 38));
//	lista = inserareInceput(lista, crearePantofi("albu", 350, 38));
//	lista = inserareInceput(lista, crearePantofi("hm", 100, 38));
//	afisarelista(lista);
//}