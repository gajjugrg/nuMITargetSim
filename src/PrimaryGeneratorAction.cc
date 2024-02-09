#include "PrimaryGeneratorAction.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);
  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="proton");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(1.*GeV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of each event
  //
  // from G4LogicalVolumeStore.

  G4double targetX = 0;
  G4double targetY = 0;
  G4double targetZ = 0;

  if (!fTargetBox)
  {
    G4LogicalVolume* targetLogicVolume = G4LogicalVolumeStore::GetInstance()->GetVolume("Target");
    if ( targetLogicVolume ) fTargetBox = dynamic_cast<G4Box*>(targetLogicVolume->GetSolid());
  }

  if ( fTargetBox ) {
    targetX = fTargetBox->GetXHalfLength()*2.;
    targetY = fTargetBox->GetYHalfLength()*2.;
    targetZ = fTargetBox->GetZHalfLength()*2.;
  }
  else  {
    G4ExceptionDescription msg;
    msg << "Envelope volume of box shape not found.\n";
    msg << "Perhaps you have changed geometry.\n";
    msg << "The gun will be place at the center.";
    G4Exception("PrimaryGeneratorAction::GeneratePrimaries()",
     "MyCode0002",JustWarning,msg);
  }


  G4double x0 = 0.0 * targetX;
  G4double y0 = 0.0 * targetY;
  G4double z0 = -0.5 * targetZ;

  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  fParticleGun->GeneratePrimaryVertex(anEvent);
}


