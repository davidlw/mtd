#ifndef _ANA_h_
#define _ANA_h_
namespace ana{
   const float massPion = 0.139570;
   const float massKaon = 0.493677;
   const float massProton = 0.938272;

   const int nuOfY = 12;
   const float ybin[nuOfY+1] = {-3, -2.5, -2., -1.5, -1., -0.5, 0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0};
   const int nuOfPt = 12;
   const float ptbin[nuOfPt+1] = {0., 0.5, 1.0, 1.5, 2.0, 3.0, 4.0, 5.0, 6.0, 8.0, 10.0, 20.0, 10000.0};

   const double evts_bkg_MB = 200;
   const double evts_bkg_central = 20;

   const double evts_data_MB = 500e6;

   const double TAA0_100 = 5.61; // mb^-1
   const double TAA0_10 = 23.2; // mb^-1
   const double pbOvermb = 1e-12/1e-3;
   const double GeV = 1;
   const double BR = 0.05;

   const double evts_sim_MB = 25e9;
   const double evts_sim_central = evts_sim_MB * 0.1;

   const float mass_lw[nuOfY] = {2.286-0.03, 2.286-0.025, 2.286-0.02, 2.286-0.015, 2.286-0.01, 2.286-0.01, 2.286-0.01, 2.286-0.01, 2.286-0.015, 2.286-0.02, 2.286-0.025, 2.286-0.03};
   const float mass_up[nuOfY] = {2.286+0.03, 2.286+0.025, 2.286+0.02, 2.286+0.015, 2.286+0.01, 2.286+0.01, 2.286+0.01, 2.286+0.01, 2.286+0.015, 2.286+0.02, 2.286+0.025, 2.286+0.03};
};
#endif
