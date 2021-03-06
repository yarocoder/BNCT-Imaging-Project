//
//  PixelSD.cc	CIPHER 3
//

#include "PixelSD.hh"

#include "PixelHit.hh"
#include "DetectorConstruction.hh"
// #include "PixelROGeometry.hh"

// #include "HistoManager.hh"

#include "RunAction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4UIsession.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4strstreambuf.hh"
#include "G4ios.hh"

#include <sstream>

#include "G4SteppingVerbose.hh" //to get the process name
#include "G4VProcess.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"


// PixelSD::PixelSD(G4String name, RunAction *run, DetectorConstruction* det)
PixelSD::PixelSD(G4String name) //, RunAction *run) //, PixelROGeometry* roGeo)
:G4VSensitiveDetector(name), HCid(-1) //Run(run) //, PMTmtx(roGeo)//, pixLoc(G4ThreeVector())
 // NbOfPixelsInX(10),NbOfPixelsInY(10)
{
  G4String HCname="PixCollection";
  collectionName.insert(HCname);
}



PixelSD::~PixelSD()
{;}



void PixelSD::Initialize(G4HCofThisEvent* HCE)
{
  hitsCollection = new PixelHitsCollection
                      (SensitiveDetectorName, collectionName[0]);

  static G4int HCid = -1;

  if (HCid < 0) {HCid = G4SDManager::GetSDMpointer()->GetCollectionID(hitsCollection);}

  // if (HCid < 0) { HCid = GetCollectionID(0); }

  HCE->AddHitsCollection(HCid, hitsCollection);

  // static G4int HCid = -1;

  // BEGINNING OF EVENT: Increment event number
  // Run->fillPerHit(G4ThreeVector(), 0.0, -1);
}



G4bool PixelSD::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
{

  G4ThreeVector* pixLoc = new G4ThreeVector();

  // G4Track* track = aStep->GetTrack();
  //
  // G4double initEng = track->GetVertexKineticEnergy();

  G4double engDep = aStep->GetTotalEnergyDeposit();

  G4TouchableHistory* touchable = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());

  if(!touchable) return false;
  // if(!ROhist) return false;

  G4String process = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName(); //Process Hit Identification
                                              //(Compton,Photoelectr.,Pair Prod.,etc)

  // G4cout << " Process : " << process << " " << G4endl;
  // G4cout << " Initial Energy : " << initenergy << " " << G4endl;

  // G4double stepl = 0.;
  // if (aStep->GetTrack()->GetDefinition()->GetPDGCharge() != 0.)
  //     stepl = aStep->GetStepLength();

  if (engDep <= 0) return false;
  // if ((edep==0.) && (stepl==0.)) return false;

  // Only bin events generated by photons.
  // if(process=="Electromagnetic")
  // {


    // G4VPhysicalVolume* physVol = ROhist->GetVolume(); // NOTE: Method with RO geometry.
    G4VPhysicalVolume* physVol = touchable->GetVolume(); // NOTE: Method with RO geometry.

    // G4VPhysicalVolume* physVol = ROhist->GetVolume(); // NOTE: Method with RO geometry.

    G4int copyNum = physVol->GetCopyNo();

    PixelHit* pixHit = new PixelHit();

    pixHit->SetEngDep(engDep);
    pixHit->SetHitPos(aStep->GetPreStepPoint()->GetPosition());

    // G4ThreeVector tempLoc();

    G4int idCheck = 0;

    for (G4int i=0; i<ScintNbX; i++)
    {
      for (G4int j=0; j<ScintNbX; j++)
      {
        for (G4int k=0; k<ScintNbM; k++)
        {
          idCheck++;

          if (idCheck == copyNum)
          {
            // pixLoc = G4ThreeVector(i, j, k);
            // pixLoc->x() = i;
            // pixLoc->y() = j;
            // pixLoc->z() = k;

            // tempLoc = G4ThreeVector(i, j, k);

            pixHit->SetPixelLoc(i, j, k);
          }
        }
      }
    // }

    hitsCollection->insert(pixHit);
    // evtorder++;
  	// Run->fillPerHit(pixLoc, engDep, 0);

    return true;
  }

  // pixHit->SetScintPixel(pixLoc);

  // for (G4int j=0;j<NbOfPixelsInX;j++)
  // {
  //   for (G4int k=0;k<NbOfPixelsInY;k++)
  //   {
  //     // PixelID[j][k] = -1;
  //   }
  // }

  // evtorder = 0;
  // recordY = -1; recordZ = -1;
  //
  // copyIDinY =-1;
  // copyIDinZ =-1;
  // edep =-2;
  // Run->fillPerHit(copyIDinY, copyIDinZ, edep);

  // PixelHit* pixHit = new PixelHit(physVol->GetLogicalVolume(), copyIDinX, copyIDinY);

  // G4VPhysicalVolume* physVol = ROhist->GetVolume();
  // //  G4VPhysicalVolume* motherVol = ROhist->GetVolume(1);
  //
  // // Examine to figure out how to incorporate an array matrix
  // copyIDinX = ROhist->GetReplicaNumber();
  // copyIDinY = ROhist->GetReplicaNumber(1);

  // int ipixel = PixCollection->insert( pixHit );
  // ipixel=ipixel*1;

  //
  // Controls the module number of interaction
  //

  // //G4double xposi = aStep->GetTrack()->GetPosition().z();
  // G4double yposi = aStep->GetTrack()->GetPosition().x();
  // G4double zposi = aStep->GetTrack()->GetPosition().y();
  // copyIDinX = initEng;   // ERROR?
  // copyIDinY = yposi;
  // copyIDinZ = zposi;

  // Interaction order, discrimination of processes and output data control

  // if(process=="compt")
  // {
  //         evtorder++;
  //         Run->fillPerHit(copyIDinY,copyIDinZ,edep);
  // }
  // if(process=="polarCompt")
  // {
  // 	evtorder++;
  // 	Run->fillPerHit(copyIDinY,copyIDinZ,edep);
  // }
  // if(process=="eIoni")
  // {
  //   evtorder++;
  //   Run->fillPerHit(copyIDinX,copyIDinY,edep);
  // }
  //
  // if(process=="Transportation") {}
  //
  // if(process=="initStep"){}

  return true;
}



// void PixelSD::EndOfEvent(G4HCofThisEvent* HCE)
// {
//
//   // END OF EVENT: Writing to data file
//   // Run->fillPerHit(pixLoc, 0.0, 1);
//
//   // HCE->AddHitsCollection(HCID, PixCollection);
// }

//
//
// void PixelSD::clear()
// {}
//
// void PixelSD::DrawAll()
// {}
//
// void PixelSD::PrintAll()
// {}
