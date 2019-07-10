//
// Dump TH3 dose data to RAW data file.
// Values are converted to 32 bit unsigned integer.
//   2014-10-13 T.Aso 
//
//  TH3ToRTDose.C
//     void TH3ToRTDose(TH3* h3, TString& rawFileName, TString gridfile="grid.dat", 
//                      TString refpointfile="refPoint.dat", TString DoseUnit="RELATIVE", 
//                      Int_t Nbit=32, Bool_t littleEndian=true, 
//                      TString OutShellScript="dcmPix.sh");
//
//  root> .x  TH3ToRTDose.C(......)
//   or 
//  
//  $ g++  -o  TH3ToRTDose.exe  TH3ToRTDose.C  `root-config --cflags --glibs`
//  $ ./TH3ToRTDose.exe <rootFileName> <rawFileName> ....
// 
//
#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TH3.h"
#include "TMath.h"

using namespace std;
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

//--------------------------------------------------------------------------------------
void GetGridInfo(TString& gridFileName, Double_t origin[3], 
                 Double_t unit[3], Int_t nxyz[3],Double_t pitch[3]){
  // 
  Int_t fVerbose = 0;
  //
  std::ifstream ifs;
  ifs.open(gridFileName);

  TString line;
  line.ReadLine(ifs); // dummy
  if ( fVerbose > 0 ) cout << line << endl;
  //
  line.ReadLine(ifs); // dummy
  if ( fVerbose > 0 ) cout << line << endl;
  line.ReadToDelim(ifs,','); // Origin X
  if ( fVerbose > 0 ) cout << line << " OX"<<endl;
  origin[0] = std::atof(line.Data());
  line.ReadToDelim(ifs,','); // Origin Y
  if ( fVerbose > 0 ) cout << line << " OY"<<endl;
  origin[1] = std::atof(line.Data());
  line.ReadToDelim(ifs); // Origin Z
  if ( fVerbose > 0 ) cout << line << " OZ"<<endl;
  origin[2] = std::atof(line.Data());
  //
  line.ReadLine(ifs); // dummy
  if ( fVerbose > 0 ) cout << line << endl;
  line.ReadToDelim(ifs,','); // Unit X1
  if ( fVerbose > 0 ) cout << line <<" X1" <<endl;
  unit[0] = std::atof(line.Data());
  line.ReadToDelim(ifs,','); // Unit X2
  if ( fVerbose > 0 ) cout << line <<" X2"<< endl;
  line.ReadToDelim(ifs); // Unit X3
  if ( fVerbose > 0 ) cout << line <<" X3"<< endl;
  //
  line.ReadLine(ifs); // dummy
  if ( fVerbose > 0 ) cout << line << endl;
  line.ReadToDelim(ifs,','); // Unit Y1
  if ( fVerbose > 0 ) cout << line << endl;
  line.ReadToDelim(ifs,','); // Unit Y2
  if ( fVerbose > 0 ) cout << line << endl;
  unit[1] = std::atof(line.Data());
  line.ReadToDelim(ifs); // Unit Y3
  if ( fVerbose > 0 ) cout << line << endl;
  //
  line.ReadLine(ifs); // dummy
  if ( fVerbose > 0 ) cout << line << endl;
  line.ReadToDelim(ifs,','); // Unit Z1
  if ( fVerbose > 0 ) cout << line << endl;
  line.ReadToDelim(ifs,','); // Unit Z2
  if ( fVerbose > 0 ) cout << line << endl;
  line.ReadToDelim(ifs); // Unit Z3
  if ( fVerbose > 0 ) cout << line << endl;
  unit[2] = std::atof(line.Data());
  //
  line.ReadLine(ifs); // dummy
  if ( fVerbose > 0 ) cout << line << endl;
  line.ReadToDelim(ifs,','); // Nx
  nxyz[0] = std::atoi(line.Data());
  if ( fVerbose > 0 ) cout << line << endl;
  line.ReadToDelim(ifs,','); // Ny
  if ( fVerbose > 0 ) cout << line << endl;
  nxyz[1] = std::atoi(line.Data());
  line.ReadToDelim(ifs); // Nz
  if ( fVerbose > 0 ) cout << line << endl;
  nxyz[2] = std::atoi(line.Data());
  //
  line.ReadLine(ifs); // dummy
  if ( fVerbose > 0 ) cout << line << endl;
  line.ReadToDelim(ifs,','); // PitchX
  if ( fVerbose > 0 ) cout << line << endl;
  pitch[0] = std::atof(line.Data());
  line.ReadToDelim(ifs,','); // PitchY
  if ( fVerbose > 0 ) cout << line << endl;
  pitch[1] = std::atof(line.Data());
  line.ReadToDelim(ifs); // PitchZ
  if ( fVerbose > 0 ) cout << line << endl;
  pitch[2] = std::atof(line.Data());
  //
  cout << "Origin : ("<<origin[0]<<","<<origin[1]<<","<<origin[2]<<")"<<endl;
  cout << "Unit   : ("<<unit[0]<<","<<unit[1]<<","<<unit[2]<<")"<<endl;
  cout << "Nxyz   : ("<<nxyz[0]<<","<<nxyz[1]<<","<<nxyz[2]<<")"<<endl;
  cout << "Pitch  : ("<<pitch[0]<<","<<pitch[1]<<","<<pitch[2]<<")"<<endl;
}

