#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

void test()
{
  TCanvas*c1 = new TCanvas ("c1", "mean and sigma distribution", 900, 700);
  c1-> Divide(2,1);

  TH1D*h1 = new TH1D ("h1","distribution of mean", 200, 0.0, 2.0);
  TH1D*h2 = new TH1D ("h2","distribution of sigma", 200, 0.0, 20.0);
  TRandom2 r;
  for (int j = 0; j<10000; j++)

    {

      // TRandom r;

  double x[20];

  float a=0;

  for (int i = 0; i<5; i++)
    {
      x[i] = r.Uniform(0,1);
      cout << x[i] << endl;
      h1->Fill(2*x[i]);

      a = a + x[i];
    }
  double u = a/5;
  cout << "mu =" << u << " ";
  //cout << " "<<endl;
  //h1->Fill(2*u);


  float s = 0;
  //double s[10];
  for (int i = 0; i<5; i++)
    {
      float si = (x[i]-u)*(x[i]-u);
      s = s + si;
      //cout << "s[i] =" << si << endl;
    }
  
  s = s/(5 - 1);
  h2->Fill(48*s);
  cout << "s=" <<s << endl;

  cout << "Next" <<endl;
    }
  cout << "Hello" <<endl;
  //c1 -> cd (1);
  //h1->Draw();

  //c1 -> cd (2);
  //h2->Draw();


  
  TF1 *f1 = new TF1("f1","[0]*x*exp([1]*x)",0,30);
  f1->SetParameters(300,-0.5);
  //f1->SetParameters(0.25,-0.5);
  //  f1->Draw("same");
  f1->Draw();
  h2->Draw("same");
  

}



