#include "memoire.h"
#include "pile.h"

struct sCellule
{
    int Valeur;
    struct sCellule *Suivant;
};

struct sPile
{
    unsigned int Hauteur;
    bool Vide;
    bool Pleine;
    struct sCellule *Sommet;
};

Pile CreerPile(void)
{
    Pile pile = Allouer(sizeof(struct sPile));
    pile->Hauteur = 0;
    pile->Vide = true;
    pile->Pleine = false;
    pile->Sommet = NULL;
    return pile;
}

bool PileVide(Pile p)
{
    return p->Vide;
}

bool PilePleine(Pile p)
{
    return p->Pleine;
}

unsigned int HauteurPile(Pile p)
{
    return p->Hauteur;
}

void Empiler(Pile p, int Elt)
{
    if( p->Hauteur < HAUTEUR_MAX )
    {
        p->Hauteur++;
        p->Vide = false;
        struct sCellule *cell = Allouer(sizeof(struct sCellule));
        cell->Valeur = Elt;

        cell->Suivant = p->Sommet;
        p->Sommet = cell;
    }
    else
    {
        p->Pleine = true;
    }
}

int SommetPile(Pile p)
{
    if( p->Vide == true ) return 0;
    else return p->Sommet->Valeur;
}

int Depiler(Pile p)
{
    if( PileVide(p) ) return 0;
    else
    {
        int sommetVal = SommetPile(p);
        struct sCellule *pSommet = p->Sommet->Suivant;
        Liberer(p->Sommet);
        p->Sommet = pSommet;
        if( p->Sommet == NULL ) p->Vide = true;

        return sommetVal;
    }
}

void AfficherPile(Pile p)
{
    printf("<%d> ", p->Hauteur);

    struct sCellule *currentCell = p->Sommet;
    for( int i=0; i<(int)p->Hauteur; i++ ) 
    {
        printf("%d ", currentCell->Valeur);
        currentCell = currentCell->Suivant;
    }
}

void LibererPile(Pile p)
{
    struct sCellule *currentCell = p->Sommet, *temp;
    while( currentCell->Suivant != NULL ) // on traverse (et libere) les cellule jusqu'a la derniere
    {
        temp = currentCell->Suivant;
        Liberer(currentCell);
        currentCell = temp;
    }
    Liberer(currentCell); // on libere la derniere cellule
    Liberer(p); 
}
