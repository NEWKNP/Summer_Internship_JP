void MergeROOTFile(TString& filein, TString& fileout, Int_t istart, Int_t iend){
  cout << "======= Merged ==========" << endl;
  cout << " Input filein       " << filein<<endl;
  cout << " Outout fileout     " << fileout<<endl;
  cout << "=========================" << endl;

  TFileMerger* t = new TFileMerger();
  t->OutputFile(fileout);

  TString fname;
  char srank[5];
  for ( Int_t i = istart; i < iend+1; i++){
    //sprintf(srank,"%s_%03d.root",i);
    fname.Append(filein);
    sprintf(srank,"_%d",i);
    fname.Append(srank);
    cout << " Merge : " << fname <<endl;
    t->AddFile(fname);
    fname.Clear();
  }

  t->Merge();
  
}
