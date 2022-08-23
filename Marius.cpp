#include "Matrice.hpp"
#include "Vecteur.hpp"
#include "File.hpp"
#include <iomanip>
#include "math.h"

#define E 0.00000000000001

using namespace std;


Vecteur residu(Matrice A , Vecteur b,Vecteur &x);
double testArret(Vecteur R);
Vecteur Resolution(Matrice A , Vecteur b);
void EquationDisplay(Matrice matrice , Vecteur vect);



int main(){
    cout<<"Veuillez bien verifier que les donnees de la matrice soit dans le matrice.txt "<<endl;
    cout<<"Et aussi que les donnees de la matrice colonne du second membre soit dans le vecteur.txt "<<endl;
    
    File f1("matrice.txt");
    File f2("vecteur.txt");
    int n;
    cout<<"Entrer la taille du systeme d'equation = ";
    cin>>n;
    Matrice A(f1,n);
    Vecteur b(f2,n);

    EquationDisplay(A,b);

    cout<<"La solution est :"<<endl;
    Resolution(A,b).display();
    return 0;
}


/*
recupere le vecteur residu 
initialise en meme temps la valeur initiale de la suite Xn   (x)
*/
Vecteur residu(Matrice A , Vecteur b,Vecteur &x){
    int n = (int)A.getMatrice().size();
    Vecteur residu(n);
    double val;

    for(int i=0;i<n;i++){
        x.setVecteur(i,1);
    }

    for(int i=0; i<n; i++){
        double p = 0;
        for(int k=0; k<n; k++){
            p += A.getMatrice()[i][k] * x.getVecteur()[k];
        }
        val = b.getVecteur()[i] - p;
        residu.setVecteur(i,val);
        val=0;
    }
    return residu;
}

/*
Retourne la sommes des valeur absolu du vecteur Residu 
*/
double testArret(Vecteur R){
    double r = 0;
    int n=R.getSize();
    for(int i=0;i<n;i++){
        r += fabs(R.getVecteur()[i]);
    }
    return r;
}

/*
itere la suite jusque a ce que A.Xn-b soit inferieur a notre Epsilon fixe
retourne le vecteur solution
*/
Vecteur Resolution(Matrice A , Vecteur b){
    int c=0;
    int n = b.getSize();
    Vecteur x(n);
    Vecteur res=residu(A,b,x);
    double sommeRes = testArret(res);
    double s=0;
    double temp = 0;
    while(E < sommeRes && c<2000){
        for(int i=0;i<n;i++){
            for(int k=0;k<n;k++){
                s+=A.getMatrice()[i][k]*x.getVecteur()[k];
            }
            temp = b.getVecteur()[i] - s;
            res.setVecteur(i,temp);
            temp = 0;

            temp = x.getVecteur()[i] + res.getVecteur()[i]/A.getMatrice()[i][i];
            x.setVecteur(i,temp);

            s=0;
            temp=0;
            cout<<"interation : "<<c<< " ....";x.display();
            c++;
        }
        sommeRes = testArret(res);
    }
    return x;
}


/*
@param Matrice matrice et vecteur vect
rendent une meilleur affichage de l'equation matrice.X=vect
*/
void EquationDisplay(Matrice matrice , Vecteur vect){
    cout<<endl<<"-------AFFICHAGE DE L' EQUATION'----------"<<endl;
    int dim = (int)matrice.getMatrice().size();
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            cout<< matrice.getMatrice()[i][j] <<"  X"<<j<<setw(10);
        }
        cout<<setw(8)<<"= "<<setw(3)<<vect.getVecteur()[i]<<endl;
    }
    cout<<"----------------------------------------"<<endl;
};