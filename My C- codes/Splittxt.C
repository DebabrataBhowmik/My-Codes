#include<iostream>
#include<fstream>

using namespace std;

void Splittxt()
{
int n = 0,d=1;
 ifstream myfile1;
 ofstream myfile2;
 string line;
 char number[20];
 string rootfilename;

myfile1.open("motherfile.txt");

while (getline(myfile1,line))
  {
    stringstream s_in(line);
    s_in>>rootfilename;
    n=n+1;
    if(!myfile2.is_open())
      {
	sprintf(number, "daughter%d.txt",d );
	myfile2.open(number);
      }
    myfile2 << rootfilename << endl;
    
    if(n%20==0)
      {
	myfile2.close();
	d+=1;
      }   
    
  }
}
