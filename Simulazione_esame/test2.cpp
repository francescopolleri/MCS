#include "poly.h"
#include<iostream>
#include<vector>

using namespace std;

int main(){
  vector<double> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  poly pol(v);

  double y=pol.eval(1);

  cout<<y<<endl;

}