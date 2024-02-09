#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "G4Version.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
// version dependent header files
#if G4VERSION_NUMBER != 1100
#include "g4root.hh" // for G4_10
#else
#include "G4AnalysisManager.hh" // for G4_11
#endif

SteppingAction::SteppingAction(EventAction* ){}

SteppingAction::~SteppingAction(){}

void SteppingAction::UserSteppingAction(const G4Step* step){
	auto aManager = G4AnalysisManager::Instance(); // Create a instance to start tracking Data
//	G4Track* track = step->GetTrack();
//	G4StepPoint* SPointPreStep = step->GetPreStepPoint();
	G4StepPoint* SPointPostStep = step->GetPostStepPoint();
	if (SPointPostStep-> GetProcessDefinedStep() !=0 ){
		auto secondary = step-> GetSecondaryInCurrentStep();
		size_t size_secondary = (*secondary).size();
		if (size_secondary) {
			for (size_t i = 0; i < (size_secondary); i++){
				auto secstep = (*secondary)[i];
				G4int pID = secstep->GetDefinition()->GetPDGEncoding();
//				G4cout << pID << G4endl;
				if (pID != 11 && pID != -11 && pID != 22) continue;
				aManager->FillNtupleIColumn(1, pID);
				aManager->FillNtupleDColumn(2, secstep-> GetKineticEnergy());
				aManager->FillNtupleDColumn(3, secstep-> GetTotalEnergy());
				aManager->FillNtupleDColumn(4, secstep-> GetMomentum().x()/CLHEP::MeV);
				aManager->FillNtupleDColumn(5, secstep-> GetMomentum().y()/CLHEP::MeV);
				aManager->FillNtupleDColumn(6, secstep-> GetMomentum().z()/CLHEP::MeV);
				aManager->FillNtupleDColumn(7, secstep-> GetPosition().x()/CLHEP::cm);
				aManager->FillNtupleDColumn(8, secstep-> GetPosition().y()/CLHEP::cm);
				aManager->FillNtupleDColumn(9, secstep-> GetPosition().z()/CLHEP::cm);	
				aManager->AddNtupleRow();
			}
		}
	}
}