Double_t  GetRefPointInfo(TString& refpointfile, Double_t RefCoord[3]){
  // 
  Int_t fVerbose = 1;
  //
  std::ifstream ifs;
  ifs.open(refpointfile);
  //=== PrintRefernce Dose ==== 
  // BeamID= 1
  // BeamDosePoint= (0.00949501,-101.991,-1543.5)
  // BeamDose= 1.81818


  TString line;
  line.ReadLine(ifs); // dummy
  if ( fVerbose > 0 ) cout << line << endl;
  //
  line.ReadLine(ifs); // dummy
  if ( fVerbose > 0 ) cout << line << endl;
  //
  line.ReadToDelim(ifs,'('); //  dummy
  if ( fVerbose > 0 ) cout << line << endl;
  line.ReadToDelim(ifs,','); //  X
  if ( fVerbose > 0 ) cout << line << " X"<<endl;
  RefCoord[0] = std::atof(line.Data());
  line.ReadToDelim(ifs,','); //  Y
  if ( fVerbose > 0 ) cout << line << " Y"<<endl;
  RefCoord[1] = std::atof(line.Data());
  line.ReadToDelim(ifs,')'); //  X
  if ( fVerbose > 0 ) cout << line << " Z"<<endl;
  RefCoord[2] = std::atof(line.Data());
  //
  line.ReadToDelim(ifs); //  Dummy
  //if ( fVerbose > 0 ) cout << line << <endl;
  //
  line.ReadToDelim(ifs,'='); //  dummy
  if ( fVerbose > 0 ) cout << line << " X"<<endl;
  line.ReadToDelim(ifs); //  Dose
  if ( fVerbose > 0 ) cout << line << " X"<<endl;
  return  std::atof(line.Data());
}
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
//--------------------------------------------------------------------------------------
Double_t DumpTH3ReformSample(TString& gridfile, TH3* h3, Double_t x, Double_t y, Double_t z)
{

  Double_t  origin[3];
  Double_t  unit[3];
  Int_t  nxyz[3];
  Double_t  pitch[3];
  GetGridInfo(gridfile, origin, unit, nxyz, pitch);

  Double_t p[3] = { x, y, z};

  Double_t pn[3];
  for ( Int_t i = 0; i < 3; i++){
    pn[i] = ( p[i] - origin[i])/(unit[i]*pitch[i])+0.5;
  }

  cout << "Input (x,y,z)        : ("<<p[0]<<","<<p[1]<<","<<p[2]<<")"<<endl;
  cout << "Input (pnx,pny,pnz)  : ("<<pn[0]<<","<<pn[1]<<","<<pn[2]<<")"<<endl;

  Double_t value;
  Bool_t ret = TH3Interpolate(h3,pn[0],pn[1],pn[2],value);
  cout << " Return "<< ret << "  value= "<<value << endl;
  return value;

}

