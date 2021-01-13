/*Napisati program koji pomoæu vezanih listi (stabala) predstavlja strukturu direktorija.
Omoguæiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij. Toènije program treba preko menija simulirati
korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define ERR (-1)
#define OKAY 0
#define size 255
#define DG 10
#define GG 100
#define IZLAZ -2


typedef struct _cvor* Stablo;
typedef struct _cvor{
	char* imeMape;

	Stablo djete;
	Stablo nextBrat;
}Cvor; 


typedef struct _stog {
	Stablo cvorStabla;

	Pozicija next;
}Stog;
typedef struct _stog* Pozicija;

int mainMenu();
int Push(Pozicija h, Stablo s);
int Pop(Pozicija h);
int NovaMapa(Stablo s, char* imeMape);
int PromijeniMapu(Stablo s, char* imeMape);
int NatragMapa(Stablo s, Pozicija h);
int PrikaziSveMape(Stablo s);
int IspisMapa(Stablo s);
int BrisiStablo(Stablo s);
int BrisiStog(Pozicija h);

int main()
{
	int succ;

	succ = mainMenu();
	if (succ == OKAY) {
		return OKAY;
	}
	else {
		return ERR;
	}
}

int mainMenu()
{
	Cvor root;
	root.djete = NULL;
	root.nextBrat = NULL;
	root.imeMape = "C:";




}

int Push(Pozicija h, Stablo s)
{
	Stog q = NULL;

	q = (Stog)malloc(sizeof(struct _stog));
	if (NULL == q) {
		printf("Nece alokacija(push stog)");
		return ERR;
	}
	q->cvorStabla = s;

	q->next = h->next;
	h->next = q;


	return OKAY;
}

int Pop(Pozicija h)
{
	Stog tmp;
	if (h->next == NULL)
		return OKAY;
	else {
		tmp = h->next;
		h->next = tmp->next;
		free(tmp);
	}

	return OKAY;
}

int NovaMapa(Stablo s, char* imeMape) {
	
}

int PromjeniMapu(Stablo s, char* imeMape);

int NatragMapa(Stablo s, Pozicija h);

int PrikaziSveMape(Stablo s);

int BrisiStablo(Stablo s)
{
	if (s == NULL) return OKAY;

	FreeTree(s->djete);
	FreeTree(s->nextBrat);
	free(s->imeMape);
	free(s);

	return OKAY;
}

int BrisiStog(Pozicija h) 
{
	Pozicija temp;

	while (h->next != NULL) {
		temp = h->next;
		h->next = temp->next;
		free(temp);
	}

	return OKAY;
}