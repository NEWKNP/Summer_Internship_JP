//--------------------------------------------------------------------------------------
//
// Dump TH3 dose data to ASCII data file.
//   2013-11-23 T.Aso 
//
Bool_t TH3Interpolate(TH3* h3, Double_t x, Double_t y, Double_t z, Double_t& value){

  TAxis* fXAxis = h3->GetXaxis();
  TAxis* fYAxis = h3->GetYaxis();
  TAxis* fZAxis = h3->GetZaxis();

  Int_t nbinX = h3->GetNbinsX();
  Int_t nbinY = h3->GetNbinsY();
  Int_t nbinZ = h3->GetNbinsZ();

  cout << "(Nx,Ny,Nz) = ("<<nbinX<<","<<nbinY<<","<<nbinZ<<")"<<endl;
  cout << " XAxis: "<<fXAxis->GetBinCenter(1)<<","<< fXAxis->GetBinCenter(nbinX)<< endl;
  cout << " YAxis: "<<fYAxis->GetBinCenter(1)<<","<< fYAxis->GetBinCenter(nbinY)<< endl;
  cout << " ZAxis: "<<fZAxis->GetBinCenter(1)<<","<< fZAxis->GetBinCenter(nbinZ)<< endl;


  if ( x < fXAxis->GetBinCenter(1) || x > fXAxis->GetBinCenter(nbinX) ) return  false;
  if ( y < fYAxis->GetBinCenter(1) || y > fYAxis->GetBinCenter(nbinY) ) return  false;
  if ( z < fZAxis->GetBinCenter(1) || z > fZAxis->GetBinCenter(nbinZ) ) return  false;

  cout << " Interpolate " << endl;
  value = h3->Interpolate(x,y,z);
  return true;
}
