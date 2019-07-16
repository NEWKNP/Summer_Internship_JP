{
    // create ROOT file

    //  Dose part

    //TFile fp("Sample_JST_xy.root");
    //TFile fp("Sample_JST_yz.root");
    TFile fp("Sample_JST_xz.root");

    TH2* nCImg = new TH2F("nCImg", "Dost.", 250, 0, 250, 150, 0, 150);

    Int_t i,j;
    Double_t MC = 0;

    TH2* CImg = (TH2*)fp.Get("CImg");

    MC = CImg->GetBinContent(CImg->GetMaximumBin());

    cout << MC << endl;
    
    // normalization
    for(i=1; i<=250; i++)
    {
        for(j=1; j<=150; j++)
        {
            Double_t BinCImg = CImg->GetBinContent(i,j);
            nCImg->SetBinContent(i,j, BinCImg/MC);
        }
    }

    nCImg->Draw("colx");
    //nCImg->Draw("coly");
    //nCImg->Draw("colz");

    cout << nCImg->GetBinContent(50,70) << endl;
    cout << nCImg->GetBinContent(250,80) << endl;

    //OSEM part 

    TH2* RPro = new TH2F("RPro", "OSEM.", 512, -256, 256, 512, -256, 256);
    TH2* nRPro = new TH2F("nRPro", "OSEM.", 512, -256, 256, 512, -256, 256);
    
    const Int_t ndim = 512;
    Float_t xy;
    std::ifstream fin;
 
    // input file name 2
    //fin.open("./result/reconstruct_sinogram_xy.csv"); // for xy
    //fin.open("./result/reconstruct_sinogram_yz.csv"); // for yz
    fin.open("./result/reconstruct_sinogram_xz.csv"); // for xz

    //fin.open("./result/reconstruct_sinogram_xy_2pi.csv"); // for xz

    //fin.open("./result/reconstruct_sinogram_xz_1it.csv"); // for xz
    //fin.open("./result/reconstruct_sinogram_xz_3it.csv"); // for xz
    //fin.open("./result/reconstruct_sinogram_xz_5it.csv"); //for xz
    //fin.open("./result/reconstruct_sinogram_xz_7it.csv"); // for xz
    //fin.open("./result/reconstruct_sinogram_xz_9it.csv"); // for xz
    //fin.open("./result/reconstruct_sinogram_xz_64ss.csv"); // for xz
    
    if(fin.is_open()==false)
    {
        cout << "open error" << endl;
        exit(1);
    }
    
    for(i=1; i<=512; i++)
    {
        for(j=1; j<=512; j++)
        {
            fin >> xy;
            //RPro -> SetBinContent(i, j, xy);
            RPro -> SetBinContent(i, j, xy);
        }
    }
    fin.close();

    Double_t MR = 0;

    // max bincontent
    MR = RPro->GetBinContent(RPro->GetMaximumBin());

    // normalization
    //for(i=1; i<=512; i++)
    for(i=512; i>=1; i--)
    {
        for(j=1; j<=512; j++)
        {
            Double_t BinContent = RPro->GetBinContent(j,i);
            if(BinContent == 0.0)
            {
	      nRPro->SetBinContent(513-i,j, 1E-30);
              //nRPro->SetBinContent(j,i, 1E-30);
	      //;
		
            }
            else
            {
                nRPro->SetBinContent(513-i,j, BinContent/MR);
                //nRPro->SetBinContent(j,i, BinContent/MR);
	    }
        }
    }

    //nRPro->Draw("colx");
    //nRPro->Draw("coly");
    //nRPro->Draw("colz");

    // output file name
    //TFile foutRoot("Sample_xy_final.root","RECREATE");
    //TFile foutRoot("Sample_yz_final.root","RECREATE");
    TFile foutRoot("Sample_xz_final.root","RECREATE");

    //TFile foutRoot("Sample_xy_1it_final.root","RECREATE");
    //TFile foutRoot("Sample_xy_3it_final.root","RECREATE");
    //TFIle foutRoot("Sample_xz_5it_final.root","RECREATE");
    //TFile foutRoot("Sample_xy_7it_final.root","RECREATE");
    //TFile foutRoot("Sample_xy_9it_final.root","RECREATE");
    //TFile foutRoot("Sample_xy_64ss_final.root","RECREATE");

    nCImg->Write();
    nRPro->Write();
    
    foutRoot.Write();
    foutRoot.Close();
    
}
