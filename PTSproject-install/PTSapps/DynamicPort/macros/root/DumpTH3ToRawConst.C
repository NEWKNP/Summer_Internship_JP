//
// Dump TH3 dose data to RAW data file.
// Values are converted to 32 bit unsigned integer.
//   2014-10-13 T.Aso 
//
void invertByteOrder32(unsigned char * _val, unsigned int& _rval){
  const int SIZE = sizeof(_rval);
  union {
    unsigned char cu[4];
    unsigned int  tu;
  } uni;
  for ( int i = 0; i < SIZE; i++){
    uni.cu[i] = _val[SIZE-1-i];
  }
  _rval = uni.tu;
}

void invertByteOrder16(unsigned char * _val, unsigned short& _rval){
  const int SIZE = sizeof(_rval);
  union {
    unsigned char cu[2];
    unsigned short  tu;
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
void dcmtkScaleCommand(TString fileCom, Int_t nbit, TString doseUnit, Double_t scale){
  std::ofstream ofile(fileCom);
  ofile << "dcmodify -ma \"(0028,0100)="<<nbit<<"\"  dose.dcm"<<endl;
  ofile << "dcmodify -ma \"(0028,0101)="<<nbit<<"\"  dose.dcm"<<endl;
  ofile << "dcmodify -ma \"(0028,0102)="<<nbit-1<<"\"  dose.dcm"<<endl;
  ofile << "dcmodify -ma \"(3004,000e)="<<scale<<"\"  dose.dcm"<<endl;
  ofile << "dcmodify -ma \"(3004,0002)="<<doseUnit<<"\"  dose.dcm"<<endl;
  ofile.close();
}
//
Int_t DumpTH3ToRawConst(TH3* h3, TString rawFileName, TString DoseUnit="RELATIVE", Int_t Nbit=16, Bool_t littleEndian=true){

  cout << "Output : "<<rawFileName<<endl;
  cout << "TH3    : "<<h3->GetName()<<endl;
  cout << "Nbit   : "<<Nbit<<endl;
  if ( !( Nbit == 32 || Nbit == 16 ) ){
    cerr << "%%% Nbit must be 32 or 16 !!!!!"<<endl;
    exit(-1);
  }

  std::ofstream ofs;

  ofs.open(rawFileName,ios::out|ios::binary);

  Int_t nx = h3->GetNbinsX();
  Int_t ny = h3->GetNbinsY();
  Int_t nz = h3->GetNbinsZ();

  Double_t min = h3 ->GetBinContent(h3->GetMinimumBin());
  Double_t max = h3 ->GetBinContent(h3->GetMaximumBin());

  //---------------
  Int_t MaxBit = 32;
  if ( Nbit == 32 ) {
    MaxBit = 21;
  }else {
    MaxBit = 16;
  }
  //---------------

  const unsigned int BITRANGE = TMath::Power(2.0,MaxBit)-1;

  Double_t factor = max/BITRANGE;
  Double_t scale  = 1.05/BITRANGE;

  cout << "(Nx,Ny,Nz) = ("<<nx<<","<<ny<<","<<nz<<")"<<endl;
  cout << "(min,max) = (" <<min<<","<<max<<")"<<endl;
  cout << "(factor, BITRANGE) = ("<<factor<<","<<BITRANGE<<")"<<endl;

  unsigned int itmp32;
  unsigned short itmp16;

  for (Int_t iz = 0; iz < nz; iz++){
    for (Int_t iy = 0; iy < ny; iy++){
      for (Int_t ix = 0; ix < nx; ix++){
        Double_t value = h3->GetBinContent(ix+1,iy+1,iz+1);
        //
        if ( Nbit == 32 ) {
          unsigned int ivalue32 = (unsigned int)(value / factor);
          if ( littleEndian ){
            ofs.write((char*)&ivalue32, 4);
          }else{
            invertByteOrder32((unsigned char*)&ivalue32,itmp32);
            ofs.write((char*)&itmp32, 4);
          }
        }else if ( Nbit == 16 ){
          unsigned short ivalue16 = (unsigned short)(value / factor);
          if ( littleEndian ){
            ofs.write((char*)&ivalue16, 2);
          }else{
            invertByteOrder16((unsigned char*)&ivalue16,itmp16);
            ofs.write((char*)&itmp16, 2);
          }
        }
      }
    }
  }
  ofs.close();

  dcmtkScaleCommand("dcmPix.sh",Nbit,DoseUnit,scale);
  dcmtkCommand("dcmPix.sh",rawFileName);

  exit(0);
}
