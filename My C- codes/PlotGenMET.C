#include<iostream>
#include"TH1.h"
using namespace std;

void PlotGenMET(){

  TFile* file1=new TFile("2HDMa_mA200_ma150.root");
  TFile* file2=new TFile("2HDMa_mA300_ma150.root");
  TFile* file3=new TFile("2HDMa_mA400_ma150.root");
  TFile* file4=new TFile("2HDMa_mA500_ma150.root");
  TFile* file5=new TFile("2HDMa_mA600_ma150.root");

  TTree *tree1 = (TTree*)file1->Get("demo/tree_");
  TTree *tree2 = (TTree*)file2->Get("demo/tree_");
  TTree *tree3 = (TTree*)file3->Get("demo/tree_");
  TTree *tree4 = (TTree*)file4->Get("demo/tree_");
  TTree *tree5 = (TTree*)file5->Get("demo/tree_");

  TH1F* his1=new TH1F("his1","his1",100,0,600);
  TH1F* his2=new TH1F("his2","his1",100,0,600);
  TH1F* his3=new TH1F("his3","his1",100,0,600);
  TH1F* his4=new TH1F("his4","his1",100,0,600);
  TH1F* his5=new TH1F("his5","his1",100,0,600);

  tree1->Draw("genMET_>>his1");
  his1->Scale(1/his1->GetEntries());
  his1->SetLineColor(kRed);
  gStyle->SetOptStat(0);

  tree2->Draw("genMET_>>his2");
  his2->Scale(1/his2->GetEntries());
  his2->SetLineColor(6);

  tree3->Draw("genMET_>>his3");
  his3->Scale(1/his3->GetEntries());
  his3->SetLineColor(kBlue);

  tree4->Draw("genMET_>>his4");
  his4->Scale(1/his4->GetEntries());
  his4->SetLineColor(kGreen);

  tree5->Draw("genMET_>>his5");
  his5->Scale(1/his5->GetEntries());
  his5->SetLineColor(kBlack);

  TCanvas* c1 = new TCanvas("c1","c1",1000,900);

  his2->GetXaxis()->SetTitle("gen MET");
  his2->Draw("hist same");
  his3->Draw("hist same");
  his1->Draw("hist same");
  his4->Draw("hist same");
  his5->Draw("hist same");

  TLegend *legend = new TLegend(0.5,0.65,0.85,0.88);
  legend->SetHeader("2HDM+a model","C"); // option "C" allows to center the header
  legend->AddEntry("his1","mA=200 ma=150","l");
  legend->AddEntry("his2","mA=300 ma=150","l");
  legend->AddEntry("his3","mA=400 ma=150","l");
  legend->AddEntry("his4","mA=500 ma=150","l");
  legend->AddEntry("his5","mA=600 ma=150","l");
  legend->Draw();

  c1->SaveAs("genMET2.png");
  //tree1->Draw("genMET_");
  //TH1 *myh1 = (TH1*)gPad->GetPrimitive("htemp");
  //myh1->Scale(1/myh1->GetEntries());

  //tree2->Draw("genMET_");
  //TH1 *myh2 = (TH1*)gPad->GetPrimitive("htemp");
  //myh2->Scale(1/myh2->GetEntries());

  /*
  tree3->Draw("genMET_");
  TH1 *myh3 = (TH1*)gPad->GetPrimitive("htemp");
  myh3->Scale(1/myh3->GetEntries());

  tree4->Draw("genMET_");
  TH1 *myh4 = (TH1*)gPad->GetPrimitive("htemp");
  myh4->Scale(1/myh4->GetEntries());

  tree5->Draw("genMET_");
  TH1 *myh5 = (TH1*)gPad->GetPrimitive("htemp");
  myh5->Scale(1/myh5->GetEntries());
  */

  //myh1->Draw("hist");
  //myh2->Draw("hist same");
  //myh3->Draw("hist same");
  //myh4->Draw("hist same");
  //myh5->Draw("hist same");

  cout<<"Hello World"<<endl;


}
