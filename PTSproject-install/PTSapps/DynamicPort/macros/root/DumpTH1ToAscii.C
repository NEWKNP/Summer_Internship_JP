//
// Dump TH1 dose data to ASCII data file.
//   2013-11-23 T.Aso 
//
//void DumpTH1ToAscii(TString& rootFileName, TString& asciiFileName,TString& histName){
void DumpTH1ToAscii(TH1* h1, TString& asciiFileName){

  //cout << "Input  : "<<rootFileName<<endl;
  cout << "Output : "<<asciiFileName<<endl;
  //cout << "TH1    : "<<histName<<endl;
  cout << "TH1    : "<<h1->GetName()<<endl;

  std::ofstream ofs(asciiFileName);

  //TFile f(rootFileName);
  //TH1* h1 = (TH1*)f.Get(histName);   //gray

  Int_t nx = h1->GetNbinsX();

  cout << "Nx = "<<nx<<endl;

      for (Int_t ix = 0; ix < nx; ix++){
        Double_t value = h1->GetBinContent(ix+1);
        ofs<< value;
        if ( ix < nx-1 ) ofs<<",";
      }
      ofs << endl;
  ofs.close();
  //f.Close();
}
