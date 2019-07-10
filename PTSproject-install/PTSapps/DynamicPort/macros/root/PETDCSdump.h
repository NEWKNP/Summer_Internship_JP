//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Apr 21 14:45:23 2016 by ROOT version 6.04/08
// from TTree PETDCS/PETDCS
// found on file: PET_Sample.root
//////////////////////////////////////////////////////////

#ifndef PETDCSdump_h
#define PETDCSdump_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class PETDCSdump {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           evno;
   Float_t         x0;
   Float_t         y0;
   Float_t         z0;
   Float_t         x1;
   Float_t         y1;
   Float_t         z1;
   Int_t           iz;
   Int_t           isec;
   Float_t         desig0;
   Float_t         desig1;
   Float_t         tsig0;
   Float_t         tsig1;

   // List of branches
   TBranch        *b_evno;   //!
   TBranch        *b_x0;   //!
   TBranch        *b_y0;   //!
   TBranch        *b_z0;   //!
   TBranch        *b_x1;   //!
   TBranch        *b_y1;   //!
   TBranch        *b_z1;   //!
   TBranch        *b_iz;   //!
   TBranch        *b_isec;   //!
   TBranch        *b_desig0;   //!
   TBranch        *b_desig1;   //!
   TBranch        *b_tsig0;   //!
   TBranch        *b_tsig1;   //!

   PETDCSdump(TTree *tree=0);
   virtual ~PETDCSdump();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef PETDCSdump_cxx
PETDCSdump::PETDCSdump(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("PET_Sample.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("PET_Sample.root");
      }
      f->GetObject("PETDCS",tree);

   }
   Init(tree);
}

PETDCSdump::~PETDCSdump()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t PETDCSdump::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t PETDCSdump::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void PETDCSdump::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("evno", &evno, &b_evno);
   fChain->SetBranchAddress("x0", &x0, &b_x0);
   fChain->SetBranchAddress("y0", &y0, &b_y0);
   fChain->SetBranchAddress("z0", &z0, &b_z0);
   fChain->SetBranchAddress("x1", &x1, &b_x1);
   fChain->SetBranchAddress("y1", &y1, &b_y1);
   fChain->SetBranchAddress("z1", &z1, &b_z1);
   fChain->SetBranchAddress("iz", &iz, &b_iz);
   fChain->SetBranchAddress("isec", &isec, &b_isec);
   fChain->SetBranchAddress("desig0", &desig0, &b_desig0);
   fChain->SetBranchAddress("desig1", &desig1, &b_desig1);
   fChain->SetBranchAddress("tsig0", &tsig0, &b_tsig0);
   fChain->SetBranchAddress("tsig1", &tsig1, &b_tsig1);
   Notify();
}

Bool_t PETDCSdump::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void PETDCSdump::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t PETDCSdump::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef PETDCSdump_cxx
