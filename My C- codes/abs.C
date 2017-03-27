#include <iostream>
#include<fstream>

//#include <stdlib.h>
//#include <math.h>       /* fabs */

using namespace std;

void abs()
{
  int i1,i2;
  int a1,a2,af1,af2;
  
  float f1,f2,f3,f4,af3,af4,a;
  
  i1= 10;
  i2=-15;

  f1 = 3.3;
  f2 = -5.5;

  a1=abs(i1);
  a2=abs(i2);
 
  af1=fabs(i1);
  af2=fabs(i2);

  cout<<"Integer abs "<<i1<<" -> "<<a1<<endl<<i2<<" ->  "<<a2<<endl;  
  cout<<"Integer fabs"<<i1<<" -> "<<af1<<endl<<i2<<" ->  "<<af2<<endl;  
 
  f3=abs(f1);
  f4=abs(f2);
  
  af3=fabs(f1);
  af4=fabs(f2);
  
  cout<<"Float abs"<<f1<<" -> "<<f3<<endl<<f2<<" ->  "<<f4<<endl;  
  cout<<"Float fabs"<<f1<<" -> "<<af3<<endl<<f2<<" ->  "<<af4<<endl;  

  a=abs(6.6);
  cout<<a<<endl;
}
