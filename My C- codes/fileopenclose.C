#include<iostream>
#include<fstream>
#include <vector>


using namespace std;

void fileopenclose()
{
  int i,n = 0,m=1;
  ofstream myfile;
  char number[20];
  
  for(i=1;i<=200;i++)
    {
      n=n+1;
      if(!myfile.is_open())
	{
	  sprintf(number, "a%d.txt",m );
	  myfile.open(number);
	}	
      
      myfile<<i<<"yes I can write"<<endl;
      
      
      if(n%10==0)
	{
	  myfile.close(); 	
	  m+=1;
	}	
    } 
  
  
  
  
  /*
    else if(i>10 && i<21)
    { 
    if(!myfile.is_open())
    {
    myfile.open("b.txt");
    }
    
    myfile<<i<<"  "<<"Oh I can write in b file also"<<endl;
    
    if(i==10){
    myfile.close(); 
    }
    }
    
  */
  
  
  
  
}
