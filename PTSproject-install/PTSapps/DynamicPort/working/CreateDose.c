{
    // input file name
    TChain *chain = new TChain("JST");
    chain -> Add("../MU-108-190-Results/SampleDS_t*");
    cout<<chain->GetNtrees() << "files readed" << endl;

    TH2* CImg = new TH2F("CImg", "", 512, -256, 256, 512, -256, 256);
    const Int_t Number = 4;
    Double_t Red[Number]   = {0.0 , 0.5  , 0.5 , 1.0};
    Double_t Blue[Number]  = {0.5 , 1.0  , 0.5 , 0.0};
    Double_t Green[Number] = {0.0 , 0.5  , 1.0 , 1.0};
    Double_t Stop[Number]  = {0.0 , 0.3 , 0.6 , 1.0};
    Int_t nb = 255;
    TColor::CreateGradientColorTable(Number,Stop,Red,Green,Blue,nb);
    
    //JST -> Draw("(iy-150):((-1)*(ix)+149)>>CImg", "dose"); // for xy
    JST -> Draw("(iy-150):((-1)*(iz)+249)>>CImg", "dose"); // for yz
    CImg -> Draw("colz");
    
    
    // output file name
    TFile foutRoot("MU-yzDose-108-190.root","RECREATE"); // for xy
    
    CImg->Write();
    foutRoot.Write();
    foutRoot.Close();
}

