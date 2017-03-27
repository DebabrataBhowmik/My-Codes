#include<iostream>
#include<fstream>
using namespace std;


TRandom r;

TH1D* h1 = new TH1D("h1","HIS",200,-10,10);
TH1D* h2 = new TH1D("h2","HISTO",100,10,3400  );


double_t gauss(double zval, double muval, double sigmaval){
  double gval = (1/(2*3.14*sigmaval))*(TMath::Exp(-((zval-muval)*(zval-muval))/(2*sigmaval*sigmaval)));
  return gval;
}

double_t ss(double x){
  double sin = TMath::Sin(x);
  return sin;
}

void gaussian()
{
  //double x;
  //TF1 *func = new TF1("func",sin(x),0, 10);
  // func->Draw();
  
  for (int i=0; i<100000; i++)
    {
      double  x = r.Gaus(0,1);
      // cout << x << endl;
            
      h1-> Fill(x);
      
    }
  
  //double_t n[20000];
  //double_t z[20000];
  //double_t g[20000];
  //double chi2[200];
  //chi2[0] = 0;
  


  
double mu_f ;
double s_f;
  
  
  double chi22 = 10000000000000;

  // double g;
  double mu,sigma;
  for (mu = -0.5; mu<0.5; mu+=0.0001)
    {
      for(sigma = 0.1; sigma < 1.9; sigma+=0.00001)
	{
	  double chi2=0 ;
	  double j=80;
	  for (j = 80;j<121;j++)
	    {
	      //chi2[0] = 0;
	      double  n = h1->GetBinContent(j);
	      //cout<<n<<"    ";
	      
	      double z = h1-> GetXaxis()-> GetBinCenter(j);
	      //     cout<<v<<endl;
	      double g= gauss(z, mu, sigma);
	      
	      //double g = (1/(2*3.14*sigma))*(exp(-((z-mu)*(z-mu))/(2*sigma*sigma)));
	      //cout<<g<<endl;
	      //chi2[j] =chi2[j-1] + (((n[j] - g[j])*(n[j] - g[j]))/n[j]);
	      chi2 += (((n - g)*(n - g))/n);
	      //cout << chi2 <<endl;
	      //h2->Fill(u);
	    }
	  
	  /// cout << "chi2 = "<<chi2 <<endl;
	  if(chi2<chi22){
	    chi22 = chi2;
	    mu_f = mu;
	    s_f = sigma;
	  }
	  ///  cout<<"modified chi22 =  "<<chi22<<endl;
	  
	    ///cout <<"mu = "<<mu<<"    ";
	  /// cout <<"s=  "<<sigma<< endl;
	}
    }
  /// cout <<"Final chi22=    "<<chi22<<endl;  
    
  cout<<"final_mu = "<<mu_f<<"       "<<"final s ="<<s_f<<endl;

  /// func->SetParameters(mu,sigma);
  //f->Draw();



  h1-> Draw();
  //h2-> Draw("same");
  //  return 0;
}
