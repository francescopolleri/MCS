#include<iostream>
#include<cmath>
#include "Compatibility.h"

using namespace std;

int main(){

double a=1;
double b=1.3;
double ea=0.1;
double eb=0.1;

Compatibility c(a,b,ea,eb);

double g = c.Comp();

cout<<g<<endl;
cout<<c<<endl;

cout<<c.BestValue()<<"+/-"<<c.BestValueError()<<endl;


return 0;


}