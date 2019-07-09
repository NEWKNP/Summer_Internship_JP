{
    //For yz
    Int_t i, j, k;
    
    std::ostringstream ost;

    // input file name
    //ost << "WP-OSEM-yzVtx-108-comparison.root";//for yzVtx
    ost << "WP-OSEM-yzDose-108-2-comparison.root";//for yzDose

    const TString rtfile = ost.str();
    cout << rtfile << endl;   // check
    
    TFile fp(rtfile);
    
    
    TH2* CImg = (TH2*)fp.Get("nCImg");
    
    TH2* RPro = (TH2*)fp.Get("nRPro");
    
    /*    
     // for ke
     
     TH2* RPro = (TH2*)fp.Get("nRPro_0k");
     TH2* RPro = (TH2*)fp.Get("nRPro_500k");
     TH2* RPro = (TH2*)fp.Get("nRPro_1000k");
     TH2* RPro = (TH2*)fp.Get("nRPro_2000k");
     TH2* RPro = (TH2*)fp.Get("nRPro_3000k");
     TH2* RPro = (TH2*)fp.Get("nRPro_4000k");
     TH2* RPro = (TH2*)fp.Get("nRPro_5000k");
     TH2* RPro = (TH2*)fp.Get("nRPro_6000k");
     */
    TCanvas* c = new TCanvas("c", "c", 0, 0, 720, 720);
    //c->Divide(2, 2);

    //c->cd(1);
    //CImg->SetStats(0);
    //CImg -> Draw("colz");
    //c->cd(2);
    
    //TH2* RIfbp = new TH2F("RIfbp", "", 512, -320, 320, 512, -320, 320);
    TH2* RIfbp = new TH2F("RIfbp", "", 512, -256, 256, 512, -256, 256);
    
    for(i=512; i>=1; i--)
    {
        for(j=1; j<=512; j++)
        {
            if(RPro->GetBinContent(j, i)>= 0.)
            {
                RIfbp -> SetBinContent(j, i, RPro->GetBinContent(j, i));
            }
            else if(RPro->GetBinContent(j, i) < 0.)
            {
                RIfbp -> SetBinContent(j, i, 1E-30);
            }
            
        }
    }
    RIfbp->SetStats(0);
    RIfbp->GetXaxis()->SetTitle("z/mm");
    RIfbp->GetYaxis()->SetTitle("y/mm");
    RIfbp->GetYaxis()->SetTitleOffset(1.30);
    RIfbp->Draw("colz");  //for Reconstructed Image
    
    TH1* h11 = new TH1F("h11", "", 512, -256, 256);
    //TH1* h12 = new TH1F("h12", "", 512, -320, 320);
    TH1* h12 = new TH1F("h12", "", 512, -256, 256);
    TH1* h14 = new TH1F("h14", "", 512, -256, 256);
    
    Float_t s, ans;
    Double_t thisBinDose, thisBinRpro;
    ans = 0;
    for(i=1; i<=512; i++)
    {
        
        thisBinDose = CImg->GetBinContent(i,257);
        thisBinRpro = RPro->GetBinContent(i,257);

        
        if(thisBinRpro < 0.)
        {
            thisBinRpro = 0.;
        }
	s = thisBinDose-thisBinRpro;

	ans += s*s;
        h11->SetBinContent(i, thisBinDose);
        h12->SetBinContent(i, thisBinRpro);
	h14->SetBinContent(i, s);
    }
    ans /= 512;
    ans = TMath::Sqrt(ans);
    printf("%lf\n",ans);
  

    //c->cd(3);
    //h11 -> Draw();
    
    //c->cd(4);
    //h12 ->Draw();

    TH1* h13 = new TH1F("h13", "", 512, -256, 256);

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
	h13->SetBinContent(i, min);
    }
    
    Int_t Mh11 = 0;
    Mh11 = h11->GetMaximumBin();
    Mh11 = Mh11 - 256;
    printf("h11MaxbinNumber:%dmm\n", Mh11);
    
    Int_t Mh12 = 0;
    Mh12 = h12->GetMaximumBin();
    Mh12 = Mh12 - 256;
    printf("h12MaxbinNumber:%dmm\n", Mh12);

    //Int_t Mh13 = 0;
    //Mh13 = h13->GetMaximumBin();
    //Mh13 = Mh13 - 256;
    //printf("h12MaxbinNumber:%dmm\n", Mh13);
     
    TCanvas* c1 = new TCanvas("c1", "c1", 0, 0, 360, 320);
    
    h11->SetXTitle("z /mm");
    h11->SetYTitle("Pixel value");
    h11->SetTitleOffset(1.2, "y");
    
    h11->SetStats(0);
    h11->SetLineColor(2);
    h11->SetLineStyle(1);
    h11->Draw("");
    
    h12->SetStats(0);
    h12->SetLineColor(9);
    h12->SetLineStyle(1);
    h12->Draw("hsame");

    // for 150 and 190M
    leg = new TLegend(0.12, 0.75, 0.54, 0.85, "");
    
    //for 230M
    //  leg = new TLegend(0.48, 0.75, 0.90, 0.85, "");
    leg->SetFillStyle(0);
    leg->SetTextSize(0.03);
    
    leg->SetBorderSize(0);
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

    TCanvas* c2 = new TCanvas("c2", "c2", 0, 0, 360, 320);
    
    h13->SetXTitle("z /mm");
    h13->SetYTitle("gamma-index");
    h13->SetTitleOffset(1.2, "y");
    h13->SetStats(0);
    h13->SetLineColor(2);
    h13->SetLineStyle(1);
    h13->SetMinimum(0);
    h13->SetMaximum(20);
    h13->Draw("");

    TCanvas* c3 = new TCanvas("c3", "c3", 0, 0, 360, 320);
    
    h14->SetXTitle("z /mm");
    h14->SetYTitle("Pixel value");
    h14->SetTitleOffset(1.2, "y");
    h14->SetStats(0);
    h14->SetLineColor(2);
    h14->SetLineStyle(1);
    h14->Draw("");
    
    
}
