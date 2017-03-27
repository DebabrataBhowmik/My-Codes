#include <iostream>
#include <cmath>
using namespace std;


void Loop()
{
  float r, x;
  //Trandom r;
  //TH1F h();
TH1F *h = new TH1F("h", "uniform random", 100, -5. , 5.);
TH1F *h2 = new TH1F("h2", "uniform random", 100, -5. , 5.);
//loop 1000
for (i=0;i<100000000; i++)
{
r = gRandom->Uniform();
//x = r.Uniform()
x = 10*r -5 ;
 h -> Fill(sin(x));
 h2 -> Fill(x);
}
h->Draw();
h2->Draw("same");
}
