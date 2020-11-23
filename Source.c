/*Napisati program koji pomoæu vezanih listi simulira rad:
a) stoga,
b) reda.
Napomena: Funkcija "push" sprema cijeli broj, sluèajno generirani u opsegu od 10 - 100.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS
#define ERR (-1)
#define OKAY 0
#define size 255
#define DG 10
#define GG 100

typedef struct Cvor* Pozicija;
struct Cvor {
	int br;
	Pozicija next;
};

int Odabir();
int Err();
int RandBr(); 
int PopStog();
int PushStof();
int PopRed();
int PushRed();

int main() {
	int succ;
	succ = Odabir();
	if (succ != OKAY) {
		printf("Neæe nešto!");
		return ERR;
	}

	else printf("Radi sve!<3");

	return 0;
};

int Odabir() {

}
int Err();
int RandBr();
int PopStog();
int PushStof();
int PopRed();
int PushRed();
