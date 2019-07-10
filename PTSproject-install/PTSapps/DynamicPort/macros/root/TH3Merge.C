//
// Dump TH3 dose data to ASCII data file.
//   2013-11-23 T.Aso 
//
void TH3Merge(TString& rootFileName, TString& outFileName,Int_t istart, Int_t iend, TString& histName="jstEdep"){

  cout << "Input  : "<<rootFileName<<endl;
  cout << "Output : "<<outFileName<<endl;
  //
  TString fname;
  char srank[5];
  //
  Int_t i = istart;
  fname.Append(rootFileName);
  sprintf(srank,"_%d",i);
  fname.Append(srank);
  TFile fin(fname);
  TH3* h3 = (TH3*)fin.Get(histName);   //gray
  Double_t xmin = h3->GetXaxis()->GetXmin();
  Double_t xmax = h3->GetXaxis()->GetXmax();
  Double_t ymin = h3->GetYaxis()->GetXmin();
  Double_t ymax = h3->GetYaxis()->GetXmax();
  Double_t zmin = h3->GetZaxis()->GetXmin();
  Double_t zmax = h3->GetZaxis()->GetXmax();
  Int_t nx = h3->GetNbinsX();
  Int_t ny = h3->GetNbinsY();
  Int_t nz = h3->GetNbinsZ();
  TString hname = h3->GetName();
  cout << " Merge : " << fname <<" "<<h3->GetName()<<endl;
  cout << "(Nx,Ny,Nz) = ("<<nx<<","<<ny<<","<<nz<<")"<<endl;
  cout << "(Xmin,Xmax) = ("<<xmin<<","<<xmax<<")"<<endl;
  cout << "(Ymin,Ymax) = ("<<ymin<<","<<ymax<<")"<<endl;
  cout << "(Zmin,Zmax) = ("<<ymin<<","<<zmax<<")"<<endl;
  //
  fname.Clear();
  fin.Close();
  //
  TFile fout(outFileName,"RECREATE");
  TH3* hout = new TH3D(histName,hname,nx,xmin,xmax,ny,ymin,ymax,nz,zmin,zmax);
  //
  for ( Int_t i = istart; i < iend+1; i++){
    fname.Append(rootFileName);
    sprintf(srank,"_%d",i);
    fname.Append(srank);
    TFile fin(fname);
    TH3* h3 = (TH3*)fin.Get(histName);   //gray
    cout << " Merge : " << fname <<endl;
    ((TH3*)fout.Get(histName))->Add(h3);
    /*
    for (Int_t iz = 0; iz < nz; iz++){
      for (Int_t iy = 0; iy < ny; iy++){
        for (Int_t ix = 0; ix < nx; ix++){
          Double_t value = h3->GetBinContent(ix+1,iy+1,iz+1);
          TH3* hout = (TH3D*)fout.Get("jstDose");
          hout->Fill(ix,iy,iz,value);
        }
      }
    }
    */
    fin.Close();
    fname.Clear();
  }
  //
  fout.cd();
  hout->Write();
  fout.Write();
  fout.Close();
}
