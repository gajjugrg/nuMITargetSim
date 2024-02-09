#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction()
:fOutputFileNamePtr(nullptr)
{
	// set printing event number per each event
	G4RunManager::GetRunManager()->SetPrintProgress(1);

	// Get analysis manager
	auto analysisManager = G4AnalysisManager::Instance();

	// Create directories
	analysisManager->SetVerboseLevel(1);
	analysisManager->SetNtupleMerging(true);
	// Creating ntuple
	analysisManager->CreateNtuple("secDist", "NuMI Target Secondary e+/e-/gamma Production");
	analysisManager->CreateNtupleIColumn("Dummy");
	analysisManager->CreateNtupleIColumn("pID");
	analysisManager->CreateNtupleDColumn("KineticEnergy");
	analysisManager->CreateNtupleDColumn("TotalEnergy");
	analysisManager->CreateNtupleDColumn("px");
	analysisManager->CreateNtupleDColumn("py");
	analysisManager->CreateNtupleDColumn("pz");
	analysisManager->CreateNtupleDColumn("x");
	analysisManager->CreateNtupleDColumn("y");
	analysisManager->CreateNtupleDColumn("z");
	analysisManager->FinishNtuple();
}

RunAction::RunAction(const G4String* outputFileName)
:fOutputFileNamePtr(outputFileName)
{
	// set printing event number per each event
	G4RunManager::GetRunManager()->SetPrintProgress(1);

	// Get analysis manager
	auto analysisManager = G4AnalysisManager::Instance();

	// Create directories
	analysisManager->SetVerboseLevel(1);
	analysisManager->SetNtupleMerging(true);
	// Creating ntuple
	analysisManager->CreateNtuple("secDist", "NuMI Target Secondary e+/e-/gamma Production");
	analysisManager->CreateNtupleIColumn("Dummy");
	analysisManager->CreateNtupleIColumn("pID");
	analysisManager->CreateNtupleDColumn("KineticEnergy");
	analysisManager->CreateNtupleDColumn("TotalEnergy");
	analysisManager->CreateNtupleDColumn("px");
	analysisManager->CreateNtupleDColumn("py");
	analysisManager->CreateNtupleDColumn("pz");
	analysisManager->CreateNtupleDColumn("x");
	analysisManager->CreateNtupleDColumn("y");
	analysisManager->CreateNtupleDColumn("z");
	analysisManager->FinishNtuple();
}

RunAction::~RunAction()
{}
// default mode
void RunAction::BeginOfRunAction(const G4Run*)
{
	// Get analysis manager
	auto analysisManager = G4AnalysisManager::Instance();
	// set output file name
	if (fOutputFileNamePtr == nullptr)
	{
		//single file mode
		G4String fileName = "PresetOuputfile.root";
		G4cout << "Single File Mode: Setting the output file name: " << fileName << G4endl;
		analysisManager->SetFileName(fileName);
	}
	else
{// batch mode
		G4cout << "Batch mode: Setting output file name: " << *fOutputFileNamePtr << G4endl;
		analysisManager->SetFileName(*fOutputFileNamePtr);
	}
	analysisManager->OpenFile();
}

void RunAction::EndOfRunAction(const G4Run*)
{
	auto analysisManager = G4AnalysisManager::Instance();
	//write and close the file at the end of each run
	analysisManager->Write();
	analysisManager->CloseFile();
}
