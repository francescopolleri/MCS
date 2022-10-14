#ifndef _VECTORN
#define _VECTORN
#include <vector>

template<class T>
class VectorN:public Vector<T>{
public:
using vector<T>::vector;

VectorN<T> operator+(const VectorN&)const;

VectorN<T> operator*(double)const;


private:

};

#endif;