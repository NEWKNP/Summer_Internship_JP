{
    // input file name
    TChain *chain = new TChain("JST");
    chain -> Add("Sample6_t*");
    cout<<chain->GetNtrees() << "\nfiles readed" << endl;
    //TH1* CImg = new TH1F("CImg", "X dose dist.", 150, 0, 150);
    //TH1* CImg = new TH1F("CImg", "Y dose dist.", 150, 0, 150);
    TH1* CImg = new TH1F("CImg", "Z dose dist.", 250, 0, 250);
    const Int_t Number = 4;
    Double_t Red[Number]   = {0.0 , 0.5  , 0.5 , 1.0};
    Double_t Blue[Number]  = {0.5 , 1.0  , 0.5 , 0.0};
    Double_t Green[Number] = {0.0 , 0.5  , 1.0 , 1.0};
    Double_t Stop[Number]  = {0.0 , 0.3 , 0.6 , 1.0};
    Int_t nb = 255;
    TColor::CreateGradientColorTable(Number,Stop,Red,Green,Blue,nb);
    
    //JST -> Draw("ix>>CImg", "de"); // for x
    //JST -> Draw("iy>>CImg", "de"); // for y
    JST -> Draw("iz>>CImg", "de"); // for z
    CImg -> Draw();
    
    // output file name
    //TFile foutRoot("Sample_JST_x.root","RECREATE"); // for x
    //TFile fourRoot("Sample_JST_y.root","RECREATE"); // for y
    TFile fourRoot("Sample_JST_z.root","RECREATE"); // for z
    
    CImg->Write();
    foutRoot.Write();
    foutRoot.Close();
}

