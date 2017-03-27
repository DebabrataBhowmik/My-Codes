#include<iostream>
#include<fstream>
#include "TROOT.h"
#include "TF1.h"
#include "TRandom.h"
#include "TStopwatch.h"

using namespace std;

double myfunction(double *x, double *p)
{
  double f = p[0]*exp(-0.5*(((x[0]-p[1])/p[2])*((x[0]-p[1])/p[2])));
  return f;
}

void fitting()
{
  double initialx=-10.0;
  double finalx=10.0;
  int numberofbins=100;
  double xrange = (finalx-initialx);
  double binsize = (xrange/numberofbins);

  TH1F*h1 = new TH1F("h1", "Gaussian random number fitting", numberofbins, initialx, finalx);
  TRandom2 a;
  // double b[1000000];
  //vector v[]
  vector<double> v;
  int numberofevents = 100000;
  for (int j=0;j<numberofevents;j++)
    { 
      //  b[j] = a.Gaus(0,2);   
      v.push_back(a.Gaus(0,2)); 
      //     h1->Fill(b[j]);
      //     h1->Fill(v[j]);
     h1->Fill(a.Gaus(0,2));
    }
  h1->Draw();
  /*
    double A,mu,sigma2;
    double f(double x, double A ,double mu,double sigma2){return A*exp(-0.5*((x-mu)/sigma2)**2);}  
    A=4000.0;
    mu=0.0;
    sigma2=1.0;
    TF1*f1=new TF1("f1","[0]*exp(-0.5*((x-[1])/[2])**2)",-3,3);
    f1->SetParameters(A,mu,sigma2);
  */
  double x[1];
  double p[3];
  
  double *X = x;
  double *P =  p;
  
  double finalmu;
  double finalsigma; 
  double finalA;

  double finalchi2 = 5000000;
  double counterofloops=0.0;

  for (double mu=-0.5;mu<0.5;mu+=0.1)
    {
      for (double sigma2=0.5;sigma2<2.5;sigma2+=0.1)
	{
	  double A =(1/(sqrt(2*3.14*(sigma2*sigma2))))*(binsize*numberofevents);
	  p[0] = A;
	  p[1] = mu;
	  p[2] = sigma2;
	  	  
	  double chi2=0;
	  //double initialfitbinnumber=20;
	  //double finalfitbinnumber=80;

	  for (i=20;i<80;i++)
	    {
	      double xi=h1->GetXaxis()->GetBinCenter( i+1 );
	      double yi=h1->GetBinContent( i+1 );
	    
	      x[0]=xi;
	      counterofloops=counterofloops+1.0;
	      cout<<counterofloops<<endl;
	      double fi= myfunction(X, P);
	   	      
	      chi2=chi2+(((yi-fi)*(yi-fi))/yi);
	    }
	  if (chi2<finalchi2)
	    {
	      finalchi2=chi2;
	      finalA=A;	     
	      finalmu = mu;
	      finalsigma2=sigma2;
	    }
	}
    }

  ndf=60;
  finalchi2=finalchi2/ndf;
  cout<<"finalmu=  "<<finalmu<<"  finalsigma2= "<<finalsigma2<<" finalchi2="<<finalchi2<<endl;  
  
  TF1 *f1 = new TF1("myfunc",myfunction,initialx,finalx,3);
  f1->SetParameters(finalA,finalmu,finalsigma2);
    
  f1->Draw("same");  
  return;
}
