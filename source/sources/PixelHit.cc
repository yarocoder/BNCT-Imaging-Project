#include "PixelHit.hh"
#include "G4ios.hh"
#include "G4VVisManager.hh"
#include "G4VHit.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"

#include "G4Transform3D.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"

#include "G4Circle.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal G4Allocator<PixelHit>* PixelHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PixelHit::PixelHit()
: G4VHit(),
  engDepPix(0.0),
  hitPos(G4ThreeVector()),
  pixLoc(G4ThreeVector()),
  hitStart(G4ThreeVector()),
  hitRot(G4RotationMatrix()),
  pixelLogVol(nullptr)
{}

// PixelHit::PixelHit(G4LogicalVolume* logVol, G4double x, G4double y)
// :pixelLogVol(logVol), XPixelID(y), YPixelID(z)

PixelHit::PixelHit(G4LogicalVolume* logVol)
: G4VHit(), pixelLogVol(logVol)
{}

PixelHit::~PixelHit()
{}


PixelHit::PixelHit(const PixelHit& right)
: G4VHit(right)
{
  // XPixelID = right.XPixelID;
  // YPixelID = right.YPixelID;
  // TrackLengthPix = right.TrackLengthPix;

  // Initialize the hit information parameters.
  engDepPix   = right.engDepPix;
  hitPos      = right.hitPos;
  pixLoc      = right.pixLoc;
  hitStart    = right.hitStart;
  hitRot      = right.hitRot;
  pixelLogVol = right.pixelLogVol;

  // Pos = right.Pos;
  // pixelLogVol = right.pLogV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const PixelHit& PixelHit::operator=(const PixelHit& right)
{
  // // Include the default behavior of a hit "=" overloaded operator.
  // G4VHit::operator=(right);

  // Initialize the hit information parameters.
  engDepPix   = right.engDepPix;
  hitPos      = right.hitPos;
  pixLoc      = right.pixLoc;
  hitStart    = right.hitStart;
  hitRot      = right.hitRot;
  pixelLogVol = right.pixelLogVol;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

int PixelHit::operator==(const PixelHit& right) const
{
  return ((pixLoc == right.pixLoc) && (engDepPix == right.engDepPix));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// void PixelHit::Draw()
// {}

void PixelHit::Draw()
{
  G4VVisManager* visManager = G4VVisManager::GetConcreteInstance();

  if(!visManager) return;
  // {
  //   G4Transform3D transRotPos(hitRot.inverse(), hitPos);
  //
  //   G4VisAttributes visAttributes;
  //
  //   const G4VisAttributes* volVisAttributes = pixelLogVol->GetVisAttributes();
  //
  //   if (pixelLogVol) visAttributes = *volVisAttributes;

  G4Circle circle(hitPos);

  circle.SetScreenSize(2);

  circle.SetFillStyle(G4Circle::filled);

  G4Colour colour(1., 1., 0.);
  // G4Colour colour(0., 1., 1.);

  G4VisAttributes attribs(colour);

  circle.SetVisAttributes(attribs);

  // visAttributes->SetColour(colour);
  // // visAttributes->SetForceWireframe(false);
  // visAttributes->SetForceSolid(true);

  visManager->Draw(circle);
  // visManager->Draw(*pixelLogVol, visAttributes, transRotPos);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void PixelHit::Print()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
