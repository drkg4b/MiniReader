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
#include <iostream>
#include <string>

// Atlas Style:
#include "MiniReader/AtlasStyle.h"

#define PR(x) std::cout << #x << " = " << x << std::endl

void plotJetEfficiency(const std::string &, const std::string &);

int main(int argc, char **argv)
{
  std::string in_dir = argv[1];
  std::string out_dir = argv[2];

  plotJetEfficiency(in_dir, out_dir);

  return 0;
}

void plotJetEfficiency(const std::string &in_sample, const std::string &out_dir)
{
  SetAtlasStyle();

  TFile file(in_sample.c_str());

  std::string processing_sample;

  if (in_sample.find("Znunu") != std::string::npos)

    processing_sample = "Znunu_";

  if (in_sample.find("D5") != std::string::npos)

    processing_sample = "D5_";

  if (in_sample.find("Compressed_450_435") != std::string::npos)

    processing_sample = "Compressed_450_435_";

  if (in_sample.find("Compressed_450_425") != std::string::npos)

    processing_sample = "Compressed_450_425_";

  std::vector<std::string> region = {"SR_"};
  std::vector<std::string> suffix = {"_M0"};
  std::vector<std::string> jvt = {"", "_jvt14", "_jvt64", "_jvt92"};
  std::vector<std::string> jvt_leg_vec = {"", ", JVT > 0.14", ", JVT > 0.64",
					  ", JVT > 0.92"};

  for (size_t i = 0; i < region.size(); ++i) {
    for (size_t j = 0; j < suffix.size(); ++j) {
      for (size_t k = 0; k < jvt.size(); ++k) {

        std::string plot_pref = region[i] + "n_pvtx_";
        std::string den_plot = plot_pref + "noCut" + suffix[j];
        std::string x_label = "N_{PV}";
        std::string jvt_acc = jvt[k] + suffix[j];
        std::string jvt_leg = jvt_leg_vec[k];

        for (int i = 3; i < 6; ++i) {

          TCanvas *c1 = new TCanvas();

          TGraphAsymmErrors *g1 = new TGraphAsymmErrors();
          TGraphAsymmErrors *g2 = new TGraphAsymmErrors();
          TGraphAsymmErrors *g3 = new TGraphAsymmErrors();
          TGraphAsymmErrors *g4 = new TGraphAsymmErrors();

          std::string n_jets = std::to_string(i) + "jets";

          g1->Divide((TH1F *)file.Get((plot_pref + n_jets + "_jetpt30" + jvt_acc).c_str()),
                     (TH1F *)file.Get(den_plot.c_str()), "cl=0.683 b(1,1) mode");

          g2->Divide((TH1F *)file.Get((plot_pref + n_jets + "_jetpt40" + jvt_acc).c_str()),
                     (TH1F *)file.Get(den_plot.c_str()), "cl=0.683 b(1,1) mode");

          g3->Divide((TH1F *)file.Get((plot_pref + n_jets + "_jetpt50" + jvt_acc).c_str()),
                     (TH1F *)file.Get(den_plot.c_str()), "cl=0.683 b(1,1) mode");

          g4->Divide((TH1F *)file.Get((plot_pref + n_jets + "_jetpt70" + jvt_acc).c_str()),
                     (TH1F *)file.Get(den_plot.c_str()), "cl=0.683 b(1,1) mode");

          TLegend *leg = 0;

          leg = new TLegend(.18, .2, .4, .45);

          leg->SetFillColor(0);
          leg->SetBorderSize(0);

          leg->AddEntry(g1, ("P_{T} " + std::to_string(i + 1) + "th Jet < 30 GeV" +
                             jvt_leg).c_str(), "L");
          leg->AddEntry(g2, ("P_{T} " + std::to_string(i + 1) + "th Jet < 40 GeV" +
                             jvt_leg).c_str(), "L");
          leg->AddEntry(g3, ("P_{T} " + std::to_string(i + 1) + "th Jet < 50 GeV" +
                             jvt_leg).c_str(), "L");
          leg->AddEntry(g4, ("P_{T} " + std::to_string(i + 1) + "th Jet < 70 GeV" +
                             jvt_leg).c_str(), "L");

          g1->SetLineColor(6);
          g1->SetMarkerColor(6);
          g1->GetXaxis()->SetRangeUser(0, 43);
          g1->GetYaxis()->SetRangeUser(0, 1.3);

          g2->SetLineColor(4);
          g2->SetMarkerColor(4);

          g3->SetLineColor(3);
          g3->SetMarkerColor(3);

          g4->SetLineColor(2);
          g4->SetMarkerColor(2);

          g1->GetXaxis()->SetTitle(x_label.c_str());
          g1->GetYaxis()->SetTitle("Jet Veto Efficiency");

          g1->Draw("AP");
          g2->Draw("PSAME");
          g3->Draw("PSAME");
          g4->Draw("PSAME");

          leg->Draw();

          std::string pdf_name = out_dir + processing_sample +
                                 n_jets + jvt_acc;

          pdf_name += ".pdf";

          c1->Print(pdf_name.c_str());
        }
      }
    }
  }
}
