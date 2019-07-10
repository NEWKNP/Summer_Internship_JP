//
// Dump Raw dose data of DCMTK.
// Values are converted to 32 bit unsigned integer.
//   2015-1-27 T.Aso 
//
void DumpRaw32(TString& rawFileName){

  TFile f("D.root","RECREATE");

  TH1D* h = new TH1D("h","dose",1019000,0,1019000);
  TH1D* h2 = new TH1D("h2","dose",2036,0,1.0549);
  TH1D* h3 = new TH1D("h3","dose",2100000,0,2100000);

  std::ifstream ifs;

  ifs.open(rawFileName,ios::in|ios::binary);

  Int_t nx = 174;
  Int_t ny = 173;
  Int_t nz = 124;
  Double_t scale = 1.0203293e-6;

  UInt_t itmp32;
  UInt_t maxVal = 0;

  for (Int_t iz = 0; iz < nz; iz++){
    for (Int_t iy = 0; iy < ny; iy++){
      for (Int_t ix = 0; ix < nx; ix++){
        ifs.read((char*)&itmp32, 4);
        if ( maxVal < itmp32 ) {
          maxVal = itmp32;
          cout << maxVal <<endl;
        }
        Double_t v = itmp32;
        if ( itmp32 > 0 ){
          h->Fill(v);
          h2->Fill((v*scale));
          h3->Fill(v);
        }
      }
    }
  }
  cout << maxVal << " "<< maxVal*scale<<endl;
  ifs.close();

  f.Write();
  f.Close();
}
