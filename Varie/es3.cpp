#include"stud.h"
#include<iostream>
#include<vector>
#include<algorithm>

bool comp(const stud& a,const stud& b){
     if(a.anno()<b.anno())
        return true;
    else    
        return false;
}   

int main(){

std::vector<stud> elenco;

stud s1("rossi",2000);
stud s2("neri",2002);
stud s3("bianco",1998);

elenco.push_back(s1);
elenco.push_back(s2);
elenco.push_back(s3);

std::sort(elenco.begin(),elenco.end(),comp);

for(auto n:elenco)
std::cout<<n.nome()<<" "<<n.anno()<<std::endl;


return 0;

}