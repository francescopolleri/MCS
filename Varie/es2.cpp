#include <map>
#include <iostream>

int main(){
std::map<std::string,int> el;
el["rossi"]=123;
el["bianchi"]=456;
el["verdi"]=789;

for (auto n:el)
std::cout<<n.first<<" "<<n.second<<std::endl;

auto it=el.find("rossi");
if(it!=el.end())
std::cout<<"Ho trovato"<<" "<<it->second<<std::endl;
else
std::cout<<"Not found"<<std::endl;

}