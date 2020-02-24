#include<iostream>
#include<fstream>

using namespace std;

double xmax=0.95;
double xmin=-0.95;    

double alpha ;
double beta ;  

double xval(double x){
  double fx = (1+alpha*x+beta*x*x)/( (xmax-xmin) + (alpha/2)*(xmax*xmax-xmin*xmin) + (beta/3)*(xmax*xmax*xmax - xmin*xmin*xmin) );
  return fx;
}

void Random(){
  cout<<"=======================Hello World================="<<endl;
  int x1=-1, x2=1;
  int div =200;
  int Nuniform = 10000;

  TH1D *h_uniform = new TH1D("h_uniform","Uniform random distribution", div, 0, 1);
  TH1D *h_transform = new TH1D("h_transfrm","Transformed random distribution", div, x1, x2);
  
  //double scale = double(div)/double(Nuniform);
  double scale = 1/double(Nuniform);

  double max_log_Likelihood = 0.;
  double alpha_cap = 0.;
  double beta_cap = 0.;
  
  for(int al=0; al<600; al++){
    double delalpha=-0.01+0.0001*al;
    for(int be=0; be<600; be++){
      double delbeta=-0.08+0.0001*be;
      
      alpha = 0.5+delalpha;
      beta = 0.5+delbeta;
      //cout<<al<<"===================================" <<beta<<endl;   
      double a = beta/3;
      double b = alpha/2;
    
      double p = -b/(3*a);
      double s = 1/(3*a);
      double t = s-p*p;
      
      double Likelihood = 1;
      double log_Likelihood = 0;
      //double d=2;
      //cout<<d**3<<endl;
      //TF1* f1 =new TF1("f1","(1+0.5*x+0.5*x*x)/(2+(2*0.5)/3)",-1,1);
      TF1* f1 =new TF1("f1","(1+0.5*x+0.5*x*x)/( (0.95-(-0.95)) + (0.5/2)*(0.95*0.95-(0.95*0.95)) + (0.5/3)*(0.95*0.95*0.95-(0.95*0.95*(-0.95))) ) ",-1,1);
      TF1* f2 =new TF1("f1","(1+0.7*x+0.4*x*x)/( (0.95-(-0.95)) + (0.7/2)*(0.95*0.95-(0.95*0.95)) + (0.4/3)*(0.95*0.95*0.95-(0.95*0.95*(-0.95))) ) ",-1,1);
      
      TRandom3 r;
      for(int i=0; i<Nuniform; i++){
	//double x = r.Uniform(-1,1);
	//double x = r.Uniform(-2,1.0);
	double x = r.Uniform(-0.6,0.4);
	h_uniform->Fill(x);
	
	//double k = beta/3+alpha/2-1-x;
	double k = ( (beta/3)*(xmax*xmax*xmax - xmin*xmin*xmin) + (alpha/2)*(xmax*xmax-xmin*xmin) +(xmax-xmin) )*x;
	double q = p*p*p + (b-3*a*k)/(6*a*a);
      
	double y = cbrt(q + sqrt(q*q+t*t*t) ) + cbrt(q - sqrt(q*q+t*t*t) ) +p;
	
	//cout<<x<<"  "<<y<<endl;
	//double y = (1+alpha*x+beta*x*x)/(2+2*beta/3) ;
	//double y = (-2*x);
	h_transform->Fill(y);
	
	Likelihood *= xval(y);
	log_Likelihood += -log(xval(y));
	//cout<<i<<"  "<<xval(y)<<"  "<<Likelihood <<"  "<<log_Likelihood<<endl;    
      }
      h_uniform->Scale(scale);
      h_uniform->Draw();
      //h_uniform->GetYaxis()->SetRangeUser(-2.0,2.0);
      gPad->SetGridx();
      gPad->SetGridy();
      
      double Intg=h_transform->Integral();
      h_transform->Scale(1/(Intg*(double(x2-x1)/double(div)) ));
      
      //h_transform->Draw();
      h_transform->GetYaxis()->SetRangeUser(0.18,1.0);
      f2->Draw("same");
      f2->SetLineColor(kBlue);
      f1->Draw("same");

      if(log_Likelihood>max_log_Likelihood) {
	max_log_Likelihood = log_Likelihood;
	alpha_cap = alpha;
	beta_cap = beta;
      }
      //cout<<Likelihood<<"  "<<log_Likelihood<<endl;
      
    }
  }
  cout<<max_log_Likelihood<<"  "<<alpha_cap << "  "<<beta_cap<<endl;
}
