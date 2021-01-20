/*. Napisati program koji iz datoteke èita postfiks izraz i zatim stvara stablo proraèuna. Iz
gotovog stabla proraèuna upisati u datoteku infiks izraz.*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ERR (-1)
#define OKAY 0
#define size 1024
#define el_size 20
#define IZLAZ (-2)
#define PETLJA 1

struct _cvor;
typedef struct _cvor* Stablo;
typedef struct _cvor {
	char el[el_size];

	Stablo L;
	Stablo D;
}Cvor;

struct _stog;
typedef struct _stog* Pozicija;
typedef struct _stog {
	Stablo cvorStabla;
	char el[el_size];

	Pozicija next;
}Stog;


Stablo KreirajCvor(char* element);
int PushStog(Pozicija h, Stablo s);
int PushRed(Pozicija r, char* el);
int Pop(Pozicija h);
char* UpisIzDatoteke(char* fileName);
int UpisIzStringa(char* buffer, Pozicija h);
int UpisUDatoteku(Pozicija r, char* fileName);
void IspisInOrder(Stablo s, Pozicija r);
int JeliBroj(char* el);
int BrisiListu(Pozicija h);
int BrisiStablo(Stablo s);


int main()
{
	Pozicija head = NULL;
	Pozicija red = NULL;
	char imeUlazneDatoteke[size] = "postfix.txt";
	char imeIzlazneDatoteke[size] = "infix.txt";

	head = (Pozicija)malloc(sizeof(Stog));
	if (head == NULL) {
		puts("Neuspjela alokacija!");
		return ERR;

	}
	head->next = NULL;

	red = (Pozicija)malloc(sizeof(Stog));
	if (red == NULL) {
		puts("Neuspjela alokacija!");
		return ERR;
	}
	red->next = NULL;
	

	UpisIzStringa(imeUlazneDatoteke, head);
	IspisInOrder(head->next->cvorStabla, red);

	UpisUDatoteku(red, imeIzlazneDatoteke);

	BrisiStablo(head->next->cvorStabla);
	BrisiListu(red);
	BrisiListu(head);
}


int PushStog(Pozicija h, Stablo s) 
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

int PushRed(Pozicija r, char* el)
{
	Pozicija q = NULL;

	q = (Pozicija)malloc(sizeof(Stog));
	if (NULL == q) {
		printf("Nece alokacija(push stog)");
		return ERR;
	}

	strcpy(q->el, el);

	q->next = r->next;
	r->next = q;


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

Stablo KreirajCvor(char* el)
{
	Stablo p = NULL;

	p = (Stablo)malloc(sizeof(Cvor));
	if (NULL == p) {
		printf("Nije uspijela alokacija");
		return NULL;
	}
	strcpy(p->el, el);
	p->D = NULL;
	p->L = NULL;

	return p;
}

char* UpisIzDatoteke(char* fileName)
{
	FILE* fp = NULL;
	char bufferZaDuljinu[size] = { '\0' };
	char* buffer = NULL;
	int duljinaStringa;

	if (strstr(fileName, ".txt") == 0)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Datoteka nije uspješno otvorena!");
		return NULL;
	}

	fgets(bufferZaDuljinu, size, fp);
	rewind(fp);

	duljinaStringa = strlen(bufferZaDuljinu);
	duljinaStringa += 1;

	buffer = (char*)malloc((duljinaStringa) * sizeof(char));
	if (buffer == NULL) {
		printf("String nije uspješno alociran!");
		return NULL;
	}

	fgets(buffer, duljinaStringa, fp);

	fclose(fp);

	return buffer;
}

int UpisIzStringa(char* fileName, Pozicija h)
{
	int retVal = 0;
	int succ = 0, n = 0;
	char el[el_size] = { '\0' };
	char op = '\0';
	char* buffer;

	buffer = UpisIzDatoteke(fileName);

	while (PETLJA) {
		retVal = sscanf(buffer, "%s%n", &el, &n);

		if (retVal != 1) {
			puts("Kraj unosa.");
			break;
		}

		if(JeliBroj(el)) {
			PushStog(h, KreirajCvor(el));
		}

		else {
			if (el != ' ') {
				Stablo opStablo = KreirajCvor(el);

				opStablo->D = h->next->cvorStabla;
				Pop(h);

				opStablo->L = h->next->cvorStabla;
				Pop(h);

				PushStog(h, opStablo);
			}
		}
		buffer += n;
	}

	return OKAY;
}

void IspisInOrder(Stablo s, Pozicija r)
{
	if (NULL == s)
		return;


	IspisInOrder(s->L, r);
	printf("%s ", s->el);
	PushRed(r, s->el);
	IspisInOrder(s->D, r);

}

int UpisUDatoteku(Pozicija r, char* fileName) {

	FILE* fp;

	if (strstr(fileName, ".txt") == 0)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("Nece da se otvori datoteka za upis..");
		return ERR;
	}
	rewind(fp);

	while (r != NULL) {
		fprintf(fp, "%s ", r->el);
		r = r->next;
	}

	fclose(fp);
	return OKAY;
}

int JeliBroj(char* el)
{
	int number = 0;

	if (sscanf(el, "%d", &number) == 1)
		return 1;

	return 0;
}

int BrisiListu(Pozicija h)
{
	Pozicija temp;

	while (h->next != NULL) {
		temp = h->next;
		h->next = temp->next;
		free(temp);
	}
	return OKAY;
}

int BrisiStablo(Stablo s)
{
	if (NULL != s) {
		BrisiStablo(s->L);
		BrisiStablo(s->D);
		free(s);
	}
}
