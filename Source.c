/*Definirati strukturu osoba(ime, prezime, godina roðenja) i napisati program koji :
a) dinamièki dodaje novi element na poèetak liste,
b) ispisuje listu,
c) dinamièki dodaje novi element na kraj liste,
d) pronalazi element u listi(po prezimenu),
e) briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERR (-1)
#define OKAY 0
#define MAX_NAME 256


typedef struct _student* Pozicija;
typedef struct _student{
	char ime[MAX_NAME];
	char prezime[MAX_NAME];
	int god_rod;
	Pozicija next;
}student;


int UnosP(Pozicija h);
int UnosK(Pozicija h);
int Ispis(Pozicija h);
Pozicija TraziPrez(Pozicija h);
Pozicija TraziPrethodni(Pozicija h, char prez);
int BrisiEl(Pozicija h);

int main() {

	int succ;
	student Head;
	Pozicija tr;
	Head.next = NULL;

	//Unošenje elemenata
	succ = UnosP(&Head);
	if (succ == ERR)
		printf("Ne radi unosP kraljice.....");

	succ = UnosP(&Head);
	if (succ == ERR)
		printf("Ne radi unosP kraljice.....");

	succ = UnosK(&Head);
	if (succ == ERR)
		printf("Ne radi unosK kraljice.....");

	//Ispis elemenata
	succ = Ispis(Head.next);
	if (succ == ERR)
		printf("Ne radi Ispis kraljice.....");

	//Primjer trazenja elementa po prezimenu 
	tr = TraziPrez(&Head);
	if (tr == ERR)
		printf("Kraljice nece trazenje......");

	printf("Prezime u naðenom elementu je: %s\n\n", tr->prezime); //Oznacava da je trazenje uspjelo

	//Primjer brisanja elementa naðenog po prezimenu
	succ = BrisiEl(&Head);
	if (succ != OKAY)
		printf("Kraljice neæe brisanje.......");
	//Ispis
	succ = Ispis(Head.next);
	if (succ == ERR)
		printf("Ne radi Ispis kraljice.....");

	return 0;
}

int UnosP(Pozicija h) {

	Pozicija p;
	p = (Pozicija)malloc(sizeof(student));
	if (p == NULL)
		return ERR;


	printf("Unesite ime prezime i godinu rodjenja(U istom ovom formatu!!):\n");
	scanf("%s %s %d", p->ime, p->prezime, &p->god_rod);

	p->next = h->next;
	h->next = p;
	
	return OKAY;
}
int UnosK(Pozicija h) {

	int succ;

	while (h->next != NULL)
		h = h->next;

	succ = UnosP(h);
	if (succ == ERR)
		printf("Ne radi unos kraljice.....");

	return OKAY;
}
int Ispis(Pozicija h){

	printf("Ispis liste:\n\n");

	while (h != NULL) {
		printf("%s %s %d\n", h->ime, h->prezime, h->god_rod);
		h = h->next;
	}

}
Pozicija TraziPrez(Pozicija h) {

	char prez[MAX_NAME];
	printf("Unesite prezime koje zelite pronaci: ");
	scanf("%s/n", prez);

	while (h != NULL && strcmp(h->prezime, prez) != 0)
		h = h->next;

	return h;
}
Pozicija TraziPrethodni(Pozicija h, char *prez) {

	Pozicija Prev = h;
	h = h->next;

	while(h != NULL && strcmp(h->prezime, prez) != 0){
		Prev = h;
		h = h->next;
	}

	if (h == NULL) {
		printf("Element nije u listi!!!");
		return NULL;
	}

	return Prev;
}
int BrisiEl(Pozicija h) {
	
	char prez[MAX_NAME];
	Pozicija Prev, pom = NULL;

	printf("Unesite prezime clana kojeg zelite izbrisati: ");
	scanf(" %s", prez);

	Prev = TraziPrethodni(h, prez);
	
	if (Prev != NULL) {
		pom = Prev->next;
		Prev->next = pom->next;
		free(pom);
		
	}

	return OKAY;
}
