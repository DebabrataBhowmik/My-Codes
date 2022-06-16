// mainlhetohepmc.cc reads the lhe file created by madgraph and generates 
// the hepmc file.

#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/HepMC2.h"

using namespace Pythia8;

double delPhi(double phi1, double phi2){
  double dPhi = fabs(phi1 - phi2);
  if(dPhi > M_PI) dPhi = 2*M_PI - dPhi;
  return dPhi;
}

int main() {


  // Interface for conversion from Pythia8::Event to HepMC event.
      HepMC::Pythia8ToHepMC ToHepMC;
  // Specify file where HepMC events will be stored.
  // HepMC::IO_GenEvent ascii_io("spin2_longitudinal_ggXWW_6.0TeV.hepmc", std::ios::out);
      HepMC::IO_GenEvent ascii_io("Output_jj_iso_0.hepmc", std::ios::out);
      //HepMC::IO_GenEvent ascii_io("bla.hepmc", std::ios::out);

#ifdef GZIPSUPPORT
  bool useGzip = true;
#else
  bool useGzip = false;
#endif
  cout << " useGzip = " << useGzip << endl;

  // Generator. We here stick with default values, but changes
  // could be inserted with readString or readFile.
  Pythia pythia;


  pythia.readString("Beams:eCM = 13000.");
  pythia.readString("HardQCD:all = on");
  //  pythia.readString("PhaseSpace:pTHatMin=300.0");
  pythia.readString("PhaseSpace:pTHatMin=20.0");
  //  pythia.readString("PhaseSpace:mHatMin=90.0");
  //pythia.readString("PhaseSpace:mHatMax=160.0");
  pythia.settings.flag("Tune:ee = 7");
  pythia.settings.flag("Tune:pp = 14");
  pythia.settings.flag("ParticleDecays:limitTau0 = on");
  pythia.settings.flag("ParticleDecays:tau0Max = 10 ");
//  pythia.settings.flag("PartonLevel:FSR",false);
//  pythia.settings.flag("PartonLevel:ISR",false);
//  pythia.settings.flag("HadronLevel:all",false);
//  pythia.settings.flag("HadronLevel:Decay",false);
//  pythia.settings.flag("PartonLevel:MPI",false);


  pythia.readString("Random:setSeed = on");
  pythia.readString("Random:seed = 0");



  pythia.init();

  //SlowJet sJets(-1, 0.4, 50., 5., 1, 2);
  // Allow for possibility of a few faulty events.
  int nAbort = 10;
  int iAbort = 0;
  int totPass = 0;
  int totPass2 = 0;
  int PtCutPassed = 0;
  // Begin event loop; generate until none left in input file.
  int nEvt = 99999;
  
  for (int iEvent = 0; iEvent <= nEvt ; ++iEvent) 
  {
   
     

 //   if(iEvent == 11)pythia.event.list();

    // Generate events, and check whether generation failed.
    if (!pythia.next()) {

      //pythia.process.list();
      // If failure because reached end of file then exit event loop.
      if (pythia.info.atEndOfFile()) break;

      // First few failures write off as "acceptable" errors, then quit.
      if (++iAbort < nAbort) continue;
      break;
    }
   


    int count = 0;
    bool sel = false;

    vector<int> vIndex;
    vector<double> vPx;
    vector<double> vPy;
    vector<double> vPz;
    vector<double> veta;
    vector<double> vphi;
    
    vector<int> vIndexSeed;
    vector<double> vPxSeed;
    vector<double> vPySeed;
    vector<double> vPzSeed;
    vector<double> vetaSeed;
    vector<double> vphiSeed;

    //cout<<endl<<"**********************************************************************"<<endl;
    //cout<<"Starting event number "<<iEvent+1<<endl;
    //cout<<"Total number of particle "<<pythia.event.size()<<endl;
    //cout<<"**********************************************************************"<<endl;

    for (int iPart = 0; iPart < pythia.event.size(); ++iPart) {
      int stat = pythia.event[iPart].status();
      int id = pythia.event[iPart].id();
      int index = pythia.event[iPart].index();
      double pt = pythia.event[iPart].pT();
      double px = pythia.event[iPart].px();
      double py = pythia.event[iPart].py();
      double pz = pythia.event[iPart].pz();
      double eta = pythia.event[iPart].eta();
      double phi = pythia.event[iPart].phi();

      //if(abs(id) == 111) //cout<< pt <<endl;
      if((stat >0) && (abs(id) == 22 || abs(id) == 11 || abs(id) == 111 || abs(id) == 221) && (pt>5)&&(eta <2.7)) //cout<< index<<"  "<<px<<"  "<<py<<"  "<<pythia.event[iPart].mother1()<< "  "<<pythia.event[iPart].mother2()<<endl;

      if(stat >0 ){
	if(abs(id) == 22 || abs(id) == 11 || abs(id) == 111 || abs(id) == 221 ){
	  vIndex.push_back(index);
	  vPx.push_back(px);
	  vPy.push_back(py);
	  vPz.push_back(pz);
	  veta.push_back(eta);
	  vphi.push_back(phi);
	  
	  //if((pt > 5) && (eta <2.7)) count++;
	  if((pt < 5) || (eta >2.7)) continue;
	  count++;
	  
	  vIndexSeed.push_back(index);
	  vPxSeed.push_back(px);
	  vPySeed.push_back(py);
	  vPzSeed.push_back(pz);
	  vetaSeed.push_back(eta);
	  vphiSeed.push_back(phi);
	}
      }
    }

    
    ////cout<<"vIndexSeed size = "<<vIndexSeed.size()<<endl;
    //cout<<"vPxSeed size = "<<vPxSeed.size()<<endl;
    if(count < 2) continue;
    
    

    vector<double> CandPt;
    vector<double> CandEta;
    vector<double> CandPhi;

    vector<bool>vecKillSeed(vPxSeed.size(), false);

    for(int i=0; i<vPxSeed.size(); i++){
      if(vecKillSeed[i]) continue;     
      double candPx1 = vPxSeed[i];
      double candPy1 = vPySeed[i];
      double candPz1 = vPzSeed[i];
      double candEta1 = vetaSeed[i];
      double candPhi1 = vphiSeed[i];
      double candPt1 = sqrt(candPx1*candPx1 + candPy1*candPy1);

      double candPtTemp = candPt1;
      double candEtaTemp = candEta1;
      double candPhiTemp = candPhi1;

      //cout<<"Test "<<vIndexSeed[i]<<" "<<candPx1<<"  "<<candPy1 << " " << candPt1<< "    "<<candEta1 << " "<< candPhi1<<endl;
      bool PtGreater = true;
      for(int j=0; j<vPx.size(); j++){
	//if(vecKillSeed[j]) continue;
	double candPx2 = vPx[j];
	double candPy2 = vPy[j];
	double candPz2 = vPz[j];
	double candEta2 = veta[j];
	double candPhi2 = vphi[j];
        double candPt2 = sqrt(candPx2*candPx2 + candPy2*candPy2);	

	if(vIndexSeed[i]!=vIndex[j]){
	  vector<int>::iterator itr = find(vIndexSeed.begin(), vIndexSeed.end(), vIndex[j]);	  
	  if((itr != vIndexSeed.end()) && (fabs(candEta1-candEta2) < 0.035) && (delPhi(candPhi1,candPhi2) < 0.035) ){
	    if (candPt1<candPt2){
	      //cout<<"Found a seed greater than itself inside cone of 0.035 "<<vIndex[j]<<endl;
	      PtGreater = false;
	      break;
	      //vecKillSeed[i] = true;
	    }
	    else vecKillSeed[distance(vIndexSeed.begin(), itr)] = true;
	    ////cout<<"killed "<<vIndex[j]<<endl;
	  }
	}
	

        
	//if( (vIndexSeed[i]!=vIndex[j]) && (fabs(candEta1-candEta2) < 0.09) && (delPhi(candPhi1,candPhi2) < 0.09) && (candPt2 < candPt1) ){
	if( (vIndexSeed[i]!=vIndex[j]) && (fabs(candEta1-candEta2) < 0.2) && (delPhi(candPhi1,candPhi2) < 0.2) && (candPt2 < candPt1) ){
	  //cout<<vIndex[j]<<" "<<candPt2<<endl;

	  candPx1+=candPx2;
	  candPy1+=candPy2;
	  candPz1+=candPz2;
	  candPtTemp = sqrt(candPx1*candPx1 + candPy1*candPy1);

	  //candEtaTemp = atanh(candPz1/sqrt(candPt1*candPt1+candPz1*candPz1));
	  candEtaTemp = atanh(candPz1/sqrt(candPtTemp*candPtTemp+candPz1*candPz1));
	  if(candPx1>0) candPhiTemp = atan(fabs(candPy1)/fabs(candPx1));
	  else candPhiTemp = M_PI - atan(fabs(candPy1)/fabs(candPx1));
	  if(candPy1<0) candPhiTemp = - candPhiTemp;
	}
      }


      if(!PtGreater){
	//cout<<"bad seed, so exiting"<<endl;
	//cout<<endl;
	continue;
      }
      //cout<<"TEST2 "<<candPx1<<"  "<<candPy1<<"  "<<candPtTemp<<"    "<<candEtaTemp<<" "<<candPhiTemp<<endl;
     
      
    
      if(candPtTemp < 30.0) continue;
      CandPt.push_back(candPtTemp);
      CandEta.push_back(candEtaTemp);
      CandPhi.push_back(candPhiTemp);
      ////cout<<"TESTPt_Eta_Phi "<<candPt<<"  "<<candEta<<"  "<<candPhi<<endl;
    }

     cout << "abc" <<endl;

    int PtcutPassed= CandPt.size();
    if(PtcutPassed>1) PtCutPassed++;

    cout << "no of photon candidates " << CandPt.size() <<endl;
  
    
    

    int nloop = CandPt.size();

    int iso = 0;


    for(int i=0;i<nloop;i++){
      //cout << "nloop = "<<nloop<<" i ="<<i<<endl;
        
      double Isolation = 0.0;
      double Isolationr = 0.0;
          
      
      for (int iPart = 0; iPart < pythia.event.size(); ++iPart) {
	int stat = pythia.event[iPart].status();
	int id = pythia.event[iPart].id();
	int index = pythia.event[iPart].index();
	double candPt2 = pythia.event[iPart].pT();
	double candPx2 = pythia.event[iPart].px();
	double candPy2 = pythia.event[iPart].py();
	double candPz2 = pythia.event[iPart].pz();
	double candEta2 = pythia.event[iPart].eta();
	double candPhi2 = pythia.event[iPart].phi();
	if(stat<1)continue;
	
	if( (fabs(CandEta[i]-candEta2) > 0.2) && (fabs(CandEta[i]-candEta2) < 0.5) && (delPhi(CandPhi[i],candPhi2) > 0.2) && (delPhi(CandPhi[i],candPhi2) < 0.5)) { 
              // && (id!=22)){
	//if((fabs(CandEta[i]-candEta2)<0.3) && (delPhi(CandPhi[i],candPhi2)<0.3)){
	  //cout<<index<<"  "<<id <<" "<<candPt2<<endl;
	  Isolation+=candPt2;

          cout<< "CandPt = "<<CandPt[i]<<" isolation = "<<Isolation<< " " << candPt2 << " " << candEta2 << " " << candPhi2 << " " << CandEta[i] << " " << CandPhi[i] << " " << id << endl;
          
	}
      }
      
      cout<<"**********************************************************************"<<endl;   

      Isolationr=Isolation/CandPt[i];
//      cout<<"CandPt = "<<CandPt[i]<<" isolation = "<<Isolation<<"  " << " isolationr = " << Isolationr << " " <<CandEta[i]<<"  "<<CandPhi[i]<<endl; 

      if(Isolationr < 0.12)iso++;
      
      
      /*
 
      if(Isolationr>0.12){
	//cout<<"going to erase"<<endl;
	CandPt.erase(CandPt.begin() + i);
	CandEta.erase(CandEta.begin() + i);
	CandPhi.erase(CandPhi.begin() + i);
	i=i-1;	
      }
      nloop = CandPt.size();
      */
    }
    
    if(iso > 1) cout << "yes" <<endl;

   
    cout<<"**********************************************************************"<<endl;          

    //cout<<"Number of photons survived "<<CandPt.size()<<endl; 
    //cout<<"Pt of survived photons"<<endl;

    //for(int i=0;i<CandPt.size();i++){
      //cout<<CandPt[i]<< "   ";
    //}
    
    if(CandPt.size() < 1) continue;
    if(CandPt.size() > 1) totPass2++;

    //0.2 cone radius algorithm
    /*    
    vector<bool>vecKill(vPxSeed.size(), false);
    vector<double> SelPt;
    
    for(int i=0; i<vPxSeed.size(); i++){
      if(vecKill[i]) continue;
      ////cout<<"i-th index vector size = "<<vIndexSeed.size()<<endl;
      ////cout<<"i-th index = "<<vIndexSeed[i]<<"  "<<CandPt[i]<<endl;
      double SelPtTemp = 0;
      int mom2, testIndex;
      SelPtTemp = CandPt[i];
      testIndex = vIndexSeed[i];
      for(int j=i+1; j<vPxSeed.size(); j++){
	if(vecKill[j]) continue;
	if( (vIndexSeed[i]!=vIndexSeed[j]) && (fabs(CandEta[i]-CandEta[j]) < 0.2) && (delPhi(CandPhi[i],CandPhi[j]) < 0.2) ){
	  ////cout<<"j-th index = "<<vIndexSeed[j]<<"  "<<CandPt[j]<<endl;
	  mom2 = pythia.event[vIndexSeed[i]].mother1();
	  if(SelPtTemp < CandPt[j]){
	    SelPtTemp =CandPt[j];
	    vecKill[i]=true;
	    testIndex = vIndexSeed[j];
	    mom2 = pythia.event[vIndexSeed[j]].mother1();
	  }
	  else{
	    vecKill[j]=true;
	  }
	}	
      }
      
      if(vIndexSeed[i]!=testIndex){      
	////cout<<CandPt[i]<<"  "<<SelPtTemp<<endl;
	////cout<<vIndexSeed[i]<<"  "<<testIndex<<endl;
	////cout<<pythia.event[vIndexSeed[i]].mother1()<< " "<<mom2<<endl;;
      }
      
      if(SelPtTemp<30) continue;
      if(vecKill[i]) continue;
      SelPt.push_back(SelPtTemp);
    }
    
    ////cout<<M_PI<<endl;
    if(SelPt.size()<2) continue;

    */

    totPass++;
    //cout<<endl;
    //cout<<"Selection passed"<<endl;
  
     if(CandPt.size() < 2) continue;
  
       // Units will be as chosen for HepMC build; but can be changed
       // by arguments, e.g. GenEvt( HepMC::Units::GEV, HepMC::Units::MM)
        HepMC::GenEvent* hepmcevt = new HepMC::GenEvent();
       ToHepMC.fill_next_event( pythia, hepmcevt );

          // Write the HepMC event to file. Done with it.
          ascii_io << hepmcevt;
          delete hepmcevt;
  }
  cout<<"==========================================================================="<<endl;
  cout<<"||             "<<"Number of events passed "<< totPass<<" out of "<<nEvt+1 <<" events"<<"                ||"<<"Only Pt cut passed "<<PtCutPassed<<endl;
  cout<<"||             "<<"Number of events passed "<< totPass2<<" out of "<<nEvt+1 <<" events"<<endl;
  cout<<"==========================================================================="<<endl;
// Give statistics. Print histogram.
  pythia.stat();
  return 0;
}
