#include"Particella.h"
#include<iostream>
#include<cmath>

int main(){

Particella<double> p1(1.5,6);

Particella<double> p2(4,7.5);

double c1=p1.charge();
double c2=p2.charge();

double m1=p1.mass();
double m2=p2.mass();

std::cout<<p1<<std::endl;

    return 0;
}