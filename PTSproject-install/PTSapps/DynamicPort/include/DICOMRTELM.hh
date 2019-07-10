//
// DICOM ELEMENTS
//
// (Modification History)
//
//  2012-06-06 T.Aso Created for RTIonPlanX tags                                
//  2017-02-29 T.Aso Define private tag of Cybernet.
//                                                                              
#ifndef DICOMRTELM_h
#define DICOMRTELM_h 1

#include "globals.hh"
#include "DICOMELM.hh"

class DICOMRTELM :public DICOMELM{

public:

  DICOMRTELM();
  ~DICOMRTELM(){};

  //
  // Private Tags
  // 
  //
  //---------------------------------------------------
  static const G4int DIC_PRV = 0x300b0000;
  static const G4int DCM_SCTID = (DIC_PRV | 0x1120); // SCT ID
  static const G4int DCM_RSID = (DIC_PRV | 0x1100); //  RANGE SHIFTER THICK
  
  static const G4int DCM_WOBRADX = (DIC_PRV | 0x1130); // Wobbler Radius X
  static const G4int DCM_WOBRADY = (DIC_PRV | 0x1140); // Wobbler Radius Y
  
  static const G4int DCM_RIDGEID = (DIC_PRV | 0x1110); // RIDGE ID

};

#endif
