#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

//cream  structura  Student
typedef struct Student {
	char* nume;
	int varsta;
	float medie;

}Student;

//functia creare
Student creareStudent(const char* n, int v, float m) {
	//cream Student S
	Student s;
	s.nume = (char*)malloc(sizeof(char) * (strlen(n) + 1));
	strcpy(s.nume, n);
	s.varsta = v;
	s.medie = m;
	return  s;
}

//afisare student
void afisareStudent(Student s) {
	printf("\n Studentul cu numele  %s are  varsta  %d si media %5.2f. \n", s.nume, s.varsta, s.medie);
}

//facem struct  nodului
typedef struct nod {
	//declaram  ce contien  in nod
	Student info;
	struct nod* next;
}nod;

//cream    nod  ;  lucram cu pointer la nod
nod* creareNod(Student info, nod* next) {
	//declaram nod* nou
	nod* nou = (nod*)malloc(sizeof(nod));
	//facem  informatia utila
	//shallow copy ;  egaleaza adresele si  nu ce se afla efectiv la adresa respectiva
	//nou->info = info;
	//deep copy - ne fol de  fct  creare student
	nou->info = creareStudent(info.nume, info.varsta, info.medie);
	nou->next = next;
	//returnam nodul  creat
	return nou;

}

//functie nserare  inceput (unde inseram,ce inseram)
nod* inserareInceput(nod* cap, Student s) {
	//cream nod  nod* nou
	nod* nou = creareNod(s, NULL);
	//intrebam daca  exista lista
	if (cap) {
		//refacem legaturile; nextul nodului nou   este  primul din lista
		nou->next = cap;
		//primul nod  din lista devine  nodul nou
		cap = nou;
	}
	else {
		//daca nu exista   inseamnac a nodul nou este unicul  nod
		cap = nou;
	}
	return  cap;
}

nod* inserareFinal(nod* cap, Student s) {
	//cream nodul  nou*
	nod* nou = creareNod(s, NULL);
	if (cap) {
		//facem copie la primul  nod
		nod* p = cap;
		//ajungem la   final-sa se opreasca pe ultimul nod 
		 while (p->next) {
			// parcurgem lista
			 p = p->next;
		 }
		 //cand iese  din  while p  se afla ultimul 
		 //facem leg intre  p si nodul nou
		 p->next = nou;
	}
	else {
		//nodul nou este singurul din  lista
		cap = nou;
	}
	return cap;
}

//afisare   
void afisareLista(nod* cap) {
	//ori  IF ori  memory leack
	if (cap) {
		//facem  mereu  o copie
		nod* p = cap;
		while (p) {
			//afisam info utila 
			afisareStudent(p->info);
			//ne mutam pe  urrm  nod
			p = p->next;
			//asta se intampla cat avem  elem in lista
		}
	}

}
//functie dezalocare lista
nod* dezalocareLista(nod* cap) {
	while (cap) {
		nod* aux = cap;
		//mutam cap pe urm nod
		cap=cap->next;
		//dez   e a ramas in spate
		free(aux->info.nume);
		free(aux);

	}
	return cap;
}


//void main() {
//	//ne cream o lista  pe care  sa o initializam cu NULL
//	nod* lista = NULL;
//	//meregem pe  principiul ce e in stanga e si in dreapta (unde inseram, ce inseram)
//	//STudentul se creaza inline cu  fct de creare Student
//	lista = inserareInceput(lista,creareStudent("ALina", 25,8));
//	lista = inserareInceput(lista,creareStudent("Oana", 24,6));
//	lista = inserareInceput(lista,creareStudent("Ion", 26,7.5));
//	lista = inserareInceput(lista,creareStudent("CArina", 28,7));
//	lista = inserareInceput(lista,creareStudent("Cristina", 23,9));
//	afisareLista(lista);
//	printf("-----------------final----------------------------------------");
//	lista = inserareFinal(lista, creareStudent("x", 25, 8));
//	lista = inserareFinal(lista, creareStudent("y", 24, 6));
//	lista = inserareFinal(lista, creareStudent("z", 26, 7.5));
//	afisareLista(lista);
//	lista = dezalocareLista(lista);
//	printf("\n afisare lista dupa dezalocare :\n ");
//
//
//
//	

}