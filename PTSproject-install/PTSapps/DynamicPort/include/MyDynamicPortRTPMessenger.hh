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
//
//  2013-11-14 T.Aso
//  2014-03-10 T.Aso Add beamid command and verbose command.
//  2014-03-10 T.Aso Add printRefBeam command.
//                
//
//
//=============================================================
#ifndef MYDYNAMICPORTRTPMESSENGER_HH
#define MYDYNAMICPORTRTPMESSENGER_HH

#include "globals.hh"
#include "G4UIcommand.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithoutParameter.hh"

class MyDynamicPortRTPSetting;

class MyDynamicPortRTPMessenger : public G4UImessenger {
  public:
    MyDynamicPortRTPMessenger(MyDynamicPortRTPSetting* setting);
    ~MyDynamicPortRTPMessenger();


    virtual void SetNewValue(G4UIcommand* command, G4String newValue);
    virtual G4String GetCurrentValue(G4UIcommand* command);

  private:
    MyDynamicPortRTPSetting *fSetting;

    G4UIdirectory* fDir;
    G4UIdirectory* fDirDICOM;
    G4UIcmdWithAString*  fCmdFileRTP;
    G4UIcmdWithoutParameter*  fCmdApplyRTP;
    G4UIcmdWithoutParameter*  fCmdInstallRTP;

    G4UIcmdWithAnInteger*  fCmdSelectBeamID;

    G4UIcmdWithoutParameter* fCmdPrintRefBeam;
    G4UIcmdWithoutParameter* fCmdPrintRTPInfo;

    G4UIcmdWithAString*  fCmdPrintRefDose;

    G4UIcmdWithAnInteger*  fCmdVerbose;

};

#endif /* FUKUIDICOMRTPMESSENGER_HH */
