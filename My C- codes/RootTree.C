#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TH1F.h"
#include "TBenchmark.h"
#include "TRandom.h"
#include "TSystem.h"


using namespace std;


void RootTree()
{
  TFile *f1 = new TFile("RECREATE.root","RECREATE");
  TTree *t1 = new TTree("t1","EventsTree");
  
  float F1,F2,F3;
  int i1,i2,i3;
  vector<int> v1;

  i1=1.0,i2=2.0,i3=3.0;
  F1=1.1,F2=2.2,F3=3.3;
  
  
  //integer Branches
  t1->Branch("i1",&i1,"i1/I");
  t1->Branch("i2",&i2);
  t1->Branch("i3",&i3);
  //Float Branches
  t1->Branch("F1",&F1);
  t1->Branch("F2",&F2);
  t1->Branch("F3",&F3);

  //Vector Branches
  t1->Branch("v1",&v1);

  for(int j=0; j<10; j++)
    {
      v1.push_back(j);
      // t1->Fill();
    }
  
  for(int i=0; i<10; i++)
    {  
      i1+=1.0;
      i2+=1.0;
      i3+=1.0;
      
      F1+=1.1;
      F2+=1.1;
      F3+=1.1;

      v1.clear();
      v1.push_back(i);
	
      t1->Fill();
    }
  //t1->Print();
  t1->Write();
  f1->Close();
}
