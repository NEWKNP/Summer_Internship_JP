//
// Dump TH3 dose data to RAW data file.
// Values are converted to 32 bit unsigned integer.
//   2014-10-13 T.Aso 
//
void invertByteOrder(char * _val, int& _rval){
  const int SIZE = sizeof(_rval);
  union {
    char cu[16];
    int  tu;
  } uni;
  for ( int i = 0; i < SIZE; i++){
    uni.cu[i] = _val[SIZE-1-i];
  }
  _rval = uni.tu;
}
void dcmtkCommand(TString fileCom, TString fileRaw){
  std::ofstream ofile(fileCom,std::ios::out | std::ios::app);
  ofile << "dcmodify -mf \"PixelData="<<fileRaw<<"\"  dose.dcm"<<endl;
  ofile.close();
}
void dcmtkScaleCommand(TString fileCom, Double_t scale){
  std::ofstream ofile(fileCom);
  ofile << "dcmodify -ma \"(0028,0100)=32\"  dose.dcm"<<endl;
  ofile << "dcmodify -ma \"(0028,0101)=32\"  dose.dcm"<<endl;
  ofile << "dcmodify -ma \"(0028,0102)=31\"  dose.dcm"<<endl;
  ofile << "dcmodify -ma \"(3004,000e)="<<scale<<"\"  dose.dcm"<<endl;
  ofile.close();
}
//
void DumpTH3ToRaw(TH3* h3, TString& rawFileName, Bool_t littleEndian=true){

  cout << "Output : "<<rawFileName<<endl;
  cout << "TH3    : "<<h3->GetName()<<endl;

  std::ofstream ofs;

  ofs.open(rawFileName,ios::out|ios::binary);

  Int_t nx = h3->GetNbinsX();
  Int_t ny = h3->GetNbinsY();
  Int_t nz = h3->GetNbinsZ();

  Double_t min = h3 ->GetBinContent(h3->GetMinimumBin());
  Double_t max = h3 ->GetBinContent(h3->GetMaximumBin());

  const unsigned int DOSERANGE = TMath::Power(2.0,31);
  //const unsigned int DOSERANGE = TMath::Power(2.0,15);

  Double_t scale = max/DOSERANGE;

  cout << "(Nx,Ny,Nz) = ("<<nx<<","<<ny<<","<<nz<<")"<<endl;
  cout << "(min,max) = (" <<min<<","<<max<<")"<<endl;
  cout << "(scale, DOSERANGE) = ("<<scale<<","<<DOSERANGE<<")"<<endl;

  int itmp;

  for (Int_t iz = 0; iz < nz; iz++){
    for (Int_t iy = 0; iy < ny; iy++){
      for (Int_t ix = 0; ix < nx; ix++){
        Double_t value = h3->GetBinContent(ix+1,iy+1,iz+1);
        unsigned int ivalue = (unsigned int)(value / scale);
        if ( littleEndian ){
          ofs.write((char*)&ivalue, 4);
        }else{
          invertByteOrder((char*)&ivalue,itmp);
          ofs.write((char*)&itmp, 4);
        }
      }
    }
  }
  ofs.close();

  dcmtkScaleCommand("dcmPix.sh",scale);
  dcmtkCommand("dcmPix.sh",rawFileName);
}
