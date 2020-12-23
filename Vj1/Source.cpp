/* Napisati program koji prvo proèita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i uèitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime,apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <malloc.h>
#define ERR (-1)
#define MAX_NAME 256

typedef struct _stud
{
	char FirstName[MAX_NAME];
	char LastName[MAX_NAME];
	int result;
}student;

int BrojanjeRedaka();
int Unos(student*, int);
int Ispis(student*, int);

int main() {
	
	student *a;
	int br, pom_unos, pom_ispis;

	//Broj redaka u datoteci student.txt
	br = BrojanjeRedaka();

	if (br == ERR)
		printf("Datoteka nije otvorena!(br.redaka)");

	printf("Broj redaka je: %d\n", br);


	//Dinamièka alokacija strukture u koju spremamo podatke
	a = (student*) malloc(br * sizeof(student));

	//Pozivanje funkcije za Unos
	pom_unos = Unos(a, br);

	if (pom_unos == ERR)
		printf("Datoteka nije otvorena!(unos)");

	//Pozivanje funkcije za Ispis
	pom_ispis = Ispis(a, br);

	if (pom_ispis != 0)
		printf("Kraljice.... Neæe ispis!");

		free(a);

	return 0;

}

int BrojanjeRedaka() {

	FILE* fp = fopen("student.txt", "r");
	int brojac = 0;

	if (fp == NULL)
	{
		printf("Kraljice ne radi ti ovo....");
		return ERR;
	}

	//Vraæanje na poèetak u datoteci
	//Ovo je dobro napraviti jer ne znamo gdje se nalazimo u njoj pa je dobro vratit se na pocetak
	rewind(fp);

	while (!feof(fp))
	{
		fscanf(fp, "%*s %*s %*d");
		brojac++;
	}
	fclose(fp);

	return brojac;

}

int Unos(student* a, int br) {

	int i;
	//Otvaranje datoteke

	FILE* fp = fopen("student.txt", "r");
	int brojac = 0;

	if (fp == NULL)
	{
		printf("Kraljice ne radi ti ovo....");
		return ERR;
	}

	//Vraæanje na poèetak u datoteci
	rewind(fp);

	//Unos 
	for (i = 0; i < br; i++)
		fscanf(fp, "%s %s %d", a[i].FirstName, a[i].LastName, & a[i].result);


	fclose(fp);

	return 0;
}

int Ispis(student* a, int br) {
	int i;
	
	for (i = 0; i < br; i++)
		printf("%s %s %d %.2f\n", a[i].FirstName, a[i].LastName, a[i].result, ((float)a[i].result / 50) * 100);

	return 0;
}

