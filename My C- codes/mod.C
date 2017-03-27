#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;

int main()
{
 double a =4.3;
 double c;
 int b = modf(a, &c);
 cout<<c<<endl;
 return 0;
}