void dcmtkCommand(TString& fileCom, TString& fileRaw){
  std::ofstream ofile(fileCom,std::ios::out | std::ios::app);
  ofile << "dcmodify -mf \"PixelData="<<fileRaw<<"\"  dose.dcm"<<endl;
  ofile.close();
}

void dcmtkGridCommand(TString& fileCom, TString& gridFile){ 
  Double_t  origin[3];
  Double_t  unit[3];
  Int_t     nxyz[3];
  Double_t  pitch[3];
  GetGridInfo(gridFile, origin, unit, nxyz, pitch);

  std::ofstream ofile(fileCom);
  ofile << "dcmodify -ma \"(0008,0070)=PTSIM\" dose.dcm"<<endl;
  ofile << "dcmodify -ma \"(0008,1010)=PTSIM\" dose.dcm"<<endl;
  ofile << "dcmodify -ma \"(0018,0050)="<< pitch[2]<<"\" dose.dcm" <<endl;
  ofile << "dcmodify -ma \"(0020,0032)="<<origin[0]<<"\\"<<origin[1]<<"\\"<<origin[2]<<"\"  dose.dcm"<<endl;
  ofile << "dcmodify -ma \"(0020,0037)="
        << unit[0]<<"\\0.0\\0.0\\"
        << "0.0\\"<<unit[1]<<"\\0.0\""
        << "  dose.dcm"<<endl;
  ofile << "dcmodify -ma \"(0028,0008)="<< nxyz[2]<<"\"  dose.dcm"<<endl;
  ofile << "dcmodify -ma \"(0028,0010)="<< nxyz[1]<<"\"  dose.dcm"<<endl;
  ofile << "dcmodify -ma \"(0028,0011)="<< nxyz[0]<<"\"  dose.dcm"<<endl;
  ofile << "dcmodify -ma \"(0028,0030)="<< pitch[0]<<"\\"<<pitch[1]<<"\" dose.dcm"<<endl;
  //--
  ofile << "dcmodify -ma \"(3004,000c)=";
  for ( Int_t i = 0 ; i < nxyz[2] ; i++){
    ofile << (i*pitch[2]);
    if ( i < nxyz[2]-1 ) ofile << "\\";
  }
  ofile << "\" dose.dcm" << endl;
  //--

}

