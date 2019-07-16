{
    Int_t i, j, k;
    
    std::ostringstream ost;

    // input file name
    //ost << "Sample_xy_final.root";//for xyDose
    ost << "Sample_yz_final.root";//for yzDose
    //ost << "Sample_xz_final.root";//for xzDose

    const TString rtfile = ost.str();
    cout << rtfile << endl;   // check
    
    TFile fp(rtfile);

    TH2* CImg = (TH2*)fp.Get("nCImg");
    TH2* RPro = (TH2*)fp.Get("nRPro");
    /*
    TCanvas* c = new TCanvas("c", "Old Reconstruct Image", 0, 0, 720, 720);

    TH2* RIfbp = new TH2F("RIfbp", "OSEM YZ", 512, -256, 256, 512, -256, 256);
    
    for(i=1; i<=512; i++)
    {
        for(j=1; j<=512; j++)
        {
            if(RPro->GetBinContent(i, j) >= 0)
            {
                RIfbp->SetBinContent(i, j, RPro->GetBinContent(i, j));
                //RIfbp->SetBinContent(j, i, RPro->GetBinContent(j, i));
            }
            else if(RPro->GetBinContent(i, j) < 0)
            {
                RIfbp->SetBinContent(i, j, 1E-30);
                //RIfbp->SetBinContent(j, i, 1E-30);
            }
        }
    }
    RIfbp->SetStats(0);
    RIfbp->GetXaxis()->SetTitle("z/mm");
    RIfbp->GetYaxis()->SetTitle("y/mm");
    RIfbp->GetYaxis()->SetTitleOffset(1.30);
    //RIfbp->Draw("colx");  //for Reconstructed Image
    RIfbp->Draw("coly");  //for Reconstructed Image
    //RIfbp->Draw("colz");  //for Reconstructed Image
    */
    TH1* h11 = new TH1F("h11", "Dost. Z", 250, -256, 256);
    TH1* h12 = new TH1F("h12", "OSEM. Z", 512, -256, 256);
    TH1* h13 = new TH1F("h13", "different Z", 512, -256, 256);
    
    Float_t s, ans;
    Double_t thisBinDose, thisBinRpro;
    ans = 0;

    for(i=1; i<=512; i++)
    {
        
        thisBinDose = CImg->GetBinContent(i,75);
        thisBinRpro = RPro->GetBinContent(i,257);
        //thisBinDose = CImg->GetBinContent(i,i);
        //thisBinRpro = RPro->GetBinContent(i,i);

        //cout << thisBinDose << endl;

        if(thisBinRpro < 0.)
        {
            thisBinRpro = 0.;
        }
	s = thisBinDose-thisBinRpro;

	ans += s*s;
        h11->SetBinContent(i, thisBinDose);
        h12->SetBinContent(i, thisBinRpro);
	h13->SetBinContent(i, s);
    }
    ans /= 512;
    ans = TMath::Sqrt(ans);
    printf("%lf\n",ans);

    TH1* h14 = new TH1F("h14", "??? Z", 512, -256, 256);

    Float_t s1, s2, s3, ans, min;
    for(i=1; i<=512; i++)
    {
        min = 100.0;
        thisBinDose = CImg->GetBinContent(i, 257);

	for(j=i-3; j<=i+3; j++)
	{
	    for(k=254; k<=260; k++)
	    {
	        thisBinRpro = RPro->GetBinContent(j, k);
		s1 = (thisBinDose-thisBinRpro)/0.03;
		s2 = (j-i)/3;
		s3 = (k-257)/3;
		ans = s1*s1 + s2*s2 + s3*s3;
		ans = TMath::Sqrt(ans);
		if(min > ans)
		{
		    min = ans;
		}
	    }
	}
	//printf("%lf\n", min);
	h14->SetBinContent(i, min);
    }
    
    Int_t MinH11 = 0, MaxH11 = 0;
    MinH11 = h11->GetMinimumBin();
    MaxH11 = h11->GetMaximumBin();
    MaxH11 = MaxH11 - 256;
    printf("h11MinbinNumber:%dmm\n", MinH11);
    printf("h11MaxbinNumber:%dmm\n", MaxH11);

    Int_t MinH12 = 0, MaxH12 = 0;
    MinH12 = h12->GetMinimumBin();
    MaxH12 = h12->GetMaximumBin();
    MaxH12 = MaxH12 - 256;
    printf("h12MinbinNumber:%dmm\n", MinH12);
    printf("h12MaxbinNumber:%dmm\n", MaxH12);

    Int_t MinH13 = 0, MaxH13 = 0;
    MinH13 = h13->GetMaximumBin();
    MaxH13 = h13->GetMaximumBin();
    MaxH13 = MaxH13 - 256;
    printf("h13MinbinNumber:%dmm\n", MinH13);
    printf("h13MaxbinNumber:%dmm\n", MaxH13);

    TCanvas* c1 = new TCanvas("c1", "Compare Dose and OSEM", 0, 0, 720, 720);
    //h11 set new scale
    h11->SetXTitle("z /mm");
    h11->SetYTitle("Pixel value");
    h11->SetTitleOffset(1.2, "x");
    
    h11->SetStats(0);
    h11->SetLineColor(2);
    h11->SetLineStyle(1);
    h11->Draw("");
    
    h12->SetStats(0);
    h12->SetLineColor(9);
    h12->SetLineStyle(1);
    h12->Draw("hsame");

    // for 150 and 190M
    leg = new TLegend(0.54, 0.80, 0.90, 0.90);
    leg->SetFillStyle(0);
    leg->SetTextSize(0.03);
    
    leg->SetBorderSize(1);
    leg->SetFillColor(0);
    
    leg->AddEntry(h11, "Dose distribution", "l");
    //leg->AddEntry(h11, "Origin of secondary particles", "l");
    
    leg->AddEntry(h12, "Reconstructed Image", "l");
    
    //  leg->AddEntry(h12, "Image (E>=0[MeV])", "l");
    //  leg->AddEntry(h12, "Image (E>=0.5[MeV])", "l");
    //  leg->AddEntry(h12, "Image (E>=1[MeV])", "l");
    //  leg->AddEntry(h12, "Image (E>=2[MeV])", "l");
    //  leg->AddEntry(h12, "Image (E>=3[MeV])", "l");
    //  leg->AddEntry(h12, "Image (E>=4[MeV])", "l");
    //  leg->AddEntry(h12, "Image (E>=5[MeV])", "l");
    //  leg->AddEntry(h12, "Image (E>=6[MeV])", "l");
   
    leg->Draw();

    TCanvas* c2 = new TCanvas("c2", "Difference", 0, 0, 720, 720);
    
    h13->SetXTitle("z /mm");
    h13->SetYTitle("gamma-index");
    h13->SetTitleOffset(1.2, "x");
    h13->SetStats(0);
    h13->SetLineColor(2);
    h13->SetLineStyle(1);
    h13->SetMinimum(0);
    h13->SetMaximum(20);
    h13->Draw("");

    TCanvas* c3 = new TCanvas("c3", "Reconstruct", 0, 0, 720, 720);
    
    h14->SetXTitle("z /mm");
    h14->SetYTitle("Pixel value");
    h14->SetTitleOffset(1.2, "x");
    h14->SetStats(0);
    h14->SetLineColor(2);
    h14->SetLineStyle(1);
    h14->Draw("");
}
