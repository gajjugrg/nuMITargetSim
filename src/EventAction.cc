#include "EventAction.hh"
#include "RunAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"

//// version dependent header files
#if G4VERSION_NUMBER != 1100
#include "g4root.hh"  // G4_10
#else
#include "G4AnalysisManager.hh"  // G4_11
#endif

#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>


EventAction::EventAction()
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{}

void EventAction::EndOfEventAction(const G4Event* /*event*/)
{}
