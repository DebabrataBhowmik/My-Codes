#include<iostream>
#include<fstream>

#include <vector>
#include "TGraph.h"
using namespace std;

double range;
TGraph finalFitGraph;
TGraph *bestFitGraph;

TGraph *fitGraph(TGraph *graphCV, vector<double> voltVec){
  double n=graphCV->GetN();
  double leftPoint = voltVec[0];
  double rightPoint = voltVec[n-1];

  vector<TF1> vecFunc;
  
  //  for(int subFit=2; subFit<5; subFit++){
  int subFit=3;
  for(int numFit=1;numFit<subFit+1; numFit++){
    string funcName = "lin" + to_string(numFit);
    cout<<funcName<<endl;
    TF1 lin1(funcName.c_str(), "pol1");
    //TF1 lin2("lin2", "pol1");
    vecFunc.push_back(lin1);
  }
    double sumChi2NDF=pow(10,50);

    for(int i=2; i<voltVec.size()-2; i++){

      graphCV->Fit(&vecFunc[0],"","",leftPoint,voltVec[i]);
      graphCV->Fit(&vecFunc[1],"+","",voltVec[i],rightPoint);
      
      //graphCV->Fit("pol1","","",leftPoint,voltVec[i]);    
      //graphCV->Fit("pol1","+","",voltVec[i],rightPoint);
      
      double chi2_1=vecFunc[0].GetChisquare();
      cout<<chi2_1<<endl;
      double NDF_1=vecFunc[0].GetNDF();
      double chi2_2=vecFunc[1].GetChisquare();
      cout<<chi2_2<<endl;
      double NDF_2=vecFunc[1].GetNDF();
      //double chi2_2=lin2.GetChisquare();
      //double NDF_2=lin2.GetNDF();
      double sumChi2NDF_temp=(chi2_1/NDF_1)+(chi2_2/NDF_2);
      if(sumChi2NDF_temp<sumChi2NDF){
	//if(i==10){
	sumChi2NDF=sumChi2NDF_temp;
	finalFitGraph = *graphCV;
	bestFitGraph=&finalFitGraph;
	//bestFitGraph->Draw("A*");
	//bestFitGraph=graphCV;
	range = voltVec[i];
      }
    }
    
    //}
  //bestFitGraph->Draw("A*");
  //finalFitGraph.Draw("A*");
  return bestFitGraph;
  //return &finalFitGraph;
}

void AnalyzeDioda(string cv_data){
  ifstream inFile;
  TGraph graph_cv;
  
  inFile.open(cv_data);
  vector<double> volt;
  vector<double> capaci;

  int lineNum =0;  
  for(string line; getline(inFile, line); ) {
    istringstream in(line);
    double voltage, capacitance, OneovC2;
    in >> voltage >> capacitance;
    cout<<voltage<<"\t"<<capacitance<<endl;
    OneovC2=1/pow(capacitance,2);
    volt.push_back(-voltage);

    capaci.push_back(OneovC2);    
    lineNum++;
  }
  
  TGraph *graphCV = new TGraph(volt.size(), &volt[0], &capaci[0]);
  //graphCV->Draw("AL*");

  TGraph *fitG = new TGraph();
  fitG=fitGraph(graphCV,volt);
  //TCanvas* mycan=new TCanvas("mycan","",1000,800);
  fitG->Draw("A*");
  gPad->SetGrid();
  //mycan->Draw();
  
  cout<<"range="<<range<<endl;
}




