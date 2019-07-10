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
//  2012-11-18  T.Aso
//
//
//=============================================================
#ifndef MYDYNAMICPORTMESSENGER_HH
#define MYDYNAMICPORTMESSENGER_HH

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIdirectory.hh"

class MyDynamicPortSetup;

class MyDynamicPortMessenger : public G4UImessenger{
  public:

    MyDynamicPortMessenger(MyDynamicPortSetup* system);
    ~MyDynamicPortMessenger();

    virtual void SetNewValue(G4UIcommand* command, G4String newValue);
    virtual G4String GetCurrentValue(G4UIcommand* command);

  private:
    G4UIdirectory* fDir;

    MyDynamicPortSetup *fSetup;
};
#endif /* DYNAMICPORTMESSENGER_HH */
