#ifndef PixelSD_h
#define PixelSD_h 1

#include "G4VSensitiveDetector.hh"
#include "PixelHitsCollection.hh"

#include "globals.hh"

#include "RunAction.hh"
#include "PixelHit.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"

#include "G4VProcess.hh"

class G4ProcessVector;
class DetectorConstruction;
// class PixelROGeometry;
class G4HCofThisEvent;
class G4Step;
class G4TouchableHistory;

class PixelSD : public G4VSensitiveDetector
{
  public:

    PixelSD(G4String name); //, RunAction*);
    // PixelSD(G4String name, RunAction*, PixelROGeometry*);
    // PixelSD(G4String name, RunAction*, DetectorConstruction*);
    ~PixelSD();

    virtual void Initialize(G4HCofThisEvent* HCE);
    virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
    // void EndOfEvent(G4HCofThisEvent* HCE);

    // void clear();
    // void DrawAll();
    // void PrintAll();

  private:

    #include "DetectorParameterDef.hh"                // Import the gamma camera parameters

    RunAction* Run;
    G4VProcess* findProcess;

    PixelHitsCollection* hitsCollection;
    // G4ThreeVector pixLoc;
    DetectorConstruction* gammaCamera;

    // PixelROGeometry* PMTmtx;

    G4int HCid;

    G4int eventOrder;
    // G4int recordX;
    // G4int recordY;
    // G4double copyIDinX;
    // G4double copyIDinY;
    G4double engDep;
    G4String process;

    G4VProcess* currentProcess;
};

#endif
