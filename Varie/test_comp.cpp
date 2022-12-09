#include<iostream>
#include<cmath>
#include "Compatibility.h"

using namespace std;

int main(){

double a=1;
double b=2;
double ea=0.1;
double eb=0.1;

Compatibility c(a,b,ea,eb);

double g = c.Comp();

cout<<g<<endl;
cout<<c<<endl;




}