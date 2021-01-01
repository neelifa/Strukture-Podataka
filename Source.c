/*Napisati program koji iz datoteke �ita postfiks izraz i zatim kori�tenjem stoga ra�una
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
char* UnosDat(char* fileName);
int UnosString(Pozicija h, char* buffer);
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
	char fileName[size];
	char* buffer = NULL;
	Pozicija head;
	head = (Pozicija)malloc(sizeof(struct cvor));
	if (head == NULL) {
		printf("Alokacija nije uspjela!(odabir)");
		return ERR;
	}
	head->next = NULL;

	printf("Unesite ime datoteke: ");
	scanf(" %s", fileName);

	buffer = UnosDat(fileName);
	if (NULL == buffer) {
		printf("Nije dobro une�eno iz datoteke!");
		return ERR;
	}

	printf("Postfix izraz glasi: %s", buffer);

	succ = UnosString(head, buffer);


	succ = Ispis(head->next);
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

char* UnosDat(char* fileName)
{
	FILE* fp = NULL;
	char bufferZaDuljinu[size] = {'\0'};
	char* buffer  = NULL;
	int duljinaStringa;

	if (strstr(fileName, ".txt") == 0)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Datoteka nije uspje�no otvorena!");
		return NULL;
	}

	fgets(bufferZaDuljinu, size, fp);
	rewind(fp);

	duljinaStringa = strlen(bufferZaDuljinu);
	duljinaStringa += 1;

	buffer = (char*)malloc((duljinaStringa) * sizeof(char));
	if (buffer == NULL) {
		printf("String nije uspje�no alociran!");
		return NULL;
	}
	
	fgets(buffer, duljinaStringa, fp);

	fclose(fp);

	return buffer;
}

int UnosString(Pozicija h, char* buffer)
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
				if (op != ' ') {
					succ = Racunaj(h, op);
				}
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
		printf("Do�lo je do gre�ke(SwitchCase (Racunaj))!");
		return ERR;
	}

	return OKAY;
}

int Ispis(Pozicija h)
{
	printf("\n");

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

