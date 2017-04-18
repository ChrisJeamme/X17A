#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "karbre.h"

karbre kArbreVide()
{
    return NULL;
}

karbre kConsArbre(element e,...)
{
    int i;
    karbre A = (struct noeud*) malloc(sizeof(struct noeud));

    va_list arguments;
    va_start(arguments, e);

        for(i=0; i<K; i++)
        {
            A->fils[i] = va_arg(arguments, karbre);
        }
        A->racine = e;

    va_end(arguments);

    return A;
}

karbre kFils(int ieme, karbre A)
{
    if(A!=NULL)
        return A->fils[ieme];
    return NULL;
}

element kRacine(karbre A)
{
    return A->racine;
}

int kEstVide(karbre A)
{
    return A==NULL;
}


void kAfficher(karbre A)
{
	kAfficher_bis(A, 0);
}


void kAfficher_bis(karbre A, int prof)
{
    int i;

	if(!kEstVide(A))
	{
		for(i=0; i<prof; i++)
			printf("   ");
        afficher_racine(A->racine);
		for(i=0; i<K; i++)
			kAfficher_bis(A->fils[i],prof+1);
	}
}

void afficher_racine(int racine)
{
    switch(racine)
    {
        case 0: //Vide
            afficher_feuille(BLANC);
        break;
        case 1: //Plein
            afficher_feuille(VERT);
        break;
        case 2:
            p("N");
        break;
    }
}

void afficher_feuille(int couleur)
{
    printf("\033[4%dm  \033[0m \n",couleur);
}

void p(char* texte)
{
    printf("\033[1;32;40m %s \033[0m \n",texte);
}

void printc(int couleur_texte, int couleur_fond, char* texte)
{
    printf("\033[1;3%d;4%dm %s \033[0m \n",couleur_texte,couleur_fond,texte);
}