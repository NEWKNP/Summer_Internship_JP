//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//=============================================================
//  Created by T.ASO
//  2013-11-14 T.Aso
//  2014-03-10 T.Aso sample code for RTIonPlan
//  2014-03-10 T.Aso PrintRefDose() method.
//
//
//=============================================================
#ifndef MYDINAMICPORTRTPSETTING_HH
#define MYDINAMICPORTRTPSETTING_HH

#include "globals.hh"
#include "MyDynamicPortRTPMessenger.hh"
#include "G4MDICOMConfiguration.hh"
#include "DICOMRT.hh"
class G4MVParticleTherapySystem;

class MyDynamicPortRTPSetting {
  public:
    MyDynamicPortRTPSetting(G4MVParticleTherapySystem* setup);
    ~MyDynamicPortRTPSetting();

    void SetRTPFile(G4String name);
    void ApplyParameters();
    void InstallModules();
  
    void SetVerbose(G4int v) { fVerbose = v; }

  public:
    void PrintReferencedBeam();
    void SelectBeamID(G4int id);
    void PrintRTPInfo();
    void PrintRefDose(std::ostream& out);

  private:
    DICOMRT  dcmrt;
    G4MVParticleTherapySystem *fSetup;
    MyDynamicPortRTPMessenger *fMessenger;
    G4MDICOMConfiguration  *fConfig;

    G4int fBeamID;

    G4int fVerbose;
};



#endif /* MyDynamicPortSETTING_HH */
