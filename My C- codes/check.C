#include<iostream>
#include<fstream>
#include "TROOT.h"
#include "TF1.h"
#include "TRandom.h"


double myfunction(double *x, double *p)
{  
  double f = p[0]*exp(-0.5*((x[0]-p[1])/p[2])*((x[0]-p[1])/p[2]));
  return f;
}


  void check()
  {
    TF1 *f1 = new TF1("myfunc",myfunction,-5,5,3);
    f1->SetParameters(4000,0,1);

    f1->Draw();
    
    
    double x[1];
    double p[3];
    
    double *a = x;
    double *b =  p;
    x[0] = 3.0;
    p[0] = 4000;
    p[1] = 0;
    p[2] = 1;
    
    // double *a ;
    //double *b ;
    
    //a=x;
    // b=p;
    
    cout <<"bla"<<endl;
    cout << myfunction (a, b)<<endl;
    // cout << myfunction (c, d)<<endl;
    
  
    
  }
