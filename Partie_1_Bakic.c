#include <stdio.h>
#include <time.h>

#define ISNOT !=
#define NOT !
#define AND &&
#define OR ||
#define then

//Fonction exponentielle (itérative)

float expo(){
    float r = 1;
    int n = 1;
    for(int i = 2; i<34; i++){
        r = r + (float)1/n;
        n = n*i;
        }
        return r;
}


//fonction puissance 


float puissance(float x, int n){
    
    if(n==0) return 1;
    if(n<0) return (1/puissance(x,-n));
    if(n==1) return x;
    
    float res = puissance(x, n/2);
    
    if(n%2 == 0){
        
        return res*res;
        
        }else{
        
        return res*res*x;
    } 
}


//On implante ici les différentes fonctions puissance pour les comparer avec la notre

float puissanceBis1(float x , int n){
    
    float res = 1;
    
    for(int i = 1; i<=n; i++){
        
        res = res * x; 
    }
    return res;
}


float puissanceBis2(float x , int n){
    
    if(n==0){
        
        return 1;
        
    }else{
        
        return puissanceBis2(x, n-1)*x;
    }
    
}

float puissanceBis3(float x , int n){
    
    if(n==0) return 1;
    
    if(n<0) return (1/puissanceBis3(x,-n));
    
    if(n==1) return x;
    
    if(n%2 == 0){
        return puissanceBis3(x, n/2)*puissanceBis3(x, n/2) ;
        
        }else{
        
        return puissanceBis3(x, n/2)*puissanceBis3(x, n/2)*x;
    } 
    
    
}

//Fonction d'Ackermann

//Itératif

int ack(int m , int n){
    
    if(m==0){
        return n+1;
        
    }else{
        
        int r = 1;
        
        for(int i = 1; i <= n+1; i++){
            
            r = ack(m-1, r);   
        }
        return r;
    }
    
}

//Récursif pur

int ackRec(int m , int n){
    
    if(m==0){
        
        return n+1;

    }else{

        if(n==0){
            return ackRec(m-1,1);
            
        }else{
            
            return ackRec(m-1,ackRec(m,m-1));

        }
    }
    
    
}
    
   
//La suite 

//Version itérative

float suite(int n){
    
    if(n==0) return 1;
    
    float x = 1;
    
    for(int i = 0; i<=n; i++){
        
        x = x+(1/x);

        
    }
    return x; 
}

//Version récursive

float suiteRec(int n){
    
    if(n==0) return 1;
    
    float xr = suiteRec(n-1);
    return xr + (1/xr);
    
}



    

int main(){
    
    //PARTIE 1 

    //exponentielle 
    printf("e vaut %f\n\n", expo());

    //puissance

    //temps de calcul
    
    //Bis1

    clock_t deb = clock();
    float calcul = puissanceBis1(3 , 8);
    clock_t fin = clock();

    printf("la fonction puissanceBis1 calcule 3^8 en %lu secondes\n\n", fin - deb);

    //Bis2

    deb = clock();
    calcul = puissanceBis2(3 , 8);
    fin = clock();

    printf("la fonction puissanceBis2 calcule 3^8 en %lu secondes\n\n", fin - deb);

    //Bis3

    deb = clock();
    calcul = puissanceBis3(3 , 8);
    fin = clock();

    printf("la fonction puissanceBis3 calcule 3^8 en %lu secondes\n\n", fin - deb);

    //Notre fonction puissance

    clock_t deb1 = clock();
    float calcul1 = puissance(3 , 8);
    clock_t fin1 = clock();

    printf("notre fonction puissance calcule 3^8 en %lu secondes\n\n", fin1 - deb1);

    //Fonction d'Ackermann
    printf("A(0,0) = %d\n\n", ack(0,0));
    printf("A(1,0) = %d\n\n", ack(1,0));
    printf("A(2,0) = %d\n\n", ack(2,0));
    printf("A(3,0) = %d\n\n", ack(3,0));
    printf("A(4,0) = %d\n\n", ack(4,0));

    //Suite

    //version itérative

    printf("X100 = %f\n\n", suite(100));

    //version récursive

    printf("X100 = %f\n\n", suiteRec(100));

    return 0;
    
}

