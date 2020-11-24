/*Napisati program koji pomoæu vezanih listi simulira rad:
a) stoga,
b) reda.
Napomena: Funkcija "push" sprema cijeli broj, sluèajno generirani u opsegu od 10 - 100.*/

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

typedef struct Cvor* Pozicija;
struct Cvor {
	int br;
	Pozicija next;
};

int Odabir();
int Stog(Pozicija h);
int Red(Pozicija h);
int Err();
int RandBr(); 
int PushStog(Pozicija h, int broj);
int PopStog(Pozicija h);
int PushRed(Pozicija h, int broj);
int PopRed(Pozicija h);
int Ispis(Pozicija h);


int main() 
{
	int succ;

	succ = Odabir();
	if (succ == OKAY) {
		printf("Sve je okay!");
		return ERR;
	} else if (succ == IZLAZ)
		printf("Izasli smo s izlazom.");
	else
		printf("Nece nesto!");

	return 0;
};

int Odabir()
{
	int c = 0;
	int succ = 0;

	srand(time(NULL));

	struct Cvor head;
	head.next = 0;

	while (1) {
		printf("Zelite li koristiti stog ili red?\n1 - Stog\n2 - Red\n3 - Izlaz iz programa\n");
		scanf("%d", &c);

		switch (c) {
		case(1):
			succ = Stog(&head);
			break;

		case(2):
			succ = Red(&head);
			break;

		case(3):
			return IZLAZ;
			break;

		default:
			printf("\nUnijeli ste nesto krivo! Pokusajte ponovno!\n\n");
		}
		if (c == 3)
			break;
	}
		
	return OKAY;
}

int Stog(Pozicija h)
{

	int i;
	int n; 
	int succ;
	int br;

	printf("\nUnesite koliko brojeva zelite unijeti u listu: ");
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		br = RandBr();
		PushStog(h, br);
	}
	succ = Ispis(h->next);

	printf("\nUnesite koliko brojeva zelite izbrisati iz liste: ");
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		PopStog(h);
	}
	succ = Ispis(h->next);
	succ = Brisi(h);

	return OKAY;
}

int Red(Pozicija h)
{
	int i;
	int n;
	int br;
	int succ;

	printf("\nUnesite koliko brojeva zelite unijeti u listu: ");
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		br = RandBr();
		PushStog(h, br);
	}
	succ = Ispis(h->next);

	printf("\nUnesite koliko brojeva zelite izbrisati iz liste: ");
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		PopRed(h);
	}

	succ = Ispis(h->next);
	succ = Brisi(h);

	return OKAY;
}

int Err()
{
	printf("Nešto nece!");

	return ERR;
}

int RandBr()
{

	return rand() % (GG - DG + 1);
}

int PushStog(Pozicija h, int broj)
{
	
	Pozicija q = NULL;
	
	q = (Pozicija)malloc(sizeof(struct Cvor));
	if (NULL == q) {
		printf("Nece alokacija(push stog)");
		return ERR;
	}
	q->br = broj;

	q->next = h->next;
	h->next = q;
	

	return OKAY;
}

int PopStog(Pozicija h)
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

int PushRed(Pozicija h, int broj)
{

	while (h->next != NULL)
		h = h->next;

	PushStog(h, broj);

	return OKAY;
}

int PopRed(Pozicija h)
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

int Ispis(Pozicija h)
{
	
	while (h != NULL) {
		printf("%d ", h->br);
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