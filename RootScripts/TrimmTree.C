#include <vector>

#include "ExRootAnalysis/ExRootClasses.h"
#include "ExRootAnalysis/ExRootLHEFReader.h"

#include "ExRootAnalysis/ExRootTreeWriter.h"
#include "ExRootAnalysis/ExRootTreeBranch.h"
#include "ExRootAnalysis/ExRootProgressBar.h"

#include "TFile.h"
#include "TTree.h"

using namespace std;

void TrimmTree(){
  //Reading ExRootAnalysis libraries 
  gSystem->Load("/home/jose/Pheno_Studies/MG5_aMC_v2_6_3_2/ExRootAnalysis/libExRootAnalysis.so");

  //ExRootAnalysis file to be trimmed
  TFile *ExR = TFile::Open("MuMu.root","READ");
  TTree *ExT = (TTree*)ExR->Get("LHEF");
  Int_t nentries = (Int_t)ExT->GetEntries();
  std::cout << "Number of events to be processed: " << nentries << std::endl;
  TClonesArray *ExParticle = new TClonesArray("TRootLHEFParticle");
  ExT->SetBranchAddress("Particle",&ExParticle);

  // File to save the trimmed tree
  TFile *MyTTF = TFile::Open("TrimmedTree.root","RECREATE");

  // Create vectors that will go into the new TTree
  std::vector<float> MuonPt;
  std::vector<float> MuonEta;
  std::vector<float> MuonPhi;
  std::vector<float> MuonE;
  std::vector<int> MuonCharge;

  // Create a TTree called TrimmedTree
  TTree *t = new TTree("TrimmedTree","Trimmed Tree from ExRootAnalysis");
  t->Branch("MuonPt",&MuonPt);
  t->Branch("MuonEta",&MuonEta);
  t->Branch("MuonPhi",&MuonPhi);
  t->Branch("MuonE",&MuonE);
  t->Branch("MuonCharge",&MuonCharge);

  for (Int_t i=0; i<nentries; i++) {
    //Loading event i content
    ExT->GetEntry(i);
    //Cleaning up memory of trimmed tree
    MuonPt.clear();
    MuonEta.clear();
    MuonPhi.clear();
    MuonE.clear();
    MuonCharge.clear();
    float mpt,meta,mphi,menergy;
    int mcharge;
    for (int j=0; j<ExParticle->GetEntries(); j++){
      TRootLHEFParticle * Particle_j = (TRootLHEFParticle*) ExParticle->At(j);
      //std::cout << Particle_j->PID << std::endl;
      if (Particle_j->PID==-13 || Particle_j->PID==13){
	mpt=Particle_j->PT;
	meta=Particle_j->Eta;
	mphi=Particle_j->Phi;
	menergy=Particle_j->E;
	if (Particle_j->PID==-13){
	  mcharge=-1;
	}
	else if (Particle_j->PID==13){
	  mcharge=1;
	}
	MuonPt.push_back(mpt);
	MuonEta.push_back(meta);
	MuonPhi.push_back(mphi);
	MuonE.push_back(menergy);
	MuonCharge.push_back(mcharge);
      }
    }
    t->Fill();
  }
  
  MyTTF->Write();
  MyTTF->Close();
}
