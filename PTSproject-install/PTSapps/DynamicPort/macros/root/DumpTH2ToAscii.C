//
// Dump TH2 dose data to ASCII data file.
//   2013-11-23 T.Aso 
//
//void DumpTH2ToAscii(TString& rootFileName, TString& asciiFileName,TString& histName){
void DumpTH2ToAscii(TH2* h2, TString& asciiFileName){

  //cout << "Input  : "<<rootFileName<<endl;
  cout << "Output : "<<asciiFileName<<endl;
  //cout << "TH2    : "<<histName<<endl;
  cout << "TH2    : "<<h2->GetName()<<endl;

  std::ofstream ofs(asciiFileName);

  //TFile f(rootFileName);
  //TH2* h2 = (TH2*)f.Get(histName);   //gray

  Int_t nx = h2->GetNbinsX();
  Int_t ny = h2->GetNbinsY();

  cout << "(Nx,Ny) = ("<<nx<<","<<ny<<")"<<endl;

    for (Int_t iy = 0; iy < ny; iy++){
      ofs<<iy<<",";
      for (Int_t ix = 0; ix < nx; ix++){
        Double_t value = h2->GetBinContent(ix+1,iy+1);
        ofs<< value;
        if ( ix < nx-1 ) ofs<<",";
      }
      ofs << endl;
    }
  ofs.close();
  //f.Close();
}
