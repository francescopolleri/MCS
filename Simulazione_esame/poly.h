#ifndef _POLY
#define _POLY

#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

class poly:public vector<double>{
    public:
    using vector::vector;

    poly(const vector<double>& p):vector<double>(p){}
    
    poly operator+(poly pol){
        poly P()
    }
    double eval(double x){
        double y=m_p0 + x*m_p1 + pow(x,2)*m_p2 + pow(x,3)*m_p3;
        return y;
    }

    private:
    
};




#endif