void ChainJSTTree(TString& filein, TString& fileout, Int_t istart, Int_t iend, TString& treeName){
  cout << "======= Merged ==========" << endl;
  cout << " Input filein       " << filein<<endl;
  cout << " Outout fileout     " << fileout<<endl;
  cout << "=========================" << endl;

  TFile fout(fileout,"RECREATE");
  TChain chain(treeName);

  TString fname;
  for ( Int_t i = istart; i < iend+1; i++){
    fname.Append(filein);
    fname.Append(Form("_%d",i));
    cout << "Append : "<<fname<<endl;
    chain.Add(fname);
    fname.Clear();
  }

  //chain.Merge(fileout);
  chain.Write();
  fout.Write();
  fout.Close();

}
