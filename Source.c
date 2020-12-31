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

struct cvor;
struct _stog;

typedef struct cvor* Stablo;
typedef struct _stog* Stog;

struct cvor {
	char* imeMape;
	Stablo djete;
	Stablo nextBrat;
};

struct _stog {
	Stablo cvorStabla;
	Stog next;
};

int mainMenu();
int Push(Stog s, char* mapa);
int Pop(Stog s);
int makeDir();
int changeDir();
int backDir();
int showDir();
int delTree();
int delStog();

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

}

int Push(Stog h, char* mapa)
{

}
int Pop(Stog h)
{

}
int makeDir();
int changeDir();
int backDir();
int showDir();
int delTree()
{
	
}
int delStog();