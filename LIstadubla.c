#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>>
#include<string.h>
#include<malloc.h>


typedef struct Casa {
	char* adresa;
	float mp;


}Casa;

Casa creareCasa(const  char* adresa, float mp) {
	Casa c;
	///alocam mem
	c.adresa = (char*)malloc(sizeof(char)*(strlen(adresa) + 1));
	strcpy(c.adresa, adresa);
	c.mp = mp;
	return c;
}

//afisare

void afisareCasa(Casa c) {
	printf("\n Casa de la  adresa %s are  o suprafata de %5.2f mp.\n", c.adresa, c.mp);
}

//face struct nod

typedef struct  nod{
	Casa info;
	struct nod* prev;
	struct nod* next;
}nod;

//creare nod
nod* creareNod(Casa info, nod* prev, nod* next) {
	//facem un nod nou
	nod* nou = (nod*)malloc(sizeof(nod));
	//setam foecare atribut
	nou->info = creareCasa(info.adresa, info.mp);
	nou->prev = prev;
	nou->next = next;
	return nou;
}

//cream a strcut  LDI - lista  dubla - salvam primul  si ultimul nod
typedef struct LDI {
	nod* prim;
	nod* ultim;
}LDI;

//inserare inceput  si  returneaza  LDI (unde, ce)
LDI  inserareInceput(LDI lista, Casa c) {
	//cream nod nou  cu  creareNOD
	nod* nou = creareNod(c, NULL,NULL);
	//exista lista
	if (lista.prim) {
		nou->next = lista.prim;
		lista.prim->prev = nou;
		//update lista
		lista.prim = nou;
	}
	else {
		//este unicul nod in lista
		lista.prim = lista.ultim = nou;
	}
	return  lista;
}

LDI inserarefinal (LDI lista, Casa c) {
	nod* nou = creareNod(c, NULL, NULL);
	if (lista.prim) {
		nou->prev = lista.ultim;
		//cine e dupa ultimul nod - nodul nou
		lista.ultim->next = nou;
		//cine e ultimul nod din lista
		lista.ultim = nou;
	}
	else {
		lista.prim = lista.ultim = nou;
	}
	return  lista;
}

//afisare  de la inceput (lista) 
void afisareInceputFinal(LDI lista) {
	//daaca exista lista - facem  referire ori  la primul ori la ultimul
	if (lista.prim) {
		//plecam de la primul  nod si parcurgem  lista
		//facem copie la primul   nod
		nod* p = lista.prim;
		while (p) {
			//afisam info  utila - Casa 
			afisareCasa(p->info);
			//ne mutam pe urm  nod
			p = p->next;
	
		}
	}
	
}

void afisareFinalInceput(LDI lista) {
	//daca exista lista - ultimul nod
	if (lista.prim) {
		//plecam de  la ultimul nod si parcurgem lista
		//facem o copie la ultimul nod
		nod* p = lista.ultim;
		while (p) {
			//afisa info utila 
			afisareCasa(p->info);
			//ne mutam pe nodul  dinainte
			p = p->prev;
		}
	}
}

//dezalocare lista- returneaza lista LDI
//cat timo avem lista  de prim  ..facem copiem  si 
LDI  dezalocare(LDI lista) {
	while (lista.prim) {
		//cream un nod auxiliat care  o sa fie  egal cu lista.prim
		nod* aux = lista.prim;
		//mutam  primul  nod pe urmatorul
		lista.prim = lista.prim->next;
		//dezalocam ce a  ramas in spate
		free(aux->info.adresa);
		free(aux);
	}
	lista.ultim = NULL;
	return lista;
}
//functie cautare lista - o caasa a ceri mp   sa fie ca param
Casa cautacasaMP(LDI lista, float mp) {
	//exista lista
	if (lista.prim){
		//copie p
		nod* p = lista.prim;
		//cat timp avem elemente in lista si cat timp nu gasim elementul  MP
		while (p && p->info.mp!=mp) {
			//ne plimbam in lista cat timp am  elemenet  si nu gasesc ceea ce am nevoie
			p = p->next;
		}
		//cand  iese din while  , ise  din 2 motive: ori nu am elemente, ori nu a agasit MP
		//daca mai  are elemente
		if (p) {
			return p->info;
		}
		else{
			//returneaza un ob  fictiv
			return creareCasa("  ", -1);
		}

		
	}
	else {
		//trebuie sa  returnam un ob  fictie   de tip casa
		return creareCasa("  ", -1);
	}
}



void main() {
	//declaram  lista
	LDI lista;
	//trebuie sa o initializam;
	lista.prim = lista.ultim = NULL;
	//incepem sa inseram
	lista = inserareInceput(lista, creareCasa("PLatanilor1", 150.50));
	lista = inserareInceput(lista, creareCasa("Dorobanti2", 50.50));
	lista = inserareInceput(lista, creareCasa("Unirii3", 350.50));
	lista = inserarefinal(lista, creareCasa("adresa4", 51));
	lista = inserarefinal(lista, creareCasa("adresa5", 65));
	lista = inserarefinal(lista, creareCasa("adresa6", 80));
	printf("\n----------------InceputFInal-----------------------\n");
	afisareInceputFinal(lista);
	printf("\n----------------FinalInceput-----------------------\n");
	afisareFinalInceput(lista);
	printf("\n----------------Afisare dupa Cauta Casa-----------------------\n");
	afisareCasa(cautacasaMP(lista, 50.50));
	afisareCasa(cautacasaMP(lista, 20));

	lista = dezalocare(lista);
	printf("\n----------------Afisare dupa dezalocare-----------------------\n");
	afisareInceputFinal(lista);

}	