//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar  5 18:03:54 2019 by ROOT version 6.12/07
// from TTree LamC3P/LamC3P
// found on file: matchLamC3P_fullSample.root
//////////////////////////////////////////////////////////

#ifndef matchLamC3P_h
#define matchLamC3P_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class matchLamC3P {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         pT;
   Float_t         y;
   Float_t         mass;
   Float_t         flavor;
   Float_t         eta;
   Float_t         isSwap;
   Float_t         matchGEN;
   Float_t         pTD1;
   Float_t         EtaD1;
   Float_t         pTD2;
   Float_t         EtaD2;
   Float_t         pTD3;
   Float_t         EtaD3;
   Float_t         beta1_PV;
   Float_t         beta2_PV;
   Float_t         beta3_PV;
   Float_t         beta1_PVerr;
   Float_t         beta2_PVerr;
   Float_t         beta3_PVerr;
   Float_t         isMtdDau1;
   Float_t         isMtdDau2;
   Float_t         isMtdDau3;
   Float_t         sigmatmtd1;
   Float_t         sigmatmtd2;
   Float_t         sigmatmtd3;

   // List of branches
   TBranch        *b_pT;   //!
   TBranch        *b_y;   //!
   TBranch        *b_mass;   //!
   TBranch        *b_flavor;   //!
   TBranch        *b_eta;   //!
   TBranch        *b_isSwap;   //!
   TBranch        *b_matchGEN;   //!
   TBranch        *b_pTD1;   //!
   TBranch        *b_EtaD1;   //!
   TBranch        *b_pTD2;   //!
   TBranch        *b_EtaD2;   //!
   TBranch        *b_pTD3;   //!
   TBranch        *b_EtaD3;   //!
   TBranch        *b_beta1_PV;   //!
   TBranch        *b_beta2_PV;   //!
   TBranch        *b_beta3_PV;   //!
   TBranch        *b_beta1_PVerr;   //!
   TBranch        *b_beta2_PVerr;   //!
   TBranch        *b_beta3_PVerr;   //!
   TBranch        *b_isMtdDau1;   //!
   TBranch        *b_isMtdDau2;   //!
   TBranch        *b_isMtdDau3;   //!
   TBranch        *b_sigmatmtd1;   //!
   TBranch        *b_sigmatmtd2;   //!
   TBranch        *b_sigmatmtd3;   //!

   matchLamC3P(TTree *tree=0);
   virtual ~matchLamC3P();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t GetEntries(){ return fChain->GetEntries();}
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifndef matchLamC3P_cxx
#define matchLamC3P_cxx
matchLamC3P::matchLamC3P(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("matchLamC3P_fullSample.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("matchLamC3P_fullSample.root");
      }
      f->GetObject("LamC3P",tree);

   }
   Init(tree);
}

matchLamC3P::~matchLamC3P()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t matchLamC3P::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t matchLamC3P::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void matchLamC3P::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("pT", &pT, &b_pT);
   fChain->SetBranchAddress("y", &y, &b_y);
   fChain->SetBranchAddress("mass", &mass, &b_mass);
   fChain->SetBranchAddress("flavor", &flavor, &b_flavor);
   fChain->SetBranchAddress("eta", &eta, &b_eta);
   fChain->SetBranchAddress("isSwap", &isSwap, &b_isSwap);
   fChain->SetBranchAddress("matchGEN", &matchGEN, &b_matchGEN);
   fChain->SetBranchAddress("pTD1", &pTD1, &b_pTD1);
   fChain->SetBranchAddress("EtaD1", &EtaD1, &b_EtaD1);
   fChain->SetBranchAddress("pTD2", &pTD2, &b_pTD2);
   fChain->SetBranchAddress("EtaD2", &EtaD2, &b_EtaD2);
   fChain->SetBranchAddress("pTD3", &pTD3, &b_pTD3);
   fChain->SetBranchAddress("EtaD3", &EtaD3, &b_EtaD3);
   fChain->SetBranchAddress("beta1_PV", &beta1_PV, &b_beta1_PV);
   fChain->SetBranchAddress("beta2_PV", &beta2_PV, &b_beta2_PV);
   fChain->SetBranchAddress("beta3_PV", &beta3_PV, &b_beta3_PV);
   fChain->SetBranchAddress("beta1_PVerr", &beta1_PVerr, &b_beta1_PVerr);
   fChain->SetBranchAddress("beta2_PVerr", &beta2_PVerr, &b_beta2_PVerr);
   fChain->SetBranchAddress("beta3_PVerr", &beta3_PVerr, &b_beta3_PVerr);
   fChain->SetBranchAddress("isMtdDau1", &isMtdDau1, &b_isMtdDau1);
   fChain->SetBranchAddress("isMtdDau2", &isMtdDau2, &b_isMtdDau2);
   fChain->SetBranchAddress("isMtdDau3", &isMtdDau3, &b_isMtdDau3);
   fChain->SetBranchAddress("sigmatmtd1", &sigmatmtd1, &b_sigmatmtd1);
   fChain->SetBranchAddress("sigmatmtd2", &sigmatmtd2, &b_sigmatmtd2);
   fChain->SetBranchAddress("sigmatmtd3", &sigmatmtd3, &b_sigmatmtd3);
   Notify();
}

Bool_t matchLamC3P::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void matchLamC3P::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t matchLamC3P::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifndef matchLamC3P_cxx
