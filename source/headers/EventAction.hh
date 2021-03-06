//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file EventAction.hh
/// \brief Definition of the EventAction class
//
// $Id: EventAction.hh 76293 2013-11-08 13:11:23Z gcosmo $
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

#include "g4csv.hh"
// #include "g4root.hh"

// #include "G4Timer.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"

class RunAction;
class HistoManager;

// class EventActionMessenger;

class EventAction : public G4UserEventAction
{
  public:

    // Define the event action constructor.
    EventAction(HistoManager*);
    // EventAction(RunAction*);

    // Define the event action destructor.
   ~EventAction();

  public:
    // Define the beginning of the event action, in which both of the
    //   accumulated energy deposition variables are initialized.
    virtual void BeginOfEventAction(const G4Event*);

    // Define the end of the event action, whuch
    virtual void EndOfEventAction(const G4Event*);

    // void SetDrawFlag(G4String val) {drawFlag = val;}
    // void SetPrintModulo(G4int val) {printModulo = val;}

  //   // Define a method to add the current-event energy deposition to the
  //   //   accumulated energy deposition for a single scoring logical volume.
  //   void AddEngDep(G4double engDep) {fEngDep += engDep;}
  //
  //   // Define a method to add the current-event energy deposition to the
  //   //   accumulated energy deposition for multiple scoring logical volumes.
  //   void AddEngDepArr(G4double engDep, G4int i) {fEngDepArr[i] += engDep;}
  //
  // private:
  //   // // Define the output file name for the fluence.
  //   // G4String fOutputFileSpec;
  //
  //   // Define the run action.
  //   RunAction* fRunAction;
  //
  //   // Define a double-precision floating-point number to store the
  //   //   accumulated energy deposition if there is only a single scoring
  //   //   logical volume.
  //   G4double fEngDep;
  //
  //   // Define a double-precision floating-point array to store the
  //   //   accumulated energy deposition if there is more than one scoring
  //   //   logical volume.
  //   G4double fEngDepArr[2];

  private:

    HistoManager* histoManager;

    G4int                   pixelCollID;
    // G4String                drawFlag;
    // // EventActionMessenger*   eventMessenger;
    // G4int                   printModulo;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
