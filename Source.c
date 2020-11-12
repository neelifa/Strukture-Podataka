/*Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
èitaju iz datoteke. */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR (-1)
#define OKAY 0
#define lng 1024

typedef struct poli* Polinom;
struct poli {
	double Koef;
	int Exp;
	Polinom next;
};

int Odabir();
int Err();
int UnosDat(Polinom p, char* fileName);
int UnosString(Polinom p, char* line);
int SortUnos(Polinom p, double koef, int exp);
int Unos(Polinom p, double koef, int exp);
int ZbrajanjePol(Polinom p, Polinom q, Polinom r);
int MnozenjePol(Polinom p, Polinom q, Polinom r);
int IspisPol(Polinom p);


int main() {

	int succ = Odabir();
	if (succ == OKAY)
		printf("\n\nSve je dobro! <3");
	else
		Err();

	return 0;
}

int Odabir() {
	int c; 
	int succ;
	char poli1[lng] = "pol1";
	char poli2[lng]= "pol2";

	struct poli p1;
	struct poli p2;
	struct poli rez;

	p1.next = NULL;
	p2.next = NULL;
	rez.next = NULL;
	
	succ = UnosDat(&p1, &poli1);
	if (succ != OKAY)
		printf("Nece unos1");
	succ = IspisPol(p1.next);

	succ = UnosDat(&p2, &poli2);
	if (succ != OKAY)
		printf("Nece unos2");
	succ = IspisPol(p2.next);

	printf("Odaberite operaciju koju želite izvršiti:\n1 - Zbrajanje polinoma\n2 - Mnozenje polinoma\n");
	scanf("%d", &c);
	
	switch (c) {
	case(1):
		succ = ZbrajanjePol(p1.next, p2.next, &rez);//saljemo prvi stvarni element od p1 i p2
		if (succ != OKAY)
			printf("Neæe zbrajanje!");
		break;

	case(2):
		succ = MnozenjePol(p1.next, p2.next, &rez);//saljemo prvi stvarni element od p1 i p2
		if (succ != OKAY)
			printf("Neæe zbrajanje kraljice!");
		break;

	default:
		Err();
		return ERR;
	}	
	succ = IspisPol(p1.next);
	succ = IspisPol(p2.next);
	succ = IspisPol(rez.next);

	return OKAY;
}

int Err() {
	printf("Error!");
	return OKAY;
}

int UnosDat(Polinom p, char* fileName) {

	FILE* fp = NULL;
	char line[lng] = {'\0'};


	if (strstr(fileName, ".txt") == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (fp == NULL){
		perror("datERROR");
		return ERR;
	}

	while (!feof(fp)) {
		memset(line, '\0', lng); //popunjava svaki clan stringa sa \0
		fgets(line, lng - 1, fp);//Kupi sve iz datoteke osim zadnjeg \0 znaka
		UnosString(p, line);
	}// ? Može i bez while ako podrazumjevamo da naša datoteka ima samo jedan redak ? (Jer koristimo fgets a ona kupi citav redak)

	fclose(fp);

	return OKAY;
}

int UnosString(Polinom p, char* line) {
	int ret = 2; //Koristimo return vrijednost od sscanf (Broj elemenata koji je procito)
	double p_koef = 0;
	int p_exp = 0;
	int n = 0;

	while(1){
		ret = sscanf(line, "%lf %d %n", &p_koef, &p_exp, &n);
		line += n;
		if (ret != 2)//Ovde je "beskonacna petlja" while(1) jer ne mogu nikako drugacije napravit provjeru kolko je stvari procito sscanf
			break;// nakon sto je provjerio jeli procito dva broja izlazi iz petlje ako nije sto znaci da smo upisali neke gluposti da ih nebi procito osim ako su dva broja
		SortUnos(p, p_koef, p_exp);
	}

	return OKAY;
}
int SortUnos(Polinom p, double koef, int exp) {

	int succ;
	Polinom temp;

	while (p->next != NULL && p->next->Exp < exp)
		p = p->next;

	if (p->next != NULL && p->next->Exp == exp) {
		p->Koef += koef;

		if (p->next->Koef == 0) {
			temp = p->next;
			p->next = p->next->next;
			free(temp);
		}
	}
	else
		succ = Unos(p, koef, exp);
	
	return OKAY;
}
int Unos(Polinom p, double koef, int exp) {

	Polinom q;

	q = (Polinom)malloc(sizeof(struct poli));
	if (q == NULL)
		return ERR;

	q->Exp = exp;
	q->Koef = koef;

	q->next = p->next;
	p->next = q;

	return OKAY;
}

int ZbrajanjePol(Polinom p, Polinom q, Polinom r) {

	double t_koef;
	int t_exp;

	while (p != NULL && q != NULL) {
		if (p->Exp == q->Exp) {
			t_koef = p->Koef + q->Koef;
			t_exp = p->Exp; //Moze i p->Exp
			SortUnos(r, t_koef, t_exp);
			p = p->next;
			q = q->next;
		}
		else if(p->Exp < q->Exp){
			t_koef = p->Koef;
			t_exp = p->Exp;
			SortUnos(r, t_koef, t_exp);
			p = p->next;
		}
		else{
			t_koef = q->Koef;
			t_exp = q->Exp;
			SortUnos(r, t_koef, t_exp);
			q = q->next;
		}
	
	}
	while (p != NULL) {
		t_koef = p->Koef;
		t_exp = p->Exp;
		SortUnos(r, t_koef, t_exp);
		p = p->next;
	}

	while (q != NULL) {
		t_koef = q->Koef;
		t_exp = q->Exp;
		SortUnos(r, t_koef, t_exp);
		q = q->next;
	}

	return OKAY;
}
int MnozenjePol(Polinom p, Polinom q, Polinom r) {

	Polinom pamti_q = q;
	double t_koef;
	int t_exp;
	int succ;

	while (p != NULL) {
		while (q != NULL) {
			t_koef = p->Koef * q->Koef;
			t_exp = p->Exp + q->Exp;
			succ = SortUnos(r, t_koef, t_exp);
			q = q->next;
		}
		q = pamti_q;
		p = p->next;
	}

	return OKAY;
}
int IspisPol(Polinom p) {

	printf("\nIspis polinoma:\n\n");

	while (p != NULL) {
		printf("(%.2lf * x ^ %d) ", p->Koef, p->Exp);
		p = p->next;
	}

	return OKAY;
}