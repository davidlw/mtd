#include "myAna.h"
#include "matchLamC3P.h"

inline float invBetaPion(const float& p){
      return std::sqrt(1 + std::pow(ana::massPion/p,2));
}

inline float invBetaKaon(const float& p){
      return std::sqrt(1 + std::pow(ana::massKaon/p,2));
}

inline float invBetaProton(const float& p){
      return std::sqrt(1 + std::pow(ana::massProton/p,2));
}

int whichY(const float& y)
{
   for(int i=0; i<ana::nuOfY; i++){
      if(y>ana::ybin[i] && y<ana::ybin[i+1]) return i;
   }
   return -1;
}
void lamC3Pmass(double minPt=2, double maxPt=3)
{
   TH1::SetDefaultSumw2(true);

   const bool drawMass = true;
   const bool drawSwapMass = false;
   const bool drawFrac = true;

   TLatex* ltx = new TLatex();
   ltx->SetTextSize(0.06);

   TF1 *fExpPion, *fExpKaon, *fExpProton;
   fExpPion = new TF1("fExpPion_dInvBetaRMS","0.005 + 0.017*exp(-x/2.8)", 0.8, 10);
   fExpKaon = new TF1("fExpKaon_dInvBetaRMS","0.005 + 0.017*exp(-x/2.8)", 0.8, 10);
   fExpProton = new TF1("fExpProton_dInvBetaRMS","0.005 + 0.017*exp(-x/2.8)", 0.8, 10);

   TFile* f1 = new TFile("matchLamC3P_fullSample.root");
   TNtuple* tp = (TNtuple*) f1->Get("LamC3P");
   matchLamC3P* t = new matchLamC3P(tp);
   std::cout << t->GetEntries() << std::endl;

   TH1F* hMass[ana::nuOfY];
   TH1F* hMassMtd[ana::nuOfY];
   TH1F* hPt[ana::nuOfY];
   TH1F* hPtMtd[ana::nuOfY];

   for(int iy=0; iy<ana::nuOfY; iy++){
      hMass[iy] = new TH1F(Form("hMass%d", iy), Form("hMass%d", iy), 60, 2.0, 2.6);
      hMassMtd[iy] = new TH1F(Form("hMassMtd%d", iy), Form("hMassMtd%d", iy), 60, 2.0, 2.6);
      hMass[iy]->GetXaxis()->SetTitle("mass (GeV");
      hMassMtd[iy]->GetXaxis()->SetTitle("mass (GeV");
      hMass[iy]->SetLineColor(kBlue);
      hMassMtd[iy]->SetLineColor(kRed);

      hPt[iy] = new TH1F(Form("hPt%d", iy), Form("hPt%d", iy), 100, 0, 10);
      hPtMtd[iy] = new TH1F(Form("hPtMtd%d", iy), Form("hPtMtd%d", iy), 100, 0, 10);
      hPt[iy]->GetXaxis()->SetTitle("p_{T} (GeV");
      hPtMtd[iy]->GetXaxis()->SetTitle("p_{T} (GeV");
      hPt[iy]->SetLineColor(kBlue);
      hPtMtd[iy]->SetLineColor(kRed);
   }
   
   for(Long64_t ientry=0; ientry<t->GetEntries(); ientry++){
      t->GetEntry(ientry);
      // require eta<1.4 ? pT > 0.8 : pT > 0.5 and within MTD acceptance
      if(std::fabs(t->EtaD1) > 3) continue;
      if(std::fabs(t->EtaD2) > 3) continue;
      if(std::fabs(t->EtaD3) > 3) continue;
      if(std::fabs(t->EtaD1) < 1.4 ? t->pTD1 <= 0.8 : t->pTD1 <= 0.5) continue;
      if(std::fabs(t->EtaD2) < 1.4 ? t->pTD2 <= 0.8 : t->pTD2 <= 0.5) continue;
      if(std::fabs(t->EtaD3) < 1.4 ? t->pTD3 <= 0.8 : t->pTD3 <= 0.5) continue;

      if(t->pT>maxPt || t->pT<minPt) continue;

      const int iy = whichY(t->y);
      if( iy == -1 ) continue;

      const float pD1 = t->pTD1 * std::cosh(t->EtaD1);
      const float pD2 = t->pTD2 * std::cosh(t->EtaD2);
      const float pD3 = t->pTD3 * std::cosh(t->EtaD3);

      if(!(t->matchGEN && !t->isSwap)) continue;

      hMass[iy]->Fill(t->mass);
      hPt[iy]->Fill(t->pT);
      bool is1sigmaPionDau1 = true;
      bool is1sigmaKaonDau1 = true;
      bool is1sigmaProtonDau1 = true;
      bool is1sigmaPionDau2 = true;
      bool is1sigmaKaonDau2 = true;
      bool is1sigmaProtonDau2 = true;
      bool is1sigmaPionDau3 = true;
      bool is1sigmaKaonDau3 = true;
      bool is1sigmaProtonDau3 = true;

      if(t->isMtdDau1) is1sigmaPionDau1 = std::fabs(1./t->beta1_PV - invBetaPion(pD1)) < 1.0 * fExpPion->Eval(pD1);
      if(t->isMtdDau1) is1sigmaKaonDau1 = std::fabs(1./t->beta1_PV - invBetaKaon(pD1)) < 1.0 * fExpKaon->Eval(pD1);
      if(t->isMtdDau1) is1sigmaProtonDau1 = std::fabs(1./t->beta1_PV - invBetaProton(pD1)) < 1.0 * fExpProton->Eval(pD1);
      if(t->isMtdDau2) is1sigmaPionDau2 = std::fabs(1./t->beta2_PV - invBetaPion(pD2)) < 1.0 * fExpPion->Eval(pD2);
      if(t->isMtdDau2) is1sigmaKaonDau2 = std::fabs(1./t->beta2_PV - invBetaKaon(pD2)) < 1.0 * fExpKaon->Eval(pD2);
      if(t->isMtdDau2) is1sigmaProtonDau2 = std::fabs(1./t->beta2_PV - invBetaProton(pD2)) < 1.0 * fExpProton->Eval(pD2);
      if(t->isMtdDau3) is1sigmaPionDau3 = std::fabs(1./t->beta3_PV - invBetaPion(pD3)) < 1.0 * fExpPion->Eval(pD3);
      if(t->isMtdDau3) is1sigmaKaonDau3 = std::fabs(1./t->beta3_PV - invBetaKaon(pD3)) < 1.0 * fExpKaon->Eval(pD3);
      if(t->isMtdDau3) is1sigmaProtonDau3 = std::fabs(1./t->beta3_PV - invBetaProton(pD3)) < 1.0 * fExpProton->Eval(pD3);


      if((t->flavor == 1 && is1sigmaKaonDau2 && ((is1sigmaPionDau1 && is1sigmaProtonDau3) || (is1sigmaPionDau3 && is1sigmaProtonDau1))) ||
         (t->flavor == -1 && is1sigmaKaonDau1 && ((is1sigmaPionDau2 && is1sigmaProtonDau3) || (is1sigmaPionDau3 && is1sigmaProtonDau2))) 
        )
      {
         hMassMtd[iy]->Fill(t->mass);
         hPtMtd[iy]->Fill(t->pT);
      }
   }
   TCanvas* c1[ana::nuOfY];
   if(drawMass){
      for(int iy=0; iy<ana::nuOfY; iy++){
         c1[iy] = new TCanvas(Form("c1%d", iy), "", 500, 450);
         c1[iy]->cd();
         gStyle->SetOptStat(0);
         hMass[iy]->Draw();
//         hMassMtd[iy]->Draw("same");
         ltx->DrawLatexNDC(0.55, 0.65, Form("%.1f < y < %.1f", ana::ybin[iy], ana::ybin[iy+1]));
         ltx->DrawLatexNDC(0.5, 0.55, Form("%.1f < pT < %.1f GeV", minPt,maxPt));
         TLegend *lgd = new TLegend(0.7, 0.8, 0.9, 0.9);
         lgd->AddEntry(hMass[iy], "w/o MTD", "p");
         lgd->AddEntry(hMassMtd[iy], "w/ MTD", "p");
         lgd->Draw();
         c1[iy]->Print(Form("figures/LamCMass_minPt%.1f_maxPt%.1f_y%d_woMTD.pdf",minPt,maxPt,iy));
         c1[iy]->Print(Form("figures/LamCMass_minPt%.1f_maxPt%.1f_y%d_woMTD.png",minPt,maxPt,iy));
      }
   }
return;
   TH1F* hMassSwap[ana::nuOfY];
   TH1F* hMassSwapMtd[ana::nuOfY];
   for(int iy=0; iy<ana::nuOfY; iy++){
      hMassSwap[iy] = new TH1F(Form("hMassSwap%d", iy), Form("hMassSwap%d", iy), 60, 1.7, 2.0);
      hMassSwapMtd[iy] = new TH1F(Form("hMassSwapMtd%d", iy), Form("hMassSwapMtd%d", iy), 60, 1.7, 2.0);
      hMassSwap[iy]->GetXaxis()->SetTitle("mass (GeV");
      hMassSwapMtd[iy]->GetXaxis()->SetTitle("mass (GeV");
      hMassSwap[iy]->SetLineColor(kBlue);
      hMassSwapMtd[iy]->SetLineColor(kRed);
   }

   TFile* f2 = new TFile("matchSwapLamC3P_fullSample.root");
   tp = (TNtuple*) f2->Get("LamC3P");
   t = new matchLamC3P(tp);
   std::cout << t->GetEntries() << std::endl;

   for(Long64_t ientry=0; ientry<t->GetEntries(); ientry++){
      t->GetEntry(ientry);
      // require eta<1.4 ? pT > 0.8 : pT > 0.5 and within MTD acceptance
      if(std::fabs(t->EtaD1) > 3) continue;
      if(std::fabs(t->EtaD2) > 3) continue;
      if(std::fabs(t->EtaD3) > 3) continue;

      if(std::fabs(t->EtaD1) < 1.4 ? t->pTD1 <= 0.8 : t->pTD1 <= 0.5) continue;
      if(std::fabs(t->EtaD2) < 1.4 ? t->pTD2 <= 0.8 : t->pTD2 <= 0.5) continue;
      if(std::fabs(t->EtaD3) < 1.4 ? t->pTD3 <= 0.8 : t->pTD3 <= 0.5) continue;

//      if(t->pT>0.5) continue;
      if(t->pT>maxPt || t->pT<minPt) continue;

      const int iy = whichY(t->y);
      if( iy == -1 ) continue;

      const float pD1 = t->pTD1 * std::cosh(t->EtaD1);
      const float pD2 = t->pTD2 * std::cosh(t->EtaD2);
      const float pD3 = t->pTD3 * std::cosh(t->EtaD3);

      if(!(t->matchGEN && t->isSwap)) continue;

      hMassSwap[iy]->Fill(t->mass);
      bool is1sigmaPionDau1 = true;
      bool is1sigmaKaonDau1 = true;
      bool is1sigmaProtonDau1 = true;
      bool is1sigmaPionDau2 = true;
      bool is1sigmaKaonDau2 = true;
      bool is1sigmaProtonDau2 = true;
      bool is1sigmaPionDau3 = true;
      bool is1sigmaKaonDau3 = true;
      bool is1sigmaProtonDau3 = true;

      if(t->isMtdDau1) is1sigmaPionDau1 = std::fabs(1./t->beta1_PV - invBetaPion(pD1)) < 1.0 * fExpPion->Eval(pD1);
      if(t->isMtdDau1) is1sigmaKaonDau1 = std::fabs(1./t->beta1_PV - invBetaKaon(pD1)) < 1.0 * fExpKaon->Eval(pD1);
      if(t->isMtdDau1) is1sigmaProtonDau1 = std::fabs(1./t->beta1_PV - invBetaProton(pD1)) < 1.0 * fExpProton->Eval(pD1);
      if(t->isMtdDau2) is1sigmaPionDau2 = std::fabs(1./t->beta2_PV - invBetaPion(pD2)) < 1.0 * fExpPion->Eval(pD2);
      if(t->isMtdDau2) is1sigmaKaonDau2 = std::fabs(1./t->beta2_PV - invBetaKaon(pD2)) < 1.0 * fExpKaon->Eval(pD2);
      if(t->isMtdDau2) is1sigmaProtonDau2 = std::fabs(1./t->beta2_PV - invBetaProton(pD2)) < 1.0 * fExpProton->Eval(pD2);
      if(t->isMtdDau3) is1sigmaPionDau3 = std::fabs(1./t->beta3_PV - invBetaPion(pD3)) < 1.0 * fExpPion->Eval(pD3);
      if(t->isMtdDau3) is1sigmaKaonDau3 = std::fabs(1./t->beta3_PV - invBetaKaon(pD3)) < 1.0 * fExpKaon->Eval(pD3);
      if(t->isMtdDau3) is1sigmaProtonDau3 = std::fabs(1./t->beta3_PV - invBetaProton(pD3)) < 1.0 * fExpProton->Eval(pD3);


      if((t->flavor == 1 && is1sigmaKaonDau2 && ((is1sigmaPionDau1 && is1sigmaProtonDau3) || (is1sigmaPionDau3 && is1sigmaProtonDau1))) ||
         (t->flavor == -1 && is1sigmaKaonDau1 && ((is1sigmaPionDau2 && is1sigmaProtonDau3) || (is1sigmaPionDau3 && is1sigmaProtonDau2)))
        )
      hMassSwapMtd[iy]->Fill(t->mass);
   }

   TCanvas* c2[ana::nuOfY];
   if(drawSwapMass){
      for(int iy=0; iy<ana::nuOfY; iy++){
         c2[iy] = new TCanvas(Form("c2%d", iy), "", 500, 450);
         c2[iy]->cd();
         gStyle->SetOptStat(0);
         hMassSwap[iy]->Draw();
         hMassSwapMtd[iy]->Draw("same");
         ltx->DrawLatexNDC(0.55, 0.65, Form("%.1f < y < %.1f", ana::ybin[iy], ana::ybin[iy+1]));
         ltx->DrawLatexNDC(0.5, 0.55, Form("%.1f < pT < %.1f GeV", minPt, maxPt));
         TLegend *lgd = new TLegend(0.7, 0.8, 0.9, 0.9);
         lgd->AddEntry(hMassSwap[iy], "w/o MTD", "lp");
         lgd->AddEntry(hMassSwapMtd[iy], "w/ MTD", "lp");
         lgd->Draw();
      }
   }

   TH1F* hFrac = new TH1F("hfrac", "hfrac", ana::nuOfY, ana::ybin);
   TH1F* hFracSwap = new TH1F("hfracSwap", "hfracSwap", ana::nuOfY, ana::ybin);

   hFrac->GetXaxis()->SetTitle("y");
   hFrac->GetYaxis()->SetTitle("yield ratio");
   hFracSwap->GetXaxis()->SetTitle("y");
   hFracSwap->GetYaxis()->SetTitle("yield ratio");

   hFrac->SetLineColor(kRed);
   hFracSwap->SetLineColor(kBlue);

   hFrac->Sumw2(false);
   hFracSwap->Sumw2(false);

   for(int iy = 0; iy<ana::nuOfY; iy++){
      float frac = hMassMtd[iy]->Integral() / hMass[iy]->Integral();
      float fracSwap = hMassSwapMtd[iy]->Integral() / hMassSwap[iy]->Integral();
      hFrac->SetBinContent(iy+1, frac);
      hFracSwap->SetBinContent(iy+1, fracSwap);
   }
   if(drawFrac){
      TCanvas* c1 = new TCanvas("cFrac", "", 500, 450);
      gPad->DrawFrame(-3, 0, 3, 1.2, ";y;yield ratio");
      hFrac->Draw("same");
      hFracSwap->Draw("same");
      TLegend *lgd = new TLegend(0.65, 0.8, 0.9, 0.95);
      lgd->AddEntry(hFrac, "non swap", "pl");
      lgd->AddEntry(hFracSwap, "swap", "pl");
      lgd->Draw();
      ltx->DrawLatexNDC(0.5, 0.65, Form("%.1f < pT < %.1f GeV", minPt, maxPt));
      c1->Print(Form("figures/LamCFrac_minPt%.1f_maxPt%.1f.pdf",minPt,maxPt));
      c1->Print(Form("figures/LamCFrac_minPt%.1f_maxPt%.1f.png",minPt,maxPt));
   }

   TFile fout(Form("lamC3PMassHists_minPt%.1f_maxPt%.1f.root",minPt,maxPt), "recreate");
   for(int iy=0; iy<ana::nuOfY; iy++){
      hMass[iy]->Write();
      hMassSwap[iy]->Write();
      hMassMtd[iy]->Write();
      hMassSwapMtd[iy]->Write();
      hPt[iy]->Write();
      hPtMtd[iy]->Write();
   }
   hFrac->Write();
   hFracSwap->Write();
}
