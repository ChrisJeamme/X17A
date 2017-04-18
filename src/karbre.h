#ifndef KARBRE_H
    #define KARBRE_H

    #define K 8

    //Types de noeuds
    #define VIDE 0
    #define PLEIN 1
    #define RIEN 2

    //Couleurs
    #define BLANC 7
    #define VERT 2

    typedef int element;

    struct noeud
    {
        element racine;
        struct noeud* fils[K];
    };
    typedef struct noeud* karbre;

    karbre kArbreVide();
    karbre kConsArbre(element e,...);
    karbre kFils(int ieme, karbre A);
    element kRacine(karbre A);
    int kEstVide(karbre A);
    void kAfficher(karbre A);
    void kAfficher_bis(karbre A, int prof);
    void kAfficher(karbre A);
    void afficher_racine(int racine);
    void afficher_feuille(int couleur);
    void p(char* texte);
    void printc(int couleur_texte, int couleur_fond, char* texte);
#endif