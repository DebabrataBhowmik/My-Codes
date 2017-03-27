#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

void testfit()
{
  TF1 *fa1 = new TF1("fa1","x*x",0,10);

  TF1 *fa2 = new TF1("fa2","x",0,10);
 fa1->Draw();
 fa2->Draw("same");
}
