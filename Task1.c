#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

//cream strcut 
typedef struct Cladire {
	//atribute
	char* denumire;
	int nrEtaje;
	float suprafata;
}Cladire;

//functia  creare
Cladire creareCladire(const char* d, int nr, float s) {
	//cream Cladire
	Cladire c;
	c.denumire = (char*)malloc(sizeof(char) * (strlen(d) + 1));
	strcpy(c.denumire, d);
	c.nrEtaje = nr;
	c.suprafata = s;
	return c;
}

//functie   afisare  cladire
void afisareCladire(Cladire c) {
	printf("\n Cladirea %s are  %d etaje  si  are o suprafata de %5.2f mp.\n ", c.denumire, c.nrEtaje, c.suprafata);

}

//declaram nodul
typedef struct nod {
	//atributele
	//info utila
	Cladire info;
	//next
	struct nod* next;
}nod;

//functia creare  nod
nod* creareNod (Cladire info,  nod*  next){
	//declaram un nod * nou
	nod* nou = (nod*)malloc(sizeof(nod));
	//adaugam info  utila
	//facem un deep  copy
	nou->info = creareCladire(info.denumire, info.nrEtaje, info.suprafata);
	nou->next = next;
	//returnam  nodulnou creat
	return nou;
}


//inserare inceput param(lista , struct)
nod* inserareInceput(nod* cap, Cladire c) {
	//cream un nod* nou
	nod* nou = creareNod(c, NULL);
	//verificam  daca  exista lista
	if (cap) {
		//refacem legaturile
		nou->next = cap;
		//nou devine primul nod
		cap = nou;
	}
	else {
		//nodul nou este  singurul   din lista
		cap = nou;
	}
	//returnam lusta
	return cap;

}
nod* inserareFinal(nod* cap, Cladire c) {
	//cream   un nod  *nou
	nod* nou = creareNod(c, NULL);
	//testam  lista
	if (cap) {
		//facem o  copie la primul nod
		nod* p = cap;
		//parcurgem lista pana la utlimul   nod (cat timp avem next)
		while (p->next) {
			p = p->next;
		}
		//cand  iese din  while ,p->next se afla pe ultimul nod
		//facem  leg intre  p->next  si  nodul nou
		p->next = nou;
	}
	else {
		//nodul nou este singurul  din lista
		cap = nou;
	}
	return  cap;

}

//functia afisare lista
nod* afisareLista(nod* cap) {
	//ori If ori memory leak
	if (cap) {
		//facem mereu o copie
		nod* p = cap;
		while (p) {
			//afisam info utila din  struct
			afisareCladire(p->info);
			//ne  mutam pe urm nod;
			p = p->next;
			//cat avem elemente in lista
		}
	}
}

//dezalocare lista
nod* dezalocareLista(nod * cap) {
		while (cap) {
			//cream   un nod  auxiliar
			nod* aux = cap;
			//mutam capul pe   urm nod
			cap = cap->next;
			//dezalocam ce  a ramas in spate
			//dezalocam info util -ce a fost cu malloc
			free(aux->info.denumire);
			free(aux);
		}
		//returnam   lista dezalocata
		return cap;
	}

void main() {
	//cream o lista si o initializam  cu NULL
		nod* lista = NULL;
		//ce e  in stg e si in dreapta
		lista = inserareInceput(lista, creareCladire("Pireus", 6, 350));
		lista = inserareInceput(lista, creareCladire("Alpha", 3, 250.5));
		lista = inserareInceput(lista, creareCladire("Omega", 9, 555));
		afisareLista(lista);
}