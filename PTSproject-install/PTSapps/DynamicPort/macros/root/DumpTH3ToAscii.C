//
// Dump TH3 dose data to ASCII data file.
//   2013-11-23 T.Aso 
//
//void DumpTH3ToAscii(TString& rootFileName, TString& asciiFileName,TString& histName="jstDose"){
void DumpTH3ToAscii(TH3* h3, TString& asciiFileName){

  //cout << "Input  : "<<rootFileName<<endl;
  cout << "Output : "<<asciiFileName<<endl;
  //cout << "TH3    : "<<histName<<endl;
  cout << "TH3    : "<<h3->GetName()<<endl;

  std::ofstream ofs(asciiFileName);

  //TFile f(rootFileName);
  //TH3* h3 = (TH3*)f.Get(histName);   //gray

  Int_t nx = h3->GetNbinsX();
  Int_t ny = h3->GetNbinsY();
  Int_t nz = h3->GetNbinsZ();

  cout << "(Nx,Ny,Nz) = ("<<nx<<","<<ny<<","<<nz<<")"<<endl;

  for (Int_t iz = 0; iz < nz; iz++){
    for (Int_t iy = 0; iy < ny; iy++){
      ofs<<iy<<",";
      for (Int_t ix = 0; ix < nx; ix++){
        Double_t value = h3->GetBinContent(ix+1,iy+1,iz+1);
        ofs<< value;
        if ( ix < nx-1 ) ofs<<",";
      }
      ofs << endl;
    }
  }
  ofs.close();
  //f.Close();
}
