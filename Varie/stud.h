#ifndef _STUD
#define _STUD
#include<iostream>
#include<vector>

class stud{

public:

stud(std::string nome="",int anno=0):m_nome(nome),m_anno(anno){}

std::string nome() const {return m_nome;}
int anno() const {return m_anno;}


private:

std::string  m_nome;
int m_anno;

};
#endif
