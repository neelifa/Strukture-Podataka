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
char* PushDat(char* fileName);
int PushString(Pozicija h, char* buffer);
int Push(Pozicija h, int broj);
int Pop(Pozicija h);
int Racunaj(Pozicija h, char op);
int Ispis(Pozicija h);
int Brisi(Pozicija h);

int main()
{
	int succ;

	succ = Odabir();

	if (succ == OKAY)
		return OKAY;
	else
		return ERR;
}

int Odabir()
{
	int succ;
	Pozicija head;
	char fileName[size];
	char* buffer = NULL;

	head = (Pozicija)malloc(sizeof(struct cvor));
	if (head == NULL) {
		printf("Alokacija nije uspjela!(odabir)");
		return ERR;
	}

	printf("Unesite ime datoteke: ");
	scanf(" %s", fileName);

	buffer = PushDat(fileName);
	if (NULL == buffer) {
		printf("Nije dobro unešeno iz datoteke!");
		return ERR;
	}
	printf("Postfix izraz glasi: %s", buffer);

	succ = PushString(head, buffer);


	succ = Ispis(head);
	if (succ == ERR) {
		printf("Funkcija Ispis(Odabir) nije uspijela!");
		return ERR;
	}

	succ = Brisi(head);
	if (succ == ERR) {
		printf("Funkcija Brisi(Odabir) nije uspijela!");
		return ERR;
	}
	free(head);
}

int Err()
{
	printf("Error poruka: Ne radi!");
	return ERR;
}

char* PushDat(char* fileName)
{
	FILE* fp = NULL;
	char buffer[size] = { '\0' };

	if (strstr(fileName, ".txt") == 0)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");

	if (fp == NULL) {
		printf("Datoteka nije uspješno otvorena!");
		return NULL;
	}
	rewind(fp);

	fgets(buffer, size, fp);
	fclose(fp);

	return buffer;
}

int PushString(Pozicija h, char* buffer)
{
	int retVal = 0;
	int succ = 0, n = 0;
	int el;
	char op;

	while (1) {
		retVal = sscanf(buffer, "%d %n", &el, &n);

		if (retVal == 1) {
			succ = Push(h, el);
		}

		else {
			retVal = sscanf(buffer, "%c%n", &op, &n);

			if (retVal == 1) {
				succ = Racunaj(h, op);
			}
			else {
				break;
			}
		}

		buffer += n;
	}

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

int Racunaj(Pozicija h, char op)
{
	int operandPrvi, operandDrugi;
	int succ;

	operandDrugi = h->next->el;
	operandPrvi = h->next->next->el;

	succ = Pop(h);
	succ = Pop(h);

	switch (op) {
	case('+'):
		succ = Push(h, operandPrvi + operandDrugi);
		break;

	case('-'):
		succ = Push(h, operandPrvi - operandDrugi);
		break;

	case('*'):
		succ = Push(h, operandPrvi * operandDrugi);
		break;

	case('/'):
		succ = Push(h, operandPrvi / operandDrugi);
		break;

	deafult:
		printf("Došlo je do greške(SwitchCase (Racunaj))!");
		return ERR;
	}

	return OKAY;
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

