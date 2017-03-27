#include<iostream>
#include<fstream>
using namespace std;


class pointer
{
public:
  
  pointer();
  ~pointer();

};

pointer::pointer()
{
  cout << "object is created";
};
  
pointer:: ~pointer()
{
};

int main()
{
  //  pointer::p; 
  int x = 10;
  int *p;
  p=&x;
  cout<<*p<<"  at  "<<p<<"   "<<endl;

  int* q = &x;
  cout<< *q<<"  at   "<<  q<<endl;
 

    int u = *q;
    cout <<u<<"  at "<<&u <<endl;
  
return 0;
}
