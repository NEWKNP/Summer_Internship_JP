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
//  2012-11-18 T.Aso               
//  2014-11-23 T.Aso UpdateEvent() with a G4Event argument.
//  2014-11-23 T.Aso UpdateRun() with a G4Run argument.    
//
//
//=============================================================
#ifndef MYDYNAMICPORTSETUP_HH
#define MYDYNAMICPORTSETUP_HH

#include "globals.hh"
#include "G4Run.hh"
#include "G4Event.hh"
#include "DynamicPortSetup.hh"
#include "MyDynamicPortRTPSetting.hh"
#include "MyDynamicPortMessenger.hh"

class MyDynamicPortSetup : public DynamicPortSetup {
  public:
    MyDynamicPortSetup(G4String name);
    virtual ~MyDynamicPortSetup();

    virtual void Setup();
    virtual G4VPhysicalVolume* BuildDefault();
    virtual void UpdateRun(const G4Run* aRun=0);
    virtual void UpdateEvent(const G4Event* aEvent=0);

  private:
   MyDynamicPortRTPSetting  *fRTPSetting;
   MyDynamicPortMessenger *fMessenger;

};



#endif /* DYNAMICSETUP */
