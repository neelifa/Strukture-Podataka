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
#define PETLJA 1


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
char* CharAlokacija(char* string);
int Push(Pozicija h, Stablo s);
int Pop(Pozicija h);
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

	strcat(putanja, root->imeMape);
	strcat(putanja, "\\");

	/*Head od stoga*/
	head = (Pozicija)malloc(sizeof(Stog));
	if (NULL == head) return ERR;

	while (PETLJA) {
		succ = IspisPutanje(putanja);

		memset(naredbeniRedak, '\0', size);
		memset(naredba, '\0', size);
		memset(imeMape, '\0', size);

		fgets(naredbeniRedak, size, stdin);

		retVal = sscanf("%s %s", naredba, imeMape);
		if(retVal = 0){
			printf("\n\nNetoèan unos!");
			continue;
		}

		if (strcmp(naredba, "md") == 0)
			succ = NovaMapa(trenutnaPozicija, imeMape);

		else if (strcmp(naredba, "dir") == 0)
			succ = PrikaziSveMape(trenutnaPozicija);

		else if (strcmp(naredba, "cd") == 0)
			trenutnaPozicija = PromijeniMapu(trenutnaPozicija, head, imeMape, putanja);

		else if (strcmp(naredba, "cd..") == 0)
			trenutnaPozicija = NatragMapa(trenutnaPozicija, head, putanja);

		else if (strcmp(naredba, "exit") == 0)
			break;
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

int Pop(Pozicija h)
{
	Pozicija tmp;
	if (h->next == NULL)
		return OKAY;
	else {
		tmp = h->next;
		h->next = tmp->next;
		free(tmp);
	}

	return OKAY;
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
	p->imeMape = imeMape;

	p->nextBrat = s->djete;
	s->djete = p;
	
	return OKAY;
}

Stablo PromjeniMapu(Stablo s, Pozicija h, char* imeMape, char* path)
{
	Push(h, s);

	s = s->djete;

	while (strcmp(s->imeMape, imeMape) != 0) {
		s = s->nextBrat;
	}

	strcat(path, "\\");
	strcat(path, imeMape);

	return s;
}

Stablo NatragMapa(Stablo s, Pozicija h, char* path);

int PrikaziSveMape(Stablo s)
{
	s = s->djete;
	printf("\n");

	while (s != NULL) {
		printf("/n/t<DIR>/t%s", s->imeMape);
		s = s->nextBrat;
	}

	return OKAY;
}

int IspisPutanje(char* path) {

	printf("\n\n%s>", path);

}

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