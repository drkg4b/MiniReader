// ROOT include(s):
#include <TGraphAsymmErrors.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TROOT.h>
#include <TFile.h>
#include <TH1F.h>

// STL include(s):
#include <string>

void plotJetEfficiency(std::string in_sample)
{
  TFile file(in_sample.c_str());

  std::string processing_sample;

  if(in_sample.find("Znunu") != std::string::npos)

    processing_sample = "Znunu";

  if(in_sample.find("D5") != std::string::npos)

    processing_sample = "D5";

  for(int i = 3; i < 6; ++i) {

    TCanvas *c1 = new TCanvas();

    TGraphAsymmErrors *g1 = new TGraphAsymmErrors();
    TGraphAsymmErrors *g2 = new TGraphAsymmErrors();
    TGraphAsymmErrors *g3 = new TGraphAsymmErrors();
    TGraphAsymmErrors *g4 = new TGraphAsymmErrors();

    std::string n_jets = std::to_string(i) + "jets";

    g1->Divide((TH1F*)file.Get(("n_pvtx_" + n_jets + "_jetpt30").c_str()),
	       (TH1F*)file.Get("n_pvtx_noCut"), "cl=0.683 b(1,1) mode");

    g2->Divide((TH1F*)file.Get(("n_pvtx_" + n_jets + "_jetpt40").c_str()),
	       (TH1F*)file.Get("n_pvtx_noCut"), "cl=0.683 b(1,1) mode");

    g3->Divide((TH1F*)file.Get(("n_pvtx_" + n_jets + "_jetpt50").c_str()),
	       (TH1F*)file.Get("n_pvtx_noCut"), "cl=0.683 b(1,1) mode");

    g4->Divide((TH1F*)file.Get(("n_pvtx_" + n_jets + "_jetpt70").c_str()),
	       (TH1F*)file.Get("n_pvtx_noCut"), "cl=0.683 b(1,1) mode");

    TLegend *leg = new TLegend(.15, .15, .36, .40);

    leg->SetFillColor(0);
    leg->SetBorderSize(0);

    leg->AddEntry(g1, "P_{T} 3rd Jet < 30 GeV", "L");
    leg->AddEntry(g2, "P_{T} 3rd Jet < 40 GeV", "L");
    leg->AddEntry(g3, "P_{T} 3rd Jet < 50 GeV", "L");
    leg->AddEntry(g4, "P_{T} 3rd Jet < 70 GeV", "L");

    g1->SetLineColor(6);
    g2->SetLineColor(4);
    g3->SetLineColor(3);
    g4->SetLineColor(2);

    g1->GetXaxis()->SetTitle("N_{PV}");
    g1->GetYaxis()->SetTitle("Jet Efficiency");

    g1->Draw("AP");
    g2->Draw("PSAME");
    g3->Draw("PSAME");
    g4->Draw("PSAME");

    leg->Draw();

    std::string pdf_name = processing_sample + n_jets + ".pdf";

    c1->Print(pdf_name.c_str());
  }
}

#ifndef __CINT__

void StandaloneApplication(int argc, char **argv)
{
  std::string in_dir = argv[1];

  plotJetEfficiency(in_dir);
}

int main(int argc, char **argv)
{

  gROOT->Reset();
  TApplication app("ROOT Application", &argc, argv);
  StandaloneApplication(app.Argc(), app.Argv());
  app.Run();

  return 0;
}

#endif // __CINT__
