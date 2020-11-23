/*Za dvije sortirane liste L1 i L2 (mogu se proèitati iz datoteke ili unijeti ruèno, bitno je
samo da su sortirane), napisati program koji stvara novu vezanu listu tako da raèuna:
a) L1 unij L2,
b) L1 presjek L2.
Liste osim pokazivaèa na slijedeæu strukturu imaju i jedan cjelobrojni element, po
kojem su sortirane.*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR (-1)
#define OKAY 0
#define size 255

typedef struct cvor* Pozicija;

struct cvor {
	int el;
	Pozicija next;
};

int Odabir();
int DatUnos(Pozicija h, char* fileName);
int StringUnos(Pozicija h, char* line);
int SortUnos(Pozicija h, int elem);
int Unos(Pozicija h, int elem);
int Unija(Pozicija h, Pozicija p, Pozicija r);
int Presjek(Pozicija h, Pozicija p, Pozicija r);
int Ispis(Pozicija h);

int main() {

	int succ;

	succ = Odabir();
	if (succ == OKAY)
		printf("Sve je dobro<3.");
	else
		printf("Error kraljice,...");

	return 0;
}

int Odabir() {
	char dat1[size] = "dat1";
	char dat2[size] = "dat2";
	int succ = 0, c = 0;
	struct cvor head1, head2, r;
	head1.next = NULL;
	head2.next = NULL;
	r.next = NULL;

	succ = DatUnos(&head1, dat1);
	succ = DatUnos(&head2, dat2);

	succ = Ispis(head1.next);
	succ = Ispis(head2.next);
	printf("Zelite li operaciju unije ili presjeka?\n\n1 - Unija lista\n2 - Presjek lista\n");
	scanf("%d", &c);

	switch (c) {
	case(1):
		succ = Unija(head1.next, head2.next, &r);
		if (succ != OKAY)
			printf("Neæe unija!");
		break;

	case(2):
		succ = Presjek(head1.next, head2.next, &r);
		if (succ != OKAY)
			printf("Neæe presjek kraljice!");
		break;

	default:

		return ERR;
	}

	succ = Ispis(r.next);

	return OKAY;
}

int DatUnos(Pozicija h, char* fileName) {

	int succ = 0;
	FILE* fp = NULL;
	char line[size] = { '\0' };


	if (strstr(fileName, ".txt") == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		perror("datERROR");
		return ERR;
	}

	while (!feof(fp)) {
		fgets(line, size, fp);
		succ = StringUnos(h, line);
	}

	fclose(fp);

	return OKAY;

}
int StringUnos(Pozicija h, char* line) {
	int ret = 0;
	int n = 0, succ = 0;
	int elem;


	while (1) {
		ret = sscanf(line, "%d %n", &elem, &n);
		line += n;
		if (ret != 1)
			break;
		succ = SortUnos(h, elem);
	}

	return OKAY;
}

int SortUnos(Pozicija h, int elem) {
	int succ = 0;

	while (h->next != NULL && h->next->el < elem)
		h = h->next;

	if (h->next != NULL && h->next->el == elem)
		return OKAY;

	succ = Unos(h, elem);

	return OKAY;
}

int Unos(Pozicija h, int elem) {

	Pozicija q = NULL;

	q = (Pozicija)malloc(sizeof(struct cvor));
	if (q == NULL)
		return ERR;

	q->el = elem;

	q->next = h->next;
	h->next = q;

	return OKAY;
}
int Unija(Pozicija h, Pozicija p, Pozicija r) {
	int elem = 0;
	int succ = 0;

	while (h != NULL && p != NULL) {
		if (h->el == p->el) {
			elem = h->el;
			succ = Unos(r, elem);
			h = h->next;
			p = p->next;
			r = r->next;
		}
		else if (h->el > p->el) {
			elem = p->el;
			succ = Unos(r, elem);
			p = p->next;
			r = r->next;
		}
		else {
			elem = h->el;
			succ = Unos(r, elem);
			h = h->next;
			r = r->next;
		}
	}

	while (h != NULL) {
		elem = h->el;
		succ = Unos(r, elem);
		h = h->next;
		r = r->next;
	}

	while (p != NULL) {
		elem = p->el;
		succ = Unos(r, elem);
		p = p->next;
		r = r->next;
	}

	return OKAY;
}
int Presjek(Pozicija h, Pozicija p, Pozicija r) {

	int elem = 0, succ = 0;

	while (h != NULL && p != NULL) {
		if (h->el == p->el) {
			elem = h->el;
			succ = Unos(r, elem);
			h = h->next;
			p = p->next;
			r = r->next;
		}
		else if (h->el > p->el) {
			p = p->next;
		}
		else {
			h = h->next;
		}
	}


	return OKAY;
}

int Ispis(Pozicija h) {

	while (h != NULL) {
		printf("%d ", h->el);
		h = h->next;
	}

	printf("\n");

	return OKAY;
}