#include<iostream>
#include<fstream>

using namespace std;

double xmax=0.95;
double xmin=-0.95;    

double alpha ;
double beta ;  

double xval(double x, double aa, double bb){
  double fx = (1+aa*x+bb*x*x)/( (xmax-xmin) + (aa/2)*(xmax*xmax-xmin*xmin) + (bb/3)*(xmax*xmax*xmax - xmin*xmin*xmin) );
  return fx;
}

void Likelihood(){
  cout<<"=======================Hello World================="<<endl;

  int x1=-1, x2=1;
  int div =200;
  int Nuniform = 10000;
  int NExp = 500;

  TH1D *h_uniform = new TH1D("h_uniform","Uniform random distribution", div, 0, 1);
  TH1D *h_transform = new TH1D("h_transfrm","Transformed random distribution", div, x1, x2);

  TH2D *h_alphabeta2D = new TH2D("h_aplha_beta","alpha-beta scattered plot", 100, 0, 1, 100, 0, 1);
   
  //double scale = double(div)/double(Nuniform);
  double scale = 1/double(Nuniform);


  //TF1* f1 =new TF1("f1","(1+0.5*x+0.5*x*x)/(2+(2*0.5)/3)",-1,1);
  TF1* f1 =new TF1("f1","(1+0.5*x+0.5*x*x)/( (0.95-(-0.95)) + (0.5/2)*(0.95*0.95-(0.95*0.95)) + (0.5/3)*(0.95*0.95*0.95-(0.95*0.95*(-0.95))) ) ",-1,1);
  TF1* f2 =new TF1("f1","(1+[0]*x+[1]*x*x)/( (0.95-(-0.95)) + ([0]/2)*(0.95*0.95-(0.95*0.95)) + ([1]/3)*(0.95*0.95*0.95-(0.95*0.95*(-0.95))) ) ",-1,1);
  //TF1* f2 =new TF1("f1","(1+0.473*x+0.513*x*x)/( (0.95-(-0.95)) + (0.473/2)*(0.95*0.95-(0.95*0.95)) + (0.513/3)*(0.95*0.95*0.95-(0.95*0.95*(-0.95))) ) ",-1,1);

  vector<vector<double>> y;
  for (int nExp = 0; nExp<NExp; nExp++){
    TRandom3 r;
    r.SetSeed (nExp);
    y.push_back(vector<double>());
    //cout<<al<<"===================================" <<beta<<endl;   
    double a = 0.5/3;
    double b = 0.5/2;
    
    double p = -b/(3*a);
    double s = 1/(3*a);
    double t = s-p*p;
      
    for(int i=0; i<Nuniform; i++){
      //double x = r.Uniform(-1,1);
      double x = r.Uniform(-0.6,0.4);
      //h_uniform->Fill(x);
      
      double k = ( (0.5/3)*(xmax*xmax*xmax - xmin*xmin*xmin) + (0.5/2)*(xmax*xmax-xmin*xmin) +(xmax-xmin) )*x;
      double q = p*p*p + (b-3*a*k)/(6*a*a);
      y[nExp].push_back(cbrt(q + sqrt(q*q+t*t*t) ) + cbrt(q - sqrt(q*q+t*t*t) ) +p);
      h_transform->Fill(y[nExp][i]);
    } 
  }

  TCanvas* c1 = new TCanvas("c1","c1",1000,900);
  c1->Divide(2,2);
  c1->cd(1);
  h_uniform->Scale(scale);
  //h_uniform->Draw();
  //h_uniform->GetYaxis()->SetRangeUser(-2.0,2.0);
  //gPad->SetGridx();
  //gPad->SetGridy();
  
  double Intg=h_transform->Integral();
  h_transform->Scale(1/(Intg*(double(x2-x1)/double(div)) ));
  h_transform->GetYaxis()->SetRangeUser(0.18,1.0);
  
  h_transform->Draw("hist");
  gPad->SetGridx();
  gPad->SetGridy();


  
  vector<double > vCurrExp;
  
  for (int nExp = 0; nExp<NExp; nExp++){
    //vCurrExp = y[nExp];
    double max_log_Likelihood = -999999.;
    double alpha_cap = 0.;
    double beta_cap = 0.;
    
    for(int al=0; al<60; al++){
      double delalpha=-0.2+0.01*al;
      for(int be=0; be<60; be++){
	double delbeta=-0.3+0.01*be;
        
	double Likelihood = 1.0;
	double log_Likelihood = 0.0;
	
	alpha = 0.5+delalpha;
	beta = 0.5+delbeta;
	
	
	for(int i=0; i<Nuniform; i++){
	  double fy = (1+alpha*y[nExp][i]+beta*y[nExp][i]*y[nExp][i])/( (xmax-xmin) + (alpha/2)*(xmax*xmax-xmin*xmin) + (beta/3)*(xmax*xmax*xmax - xmin*xmin*xmin) );
	  log_Likelihood += log(fy);
	}
	
      
	if(log_Likelihood>max_log_Likelihood) {
	  max_log_Likelihood = log_Likelihood;
	  alpha_cap = alpha;
	  beta_cap = beta;
	}
      }
    }
      cout<<max_log_Likelihood<<"  "<<alpha_cap << "  "<<beta_cap<<endl;
      f2->SetParameters(alpha_cap,beta_cap);
      
      h_alphabeta2D->Fill(alpha_cap, beta_cap);    
  }
  
  
  f2->Draw("same");
  f2->SetLineColor(kRed);
  f1->Draw("same");
  f1->SetLineColor(kBlue);
  
  
  c1->cd(2);  
  h_alphabeta2D->Draw();
  
}