void dcmtkRefPointCommand(TString& fileCom, TString& refpointfile){
  std::ofstream ofile(fileCom,std::ios::out | std::ios::app);
  Double_t RefCoord[3];
  // In RTPlan (Prescribed Dose)
  Double_t refDose = GetRefPointInfo(refpointfile, RefCoord); 
  ofile << "dcmodify -ma \"(3004,0008)="<<RefCoord[0]<<"\\"<<RefCoord[1]<<"\\"<<RefCoord[2]<<"\"  dose.dcm"<<endl;
  ofile.close();
}
void dcmtkScaleCommand(TString& fileCom, Int_t nbit, TString& doseUnit, Double_t scale){
  std::ofstream ofile(fileCom,std::ios::out | std::ios::app);
  ofile << "dcmodify -ma \"(0028,0100)="<<nbit<<"\"  dose.dcm"<<endl;
  ofile << "dcmodify -ma \"(0028,0101)="<<nbit<<"\"  dose.dcm"<<endl;
  ofile << "dcmodify -ma \"(0028,0102)="<<nbit-1<<"\"  dose.dcm"<<endl;
  ofile << "dcmodify -ma \"(3004,000e)="<<scale<<"\"  dose.dcm"<<endl;
  ofile << "dcmodify -ma \"(3004,0002)="<<doseUnit<<"\"  dose.dcm"<<endl;
  ofile.close();
}
//
void TH3ToRTDose(TH3* h3, TString& rawFileName, TString gridfile="grid.dat", TString refpointfile="refpoint.dat", TString DoseUnit="RELATIVE", Int_t Nbit=32, Bool_t littleEndian=true, TString OutShellScript="dcmPix.sh"){

  cout << "Output : "<<rawFileName<<endl;
  cout << "TH3    : "<<h3->GetName()<<endl;
  cout << "grid   : "<<gridfile<<endl;
  cout << "RefPoint: "<<refpointfile<<endl;

  cout << "Nbit   : "<<Nbit<<endl;
  if ( !( Nbit == 32 || Nbit == 16 ) ){
    cerr << "%%% Nbit must be 32 or 16 !!!!!"<<endl;
    exit(0);
  }

  Double_t RefCoord[3];
  // In RTPlan (Prescribed Dose)
  Double_t refDose = GetRefPointInfo(refpointfile, RefCoord); 
  // In PTSIM
  Double_t refPointValue = DumpTH3ReformSample(gridfile,h3,RefCoord[0], RefCoord[1], RefCoord[2]); 
  // Normalization factor
  Double_t normFact = refDose/refPointValue;

  cout << " RefDose " << refDose <<endl;
  cout << " RefPoint Value " << refPointValue <<endl;
  cout << " normFact " << normFact <<endl;

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

  Double_t scale  = (max*normFact)/BITRANGE;

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

  dcmtkGridCommand(OutShellScript,gridfile);
  dcmtkScaleCommand(OutShellScript,Nbit,DoseUnit,scale);
  dcmtkRefPointCommand(OutShellScript,refpointfile);
  dcmtkCommand(OutShellScript,rawFileName);

  
}

//
#ifndef __CINT__
int main(int argc, char** argv){

  if ( argc == 1 ){
    cout << " Syntax : DicomConv.exe  "<<endl;
    cout <<"  TString& rootFileName, TString& rawFileName, "<<endl;
    cout <<"  TString gridfile, TString refpointfile, "<<endl;
    cout <<"  TString DoseUnit, Int_t Nbit, Bool_t littleEndian," <<endl; 
    cout <<"  TString OutShellScript "<<endl;
    return -1;
  }else{
    cout << argc << endl;
  }

  TString  rootFileName=argv[1];
  TString  rawFileName=argv[2];
  TString  gridfile = "grid.dat";
  TString  refpointfile="refdose.dat";
  TString  DoseUnit="RELATIVE";
  Int_t    Nbit=32;
  //Bool_t   littleEndian=true;
  Bool_t   littleEndian=false;
  TString  OutShellScript="dcmPix.sh";

  cout << rootFileName <<endl;
  cout << rawFileName <<endl;
  if ( argc > 3 ) gridfile     = argv[3];
  cout << gridfile <<endl;
  if ( argc > 4 ) refpointfile = argv[4];
  cout << refpointfile<<endl;
  if ( argc > 5 ) DoseUnit     = argv[5];
  cout << DoseUnit <<endl;
  if ( argc > 6 ) Nbit = std::atoi(argv[6]);
  cout << Nbit <<endl;
  if ( argc > 7 ) {
    if ( TString(argv[7]) == "true" ) littleEndian = true;
    else littleEndian = false;
  }
  cout << littleEndian <<endl;
  if ( argc > 7 ) OutShellScript = argv[8];
  cout << OutShellScript <<endl;

  TFile f(rootFileName);
  TH3* h3 = (TH3*)(f.Get("jstDose"));
  h3->Print();
  TH3ToRTDose(h3,rawFileName,gridfile,refpointfile,DoseUnit,Nbit,littleEndian,OutShellScript);

  return 0;
}
#endif
