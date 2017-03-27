#include<iostream>
#include<fstream>
#include <vector>

using namespace std;

void ecaltest(){
  string   line;
  ifstream myfile;

  const  int ncol = 1;
  const  int nevt = 200;

  double sens[nevt][ncol] = {0};

  double Eta[nevt]={0};
  double Phi[nevt]={0};
  double Edep[nevt]={0};

  double ss[nevt]={0};

  int      ievt = 0;

  int n=21;
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
                                                                                                                                      
            }
	  ss[ievt] = sens[ievt][0];
	}
	      myfile.close();
	      m+=1;
	    
    }
  for(ievt=1;ievt<=nevt;ievt++)
    {
       cout<<ss[ievt]<<endl;
    }


	}
