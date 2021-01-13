#include <stdio.h> 
#include <stdlib.h>

#define OKAY 0
#define ERR (-1)

struct _cvor;
typedef struct _cvor* Stablo;

typedef struct _cvor {
	int el;
	Stablo L;
	Stablo D;
}Cvor;

Stablo kreirajCvor(int el);
Stablo unesiCvor(Stablo s, Stablo el);
void ispisInOrder(Stablo s);
Stablo traziCvor(Stablo s, int el);
Stablo traziMax(Stablo s);
Stablo traziMin(Stablo s);
Stablo brisiCvor(Stablo s, int el);
Stablo brisiSve(Stablo s);

int main() 
{
	Stablo root = NULL;
	Stablo p = NULL;
	Stablo trazi = NULL;
	Stablo brisi = NULL;

	p = kreirajCvor(16);
	root = unesiCvor(root, p);

	p = kreirajCvor(7);
	root = unesiCvor(root, p);

	p = kreirajCvor(19);
	root = unesiCvor(root, p);

	p = kreirajCvor(6);
	root = unesiCvor(root, p);

	p = kreirajCvor(8);
	root = unesiCvor(root, p);

	p = kreirajCvor(3);
	root = unesiCvor(root, p);

	ispisInOrder(root);

	puts("\n");

	trazi = traziCvor(root, 7);
	printf("%d", trazi->el);

	puts("\n");

	brisiCvor(root, 3);
	ispisInOrder(root);

	brisiSve(root);

	return OKAY;
}

Stablo kreirajCvor(int el)
{
	Stablo p = NULL;

	p = (Stablo)malloc(sizeof(Cvor));
	if (NULL == p) {
		printf("Nije uspijela alokacija");
		return NULL;
	}
	p->el = el;
	p->D = NULL;
	p->L = NULL;

	return p;
}

Stablo unesiCvor(Stablo s, Stablo p)
{
	if (NULL == s) 
		return p;

	if (s->el > p->el) {
		s->L = unesiCvor(s->L, p);
	}
	else if (s->el < p->el) {
		s->D = unesiCvor(s->D, p);
	}
	else {
		printf("Element %d veæ postoji u stablu!", p->el);
		free(p);
	}

	return s;
}

void ispisInOrder(Stablo s)
{
	if (NULL == s) 
		return;
	

	ispisInOrder(s->L);
	printf("%d ", s->el);
	ispisInOrder(s->D);

}

Stablo traziCvor(Stablo s, int el)
{
	if (NULL == s) 
		return NULL;

	if (s->el == el) {
		return s;
	}

	else if (s->el > el) {
		return traziCvor(s->L, el);
	}

	else /*if(s->el < el)*/ {
		return traziCvor(s->D, el);
	}
}

Stablo traziMax(Stablo s)
{
	if (NULL != s) {
		while (NULL != s->D)
			s = s->D;
	}

	return s;
}

Stablo traziMin(Stablo s)
{
	if (NULL != s) {
		while (NULL != s->L)
			s = s->L;
	}

	return s;
}

Stablo brisiCvor(Stablo s, int el)
{
	if (NULL == s) {
		printf("Ne postoji element s vrijednosti %d. ", el);
		return s;
	}
	else if (el < s->el) {
		s->L = brisiCvor(s->L, el);
	}
	else if(el > s->el) {
		s->D = brisiCvor(s->D, el);
	}
	else {
		Stablo temp = NULL;
		if (NULL != s->L && NULL != s->D) {
			temp = traziMin(s->D);
			s->el = temp->el;
			s->D = brisiCvor(s->D, temp->el);
		}
		else {
			temp = s;

			if (NULL == s->L) {
				s = s->D;
			}
			else {
				s = s->L;
			}

			free(temp);
		}
	}

	return s;
}

Stablo brisiSve(Stablo s) {
	if (NULL != s) {
		brisiSve(s->L);
		brisiSve(s->D);
		free(s);
	}
	return NULL;
}