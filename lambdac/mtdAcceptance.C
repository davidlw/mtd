#include "matchLamC3P.h"
#include "myAna.h"
int whichY(const float& y)
{
   for(int i=0; i<ana::nuOfY; i++){
      if(y>ana::ybin[i] && y<ana::ybin[i+1]) return i;
   }
   return -1;
}

void mtdAcceptance(double minPt=2, double maxPt=3)
{
   TFile* f1 = new TFile("matchLamC3P_fullSample.root");
   TNtuple* tp = (TNtuple*) f1->Get("LamC3P");
   matchLamC3P* t = new matchLamC3P(tp);
   std::cout << t->GetEntries() << std::endl;

   // we have a look at LamC3P pT < 0.5 and full pT with |y| < 3
   // here is related to pT<0.5
   TH1F* hDraw = new TH1F("hDraw", "", ana::nuOfY, ana::ybin);
   TH1F* hNoMtd = new TH1F("hNotMtd", "hNoMtd", ana::nuOfY, ana::ybin);
   TH1F* hDau1Mtd = new TH1F("hDau1tMtd", "hDau1Mtd", ana::nuOfY, ana::ybin);
   TH1F* hDau2Mtd = new TH1F("hDau2tMtd", "hDau2Mtd", ana::nuOfY, ana::ybin);
   TH1F* hDau3Mtd = new TH1F("hDau3tMtd", "hDau3Mtd", ana::nuOfY, ana::ybin);
   TH1F* hAllMtd = new TH1F("hAlltMtd", "hAllMtd", ana::nuOfY, ana::ybin);

   TH1F* hDrawY = new TH1F("hDrawY", "", ana::nuOfY, ana::ybin);
   TH1F* hAllY = new TH1F("hAllY", "hAllY", ana::nuOfY, ana::ybin);
   TH1F* hNoMtdY = new TH1F("hNoMtdY", "hNoMtdY", ana::nuOfY, ana::ybin);
   TH1F* hDau1MtdY = new TH1F("hDau1MtdY", "hDau1MtdY", ana::nuOfY, ana::ybin);
   TH1F* hDau2MtdY = new TH1F("hDau2MtdY", "hDau2MtdY", ana::nuOfY, ana::ybin);
   TH1F* hDau3MtdY = new TH1F("hDau3MtdY", "hDau3MtdY", ana::nuOfY, ana::ybin);
   TH1F* hAllMtdY = new TH1F("hAllMtdY", "hAllMtdY", ana::nuOfY, ana::ybin);

   // here is related to full pT
   TH1F* hDrawPt = new TH1F("hDrawPt", "", 100, 0, 10);
   TH1F* hAllPt = new TH1F("hAllPt", "All", 100, 0, 10);
   TH1F* hNoMtdPt = new TH1F("hNoMtd", "hNoMtd", 100, 0, 10);
   TH1F* hDau1MtdPt = new TH1F("hDau1Mtd", "hDau1Mtd", 100, 0, 10);
   TH1F* hDau2MtdPt = new TH1F("hDau2Mtd", "hDau2Mtd", 100, 0, 10);
   TH1F* hDau3MtdPt = new TH1F("hDau3Mtd", "hDau3Mtd", 100, 0, 10);
   TH1F* hAllMtdPt = new TH1F("hAllMtd", "hAllMtd", 100, 0, 10);

   std::vector<Long64_t> nNoMtd(ana::nuOfY, 0);
   std::vector<Long64_t> nDau1Mtd(ana::nuOfY, 0);
   std::vector<Long64_t> nDau2Mtd(ana::nuOfY, 0);
   std::vector<Long64_t> nDau3Mtd(ana::nuOfY, 0);
   std::vector<Long64_t> nAllMtd(ana::nuOfY, 0);

   std::vector<Long64_t> nTotal(ana::nuOfY, 0);

   for(Long64_t ientry=0; ientry<t->GetEntries(); ientry++){
      t->GetEntry(ientry);

      const int iy = whichY(t->y);
      if( iy == -1 ) continue;

      if(fabs(t->EtaD1) > 3) continue;
      if(fabs(t->EtaD2) > 3) continue;
      if(fabs(t->EtaD3) > 3) continue;

      if(fabs(t->EtaD1) < 1.4 ? t->pTD1 <= 0.8 : t->pTD1 <= 0.5) continue;
      if(fabs(t->EtaD2) < 1.4 ? t->pTD2 <= 0.8 : t->pTD2 <= 0.5) continue;
      if(fabs(t->EtaD3) < 1.4 ? t->pTD3 <= 0.8 : t->pTD3 <= 0.5) continue;

      if(t->pT < maxPt && t->pT > minPt){
         if(t->isMtdDau1) nDau1Mtd[iy]++;
         if(t->isMtdDau2) nDau2Mtd[iy]++;
         if(t->isMtdDau3) nDau3Mtd[iy]++;
         if(!t->isMtdDau1 && !t->isMtdDau2 && !t->isMtdDau3) nNoMtd[iy]++;
         if(t->isMtdDau1 && t->isMtdDau2 && t->isMtdDau3) nAllMtd[iy]++;
         nTotal[iy]++;
      
         hAllY->Fill(t->y);
         if(t->isMtdDau1) hDau1MtdY->Fill(t->y);
         if(t->isMtdDau2) hDau2MtdY->Fill(t->y);
         if(t->isMtdDau3) hDau3MtdY->Fill(t->y);
         if(!t->isMtdDau1 && !t->isMtdDau2 && !t->isMtdDau3) hNoMtdY->Fill(t->y);
         if(t->isMtdDau1 && t->isMtdDau2 && t->isMtdDau3) hAllMtdY->Fill(t->y);
      }

      hAllPt->Fill(t->pT);
      if(t->isMtdDau1) hDau1MtdPt->Fill(t->pT);
      if(t->isMtdDau2) hDau2MtdPt->Fill(t->pT);
      if(t->isMtdDau3) hDau3MtdPt->Fill(t->pT);
      if(!t->isMtdDau1 && !t->isMtdDau2 && !t->isMtdDau3) hNoMtdPt->Fill(t->pT);
      if(t->isMtdDau1 && t->isMtdDau2 && t->isMtdDau3) hAllMtdPt->Fill(t->pT);
   }
   

   for(int iy=0; iy<ana::nuOfY; iy++){
      hNoMtd->SetBinContent(iy+1, (double)nNoMtd[iy]/nTotal[iy]);
      hDau1Mtd->SetBinContent(iy+1, (double)nDau1Mtd[iy]/nTotal[iy]);
      hDau2Mtd->SetBinContent(iy+1, (double)nDau2Mtd[iy]/nTotal[iy]);
      hDau3Mtd->SetBinContent(iy+1, (double)nDau3Mtd[iy]/nTotal[iy]);
      hAllMtd->SetBinContent(iy+1, (double)nAllMtd[iy]/nTotal[iy]);
   }

//   TCanvas *c1 = new TCanvas();
//   gStyle->SetOptStat(0);
//   hDraw->GetYaxis()->SetRangeUser(0, 1.35);
//   hDraw->GetXaxis()->SetTitle("y");
//   hNoMtd->SetLineColor(kBlack);
//   hDau1Mtd->SetLineColor(kRed);
//   hDau2Mtd->SetLineColor(kBlue);
//   hAllMtd->SetLineColor(kGreen);
//   hDraw->Draw();
//   hNoMtd->Draw("same");
//   hDau1Mtd->Draw("same");
//   hDau2Mtd->Draw("same");
//   hAllMtd->Draw("same");
//   TLegend *l1 = new TLegend(0.5, 0.6, 0.97, 0.95);
//   l1->AddEntry(hNoMtd, "ratio of LamC3P yield w/o mtd and all LamC3P", "pl");
//   l1->AddEntry(hDau1Mtd, "ratio of LamC3P yield whose dau1 w/ mtd to all LamC3P", "pl");
//   l1->AddEntry(hDau2Mtd, "ratio of LamC3P yield whose dau2 w/ mtd to all LamC3P", "pl");
//   l1->AddEntry(hAllMtd, "ratio of LamC3P yield whose dau1 & dau2 w/ mtd to all LamC3P", "pl");
//   l1->Draw();

   // full range of pT, with |y|<3 
   TLatex* latex = new TLatex();
   latex->SetTextSize(0.036);

   TCanvas* c2 = new TCanvas("cLamC3PpT", "", 450, 500);

   gStyle->SetOptStat(0);

   hDrawPt->GetYaxis()->SetRangeUser(0, 1.3);
   hDrawPt->GetYaxis()->SetTitle("LamC3P yield ratio");
   hDrawPt->GetXaxis()->SetTitle("LamC3P pT (GeV)");
   hDrawPt->Draw();

   hDau1MtdPt->Divide(hAllPt);
   hDau2MtdPt->Divide(hAllPt);
   hDau3MtdPt->Divide(hAllPt);
   hAllMtdPt->Divide(hAllPt);
   hNoMtdPt->Divide(hAllPt);

   hDau1MtdPt->SetLineColor(kBlue+6);
   hDau2MtdPt->SetLineColor(kBlue-6);
   hDau3MtdPt->SetLineColor(kGreen+6);
   hAllMtdPt->SetLineColor(kRed);
   hNoMtdPt->SetLineColor(kBlack);

   hDau1MtdPt->Draw("same");
   hDau2MtdPt->Draw("same");
   hDau3MtdPt->Draw("same");
   hAllMtdPt->Draw("same");
   hNoMtdPt->Draw("same");

   latex->DrawLatexNDC(0.6, 0.68, "-3 < LamC3P Rapidity < 3");

   TLegend *l2 = new TLegend(0.5, 0.75, 0.97, 0.95);
   l2->AddEntry(hNoMtdPt, "no daughter has mtd hits", "pl");
   l2->AddEntry(hDau1MtdPt, "dau1 w/ mtd", "pl");
   l2->AddEntry(hDau2MtdPt, "dau2 w/ mtd", "pl");
   l2->AddEntry(hDau3MtdPt, "dau3 w/ mtd", "pl");
   l2->AddEntry(hAllMtdPt, "dau1 && dau2 && dau3 w/ mtd", "pl");
   l2->Draw();

   TCanvas* c3 = new TCanvas("cLamC3PY", "", 450, 500);

   gStyle->SetOptStat(0);

   hDrawY->GetYaxis()->SetRangeUser(0, 1.3);
   hDrawY->GetYaxis()->SetTitle("LamC3P yield ratio");
   hDrawY->GetXaxis()->SetTitle("LamC3P y");
   hDrawY->Draw();

   hDau1MtdY->Divide(hAllY);
   hDau2MtdY->Divide(hAllY);
   hDau3MtdY->Divide(hAllY);
   hAllMtdY->Divide(hAllY);
   hNoMtdY->Divide(hAllY);

   hDau1MtdY->SetLineColor(kBlue+6);
   hDau2MtdY->SetLineColor(kBlue-6);
   hDau3MtdY->SetLineColor(kGreen+6);

   hAllMtdY->SetLineColor(kRed);
   hNoMtdY->SetLineColor(kBlack);

   hDau1MtdY->Draw("same");
   hDau2MtdY->Draw("same");
   hDau3MtdY->Draw("same");
   hAllMtdY->Draw("same");
   hNoMtdY->Draw("same");

   latex->DrawLatexNDC(0.6, 0.68, Form("LamC3P %.1f < p_{T} < %.1f GeV",minPt,maxPt));

   TLegend *l3 = new TLegend(0.5, 0.75, 0.97, 0.95);
   l3->AddEntry(hNoMtdY, "no daughter has mtd hits", "pl");
   l3->AddEntry(hDau1MtdY, "dau1 w/ mtd", "pl");
   l3->AddEntry(hDau2MtdY, "dau2 w/ mtd", "pl");
   l3->AddEntry(hDau3MtdY, "dau3 w/ mtd", "pl");
   l3->AddEntry(hAllMtdY, "dau1 && dau2 && dau3 w/ mtd", "pl");
   l3->Draw();

   //std::cout << hNoMtdY->GetBinContent(5+1) << std::endl;
   //std::cout << (double)nNoMtd[5]/nTotal[5] << std::endl;
   //std::cout << hDau1MtdY->GetBinContent(5+1) << std::endl;
   //std::cout << (double)nDau1Mtd[5]/nTotal[5] << std::endl;
   //std::cout << hDau2MtdY->GetBinContent(5+1) << std::endl;
   //std::cout << (double)nDau2Mtd[5]/nTotal[5] << std::endl;
   //std::cout << hDau3MtdY->GetBinContent(5+1) << std::endl;
   //std::cout << (double)nDau3Mtd[5]/nTotal[5] << std::endl;
   //std::cout << hAllMtdY->GetBinContent(5+1) << std::endl;
   //std::cout << (double)nAllMtd[5]/nTotal[5] << std::endl;
}
