#include "LamC3P.h"
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
#include "TNtuple.h"

#include "myAna.h"

inline float invBetaPion(const float p){
    return std::sqrt(1 + std::pow(ana::massPion/p,2));
}

inline float invBetaKaon(const float p){
    return std::sqrt(1 + std::pow(ana::massKaon/p,2));
}

inline float invBetaProton(const float p){
    return std::sqrt(1 + std::pow(ana::massProton/p,2));
}

void fillMatchSwapNtuple()
{
    TH1F::SetDefaultSumw2(true);

    TChain *chain = new TChain("lamc3pana_mc/VertexCompositeNtuple");
    TFileCollection* fc = new TFileCollection("dum", "", "lamc3psignal.list");
    chain->AddFileInfoList(fc->GetList()); 
    LamC3P *t = new LamC3P(chain);
    std::cout << "total entries: " << t->GetEntries() << std::endl;

    TH2F* hInvBetaVsPDau1 = new TH2F("hInvBetaVsPDau1", "hInvBetaVsPDau1", 1000, 0, 5, 1000, 0.9, 1.7);
    TH2F* hInvBetaVsPDau2 = new TH2F("hInvBetaVsPDau2", "hInvBetaVsPDau2", 1000, 0, 5, 1000, 0.9, 1.7);
    TH2F* hInvBetaVsPDau3 = new TH2F("hInvBetaVsPDau3", "hInvBetaVsPDau3", 1000, 0, 5, 1000, 0.9, 1.7);

    TH2F* hdInvBetaPionVsPDau1 = new TH2F("hdInvBetaPionVsPDau1", "hdInvBetaPionVsPDau1", 1000, 0, 5, 1000, 0.9, 1.7);
    TH2F* hdInvBetaPionVsPDau2 = new TH2F("hdInvBetaPionVsPDau2", "hdInvBetaPionVsPDau2", 1000, 0, 5, 1000, 0.9, 1.7);
    TH2F* hdInvBetaPionVsPDau3 = new TH2F("hdInvBetaPionVsPDau3", "hdInvBetaPionVsPDau3", 1000, 0, 5, 1000, 0.9, 1.7);

    TH2F* hdInvBetaKaonVsPDau1 = new TH2F("hdInvBetaKaonVsPDau1", "hdInvBetaKaonVsPDau1", 1000, 0, 5, 1000, 0.9, 1.7);
    TH2F* hdInvBetaKaonVsPDau2 = new TH2F("hdInvBetaKaonVsPDau2", "hdInvBetaKaonVsPDau2", 1000, 0, 5, 1000, 0.9, 1.7);
    TH2F* hdInvBetaKaonVsPDau3 = new TH2F("hdInvBetaKaonVsPDau3", "hdInvBetaKaonVsPDau3", 1000, 0, 5, 1000, 0.9, 1.7);

    TH2F* hdInvBetaProtonVsPDau1 = new TH2F("hdInvBetaProtonVsPDau1", "hdInvBetaProtonVsPDau1", 1000, 0, 5, 1000, 0.9, 1.7);
    TH2F* hdInvBetaProtonVsPDau2 = new TH2F("hdInvBetaProtonVsPDau2", "hdInvBetaProtonVsPDau2", 1000, 0, 5, 1000, 0.9, 1.7);
    TH2F* hdInvBetaProtonVsPDau3 = new TH2F("hdInvBetaProtonVsPDau3", "hdInvBetaProtonVsPDau3", 1000, 0, 5, 1000, 0.9, 1.7);

    TNtuple *ntp = new TNtuple("LamC3P", "LamC3P", 
            "pT:y:mass:flavor:eta:isSwap:matchGEN:pTD1:EtaD1:pTD2:EtaD2:pTD3:EtaD3:beta1_PV:beta2_PV::beta3_PV:beta1_PVerr:beta2_PVerr:beta3_PVerr:isMtdDau1:isMtdDau2:isMtdDau3:sigmatmtd1:sigmatmtd2:sigmatmtd3");

    int isMtdWrong = 0;
    Long64_t nLamC3P = 0;
    for(Long64_t ientry=0; ientry<t->GetEntries(); ++ientry){
        t->GetEntry(ientry);
        //bool trkQuality = t->pTD1 > 0.77 && t->pTD2 > 0.77;
        //if(!trkQuality) continue;

        const float pD1 = t->pTD1 * std::cosh(t->EtaD1);
        const float pD2 = t->pTD2 * std::cosh(t->EtaD2);
        const float pD3 = t->pTD3 * std::cosh(t->EtaD3);

        // fill dau1 histograms
        if(t->isMtdDau1 && std::fabs(t->EtaD1)<3){
            hInvBetaVsPDau1->Fill(pD1, 1./t->beta1_PV);
            hdInvBetaPionVsPDau1->Fill(pD1, 1./t->beta1_PV - invBetaPion(pD1));
            hdInvBetaKaonVsPDau1->Fill(pD1, 1./t->beta1_PV - invBetaKaon(pD1));
            hdInvBetaProtonVsPDau1->Fill(pD1, 1./t->beta1_PV - invBetaProton(pD1));
        } 
        // fill dau2 histograms
        if(t->isMtdDau2 && std::fabs(t->EtaD2)<3){
            hInvBetaVsPDau2->Fill(pD2, 1./t->beta2_PV);
            hdInvBetaPionVsPDau2->Fill(pD2, 1./t->beta2_PV - invBetaPion(pD2));
            hdInvBetaKaonVsPDau2->Fill(pD2, 1./t->beta2_PV - invBetaKaon(pD2));
            hdInvBetaProtonVsPDau2->Fill(pD2, 1./t->beta2_PV - invBetaProton(pD2));
        } 
        // fill dau3 histograms
        if(t->isMtdDau3 && std::fabs(t->EtaD3)<3){
            hInvBetaVsPDau3->Fill(pD3, 1./t->beta3_PV);
            hdInvBetaPionVsPDau3->Fill(pD3, 1./t->beta3_PV - invBetaPion(pD3));
            hdInvBetaKaonVsPDau3->Fill(pD3, 1./t->beta3_PV - invBetaKaon(pD3));
            hdInvBetaProtonVsPDau3->Fill(pD3, 1./t->beta3_PV - invBetaProton(pD3));
        }

        // look up whether there is a case track has mtd hits when eta>3
        if(t->isMtdDau1 && std::fabs(t->EtaD1)>3) isMtdWrong++;
        if(t->isMtdDau2 && std::fabs(t->EtaD2)>3) isMtdWrong++;
        if(t->isMtdDau3 && std::fabs(t->EtaD3)>3) isMtdWrong++;

        // cut those unmatched and swap candidates
        if(t->matchGEN && t->isSwap) nLamC3P++;
        if(!(t->matchGEN && t->isSwap)) continue;
        float var[256];
        int j=0;
        var[j++] = t->pT;
        var[j++] = t->y;
        var[j++] = t->mass;
        var[j++] = t->flavor;
        var[j++] = t->eta; 
        var[j++] = t->isSwap;
        var[j++] = t->matchGEN;
        var[j++] = t->pTD1;
        var[j++] = t->EtaD1;
        var[j++] = t->pTD2;
        var[j++] = t->EtaD2;
        var[j++] = t->pTD3;
        var[j++] = t->EtaD3;
        var[j++] = t->beta1_PV;
        var[j++] = t->beta2_PV;
        var[j++] = t->beta3_PV;
        var[j++] = t->beta1_PVerr;
        var[j++] = t->beta2_PVerr;
        var[j++] = t->beta3_PVerr;
        var[j++] = t->isMtdDau1;
        var[j++] = t->isMtdDau2;
        var[j++] = t->isMtdDau3;
        var[j++] = t->sigmatmtd1;
        var[j++] = t->sigmatmtd2;
        var[j++] = t->sigmatmtd3;

        ntp->Fill(var);

    }
    std::cout << "counts of sigmatmtd >= 0 but fabs(eta)>3: " << isMtdWrong << std::endl;
    std::cout << "number of LamC3P passing selection: " << nLamC3P << std::endl;
    TFile* fout;
    fout = new TFile("matchSwapLamC3P_fullSample.root", "recreate");
    ntp->Write();
    hInvBetaVsPDau1->Write();
    hInvBetaVsPDau2->Write();
    hInvBetaVsPDau3->Write();
    hdInvBetaPionVsPDau1->Write();
    hdInvBetaPionVsPDau2->Write();
    hdInvBetaPionVsPDau3->Write();
    hdInvBetaKaonVsPDau1->Write();
    hdInvBetaKaonVsPDau2->Write();
    hdInvBetaKaonVsPDau3->Write();
    hdInvBetaProtonVsPDau1->Write();
    hdInvBetaProtonVsPDau2->Write();
    hdInvBetaProtonVsPDau3->Write();
}
