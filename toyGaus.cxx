// C++ headers
#include <iostream>
#include <fstream>
#include "Riostream.h"
#include <cstdlib>
#include <string>
#include <vector>
#include <math.h>
#include <set>
#include <map>

//need this stuff to compile in linux:
#include <TROOT.h>
#include <TApplication.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TStreamerElement.h>
#include <TStyle.h>
#include "TSystemDirectory.h"

#include "TFile.h"
#include "TNtuple.h"
#include "TTree.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TMath.h"
#include "TChain.h"
#include "TLegend.h"
#include "TFractionFitter.h"
#include "TVirtualFitter.h"
#include "TCut.h"
#include "TObject.h"
#include "TGaxis.h"
#include "TSpectrum.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TSpline.h"
#include "TPaveText.h"
#include "Fit/FitResult.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"
#include "TRandom.h"
#include "TRandom3.h"
#include "TDatime.h"
#include "Math/MinimizerOptions.h"

using namespace std;
// -------------------------- set Some fitting prerequsites --------------------
const Double_t _y_CM = -2.03;
Double_t proportion(Double_t *x, Double_t *p);

void toyGaus(){
  gRandom = new TRandom3(0);
  double y0, y1, y2, y3, y4, y5, y6;
  y0 = gRandom->Gaus(-0.0173913,0.000275362);
  y1 = gRandom->Gaus(0.00217391,0.000210145);
  y2 = gRandom->Gaus(-0.00797101,0.000195652);
  y3 = gRandom->Gaus(0.0057971,0.000271739);
  y4 = gRandom->Gaus(0.00678684,0.000220404);
  y5 = gRandom->Gaus(0.0191681,0.000129847);
  y6 = gRandom->Gaus(0.0203576,0.000461443);
  double vll[7]={y0, y1, y2, y3, y4, y5, y6};
  double yy_7p2_7p7[7] = { -0.45, -0.15, 0.15, 0.45, -1.25-_y_CM, -0.75-_y_CM, -0.25-_y_CM};
  TGraphErrors *graph_v1_vs_y_7p2_7p7 = new TGraphErrors(7, yy_7p2_7p7, vll, 0, 0);
  graph_v1_vs_y_7p2_7p7->SetMarkerStyle(31);
  graph_v1_vs_y_7p2_7p7->SetMarkerColor(kBlack);
  graph_v1_vs_y_7p2_7p7->SetLineColor(kBlack);
  graph_v1_vs_y_7p2_7p7->SetMarkerSize(2);
  graph_v1_vs_y_7p2_7p7->Draw();
  TF1 * tf1_dv1dy_7p2_7p7 = new TF1("tf1_dv1dy_7p2_7p7",proportion,0.,2.,1);
  graph_v1_vs_y_7p2_7p7->Fit(tf1_dv1dy_7p2_7p7,"E+","R",-0.6,/*2.*/0.-_y_CM);
  graph_v1_vs_y_7p2_7p7->GetFunction("tf1_dv1dy_7p2_7p7")->Draw("same");
}
Double_t proportion(Double_t *x, Double_t *p)
{
  return ( p[0] * x[0]);
}
