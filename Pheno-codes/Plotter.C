#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
void Plotter(){

  //float lumi_data= 41.529;
  float lumi_data= 3000;
  vector<double> Xsec;

  ifstream myfile;
  double xsec;
  /*
  if(!myfile.is_open()){
    myfile.open("Xsecs.txt");
  }
  int i=0;
  while (myfile >> xsec){
    i++;
      xsec=xsec*1000;
    Xsec.push_back(xsec);
  }
*/
    
  TString ext = ".root";
  
  vector<TString> filename; 

  filename.push_back("Output_scatter_sig64");
  filename.push_back("Output_scatter_sig120");
  filename.push_back("Output_scatter_ttbarsemilep");
  filename.push_back("Output_scatter_ttbarlep");
  filename.push_back("Output_scatter_zjj");
  filename.push_back("Output_scatter_wjj");
  filename.push_back("Output_scatter_bbbar");
  filename.push_back("Output_scatter_zhbb");
  filename.push_back("Output_scatter_vv");

  vector<TString> legend; 

  legend.push_back("signal m_{DM}=64 GeV");
  legend.push_back("signal m_{DM}=120 GeV");
  legend.push_back("t#bar{t} semi leptonic");
  legend.push_back("t#bar{t} leptonic");
  legend.push_back("zjj");
  legend.push_back("wjj");
  legend.push_back("b#bar{b}");
  legend.push_back("zh");
  legend.push_back("vv");

  vector<int> color; 

  color.push_back(3);
  color.push_back(70);
  color.push_back(93);
  color.push_back(50);
  color.push_back(9);
  color.push_back(40);
  color.push_back(1);
  color.push_back(28);
  color.push_back(32);
  

  /*  
  for(int i=0;i<Xsec.size();i++){
  cout<<"size of Xsec vector = "<<Xsec.size()<<endl;
  //for(int i=0;i<filename.size();i++){
  //cout<<"size of file vector = "<<filename.size()<<endl;
    cout<<filename[i]<<"  "<<Xsec[i]<<endl;
  }
  */
  
  vector<TString> histoname;

  histoname.push_back( "h1_metsig");
  histoname.push_back( "h1_ptb1");
  histoname.push_back( "h1_ptb2");
  histoname.push_back( "h1_ht");
  histoname.push_back( "h1_metsig");
  histoname.push_back( "h1_delphib1met");
  histoname.push_back( "h1_delphib2met");
  histoname.push_back( "h1_MET");
  histoname.push_back( "h1_dRb1j1");
  histoname.push_back( "h1_jtno");
  histoname.push_back( "h1_DRbb");
  histoname.push_back( "h1_dRj1j2");
  histoname.push_back( "h1_DPhij1j2");
  histoname.push_back( "h1_invjj");
  histoname.push_back( "h1_invbb");
  
  const int histos=histoname.size();
  const int filenum=filename.size();
  
  char str[80];
  vector<TLegend*> vleg;
  for(int k=0;k<histos;k++){
    sprintf(str, "leg%d",k);
    TLegend* str = new TLegend(0.75,0.75,0.95,0.95);
    vleg.push_back(str);
  }

  //TLegend* str1 = new TLegend(0.65,0.65,0.9,0.9);
  //TLegend* str2 = new TLegend(0.12,0.65,0.37,0.9);
  TLegend* str1 = new TLegend(0.58,0.58,0.895,0.9);
  TLegend* str2 = new TLegend(0.18,0.58,0.52,0.9);

  double setYmin;
  for(int j=0;j<histos;j++){
    //if(!(histoname[j]=="diPhoMass")) continue;
    THStack *hs = new THStack("hs","");
    TCanvas *cCurrent = new TCanvas(histoname[j],histoname[j],1000,700);
    gStyle->SetOptStat(0);
    double binPrev=0;
    double bin=0;
    double YRange = 1.0;

    bool LegendLeft = false;
    //TLegend* str2 = new TLegend(0.75,0.75,0.95,0.95);

    TH1D*current;
    for(int i=0;i<filenum;i++){
      TFile *file = new TFile(filename[i]+ext);      
      //double NEvts_MC = h_SumW2->Integral();
      //double lumi_MC = NEvts_MC/Xsec[i];
      TH1D* temp = (TH1D*)file->Get(histoname[j]);
      //cout<<filename[i]<<"  "<<Xsec[i]<<endl;
      double NEvts_MC = temp->Integral();
      //double lumi_MC = NEvts_MC/Xsec[i];
      //temp->Scale(10000/NEvts_MC);
      //int color = i+3;
      int col = color[i];
      //temp->Sumw2();
      //temp->Scale(lumi_data/lumi_MC);
      //temp->Scale(lumi_data/lumi_MC);

      temp->Scale(1.0/NEvts_MC);
      temp->SetLineColor(col);
      
      //vleg[j]->AddEntry(temp,legend[i]);

      //temp->SetLineWidth(2.);

      /*
      if(histoname[j]=="diPhoMass"){
	temp->Sumw2();
	if(filename[i] == "HistosSig_m64_cuts_") cout <<temp->Integral()<<endl;
	temp->SetLineColor(color);
	temp->SetFillColor(color);
	if(i==0) gPad-> SetLogy();
	str2->AddEntry(temp,filename[i]);
	hs->Add(temp);
      }
      */
      
      binPrev = bin;
      bin = temp->GetBinContent(temp->GetMaximumBin());
      //bin = temp->GetMaximumBin();
      //bin = temp->GetBinContent(bin);
      //cout <<binPrev<<"  "<< bin<<endl;
      if(bin>binPrev) YRange = 3.0*bin;
      if(i==0) current = (TH1D*)temp->Clone();
      if(histoname[j]=="h1_invjj") setYmin = 0.005;
      //else setYmin = 0.0005;
      else setYmin = 0.0005;
      //current->GetYaxis()->SetRangeUser(0.01, YRange);

      string a =(string)histoname[j];
      if(a.find("Phi") != string::npos || a.find("dR") != string::npos || a.find("phi") != string::npos){
	cout<<histoname[j]<<endl;
	current->GetYaxis()->SetRangeUser(setYmin, 6.0);
      }
      else if(a.find("jtno") != string::npos){
	current->GetYaxis()->SetRangeUser(setYmin, 4.0);
      }

      else if(a.find("invbb") != string::npos){
	current->GetYaxis()->SetRangeUser(setYmin, 1.0);
      }	
      else if(a.find("invjj") != string::npos){
	current->GetYaxis()->SetRangeUser(setYmin, 0.1);
      }	
      else current->GetYaxis()->SetRangeUser(setYmin, YRange);

      //current->GetYaxis()->SetRangeUser(setYmin, YRange);

      if(bin>binPrev){
	if(temp->GetMaximumBin() > 0.6*temp->GetNbinsX()) LegendLeft=true;
	else if(temp->GetMaximumBin() < 0.6*temp->GetNbinsX()) LegendLeft=false;
      }
      if(j==0){
	  str1->AddEntry(temp,legend[i]);
	  str2->AddEntry(temp,legend[i]);
	}
	
      
      if(i == 0){
	gStyle->SetOptTitle(0);
	gStyle->SetPadBottomMargin(0.14);
	gStyle->SetPadLeftMargin(0.14);
	current->GetXaxis()->SetTitleSize(0.05);
	current->GetXaxis()->SetLabelSize(0.05);
	current->GetYaxis()->SetTitleSize(0.05);
	current->GetYaxis()->SetLabelSize(0.05);
	current->GetXaxis()->SetTitleOffset(1.2);
	current->GetYaxis()->SetTitleOffset(1.2);
	current->GetYaxis()->SetTitle("Events (Normalized)");
	if(histoname[j]=="h1_ptb1"){
	  gPad-> SetLogy();
	  //current->SetMinimum(50);
	  current->GetXaxis()->SetTitle("leading b jet P_{T}(GeV)");
	  current->SetTitle("P_{T} distribution of leading b jet");
	}
	
	if(histoname[j]=="h1_ptb2"){
	  gPad-> SetLogy();
	  //temp->SetMinimum(50);
	  current->GetXaxis()->SetTitle("sub-leading b jet P_{T}(GeV)");
	  current->SetTitle("P_{T} distribution of sub-leading b jet");
	}

	if(histoname[j]=="h1_ht"){
	  gPad-> SetLogy();
	  //temp->SetMinimum(50);
	  current->GetXaxis()->SetTitle("H_{T}(GeV)");
	  current->GetXaxis()->SetRangeUser(0,600);
	  current->SetTitle("Distribution of h_{T}");
	}

	if(histoname[j]=="h1_metsig"){
	  gPad-> SetLogy();
	  //temp->SetMinimum(50);
	  current->GetXaxis()->SetTitle("MET significance (#sqrt{GeV})");
	  //current->GetXaxis()->SetTitle("MET significance (GeV)^{1/2}");
	  current->GetXaxis()->SetRangeUser(0,20);
	  current->SetTitle("MET significance distribution");
	}
	
	if(histoname[j]=="h1_delphib1met"){
	  gPad-> SetLogy();
	  //temp->SetMinimum(50);
	  current->GetXaxis()->SetTitle("#Delta#phi(leading b, #slash{E}_{T})");
	  current->SetTitle("#Delta #phi distribution between leading b and MET");
	}


	if(histoname[j]=="h1_delphib2met"){
	  gPad-> SetLogy();
	  //temp->SetMinimum(50);
	  current->GetXaxis()->SetTitle("#Delta#phi(sub-leading b, #slash{E}_{T})");
	  current->SetTitle("#Delta #phi distribution between sub-leading b and MET");
	}

	if(histoname[j]=="h1_MET"){
	  gPad-> SetLogy();
	  //temp->SetMinimum(50);
	  current->GetXaxis()->SetTitle("#slash{E}_{T}(GeV)");
	  current->GetXaxis()->SetRangeUser(0,500);
	  current->SetTitle("MET distribution");
	}

	if(histoname[j]=="h1_dRb1j1"){
	  gPad-> SetLogy();
	  //temp->SetMinimum(50);
	  current->GetXaxis()->SetTitle("dR(leading b, leading non-b jet)");
	  current->SetTitle("Distribution of dR between leading b jet and leading non-b jet");
	}
	
	if(histoname[j]=="h1_jtno"){
	  gPad-> SetLogy();
	  //temp->SetMinimum(50);
	  current->GetXaxis()->SetTitle("Number of non-b jets");
	  current->SetTitle("Distribution of number of jet");
	}

	if(histoname[j]=="h1_DRbb"){
	  gPad-> SetLogy();
	  //temp->SetMinimum(50);
	  current->GetXaxis()->SetRangeUser(0,7);
	  current->GetXaxis()->SetTitle("dR(leading b, sub-leading b)");
	  current->SetTitle("Distribution of dR between leading and sub-leading b jet");
	}

	if(histoname[j]=="h1_dRj1j2"){
	  gPad-> SetLogy();
	  //temp->SetMinimum(50);
	  current->GetXaxis()->SetTitle("dR(non-b leading j, non-b sub-leadingleading j)");
	  current->SetTitle("Distribution of dR between non-b leading and sub-leading jet");
	}

	if(histoname[j]=="h1_DPhij1j2"){
	  gPad-> SetLogy();
	  //temp->SetMinimum(50);
	  current->GetXaxis()->SetTitle("#Delta#phi(non-b leading j, non-b sub-leadingleading j)");
	  current->SetTitle("Distribution of #Delta#phi between non-b leading and sub-leading jet");
	}

	if(histoname[j]=="h1_invjj"){
	  gPad-> SetLogy();
	  //temp->SetMinimum(50);
	  current->GetXaxis()->SetTitle("M_{j_{1}j_{2}}(GeV)");
	  current->SetTitle("Distribution of invariant mass of non-b leading and sub-leading jet");
	}

	if(histoname[j]=="h1_invbb"){
	  gPad-> SetLogy();
	  //temp->SetMinimum(50);
	  current->GetXaxis()->SetTitle("M_{b_{1}b_{2}}(GeV)");
	  current->SetTitle("Distribution of invariant mass of leading and sub-leading b jet");
	}
	/*
      	if(histoname[j]=="LeadPt"){
	  gPad-> SetLogy();
	  //temp->SetMinimum(50);
	  temp->GetXaxis()->SetTitle("Pt_{#gamma1}");
	}

	if(histoname[j]=="SubLeadPt"){
	  gPad-> SetLogy();
	  //temp->SetMinimum(50);
	  temp->GetXaxis()->SetTitle("Pt_{#gamma2}");
	}
	
	if(histoname[j]=="dRdiPho"){
	  gPad-> SetLogy();
	  temp->SetMinimum(50);
	  temp->GetXaxis()->SetTitle("#DeltaR #gamma_{1} #gamma_{2} ");
	}
	
	if(histoname[j]=="MET"){
	  gPad-> SetLogy();
	  temp->GetXaxis()->SetTitle("#slash{E}_{T}");
	}

	if(histoname[j]=="dPhiPho1MET"){
	  gPad-> SetLogy();
	  temp->GetXaxis()->SetTitle("#Delta#phi #gamma_{1} MET ");
	}
	
	if(histoname[j]=="dPhiPho2MET"){
	  gPad-> SetLogy();
	  temp->GetXaxis()->SetTitle("#Delta#phi #gamma_{2} MET");
	}

	if(histoname[j]=="NJet"){
	  gPad-> SetLogy();
	  temp->GetXaxis()->SetTitle("Number of Jets");
	}		

	if(histoname[j]=="Razor"){
	  //gPad-> SetLogy();
	  temp->GetXaxis()->SetTitle("R");
	  temp->GetXaxis()->SetRangeUser(0.0, 2.5);
	  temp->GetYaxis()->SetRangeUser(0.0, 1600.0);
	}	
	*/
	current->Draw("hist");
      }
      else if(i!=0) temp->Draw("same hist");
    }
    
    //vleg[j]->Draw("same"); 
    if(LegendLeft) str2->Draw("same");
    else if(!LegendLeft) str1->Draw("same");
    cCurrent->SaveAs(histoname[j]+".png");
    cCurrent->SaveAs(histoname[j]+".pdf");
    delete cCurrent;

  }

  /*
    if(histoname[j]=="diPhoMass") {
      hs->Draw("hist");
      //hs->GetYaxis()->SetLimits(0.01, 1000.0);    
      gPad-> SetLogy();
      hs->GetXaxis()->SetTitle("M_{#gamma#gamma}");
      //hs->GetYaxis()->SetRangeUser(0.01, 100000000000000.0);
      str2->Draw("same"); 
    }
    */
}
  
  /*
  int binPrev = bin;
  int bin = temp->GetMaximumBin();
  if(bin>binPrev) Yrange = 1.4*bin;
  
  if(i==0){
    TH1D*current = (TH1D*)temp->Clone();
    current->Draw();
  }
  current->GetYaxis()->SetRangeUser(0.0, Yrange);
  */
    


