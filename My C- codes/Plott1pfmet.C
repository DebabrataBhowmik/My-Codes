#include<iostream>
#include"TH1.h"
using namespace std;

void Plott1pfmet(){
  
  TFile* file1=new TFile("nTuple_2HDMa_mA200_ma150.root");
  TFile* file2=new TFile("nTUple_2HDMa_mA300_ma150.root");
  TFile* file3=new TFile("nTUple_2HDMa_mA400_ma150.root");
  TFile* file4=new TFile("nTUple_2HDMa_mA500_ma150.root");
  TFile* file5=new TFile("nTUple_2HDMa_mA600_ma150.root");
  
  TTree *tree1 = (TTree*)file1->Get("DiPhotonTree");
  TTree *tree2 = (TTree*)file2->Get("DiPhotonTree");
  TTree *tree3 = (TTree*)file3->Get("DiPhotonTree");
  TTree *tree4 = (TTree*)file4->Get("DiPhotonTree");
  TTree *tree5 = (TTree*)file5->Get("DiPhotonTree");
  
  TH2F* his21=new TH2F("Ptgg-MET","Ptgg-MET Scatter plot MA=200 GeV",200,0,1000, 200,0,1000);
  TH2F* his22=new TH2F("Ptgg-MET","Ptgg-MET Scatter plot MA=300 GeV",200,0,1000, 200,0,1000);
  TH2F* his23=new TH2F("Ptgg-MET","Ptgg-MET Scatter plot MA=400 GeV",200,0,1000, 200,0,1000);
  TH2F* his24=new TH2F("Ptgg-MET","Ptgg-MET Scatter plot MA=500 GeV",200,0,1000, 200,0,1000);
  TH2F* his25=new TH2F("Ptgg-MET","Ptgg-MET Scatter plot MA=600 GeV",200,0,1000, 200,0,1000);

  TH1F* his1=new TH1F("his1","his1",100,0,600);
  TH1F* his2=new TH1F("his2","his1",100,0,600);
  TH1F* his3=new TH1F("his3","his1",100,0,600);
  TH1F* his4=new TH1F("his4","his1",100,0,600);
  TH1F* his5=new TH1F("his5","his1",100,0,600);

  TFile* f1 = new TFile("test.root", "RECREATE");
    
  tree1->Draw("t1pfmet>>his1");
  his1->Scale(1/his1->GetEntries());
  his1->SetLineColor(kRed);
  gStyle->SetOptStat(0);

  tree2->Draw("t1pfmet>>his2");
  his2->Scale(1/his2->GetEntries());
  his2->SetLineColor(6);

  tree3->Draw("t1pfmet>>his3");
  his3->Scale(1/his3->GetEntries());
  his3->SetLineColor(kBlue);

  tree4->Draw("t1pfmet>>his4");
  his4->Scale(1/his4->GetEntries());
  his4->SetLineColor(kGreen);

  tree5->Draw("t1pfmet>>his5");
  his5->Scale(1/his5->GetEntries());
  his5->SetLineColor(kBlack);

  TCanvas* c1 = new TCanvas("c1","c1",1000,900);

  his2->SetTitle("");
  his2->GetXaxis()->SetTitle("t1pfmet");
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

  //c1->SaveAs("genMET2.png");

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


  TCanvas* c2 = new TCanvas("c2","c2",1000,900);
  tree1->Draw("t1pfmet:ptgg","", "text colz");
  TH2F *h21 = (TH2F*)gPad->GetPrimitive("htemp");
  h21->SetTitle("MA=200 GeV");
  h21->GetXaxis()->SetTitle("P_{T} (#gamma#gamma)");
  h21->GetYaxis()->SetTitle("MET");
  h21->GetYaxis()->SetTitleOffset(1.4);
  h21->GetXaxis()->SetTitleOffset(1.3);
  h21->GetXaxis()->SetRangeUser(0, 400);
  h21->GetYaxis()->SetRangeUser(0, 500);
  h21->Draw("text colz");
  h21->Write("h_200");
  c2->SaveAs("ptgg_MET_200.pdf");
  c2->SaveAs("ptgg_MET_200.png");
  TVirtualPad* p11;
  p11 = c2->cd();
  p11 -> SetLogz();
  c2->SaveAs("ptgg_MET_200_log.png");
  c2->SaveAs("ptgg_MET_200_log.pdf");
  p11 -> SetLogz(0);
  //delete c2;
  
  tree2->Draw("t1pfmet:ptgg","", "text colz");
  TH2F *h22 = (TH2F*)gPad->GetPrimitive("htemp");
  h22->SetTitle("MA=300 GeV");
  h22->GetXaxis()->SetTitle("P_{T} (#gamma#gamma)");
  h22->GetYaxis()->SetTitle("MET");
  h22->GetYaxis()->SetTitleOffset(1.4);
  h22->GetXaxis()->SetTitleOffset(1.3);
  h22->GetXaxis()->SetRangeUser(0, 400);
  h22->GetYaxis()->SetRangeUser(0, 500);
  h22->Draw("text colz");
  h22->Write("h_300");
  c2->SaveAs("ptgg_MET_300.pdf");
  c2->SaveAs("ptgg_MET_300.png");
  //delete c2;
  p11 = c2->cd();
  p11 -> SetLogz();
  c2->SaveAs("ptgg_MET_300_log.png");
  c2->SaveAs("ptgg_MET_300_log.pdf");
  p11 -> SetLogz(0);
  
  tree3->Draw("t1pfmet:ptgg","", "text colz");
  TH2F *h23 = (TH2F*)gPad->GetPrimitive("htemp");
  h23->SetTitle("MA=400 GeV");
  h23->GetXaxis()->SetTitle("P_{T} (#gamma#gamma)");
  h23->GetYaxis()->SetTitle("MET");
  h23->GetYaxis()->SetTitleOffset(1.4);
  h23->GetXaxis()->SetTitleOffset(1.3);
  h23->GetXaxis()->SetRangeUser(0, 400);
  h23->GetYaxis()->SetRangeUser(0, 500);
  h23->Draw("text colz");
  h23->Write("h_400");
  c2->SaveAs("ptgg_MET_400.pdf");
  c2->SaveAs("ptgg_MET_400.png");
  //delete c2;
  p11 = c2->cd();
  p11 -> SetLogz();
  c2->SaveAs("ptgg_MET_400_log.png");
  c2->SaveAs("ptgg_MET_400_log.pdf");
  p11 -> SetLogz(0);
  
  tree4->Draw("t1pfmet:ptgg","", "text colz");
  TH2F *h24 = (TH2F*)gPad->GetPrimitive("htemp");
  h24->SetTitle("MA=500 GeV");
  h24->GetXaxis()->SetTitle("P_{T} (#gamma#gamma)");
  h24->GetYaxis()->SetTitle("MET");
  h24->GetYaxis()->SetTitleOffset(1.4);
  h24->GetXaxis()->SetTitleOffset(1.3);
  h24->GetXaxis()->SetRangeUser(0, 400);
  h24->GetYaxis()->SetRangeUser(0, 500);
  h24->Draw("text colz");
  h24->Write("h_500");
  c2->SaveAs("ptgg_MET_500.pdf");
  c2->SaveAs("ptgg_MET_500.png");
  //delete c2;
  p11 = c2->cd();
  p11 -> SetLogz();
  c2->SaveAs("ptgg_MET_500_log.png");
  c2->SaveAs("ptgg_MET_500_log.pdf");
  p11 -> SetLogz(0);

  tree5->Draw("t1pfmet:ptgg","", "text colz");
  TH2F *h25 = (TH2F*)gPad->GetPrimitive("htemp");
  h25->SetTitle("MA=600 GeV");
  h25->GetXaxis()->SetTitle("P_{T} (#gamma#gamma)");
  h25->GetYaxis()->SetTitle("MET");
  h25->GetYaxis()->SetTitleOffset(1.4);
  h25->GetXaxis()->SetTitleOffset(1.3);
  h25->GetXaxis()->SetRangeUser(0, 400);
  h25->GetYaxis()->SetRangeUser(0, 500);
  h25->Draw("text colz");
  h25->Write("h_600");
  c2->SaveAs("ptgg_MET_600.pdf");
  c2->SaveAs("ptgg_MET_600.png");

  p11 = c2->cd();
  p11 -> SetLogz();
  c2->SaveAs("ptgg_MET_600_log.png");
  c2->SaveAs("ptgg_MET_600_log.pdf");
  p11 -> SetLogz(0);
  delete c2;
  
  //cout<<"Hello World"<<endl;


}
