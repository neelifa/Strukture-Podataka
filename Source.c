/*Napisati program koji iz datoteke èita postfiks izraz i zatim korištenjem stoga raèuna
rezultat. Stog je potrebno realizirati preko vezane liste.*/

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

struct cvor;
typedef struct cvor* Pozicija;

struct cvor {
	int el;
	Pozicija next;
};

int Odabir();
int Err();
int PushDat(Pozicija h, char* fileName);
int PushString(Pozicija h, char* buffer);
int Push(Pozicija h, int broj);
int Pop(Pozicija h);
int Racunaj();
int Ispis(Pozicija h);
int Brisi(Pozicija h);

int main()
{
	int succ;

	succ = Odabir();

	return OKAY;
}

int Odabir()
{
	int succ;
	Pozicija head;
	head = (Pozicija)malloc(sizeof(struct cvor));
	if (head == NULL) {
		printf("Alokacija nije uspjela!(odabir)");
		return ERR;
	}




}

int Err()
{
	printf("Error poruka: Ne radi!");
	return ERR;
}

int PushDat(Pozicija h, char* fileName)
{
	FILE* fp = NULL;
	int succ;
	char buffer[size];

	if (strstr(fileName, ".txt") == 0)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Datoteka nije uspješno otvorena!");
		return ERR;
	}

	while (!feof) {
		fgets(buffer, size, fp);
		succ = PushString(h, buffer);
	}

	fclose(fp);

}

int PushString(Pozicija h, char* buffer)
{

}

int Push(Pozicija h, int broj)
{
	Pozicija q = NULL;

	q = (Pozicija)malloc(sizeof(struct cvor));
	if (NULL == q) {
		printf("Alokacija nije uspijela!(push)");
		return ERR;
	}
	q->el = broj;

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

int Racunaj()
{

}

int Ispis(Pozicija h)
{
	while (h != NULL) {
		printf("%d ", h->el);
		h = h->next;
	}
	printf("\n");

	return OKAY;
}

int Brisi(Pozicija h)
{
	Pozicija temp;

	while (h->next != NULL) {
		temp = h->next;
		h->next = temp->next;
		free(temp);
	}
	return OKAY;
}

