#ifndef _PUNTO
#define _PUNTO

using namespace std;

class punto{
    public:
    punto(double x=0,double y=0):m_x(x),m_y(y){}

    double X(){return m_x;}
    double Y(){return m_y;}

    private:
    double m_x;
    double m_y;
};




















#endif