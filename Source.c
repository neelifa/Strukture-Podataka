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
#define IZLAZ (-2)
#define PETLJA 1

struct _cvor;
typedef struct _cvor* Stablo;
typedef struct _cvor{
	char* imeMape;

	Stablo djete;
	Stablo nextBrat;
}Cvor; 

struct _stog;
typedef struct _stog* Pozicija;
typedef struct _stog {
	Stablo cvorStabla;

	Pozicija next;
}Stog;


int mainMenu();
char* CharAlokacija(char* string);
int Push(Pozicija h, Stablo s);
Stablo Pop(Pozicija h);
int ProstorZaNovuMapu(Stablo* s);
int NovaMapa(Stablo s, char* imeMape);
Stablo PromijeniMapu(Stablo s, Pozicija h, char* imeMape, char* path);
Stablo NatragMapa(Stablo s, Pozicija h, char* path);
int PrikaziSveMape(Stablo s);
int IspisPutanje(char* path);
int BrisiStablo(Stablo s);
int BrisiStog(Pozicija h);

int main()
{
	int succ;
	succ = mainMenu();
	if (succ != OKAY)
		return ERR;
	return OKAY;
}

int mainMenu()
{
	Stablo root = NULL;
	Stablo trenutnaPozicija = NULL;

	Pozicija head = NULL;

	char* naredbeniRedak = "\0";
	char* naredba = "\0";
	char* imeMape = "\0";
	char* putanja = "\0";

	int retVal = 0;
	int succ = 0;

	/*Naredbe*/
	naredbeniRedak = CharAlokacija(naredbeniRedak);
	naredba = CharAlokacija(naredba);
	imeMape = CharAlokacija(imeMape);
	putanja = CharAlokacija(putanja);

	/*Root od stabla*/
	ProstorZaNovuMapu(&root);
	root->imeMape = (char*)malloc(size * sizeof(char));
	memset(root->imeMape, '\0', sizeof(root->imeMape));
	root->imeMape = "C:";
	root->djete = NULL;
	root->nextBrat = NULL;
	trenutnaPozicija = root;

	memset(putanja, '\0', sizeof(putanja));
	strcat(putanja, root->imeMape);

	/*Head od stoga*/
	head = (Pozicija)malloc(sizeof(Stog));
	if (NULL == head) return ERR;
	head->next = NULL;

	while (PETLJA) {
		succ = IspisPutanje(putanja);

		memset(naredbeniRedak, '\0', size);
		memset(naredba, '\0', size);
		memset(imeMape, '\0', size);

		fgets(naredbeniRedak, size, stdin);

		retVal = sscanf(naredbeniRedak, "%s %s", naredba, imeMape);
		
		if (strcmp(naredba, "md") == 0) {
			succ = NovaMapa(trenutnaPozicija, imeMape);
		}
		else if (strcmp(naredba, "dir") == 0) {
			succ = PrikaziSveMape(trenutnaPozicija);
		}
		else if (strcmp(naredba, "cd") == 0) {
			trenutnaPozicija = PromijeniMapu(trenutnaPozicija, head, imeMape, putanja);
		}
		else if (strcmp(naredba, "cd..") == 0){
			trenutnaPozicija = NatragMapa(trenutnaPozicija, head, putanja);
		}
		else if (strcmp(naredba, "exit") == 0) {
			break;
		}
		else
			printf("Neispravan unos");

	}

	return OKAY;
}

char* CharAlokacija(char* string) 
{
	string = (char*)malloc(size * sizeof(char));

	return string;
}

int Push(Pozicija h, Stablo s)
{
	Pozicija q = NULL;

	q = (Pozicija)malloc(sizeof(Stog));
	if (NULL == q) {
		printf("Nece alokacija(push stog)");
		return ERR;
	}
	q->cvorStabla = s;

	q->next = h->next;
	h->next = q;


	return OKAY;
}

Stablo Pop(Pozicija h)
{
	Pozicija tmp;
	Stablo ret;

	if (NULL != h->next ) {

		ret = h->next->cvorStabla;

		tmp = h->next;
		h->next = tmp->next;
		free(tmp);

		return ret;
	}
	return NULL;
}

int ProstorZaNovuMapu(Stablo* s) {
	Stablo tmp = NULL;

	tmp = (Stablo)malloc(sizeof(Cvor));
	if (tmp == NULL) return ERR;

	tmp->djete = NULL;
	tmp->nextBrat = NULL;

	*s = tmp;

	return OKAY;
}

int NovaMapa(Stablo s, char* imeMape) {

	Stablo p;

	ProstorZaNovuMapu(&p);

	p->imeMape = (char*)malloc(sizeof(strlen(imeMape) + 1));
	strcpy(p->imeMape, imeMape);

	p->nextBrat = s->djete;
	s->djete = p;
	
	return OKAY;
}

Stablo PromijeniMapu(Stablo s, Pozicija h, char* imeMape, char* path)
{
	Stablo temp = s;

	Push(h, s);

	s = s->djete;

	while (NULL != s && strcmp(s->imeMape, imeMape) != 0) {
		s = s->nextBrat;
	}

	if (NULL == s) {
		printf("Ne postoji mapa %s!", imeMape);
		return temp;
	}


	strcat(path, "\\");
	strcat(path, imeMape);

	return s;
}

Stablo NatragMapa(Stablo s, Pozicija h, char* path)
{
	char* krajPatha = NULL;
	Stablo temp;

	temp = Pop(h);

	if (temp == NULL) {
		printf("Nalazite se u root mapi!");
	}
	else {
		s = temp;

		krajPatha = strrchr(path, '\\');
		*krajPatha = '\0';

	}
	return s;

}

int PrikaziSveMape(Stablo s)
{
	s = s->djete;

	while (s != NULL) {
		printf("\n\t<DIR>\t %s", s->imeMape);
		s = s->nextBrat;
	}
	return OKAY;
}

int IspisPutanje(char* path) {

	printf("\n%s>", path);

}

int BrisiStablo(Stablo s)
{
	if (s == NULL) return OKAY;

	BrisiStablo(s->djete);
	BrisiStablo(s->nextBrat);
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