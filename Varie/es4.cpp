#include<iostream>
#include"Vector.h" //siccome sto usando la classe con Template devo specificare di che tipo sono gli elementi dei vettori del file
#include<vector>
#include<fstream>
#include<algorithm>

bool comp(double a,double b){
     if(a<b)
        return true;
     else
        return false;
}

int main(){

std::string nomefile;                       //apertura file con i vettori
std::cout<<"digita nome file"<<std::endl;
std::cin>>nomefile;
std::ifstream file(nomefile);

std::vector<Vector<double>> vec;
std::vector<double> mod;

Vector<double> V;          //lettura vettori dal file
int i=0;
while(file>>V){
    vec.push_back(V);
    mod.push_back(V.modulo());
    i++;
}

Vector<double> S;       //vettore Somma
double x,y,z;
for(int j=0;j<vec.size();j++){
S=S+vec[j];
}

std::cout<<S<<std::endl;

std::sort(mod.begin(),mod.end(),comp);   //ordinamento in base al modulo

for(int n=0;n<mod.size();n++){  
std::cout<<mod[n]<<std::endl;
}
 return 0;
}