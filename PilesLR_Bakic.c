
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

//typedef enum { FALSE, TRUE} bool;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste � vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);


/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


void initVide( Liste *L)
{
    *L = NULL ;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

int premier(Liste l)
{
    return l->nombre ; 
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}

void empile(int x, Liste *L)
{
      *L = ajoute(x,*L) ; 
}

Liste suite(Liste l)
{
    return l->suivant ;
}


void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l)
{
    if(estVide(l))
        printf("\n");
    else
    {
        printf("%d ", premier(l));
        affiche_rec(suite(l));
    }
}


void affiche_iter(Liste l)
{
    Liste L2 = l;
    while(!estVide(L2))
    {
        printf("%d ", premier(L2));
        L2 = suite(L2);
    }
    printf("\n");
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
         return 0 ;
    else return (1 + longueur_rec(l->suivant)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P ISNOT NULL)
    {   P = P->suivant ;
        cpt++ ;
    }
    return cpt ;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD (Liste *L)
          // *L non NULL ie liste non vide
{
     if ( ((**L).suivant) == NULL )
            depile(L) ;   // moralement : depile(& (*L)) ;
     else VD (& ( (**L).suivant )) ;
}

void VireDernier_rec (Liste *L)
{
     if ( (*L) ISNOT NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
    if ( (*L) ISNOT NULL)
    {
        while ( ((**L).suivant) ISNOT NULL )
                 L = & ( (**L).suivant ) ;
        free(*L) ;
        *L = NULL ;
     }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L);
        VideListe(L);
    }
      
}

/*************************************************/
/*                                               */
/*           Mes fonctions                       */
/*                                               */
/*************************************************/


/***************************************Fonction ZeroEnDeuxiemePosition*****************************************/

bool zdp(Liste l){

    return premier(suite(l)) == 0;

}

/****************************************Fonction queDesZeros***************************************************/

bool queDesZeros(Liste l){

    if(estVide(l)) return true;

    if(premier(l)!=0) return false;

    return queDesZeros(suite(l));

}

/****************************************Fonction compte0Initiaux***************************************************/

//version récursive (sans ss-fonctions)

int recCZI(Liste l){
    
    if (estVide(l)) return 0;
    if(premier(l)==0){
        return 1 + recCZI(suite(l));
    }
    return recCZI;
}

//version itérative

int itCZI(Liste l){

    int cpt = 0;
    Liste temp = l;

    while( (NOT(estVide(temp))) && (premier(temp)==0) ){
        temp = suite(temp);
        cpt++;
    }

    return cpt;
}

//versions récursives terminales
//1

//ici la sous-fonction
int rectermCZI(int cum, Liste l){

    if( (premier(l)!=0) || estVide(l) ){

        return cum;
    }

    return rectermCZI(cum + 1, suite(l));

}

//la fonction principale
int termCZI(Liste l){

    return rectermCZI(0,l);

}

//2

//ici la sous-procédure

void rtCZI(int *cum, Liste l){

    if( NOT( (premier(l)!=0) || estVide(l) )){

        *cum = *cum + 1;
        rtCZI(cum, suite(l)); 
    }

}

//la fonction

int tCZI(Liste l){

    int cum = 0;
    rtCZI(&cum, l);
    return cum;

}

/*************************************************************************Fonction IntersectionTriee********************************************************************************************/

void it(Liste l1, Liste l2, Liste *l3){

    if( NOT(estVide(l1)) && NOT(estVide(l2)) ){

        if(premier(l1)==premier(l2)){

            empile(premier(l1), l3);
            it(suite(l1), suite(l2), l3);

        }

        if( premier(l1) < premier(l2) ){

            it(suite(l1), l2, l3 );
        
        }else{

            it(l1, suite(l2), l3);
        }

    }


}



Liste intersectionTriee(Liste l1, Liste l2){

    Liste l3;
    initVide(&l3);
    it(l1, l2, &l3);
    return l3;

} 


/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

void poup (Liste l){
        printf("Double Affichage \n") ;
        affiche_rec(l) ;
        affiche_iter(l) ;

        printf("Longueur en double %d %d \n\n", 
                           longueur_rec(l), 
                           longueur_iter(l) 
               ) ;
}


int main(int argc, char** argv)
{
   Liste l ;

        initVide (&l) ;

          poup(l) ;

             empile(4, &l) ;

          poup(l) ;

             empile(5, &l) ;
             empile(6, &l) ;
             empile(7, &l) ;
             empile(8, &l) ;
             empile(9, &l) ;

          poup(l) ;

        VireDernier_rec  (&l) ;
        VireDernier_iter (&l) ;
        depile(& l) ;

          poup(l) ;

    VideListe(&l);

    /***************************TEST DE ZDP*********************************/

    Liste s;

    initVide(&s);

    empile(5,&s);
    empile(3,&s);
    empile(0,&s);
    empile(3,&s);

    poup(s);

    printf("retour de test de zdp (qui doit valoir 1) : %d\n\n", zdp(s));
/*
    Liste z;

    initVide(&z);

    empile(5,&z);
    empile(3,&z);
    empile(3,&z);
    empile(3,&z);

    poup(z);

    printf("retour de test de zdp (qui doit valoir 0) : %d\n\n", zdp(s));

*/
    /***************************TEST DE queDesZeros*********************************/

    Liste r;

    initVide(&r);

    empile(0,&r);
    empile(0,&r);
    empile(0,&r);
    empile(0,&r);

    printf("retour de test de queDesZeros (qui doit valoir 1) : %d\n\n", queDesZeros(r));

    /*Liste w;

    initVide(&w);

    empile(0,&w);
    empile(0,&w);
    empile(2,&w);
    empile(0,&w);

    printf("retour de test de queDesZeros (qui doit valoir 0) : %d\n\n", queDesZeros(w));
    */

/***************************TEST DE Comte0Initiaux*********************************/

    /*Liste w;

    initVide(&w);
    empile(0,&w);

    printf("TEST recCZI %d", recCZI(w));
    */

    /*
    Liste w;

    initVide(&w);
    empile(2,&w);
    empile(0,&w);
    empile(1,&w);
    empile(0,&w);

    printf("TEST termCZI %d", tCZI(w));
    */

   /***************************TEST DE IntersectionTriee*********************************/

    Liste w;

    initVide(&w);
    empile(9,&w);
    empile(8,&w);
    empile(6,&w);
    empile(4,&w);
    empile(4,&w);
    empile(2,&w);
    empile(2,&w);
    empile(2,&w);

    Liste z;

    initVide(&z);
    empile(8,&z);
    empile(8,&z);
    empile(4,&z);
    empile(4,&z);
    empile(3,&z);
    empile(3,&z);
    empile(2,&z);
    empile(2,&z);
    empile(1,&z);
    empile(1,&z);

    Liste y;

    initVide(&y);
    empile(1,&y);

    Liste k = suite(y);
    
    //y = intersectionTriee(w,z);

    poup(k);


    return 0;
    

}





