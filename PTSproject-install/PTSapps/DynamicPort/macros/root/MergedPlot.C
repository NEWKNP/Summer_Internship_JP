void MergedPlot(TString& filename, TString& outFile="MergedPlot.png"){

  TFile f(filename);
  TH3* jsth = (TH3*)f.Get("jstEdep");

  TH2* proj_xz = (TH2*)jsth->Project3D("xz");
  TH2* proj_xy = (TH2*)jsth->Project3D("xy");

  jsth->GetYaxis()->SetRange(60,60);
  TH2* jstEdep_xz00 = jsth->Project3D("xz00");

  jsth->GetYaxis()->SetRange(0,0);//Reset
  jsth->GetZaxis()->SetRange(70,70);
  TH2* jstEdep_xy00 = jsth->Project3D("xy00");

  jsth->GetYaxis()->SetRange(60,60);
  jsth->GetZaxis()->SetRange(70,70);
  TH1* jstEdep_x00 = jsth->Project3D("x00");

  jsth->GetYaxis()->SetRange(0,0);//Reset
  jsth->GetXaxis()->SetRange(90,90);
  jsth->GetZaxis()->SetRange(70,70);
  TH1* jstEdep_y00 = jsth->Project3D("y00");


  TCanvas * c1 = new TCanvas("c1",filename,800,1200);

  c1->Divide(2,3);

  c1->cd(1);
  proj_xz->Draw("colz");

  c1->cd(2);
  proj_xy->Draw("colz");

  c1->cd(3);
  jstEdep_xz00->Draw("colz");

  c1->cd(4);
  jstEdep_xy00->Draw("colz");

  c1->cd(5);
  jstEdep_x00->Draw();

  c1->cd(6);
  jstEdep_y00->Draw();

  //
  c1->cd();
  //c1->Update();

  c1->Print(outFile);
}
