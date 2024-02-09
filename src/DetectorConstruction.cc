#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  G4double targetX = 15 * mm;
  G4double targetY = 6.4 * mm;
  G4double targetZ = 95.38 * cm;
  G4double density = 1.78 * g/cm3;
  G4double a = 12.0107 * g/mole;
  G4double z = 6.0;
  G4Material* target_mat = new G4Material("graphite", z, a, density);

  G4cout << target_mat->GetA()/(g/mole) << G4endl;
  G4cout << target_mat->GetZ() << G4endl;
  G4cout << target_mat->GetDensity()/(g/cm3) << G4endl;

  G4bool checkOverlaps = true;

  // World
  G4double world_sizeX = 1.5 * targetX;
  G4double world_sizeY = 1.5 * targetY;
  G4double world_sizeZ = 1.5 * targetZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box* solidWorld = new G4Box("World", 0.5*world_sizeX, 0.5*world_sizeY, 0.5*world_sizeZ);   
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");           
  G4VPhysicalVolume* physWorld = new G4PVPlacement(0,  G4ThreeVector(), logicWorld, "World", 0, false, 0, checkOverlaps);    

  // Target 
  G4Box* solidTarget = new G4Box("Target", 0.5*targetX, 0.5*targetY, 0.5*targetZ); 
  G4LogicalVolume* logicTarget = new G4LogicalVolume(solidTarget, target_mat, "Target");    
  new G4PVPlacement(0, G4ThreeVector(), logicTarget, "Target", logicWorld, false,  0, checkOverlaps);  

  // Set logicEnv as scoring volume
  fScoringVolume = logicTarget;

  //always return the physical World
  return physWorld;
}

