#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ISNOT !=
#define NOT !
#define AND &&
#define OR ||
#define then
 


typedef struct bloc_image { 
    bool toutnoir ;
    struct bloc_image *fils[4] ; 
    } 
    bloc_image ;

typedef bloc_image *image ;

image Construit_blanc(){
    return NULL;
}

image Construit_noir(){
    image b = (image)malloc(sizeof(bloc_image));
    b->toutnoir = true;
    b->fils[0] = NULL;
    b->fils[1] = NULL;
    b->fils[2] = NULL;
    b->fils[3] = NULL;
    return b;
}

image Construit_composee( image ihg, image ihd, image ibg, image ibd){

    image b = (image)malloc(sizeof(bloc_image));
    b->toutnoir = false;
    b->fils[0] = ihg;
    b->fils[1] = ihd;
    b->fils[2] = ibg;
    b->fils[3] = ibd;

    return b;

}


//REVERIFIER L'AFFICHAGE NORMAL AU NIVEAU DES PLUS

void affiche_normal(image b){
    if(b == NULL){
        printf("B ");
    }else{
        if(b->toutnoir){
         printf("N ");
    
        }else{
            printf("+ ");
            for(int i = 0; i<4; i++){
                affiche_normal(b->fils[i]);
            }
        }
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//fonction  affiche_profondeur

void affiche_profondeur(image b,int k){
    
    if(b==NULL){
        printf("B%d ", k);
    }
    else{
        
        if(b->toutnoir){
         printf("N%d ", k);
        }
        else{
            
            printf("+%d ", k);
            k = k+1;
            for(int i = 0; i<4; i++){
                affiche_profondeur(b->fils[i],k);
                
            }
            
        }
    }
}

bool EstNoire(image b){
    if(b==NULL){
        return false;
    }else{
        return b->toutnoir;
    }
}

bool EstBlanche(image b){
    if(b==NULL){
        return true;
    }else{
        if(b->toutnoir) return false;
        for(int i = 0; i<4; i ++){
            if(EstNoire(b->fils[i])) return false;
        }
        return true;
    }
}

//////////////////////////////////////////////////////////////////////////////

image Copie(image p){
    if(p==NULL){
        return NULL;
    }
    if(p->toutnoir==true){
        image q = Construit_noir();
        return q;
    }
    else{
        image q = Construit_composee(Copie(p->fils[0]), Copie(p->fils[1]), Copie(p->fils[2]), Copie(p->fils[3]));
        return q;
    }
}

//Fonction rendMemoire

void rendMemoire(image *img){

    if((*img) != NULL){

        for(int i = 0; i<4; i++){

            rendMemoire(&((*img)->fils[i]));

            free(*img);

        }
    }
}

///////////////////////////////////////////////////////////////////////////////////

double aire(image b){
    if(EstNoire(b)) return 1.0;
    if(EstBlanche(b)) return 0.0;
    return (1.0/4.0)*( aire(b->fils[0]) + aire(b->fils[1]) + aire (b->fils[2]) + aire(b->fils[3]) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////

int cSIG(image b){
    if(EstNoire(b) OR EstBlanche(b)) return 0;
    double a = aire(b);
    if((a>= (1.0/3.0)) && (a<= (2.0/3.0))){
        return 1 + cSIG(b->fils[0]) + cSIG(b->fils[1]) + cSIG(b->fils[2]) + cSIG(b->fils[3]);
    }else{
        return 0 + cSIG(b->fils[0]) + cSIG(b->fils[1]) + cSIG(b->fils[2]) + cSIG(b->fils[3]);
    }
}

//Négatif

void negatif(image *b){
    if(EstNoire(*b)){
       *b = NULL;
    }else{
        if(EstBlanche(*b)){
            if(NOT(*b==NULL)){
                (*b)->toutnoir = true;
            }else{
                *b = Construit_noir();
            }  
        }else{
            for(int i = 0; i<4; i++){
                negatif( &((*b)->fils[i]));
            }
        }
    } 
}

/////////////////////////////////////////////////////////////////////////////////////////

image Lecture() { 
    char tmp = getchar(); 
    if (tmp == '+') { 
        image a = Lecture(), 
        b = Lecture(), 
        c = Lecture(), 
        d = Lecture(); 
        return Construit_composee(a, b, c, d); 
    } else if (tmp == 'B') { 
        return Construit_blanc(); 
    } else if (tmp == 'N') { 
        return Construit_noir(); 
    } else { 
        return Lecture(); 
    }
} 


////////////////////////////////////////////////////

bool UnionNoire(image *b, image *d){
    if(EstNoire(*b) || EstNoire(*d)){
        return true;
    }
    else if(EstBlanche(*b) && EstBlanche(*d)){
        return false;
    }
    else if((EstBlanche(*b) && EstNoire(*d)) || (EstBlanche(*d) && EstNoire(*b)) ){
        return true;
    }else{
        if(EstNoire(*b) || EstBlanche(*b)){
            return (UnionNoire(b,&((*d)->fils[0])) && UnionNoire(b,&((*d)->fils[1]))
                && UnionNoire(b,&((*d)->fils[2])) && UnionNoire(b,&((*d)->fils[3])));

        }else if(EstNoire(*d) || EstBlanche(*d)){
            return (UnionNoire(&((*b)->fils[0]),d) && UnionNoire(&((*b)->fils[1]),d)
            && UnionNoire(&((*b)->fils[2]),d) && UnionNoire(&((*b)->fils[3]),d));
        } else {
            return (UnionNoire(&((*b)->fils[0]),&((*d)->fils[0])) && UnionNoire(&((*b)->fils[1]),&((*d)->fils[1]))
            && UnionNoire(&((*b)->fils[2]),&((*d)->fils[2])) && UnionNoire(&((*b)->fils[3]),&((*d)->fils[3])));
        }
    }
}




void intersection(image *a, image *b){
    
    if((EstBlanche(*a) && EstNoire(*b)) || (EstNoire(*a) && EstBlanche(*b))){
    *a = Construit_blanc();
    }
    if((NOT(EstNoire(*a) && EstNoire(*b)) && (NOT(EstBlanche(*a) && EstBlanche(*b))))){
        if(EstNoire(*a) || EstBlanche(*a)){
            for(int i =0; i < 4; i++){
                intersection( a, &((*b)->fils[i]));
            }

        }else{ 

            if(EstNoire(*b) || EstBlanche(*b)){
                for(int i =0; i < 4; i++){
                    intersection( &((*a)->fils[i]), b);
                }  
            }else{
                for(int i =0; i < 4; i++){
                    intersection( &((*a)->fils[i]), &((*b)->fils[i]));
                }  
            }
        }
    }

}

int main(){
    
    //QUELQUES IMAGES

    image b1 = Construit_composee(
                    Construit_noir(),
                    Construit_composee(Construit_blanc(),Construit_blanc(),Construit_noir(),Construit_blanc()),
                    Construit_blanc(),
                    Construit_composee( Construit_noir(),
                                        Construit_composee(
                                                            Construit_noir(),
                                                            Construit_noir(),
                                                            Construit_blanc(),
                                                            Construit_composee(Construit_noir(),Construit_blanc(),Construit_noir(),Construit_noir())
                                                            ),
                                        
                                        Construit_blanc(),
                                        Construit_noir()
                                        )
                    );
    image o = Construit_composee(Construit_composee(Construit_noir(),Construit_blanc(),Construit_noir(),Construit_blanc()),
                                Construit_composee(Construit_blanc(),Construit_noir(),Construit_noir(),Construit_blanc()),
                                Construit_blanc(),
                                Construit_composee(Construit_noir(),Construit_noir(),Construit_blanc(),Construit_blanc())
                                );
    image w = Construit_composee(Construit_noir(),
                                Construit_composee(Construit_noir(),Construit_blanc(),Construit_noir(),Construit_noir()),
                                Construit_noir(),
                                Construit_composee(Construit_noir(),Construit_blanc(),Construit_noir(),Construit_noir())
                                );
    
    
    //TESTS 
    printf("\n");
    printf("Affichage normal et prodondeur image o : \n");
    affiche_normal(o);
    printf("\n");
    affiche_profondeur(o,0);

    printf("\n");

    image b = Construit_blanc();
    image n = Construit_composee(Construit_blanc(),Construit_noir(),Construit_noir(),Construit_noir());
    
    printf("\n");
    printf("Aire de n :\n");
    printf("%f\n",aire(n));
    printf("\n");
    
    printf("Image b1 :\n");
    affiche_normal(b1);
    printf("\n");
    printf("CompteSousImagesGrises de b1 : \n");
    printf("%d\n",cSIG(b1));
    printf("\n");
    
    printf("Affichage de image n :\n");
    affiche_normal(n);
    negatif(&n);
    
    printf("\nAffichage négatif de image n :\n");
    affiche_normal(n);
    printf("\n");
    
    printf("Entrez 2 images : \n ");
    image c = Lecture();
    image d = Lecture();

    printf("\n");
    printf("\nUnion noire des 2 images rentrées : \n ");
    printf("%d", UnionNoire(&c,&d));

    printf("\nintersection des 2 images rentrées : \n ");
    intersection(&c,&d);
    affiche_normal(c);

   //+0 N1 +1 B2 B2 N2 B2 B1 +1 N2 +2 N3 N3 B3 +3 N4 B4 N4 N4 B2 N2

}
