// ROOT include(s):
#include <TGraphAsymmErrors.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TFile.h>
#include <TH1F.h>

// STL include(s):
#include <string>

// Atlas Style:
#include "MiniReader/AtlasStyle.h"

void plotJetEfficiency(std::string in_sample, std::string out_dir)
{
  SetAtlasStyle();

  TFile file(in_sample.c_str());

  std::string processing_sample;

  if(in_sample.find("Znunu") != std::string::npos)

    processing_sample = "Znunu_";

  if(in_sample.find("D5") != std::string::npos)

    processing_sample = "D5_";

  if(in_sample.find("Compressed1") != std::string::npos)

    processing_sample = "Compressed1_";

  if(in_sample.find("Compressed2") != std::string::npos)

    processing_sample = "Compressed2_";

  for(int k = 0; k < 2; ++k) {

    std::string jvf_acc = "";
    std::string jvf_leg = "";

    if (k == 1) {

      jvf_acc = "_jvf_acc";
      jvf_leg = ", |#eta| < 2.4, JVF > .5";
    }

    for(int i = 3; i < 6; ++i) {

      TCanvas *c1 = new TCanvas();

      TGraphAsymmErrors *g1 = new TGraphAsymmErrors();
      TGraphAsymmErrors *g2 = new TGraphAsymmErrors();
      TGraphAsymmErrors *g3 = new TGraphAsymmErrors();
      TGraphAsymmErrors *g4 = new TGraphAsymmErrors();

      std::string n_jets = std::to_string(i) + "jets";

      g1->Divide((TH1F*)file.Get(("n_pvtx_" + n_jets + "_jetpt30" + jvf_acc).c_str()),
		 (TH1F*)file.Get("n_pvtx_noCut"), "cl=0.683 b(1,1) mode");

      g2->Divide((TH1F*)file.Get(("n_pvtx_" + n_jets + "_jetpt40" + jvf_acc).c_str()),
		 (TH1F*)file.Get("n_pvtx_noCut"), "cl=0.683 b(1,1) mode");

      g3->Divide((TH1F*)file.Get(("n_pvtx_" + n_jets + "_jetpt50" + jvf_acc).c_str()),
		 (TH1F*)file.Get("n_pvtx_noCut"), "cl=0.683 b(1,1) mode");

      g4->Divide((TH1F*)file.Get(("n_pvtx_" + n_jets + "_jetpt70" + jvf_acc).c_str()),
		 (TH1F*)file.Get("n_pvtx_noCut"), "cl=0.683 b(1,1) mode");

      TLegend *leg = new TLegend(.18, .2, .4, .45);

      leg->SetFillColor(0);
      leg->SetBorderSize(0);

      leg->AddEntry(g1, ("P_{T} " + std::to_string(i + 1) + "th Jet < 30 GeV" +
			 jvf_leg).c_str(), "L");
      leg->AddEntry(g2, ("P_{T} " + std::to_string(i + 1) + "th Jet < 40 GeV" +
			 jvf_leg).c_str(), "L");
      leg->AddEntry(g3, ("P_{T} " + std::to_string(i + 1) + "th Jet < 50 GeV" +
			 jvf_leg).c_str(), "L");
      leg->AddEntry(g4, ("P_{T} " + std::to_string(i + 1) + "th Jet < 70 GeV" +
			 jvf_leg).c_str(), "L");

      g1->SetLineColor(6);
      g1->SetMarkerColor(6);
      g2->SetLineColor(4);
      g2->SetMarkerColor(4);
      g3->SetLineColor(3);
      g3->SetMarkerColor(3);
      g4->SetLineColor(2);
      g4->SetMarkerColor(2);

      g1->GetXaxis()->SetTitle("N_{PV}");
      g1->GetYaxis()->SetTitle("Jet Veto Efficiency");

      g1->Draw("AP");
      g2->Draw("PSAME");
      g3->Draw("PSAME");
      g4->Draw("PSAME");

      leg->Draw();

      std::string pdf_name = out_dir + processing_sample + n_jets + jvf_acc + ".pdf";

      c1->Print(pdf_name.c_str());
    }
  }

  TCanvas *c1 = new TCanvas();

  gStyle->SetOptStat(0);

  TH1F *h1 = (TH1F*)file.Get("n_jet_per_n_pvtx_pfx");
  TH1F *h2 = (TH1F*)file.Get("n_jet_per_n_pvtx_jvf_acc_pfx");

  h1->SetTitle("");
  h1->GetXaxis()->SetTitle("N_{PV}");
  h1->GetYaxis()->SetTitle("<N_{Jets}>");
  h1->Draw();

  c1->Print((out_dir + "n_jet_per_n_pvtx.pdf").c_str());

  h2->SetTitle("");
  h2->GetXaxis()->SetTitle("N_{PV}");
  h2->GetYaxis()->SetTitle("<N_{Jets}>");
  h2->Draw();

  c1->Print((out_dir + "n_jet_per_n_pvtx_jvf_acc.pdf").c_str());
}

#ifndef __CINT__

// void StandaloneApplication(int argc, char **argv)
// {
//   std::string in_dir = argv[1];

//   plotJetEfficiency(in_dir);
// }

int main(int argc, char **argv)
{

  gROOT->Reset();
  // TApplication app("ROOT Application", &argc, argv);
  // StandaloneApplication(app.Argc(), app.Argv());
  // app.Run();

  std::string in_dir = argv[1];
  std::string out_dir = argv[2];

  plotJetEfficiency(in_dir, out_dir);

  return 0;
}

#endif // __CINT__
