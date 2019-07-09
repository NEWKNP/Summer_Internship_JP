//Sinogram
{
        // input file name
        //TFile f("../Sample.root");
        
        // for csv file of xz
        
        //TTree* tree = (TTree*)f.Get("TUBD");
  
        TChain *tree = new TChain("TUBD");
	tree->Add("Sample6_t*");
	cout << tree->GetNtrees() << "\nfiles readed" << endl;

        Float_t px = 0.;
        Float_t pz = 0.;
        Float_t x = 0.;
        Float_t z = 0.;
	Float_t ke = 0.;
        Int_t pid = 0;
        
        tree->SetBranchAddress("px", &px);
        tree->SetBranchAddress("pz", &pz);
        tree->SetBranchAddress("x", &x);
        tree->SetBranchAddress("z", &z);
        tree->SetBranchAddress("pid", &pid);
	tree->SetBranchAddress("ke", &ke);
        
        Double_t s = 0.;
        Double_t s2 = 0.;
        Double_t theta = 0.;
        Double_t iRadian = 0.;
        
        Double_t sX = 0.;
        Double_t sZ = 0.;
        
	//Plane
        TCanvas* c = new TCanvas("c", "c", 0, 0, 720, 720);
        //c->Divide(2, 2); 
        //--  1 pixel -> 1mm
    
        TH1* s_mm = new TH1F("s_mm", "s /mm", 512 , -256, 256);
        TH1* theta_deg = new TH1F("theta_deg", "theta /deg", 512 , 0, 360);

        TH2* preCPro = new TH2F("preCPro", "preProjectionData", 512, 0, 256, 512, 0, 360);
        TH2* CPro = new TH2F("CPro", "ProjectionData-XZ", 512, -256, 256, 512, 0, 360);
    
        //Calculate Sx Sz theta from x0,z0,px,pz
    
        Int_t nEntry = tree->GetEntries();
        
        for(Int_t iEntry=0; iEntry<nEntry; ++iEntry)
        {
            tree->GetEntry(iEntry);
	    //if(pid==22&&(ke>=4300&&ke<=4600)||(ke>=5100&&ke<=5400)||(ke>=6000&&ke<=6200)||(ke>=6800&&ke<=7200))
	    if(pid==22)
            {
                
                if(px!=0.0 && pz!=0.0)
                {
                    sX = ((z-x*(pz/px))/((-1)*(pz/px)-(px/pz)));
                    sZ = ((x-z*(px/pz))/((-1)*(pz/px)-(px/pz)));
                    
                    iRadian = TMath::ATan2(sX, sZ);
                }
                else if(pz==0.0 && px!=0.0)
                {
                    sZ = z;
                    sX = 0.0;
                    
                    if(x>=0.0)
                    {
                        iRadian = 0.0;
                    }
                    else if(x<0.0)
                    {
                        iRadian = TMath::Pi();
                    }
                }
                else if(pz!=0.0 && px==0.0)
                {
                    sZ = 0.0;
                    sX = x;
                    
                    if(z>0.0)
                    {
                        iRadian = TMath::Pi() * (-1);
                    }
                    else if(z<=0.0)
                    {
                        iRadian = TMath::PiOver2();  // PiOver2 = Pi()/2.0
                    }
                }
                
                s2 = TMath::Power(sX, 2.0) + TMath::Power(sZ, 2.0);
                s = TMath::Sqrt(s2);
                
                Double_t subS = (0.0-sZ)*(x-sX) - (0.0-sX)*(z-sZ);
                
                if(subS > 0.0) // left
                {
                    s = s*(-1.0);
                    
                    iRadian = iRadian - TMath::Pi();
                    
                    if(iRadian < (-1)*TMath::Pi())
                    {
                        iRadian = iRadian + TMath::TwoPi();
                    }
                }
                else if(subS < 0.0) // right
                {
                    ;
                }
                else if(subS==0.0)
                {
                    if(sZ==0.0)
                    {
                        s = x;
                    }
                    else if(sX==0.0)
                    {
                        s = z;
                    }
                }
                
                theta = iRadian * 180.0 / TMath::Pi();
                
                if(theta < 0.)
                {
                    theta = theta + 360.0;
                }
                
                s_mm -> Fill(s);
                theta_deg -> Fill(theta);
                preCPro -> Fill(s, theta);
                CPro -> Fill(s, theta);
                
                //printf("z0(%10.4f, %10.4f), sZ(%10.4f, %10.4f) %10.4f, %10.4f\n", z, y, sZ, sY, s, theta);  // Test
            }
            
            //roop end
            
        }
        //c->cd(1);
        //s_mm->Draw();
        //c->cd(2);
        //theta_deg->Draw();
        //c->cd(3);
        //preCPro->Draw();
        //c->cd(4);

        CPro->SetStats(0);
        CPro->GetXaxis()->SetTitle("s");
        CPro->GetYaxis()->SetTitle("theta");
        CPro->GetYaxis()->SetTitleOffset(1.30);
        CPro -> Draw("coly");

        // - csv -------------------------------------------------
        
	std::ofstream ofs;
        ofs.open("./result/SinogramXZ.csv");
        
        for(Int_t i=1; i<=512; i++)
        {
            for(Int_t k=1; k<=512; k++)
            {
                Double_t BinContent= CPro->GetBinContent(k, i);
                //cout << BinContent << endl;
                ofs << BinContent << endl;
            }
        }
        
        ofs.close();
        
        cout << "save: SinogramXZ.csv" << endl;
}
