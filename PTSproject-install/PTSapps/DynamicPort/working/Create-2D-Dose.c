{
    // input file name
    TChain *chain = new TChain("JST");
    chain -> Add("Sample6_t*");
    cout<<chain->GetNtrees() << "\nfiles readed" << endl;
    //TH2* CImg = new TH2F("CImg", "XY dose dist.", 150, 0, 150, 150, 0, 150);
    //TH2* CImg = new TH2F("CImg", "YZ dose dist.", 250, 0, 250, 150, 0, 160);
    TH2* CImg = new TH2F("CImg", "XZ dose dist.", 250, 0, 250, 150, 0, 150);
    const Int_t Number = 4;
    Double_t Red[Number]   = {0.0 , 0.5  , 0.5 , 1.0};
    Double_t Blue[Number]  = {0.5 , 1.0  , 0.5 , 0.0};
    Double_t Green[Number] = {0.0 , 0.5  , 1.0 , 1.0};
    Double_t Stop[Number]  = {0.0 , 0.3 , 0.6 , 1.0};
    Int_t nb = 255;
    TColor::CreateGradientColorTable(Number,Stop,Red,Green,Blue,nb);
    
    //JST -> Draw("ix:iy>>CImg", "de"); // for xy
    //JST -> Draw("iy:iz>>CImg", "de"); // for yz
    JST -> Draw("ix:iz>>CImg", "de"); // for xz
    //CImg -> Draw("colx");
    CImg -> Draw("coly");
    //CImg -> Draw("colz");
    
    
    // output file name
    //TFile foutRoot("Sample_JST_xy.root","RECREATE"); // for xy
    //TFile foutRoot("Sample_JST_yz.root","RECREATE"); // for yz
    TFile foutRoot("Sample_JST_xz.root","RECREATE"); // for xz
    
    CImg->Write();
    foutRoot.Write();
    foutRoot.Close();
}

