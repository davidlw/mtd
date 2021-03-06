#include "myAna.h"
#include "HyJets.h"
#include "TMath.h"
#include <iostream>
#include "TH1.h"
#include "TH2.h"
#include "TH2F.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TChain.h"
#include "THashList.h"
#include "TLatex.h"
#include "TFileCollection.h"
#include "TVector3.h"
#include "TF1.h"
#include "TH3F.h"

inline float invBetaPion(const float& p){
      return std::sqrt(1 + std::pow(ana::massPion/p,2));
}

inline float invBetaKaon(const float& p){
      return std::sqrt(1 + std::pow(ana::massKaon/p,2));
}

inline float invBetaProton(const float& p){
      return std::sqrt(1 + std::pow(ana::massProton/p,2));
}

bool passTopoCuts(HyJets* t)
{
//   if(t->VtxProb < 0.1) return false;
   return true;
}

void fillHyJetsMass()
{
   TChain* chain = new TChain("lamc3pana_mc/VertexCompositeNtuple");
   TFileCollection* fc = new TFileCollection("dum", "", "hyjets_sample_wPID.list");
   chain->AddFileInfoList(fc->GetList()); 
   HyJets* t = new HyJets(chain);
   std::cout << t->GetEntries() << std::endl;

   TF1* fExpBTL = new TF1("fExpBTL_dInvBetaRMS","0.005 + 0.016*exp(-x/4.4)");
   TF1* fExpETL = new TF1("fExpETL_dInvBetaRMS","0.003 + 0.006*exp(-x/7.6)");

   double massbin[61];
   for(int i=0; i<61; i++){
      massbin[i] = i * 0.005 + 2.15;
   }

   TH3F* hMassVsPtVsY = new TH3F("hMassVsPtVsY", "hMassVsPtVsY", 60, -3, 3, 100, 0, 10, 60, 2.15, 2.45);
   TH3F* hMassVsPtVsYCent = new TH3F("hMassVsPtVsYCent", "hMassVsPtVsYCent", 60, -3, 3, 100, 0, 10, 60, 2.15, 2.45);

   TH3F* hMassVsPtVsYMtd = new TH3F("hMassVsPtVsYMtd", "hMassVsPtVsYMtd", 60, -3, 3, 100, 0, 10, 60, 2.15, 2.45);
   TH3F* hMassVsPtVsYCentMtd = new TH3F("hMassVsPtVsYCentMtd", "hMassVsPtVsYCentMtd", 60, -3, 3, 100, 0, 10, 60, 2.15, 2.45);

   std::cout << hMassVsPtVsY->GetZaxis()->FindBin(2.3);

   for(Long64_t ientry=0; ientry<t->GetEntries(); ientry++){
      t->GetEntry(ientry);

      if(std::fabs(t->EtaD1) > 3) continue;
      if(std::fabs(t->EtaD2) > 3) continue;
      if(std::fabs(t->EtaD3) > 3) continue;

      const float pD1 = t->pTD1 * std::cosh(t->EtaD1);
      const float pD2 = t->pTD2 * std::cosh(t->EtaD2);
      const float pD3 = t->pTD3 * std::cosh(t->EtaD3);

      if(std::fabs(t->EtaD1) < 1.4 ? t->pTD1 <= 0.8 : (pD1 <= 0.7 || t->pTD1<0.4)) continue;
      if(std::fabs(t->EtaD2) < 1.4 ? t->pTD2 <= 0.8 : (pD2 <= 0.7 || t->pTD1<0.4)) continue;
      if(std::fabs(t->EtaD3) < 1.4 ? t->pTD3 <= 0.8 : (pD3 <= 0.7 || t->pTD1<0.4)) continue;

      const float dInvBetaCut1 = std::fabs(t->EtaD1<1.5) ? fExpBTL->Eval(pD1) : fExpETL->Eval(pD1);
      const float dInvBetaCut2 = std::fabs(t->EtaD2<1.5) ? fExpBTL->Eval(pD2) : fExpETL->Eval(pD2);
      const float dInvBetaCut3 = std::fabs(t->EtaD3<1.5) ? fExpBTL->Eval(pD3) : fExpETL->Eval(pD3);

      const bool isCentral = t->centrality < 20;

      if( fabs(t->y)>3 ) continue;

      if(!passTopoCuts(t)) continue;

      hMassVsPtVsY->Fill(t->y, t->pT, t->mass);
      if(isCentral) hMassVsPtVsYCent->Fill(t->y, t->pT, t->mass);

      bool is1sigmaPionDau1 = false;
      bool is1sigmaKaonDau1 = false;
      bool is1sigmaProtonDau1 = false;
      bool is1sigmaPionDau2 = false;
      bool is1sigmaKaonDau2 = false;
      bool is1sigmaProtonDau2 = false;
      bool is1sigmaPionDau3 = false;
      bool is1sigmaKaonDau3 = false;
      bool is1sigmaProtonDau3 = false;

      if(t->isMtdDau1) is1sigmaPionDau1 = std::fabs(1./t->beta1_PV - invBetaPion(pD1)) < 1.0 * dInvBetaCut1;
      if(t->isMtdDau1) is1sigmaKaonDau1 = std::fabs(1./t->beta1_PV - invBetaKaon(pD1)) < 1.0 * dInvBetaCut1;
      if(t->isMtdDau1) is1sigmaProtonDau1 = std::fabs(1./t->beta1_PV - invBetaProton(pD1)) < 1.0 * dInvBetaCut1;
      if(t->isMtdDau2) is1sigmaPionDau2 = std::fabs(1./t->beta2_PV - invBetaPion(pD2)) < 1.0 * dInvBetaCut2;
      if(t->isMtdDau2) is1sigmaKaonDau2 = std::fabs(1./t->beta2_PV - invBetaKaon(pD2)) < 1.0 * dInvBetaCut2;
      if(t->isMtdDau2) is1sigmaProtonDau2 = std::fabs(1./t->beta2_PV - invBetaProton(pD2)) < 1.0 * dInvBetaCut2;
      if(t->isMtdDau3) is1sigmaPionDau3 = std::fabs(1./t->beta3_PV - invBetaPion(pD3)) < 1.0 * dInvBetaCut3;
      if(t->isMtdDau3) is1sigmaKaonDau3 = std::fabs(1./t->beta3_PV - invBetaKaon(pD3)) < 1.0 * dInvBetaCut3;
      if(t->isMtdDau3) is1sigmaProtonDau3 = std::fabs(1./t->beta3_PV - invBetaProton(pD3)) < 1.0 * dInvBetaCut3;

      if((t->flavor == 1 && is1sigmaKaonDau2 && ((is1sigmaPionDau1 && is1sigmaProtonDau3) || (is1sigmaPionDau3 && is1sigmaProtonDau1))) ||
         (t->flavor == -1 && is1sigmaKaonDau1 && ((is1sigmaPionDau2 && is1sigmaProtonDau3) || (is1sigmaPionDau3 && is1sigmaProtonDau2)))
        )
      {
         hMassVsPtVsYMtd->Fill(t->y, t->pT, t->mass);
         if(isCentral) hMassVsPtVsYCentMtd->Fill(t->y, t->pT, t->mass);
      }
   }

   TFile fout("hyjetsMassHists_reRECO_all.root", "recreate");
   hMassVsPtVsY->Write();
   hMassVsPtVsYCent->Write();
   hMassVsPtVsYMtd->Write();
   hMassVsPtVsYCentMtd->Write();
}
