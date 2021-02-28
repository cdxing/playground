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

void toyjackknife(){
  TFile *f_out = new TFile("toyjackknife.root", "recreate");
  int i_knife = 10;
  TH1D *h1[i_knife+1];
  for(int jkk=0; jkk<i_knife+1; jkk++){
    h1[jkk] = new TH1D(Form("h1_%d",jkk),Form("h1_%d",jkk),1000,-5, 5.);
  }
  TH1D *h_jkk = new TH1D("h_jkk","h_jkk",10000,-0.1, 0.1);
  gRandom = new TRandom3(0);
  // gRandom1 = new TRandom3(0);
  double mean_data=0.;
  for(int i=0; i<1000000;i++){
    double randgaus, randuni;
    // gRandom->SetSeed (i);
    // if(i % 100000 == 0) gRandom -> SetSeed(i);
    randgaus = gRandom->Gaus(0, 1);
    randuni  = gRandom->Uniform(i_knife);
    mean_data +=  randgaus;
    // randuni  = i % i_knife + 1;
    for(int jkk=0; jkk<i_knife+1; jkk++){
      if(jkk == 0 || (randuni > jkk - 1 && randuni <= jkk)){
        h1[jkk]->Fill(randgaus);
      }
    }
  }
  for(int jkk=1; jkk<i_knife+1; jkk++){
    h1[jkk]->Add(h1[0],h1[jkk],1.,-1.);
  }
  for(int jkk=1; jkk<i_knife+1; jkk++){
    h1[jkk]->Fit("gaus","E+","R",-4.,4.);
    TF1 *fit = h1[jkk]->GetFunction("gaus");
    h_jkk->Fill((double)fit->GetParameter(1));
  }
  h_jkk->Fit("gaus","E+","R",-0.,0.006);
  h1[0]->Fit("gaus","E+","R",-4,4);
  mean_data /= 1000000.;
  cout << "mean_data is: " << mean_data<< endl;
  f_out->Write();
  f_out->Close();
}
