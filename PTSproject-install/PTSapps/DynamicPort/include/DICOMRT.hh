//
// DICOM ELEMENTS 
//
#ifndef DICOMRT_h
#define DICOMRT_h 1

#include <vector>
#include "globals.hh"
#include "G4String.hh"
#include "DICOMRTELM.hh"

#include "G4ThreeVector.hh"
class G4Rotation;
class G4Material;

//=============================================================
//  Created by T.ASO
//
//  2014-03-10 T.Aso
//  2014-03-10 T.Aso  fBeamDosePointVec,fBeamDoseVec, for storing
//                    Reference dose info.
//  2017-02-20 T.Aso Verbose
//
//=============================================================

class DICOMRT {

public:

  DICOMRT();
  ~DICOMRT(){}

public:
  // File Name for DICOM-RTX
  static G4String FILERT;

  void SetVerbose(G4int v){ fVerbose = v; };
  G4int GetVerbose(){ return fVerbose; };

  void Separator(G4String str, std::vector<G4String>& vec);
  void Separator(G4String str, std::vector<G4double>& vec);

  void FillSQIdx();
  void FillBeamID();

  void  SetBeamID(G4int ibeam);
  G4int GetBeamID(){ return fCurrentBeamId; }
  G4int GetNofBeam();
  G4ThreeVector& GetBeamDosePoint(){ return fBeamDosePointVec[fCurrentBeamIndex]; }
  G4double GetBeamDose(){ return fBeamDoseVec[fCurrentBeamIndex]; }

  void SetIdx(G4int istart, G4int ilast) { fIdxStart=istart; fIdxLast=ilast; }
  void ResetIdx() { fIdxStart=0; fIdxLast=INT_MAX; }
  void SetIdxByBeamID();
  void SetIdxBySQ(G4int sqid);

  G4int GetTagPointer(G4int idx);
  G4int GetIdx(G4int tag,G4int i=0);
  void MGetTagInfo(G4int tag, std::vector<G4int>& idx);
  /************************/

  enum{ idxProcedureCodeSQ, 
        idxReferencedStudySQ, 
        idxDoseGirdDefinitionSQ,
        idxFractionGroupSQ,
        idxPatientSetupSQ,
        idxReferencedSetupImageSQ,
        idxIonBeamSQ, 
        idxReferencedStructureSetSQ };

private:

  std::vector<G4int> idxSQVec;

  G4int fIdxStart;
  G4int fIdxLast;

private:
  G4int fCurrentBeamIndex;  // Current Beam in index of vector
  G4int fCurrentBeamId;     // Current Beam Number
  std::vector<G4int> fBeamIdVec;
  std::vector<G4ThreeVector> fBeamDosePointVec;
  std::vector<G4double> fBeamDoseVec;

  G4int fVerbose;

};

#endif
