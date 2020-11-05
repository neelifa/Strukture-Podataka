/*Definirati strukturu osoba(ime, prezime, godina roðenja) i napisati program koji :
a) dinamièki dodaje novi element na poèetak liste,
b) ispisuje listu,
c) dinamièki dodaje novi element na kraj liste,
d) pronalazi element u listi(po prezimenu),
e) briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/

/*Prethodnom zadatku dodati funkcije:
a) dinamièki dodaje novi element iza odreðenog elementa,
b) dinamièki dodaje novi element ispred odreðenog elementa,
c) sortira listu po prezimenima osoba,
d) upisuje listu u datoteku,
e) èita listu iz datoteke.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERR (-1)
#define OKAY 0
#define MAX_NAME 256


typedef struct _student* Pozicija;
typedef struct _student {
	char ime[MAX_NAME];
	char prezime[MAX_NAME];
	int god_rod;
	Pozicija next;
}student;

int UnosP(Pozicija h);
int UnosK(Pozicija h);
int Ispis(Pozicija h);
Pozicija TraziPrez(Pozicija h, char* prez);
Pozicija TraziPrethodni(Pozicija h, char* prez);
int BrisiEl(Pozicija h);
int Sortiraj(Pozicija h);
int UnosIza(Pozicija h);
int UnosIspred(Pozicija h);
int UpisiDat(Pozicija h);
int CitajDat(Pozicija h);

int main() {

	int succ;
	student Head;
	Pozicija tr;
	Head.next = NULL;

	//Unošenje elemenata

	//Unos na poèetak liste
	succ = UnosP(&Head);
	if (succ == ERR)
		printf("Ne radi unosP kraljice.....");

	succ = UnosP(&Head);
	if (succ == ERR)
		printf("Ne radi unosP kraljice.....");

	//Unos na kraj liste
	succ = UnosK(&Head);
	if (succ == ERR)
		printf("Ne radi unosK kraljice.....");

	//Unos iza nekog elementa
	succ = UnosIza(&Head);
	if (succ == ERR)
		printf("Kraljice ne radi ti unos iza...........");

	//Unos ispred nekog elementa
	succ = UnosIspred(&Head);
	if (succ == ERR)
		printf("Kraljice ne radi ti unos ispred...........");

	//Ispis elemenata
	succ = Ispis(Head.next);
	if (succ == ERR)
		printf("Ne radi Ispis kraljice.....");

	//Sortiranje i ispis
	//succ = Sortiraj(&Head);
	//if (succ != OKAY)
		//printf("Ne radi sortiranje kraljice.....");

	/*succ = Ispis(Head.next);
	if (succ == ERR)
		printf("Ne radi Ispis kraljice.....");*/

		//Primjer trazenja elementa po prezimenu 
		/*printf("Unesite prezime koje zelite pronaci: ");
		scanf("%s/n", prez);
		tr = TraziPrez(&Head, prez);
		if (tr == ERR)
			printf("Kraljice nece trazenje......");*/

			//printf("Prezime u naðenom elementu je: %s\n\n", tr->prezime); //Oznacava da je trazenje uspjelo

			//Primjer brisanja elementa naðenog po prezimenu
			/*succ = BrisiEl(&Head);
			if (succ != OKAY)
				printf("Kraljice neæe brisanje.......");*/
				//Ispis
				/*succ = Ispis(Head.next);
				if (succ == ERR)
					printf("Ne radi Ispis kraljice.....");*/



	return 0;
}

int UnosP(Pozicija h) {

	Pozicija p;
	p = (Pozicija)malloc(sizeof(student));
	p->next = NULL;
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
int Ispis(Pozicija h) {

	printf("Ispis liste:\n\n");

	while (h != NULL) {
		printf("%s %s %d\n", h->ime, h->prezime, h->god_rod);
		h = h->next;
	}

	return OKAY;

}
Pozicija TraziPrez(Pozicija h, char* prez) {

	while (h != NULL && strcmp(h->prezime, prez) != 0)
		h = h->next;

	return h;
}
Pozicija TraziPrethodni(Pozicija h, char* prez) {

	Pozicija Prev = h;
	h = h->next;

	while (h != NULL && strcmp(h->prezime, prez) != 0) {
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
int Sortiraj(Pozicija h) {
	Pozicija j, prev_j, temp;

	while (h->next != NULL) {
		prev_j = h;
		j = h->next;

		while (j->next != NULL) {
			if (strcmp(j->prezime, j->next->prezime) > 0) {
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}
			prev_j = j;
			j = j->next;
		}
		j = NULL;
	}

	return OKAY;
}
int UnosIza(Pozicija h) {
	Pozicija pr;
	char iza[MAX_NAME];
	int succ;

	printf("Unesite prezime elementa iza kojega želite unijeti novi element: ");
	scanf(" %s", iza);

	pr = TraziPrez(h, iza);

	succ = UnosP(pr);
	if (succ == ERR) {
		printf("Unos iza neæe.........");
		return ERR;
	}

	return OKAY;
}
int UnosIspred(Pozicija h) {
	char ispred[MAX_NAME];
	Pozicija pred;
	int succ;

	printf("Unesite prezime elementa ispred kojega zelite unijeti novi element: ");
	scanf(" %s", ispred);

	pred = TraziPrethodni(h, ispred);

	succ = UnosP(pred);
	if (succ == ERR) {
		printf("Unos ispred neæe.........");
		return ERR;
	}

	return OKAY;

}
int UpisiDat(Pozicija h) {

	FILE* fp;

	fp = fopen("studenti1.txt", "w");
	if (fp == NULL) {
		printf("Neæe da se otvori datoteka za upis kween....");
		return ERR;
	}
	rewind(fp);

	while (!feof(fp)) {
		fprintf(fp, "%s %s %d\n", h->ime, h->prezime, h->god_rod);
		h = h->next;
	}

	fclose(fp);
	return OKAY;
}
int CitajDat(Pozicija h) {
	FILE* fp;

	fp = fopen("studenti.txt", "w");
	if (fp == NULL) {
		printf("Neæe da se otvori datoteka za citanje kween....");
		return ERR;
	}
	rewind(fp);

	while (!feof(fp)) {
		Pozicija q;
		q = (Pozicija)malloc(sizeof(student));
		q->next = NULL;

		fscanf(fp, "%s %s %d", q->ime, q->prezime, &q->god_rod);
		printf("%s %s %d\n", q->ime, q->prezime, q->god_rod);
		q->next = h->next;
		h->next = q;
	}
	fclose(fp);
	return OKAY;
}
