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
/// \file RunAction.cc
/// \brief Implementation of the RunAction class
//
// $Id: RunAction.cc 70756 2013-06-05 12:20:06Z ihrivnac $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "RunAction.hh"
// #include "Run.hh"
// #include "DetectorConstruction.hh"
// #include "PrimaryGeneratorAction.hh"
// #include "HistoManager.hh"

#include "G4Run.hh"
// #include "g4csv.hh"
// #include "g4root.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4AccumulableManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"

#include "HistoManager.hh"

#include "Randomize.hh"
#include <iomanip>
#include <assert.h>

#include "G4ios.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// RunAction::RunAction(const G4String& outputFile)
RunAction::RunAction(HistoManager* hist)
: G4UserRunAction(), runID(0), histoManager(hist)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// RunAction::RunAction(const G4String& outputFile)
// : G4UserRunAction(), runID(0)
//   // NbOfPixelsInX(10), NbOfPixelsInY(10)
//   // fOutputFileSpec(outputFile), fEngDep(0.), fEngDepSqr(0.)
// {
//   // // Create an instance of an accumulable manager.
//   // G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
//   //
  // // Register the energy deposit accumulable and the square of that quantity for
  // //   the case of only a single scoring volume.
  // accumulableManager->RegisterAccumulable(fEngDep);
  // accumulableManager->RegisterAccumulable(fEngDepSqr);
  //
  // // Iterate through and register all the elements in the vectors containing the
  // //   energy deposition accumulables and the squares of those quantities in the
  // //   case of multiple scoring volumes.
  // for (int i = 0; i < 2; i++)
  // {
  //   accumulableManager->RegisterAccumulable(fEngDepArr[i]);
  //   accumulableManager->RegisterAccumulable(fEngDepSqrArr[i]);
  //
  //   // accumulableManager->RegisterAccumulable(fEngDepArr.at(i));
  //   // accumulableManager->RegisterAccumulable(fEngDepSqrArr.at(i));
  // }
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
  #include "DetectorParameterDef.icc"

  // // Initialize the histograms.
  // auto analysisManager = G4AnalysisManager::Instance();
  // // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  //
  // analysisManager->SetVerboseLevel(1);
  //
  // analysisManager->SetFirstHistoId(1);
  //
  // analysisManager->OpenFile();
  // analysisManager->OpenFile(filename);
  // analysisManager->SetHistoDirectoryName(directory);

  // aRun->SetRunID(runID++);
  ((G4Run*)(aRun))->SetRunID(runID++);

  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

  if (G4VVisManager::GetConcreteInstance())
  {
    G4UImanager* UI = G4UImanager::GetUIpointer();
    UI->ApplyCommand("/vis/scene/notifyHandlers");
  }

  histoManager->Book();

}

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// void RunAction::Book()
// {
//   #include "DetectorParameterDef.icc"
//
//   // Initialize the histograms.
//   auto analysisManager = G4AnalysisManager::Instance();
//
//   // // Initialize an array to hold the histogram IDs.
//   G4int idTot = PMTNbX*PMTNbY*PMTNbM;
//
//   G4String title[idTot];
//
//   G4int titleID = 0;
//
//   // const G4String title[PixelNbX][PixelNbY][PixelNbM];
//   //
//   // Fill the histogram ID array.
//   for (int i=0; i<PixelNbX; i++)
//   {
//     for (int j=0; j<PixelNbY; j++)
//     {
//       for (int k=0; k<PixelNbM; k++)
//       {
//         titleID++;
//
//         std::string titleTemp;
//
//         titleTemp = "Pixel " + std::to_string(i) + ", " + std::to_string(j) + ", " + std::to_string(k);
//
//         title[titleID] = titleTemp;
//       }
//     }
//   }
//
//   titleID = 0;
//
//   // Iterate through and create all histograms.
//   for (int i=0; i<PixelNbX; i++)
//   {
//     for (int j=0; j<PixelNbY; j++)
//     {
//       for (int k=0; k<PixelNbM; k++)
//       {
//         titleID++;
//
//         G4int ih = analysisManager->CreateH1(title[titleID], "Gamma Spectrum",
//         numBins, engMin, engMax, "keV");
//
//         analysisManager->SetH1Activation(ih, true);
//       }
//     }
//   }
//
// }


  // // Histograms
  // //
  // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  //
  // // Open a ROOT file if the analysis manager is active.
  // if (analysisManager->IsActive()) analysisManager->OpenFile();
  //
  // // Save the random number store status.
  // G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  // if (isMaster) G4Random::showEngineStatus();
  //
  // // Reset accumulables held in the accumulable manager to their initial values.
  // G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  // accumulableManager->Reset();

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* aRun)
{
  // // Initialize the histograms.
  // auto analysisManager = G4AnalysisManager::Instance();
  // // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  //
  // analysisManager->Write();
  // analysisManager->CloseFile();

  // delete analysisManager;

  histoManager->Save();

  if (G4VVisManager::GetConcreteInstance())
  { G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/update"); }

  G4cout << "number of event = " << aRun->GetNumberOfEvent() << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void RunAction::fillPerHit(G4ThreeVector pixLoc = G4ThreeVector(), G4double hitEnergy = 0.0, G4int eventStep = 0)
// {
//   static G4int EventNumber = 0;
//   // static G4int Multiplicity = 0;
//
//   // static G4double initEnergy = 0;
//   static G4double totalEngDep = 0;
//
//   // EventNumber++;
//
//   /*** Writing to Data File ***/
//
//   // BEGINNING OF EVENT: Increment event number
//   if (eventStep == -1)
//   {
//     // IDinX = 0;
//     // IDinY = 0;
//     EventNumber++;
//   }
//
//   // END OF EVENT: Writing to data file
//   else if (eventStep == 1)
//   {
//
//     // if (TotalPixelEnergy == InitEnergy) { FullyDetected++; }
//
//     // if (TotalPixelEnergy > 20*keV) { Detected++; }
//
//     // Open the data file for writing and name it.
//     outputDataFile.open("gammacameradata");
//
//     // Fill the output data file.
//     outputDataFile << " Source Photon #:   " << EventNumber                             // << G4endl
//                    << " Position:          "
//                    << pixLoc.x() << " " << pixLoc.y() << " " << pixLoc.z()
//                    << " Energy Deposition: " << totalEngDep;                               // << G4endl
//                   //  << " Fully Detected:  " << FullyDetected;
//     // outputDataFile << "Detected: " << Detected << G4endl; << " Fully Detected: " << FullyDetected;
//
//     // Close the output data file.
//     outputDataFile.close();
//
//     /*** Reseting the variables at the end of the current event ***/
//     totalEngDep = 0;
//     // Multiplicity = 0;
//
//   }
//
//   // DURING EVENT: Writing on File
//   else
//   {
//     // Multiplicity++;
//     //
//     // if (Multiplicity == 1) { InitEnergy=IDinX; }
//
//     totalEngDep = totalEngDep + hitEnergy;
//
//     // if (PixelEnergy > 20*keV)
//     // {
//     //   TotalPixelEnergy = TotalPixelEnergy + PixelEnergy;
//     // }
//
//     // // Print to screen the hit information.
//     // G4cout << "Initial Energy: " << InitEnergy
//     //        << " Energy: " << PixelEnergy << " Total: "
//     //        << TotalPixelEnergy << G4endl;
//
//   }
//
// }

  // // If a visual manager exists.
  // //
  // if (G4VVisManager::GetConcreteInstance())
  // {
  //   // Refreshes the visual viewer
  //   G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/update");
  // }
  //
  // G4int numOfEvents = aRun->GetNumberOfEvent();
  // if (numOfEvents == 0) return;
  //
  // // Print the number of events that occurred in the run.
  // G4cout << "Number of Events Processed: " << numOfEvents << G4endl;
  //
  // // Get an instance of the analysis manager to save the histograms.
  // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  //
  // // If the analysis manager is active, write the histograms to the ROOT file
  // //   and close it.
  // if (analysisManager->IsActive())
  // {
  //   analysisManager->Write();
  //   analysisManager->CloseFile();
  // }
  //
  // // Merge the energy deposition accumulables.
  // G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  // accumulableManager->Merge();
  //
  // // Compute dose = total energy deposit in a run and its variance
  // //
  // G4double engDep  = fEngDep.GetValue();
  // G4double engDepSqr = fEngDepSqr.GetValue();
  //
  // G4double rms = engDepSqr - engDep*engDep/numOfEvents;
  // if (rms > 0.) rms = std::sqrt(rms); else rms = 0.;
  //
  // // Run conditions
  // //
  // G4cout << G4endl << G4endl << " The run consists of " << numOfEvents
  //        << " particle(s)" << G4endl << G4endl;

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// void RunAction::AddEngDep(G4double& engDep)
// {
//   // Accumulate the energy deposition from the event calling this method for
//   //   the case of only one scoring volume.
//   fEngDep  += engDep;
//   fEngDepSqr += engDep * engDep;
// }
//
// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// void RunAction::AddEngDepArr(G4double (&engDep)[2])
// {
//   // Iterate through all the scoring volumes and accumulate the energy
//   //   deposition from the event action calling this method.
//   for (int i = 0; i < 2; i++)
//   {
//     // Grab the energy deposition for the scoring volume of interest. Throw an
//     //   error if we are out of range of the energy deposition vector number
//     //   of elements. (Use of ".at(i)" in place of "[i]" ensures this error
//     //   checking.)
//     G4double engDepForI = engDep[i];
//     // engDepForI = engDep.at(i);
//
//     // Accumulate the energy deposition from the event action calling this
//     //   method for the case of multiple scoring volumes.
//     fEngDepArr[i]  += engDepForI;
//     fEngDepSqrArr[i] += engDepForI * engDepForI;
//   }
// }
