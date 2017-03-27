#include<iostream>
#include<fstream>
#include <vector>

using namespace std;

void ecalfit()
{
  string   line;
  ifstream myfile;
  
  const  int ncol = 3;
  const  int nevt = 2200000;
  
  double sens[nevt][ncol] = {0};
  
  double Eta[nevt]={0};
  double Phi[nevt]={0};
  double Edep[nevt]={0};
  
  int      ievt = 0;
  
  int n=23;
  int m=1;
  
  char number[20];
  
  for(int i =1;i<n;i++)
    {
      if(!myfile.is_open())
        {
          sprintf(number, "a%d.txt",m );
          myfile.open(number);
        }
      
      while (getline(myfile,line))
	{
	  ievt+=1;
	  stringstream s_in(line);
	  
	  
	  for (int icol = 0; icol < ncol; icol++)
	    {
	      if (s_in>>sens[ievt][icol])
		{ 
		  
		} 
	      else
		{
		  cout<<"error reading data in line "<<ievt<<endl;
		} 
	      //cout<<sens[ievt][icol]<<"    ";
	    } 
	  
	  
	  //cout<<endl;
	  
	  Eta[ievt] = sens[ievt][0];
	  Phi[ievt] = sens[ievt][1];
	  Edep[ievt] = sens[ievt][2];
	  
	  
	  // cout<<"la la la la         " <<Eta[ievt]<<"    "<<Phi[ievt]<<"    "<<Edep[ievt]<<endl;
	  
	  
	  
	  //	Edep[ievt] += Edep[ievt-1];
	  //	cout<<"BBla BBla BBla BBla         "<<ievt<<"BBla BBla    "<<Edep[ievt]<<endl;
	  
	  
 
	  
	  
	  for (int j = 0; j < ievt; j++)
	    {//cout<<"Eta[j]=" <<Eta[j] <<"    "<<"Phi[j]=" <<Phi[j] << endl;
	      if(Eta[j]==Eta[ievt] && Phi[j]==Phi[ievt])
		{
		  Edep[ievt] += Edep[j];
		  Eta[j]=0;
		  Phi[j]=0;
		  Edep[j]=0 ;
		}
	    }
	}
      myfile.close();
      m+=1; 
      
    }
  for(ievt=0;ievt<=nevt;ievt++)
    {
      cout<<Eta[ievt]<<"    "<<Phi[ievt]<<"    "<<Edep[ievt]<<endl;
    } 
  
  
  
  
  return;
}
