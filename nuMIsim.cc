#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "G4Version.hh"

// version dependent header files
#if G4VERSION_NUMBER != 1100
#include "G4MTRunManager.hh"  // for G4_10
#else
#include "G4RunManagerFactory.hh" // for G4_11
#endif

#include "G4SteppingVerbose.hh"
#include "G4UImanager.hh"
#include "FTFP_BERT.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4Version.hh"

#include "Randomize.hh"

#include <unistd.h>
#include <cstdlib>

void print_usage(){
  G4cerr << "Usage: " << G4endl;
  G4cerr << "   -m [macro (input) file name] (reuired) " << G4endl;
  G4cerr << "   -o [output (date) file name]" << G4endl;
  G4cerr << "   -s [random number randSeed]"  << G4endl;
}

int main(int argc,char** argv)
{
  if (argc == 1) {
    print_usage();
    return EXIT_FAILURE; // Exit the program after printing the usage information
  }
  G4long randSeed = time(NULL); // here is where we set the seed
  G4UIExecutive* ui = nullptr;
  G4String macroFilename, dataFilename;
  G4String* dataFilename_ptr = &dataFilename;
  for(int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if(arg == "-m" && i + 1 < argc) {
      macroFilename = argv[++i]; // Increment 'i' to skip next argument since it's a value
    } else if(arg == "-o" && i + 1 < argc) {
      dataFilename = argv[++i];
    } else if(arg == "-s" && i + 1 < argc) {
      randSeed = std::atol(argv[++i]);
    } else {
      print_usage();
      return EXIT_FAILURE; // Exit if any unrecognized option or value is missing
    }
  }

      // Check if macroFilename is still empty after parsing
  if (macroFilename.empty()) {
    std::cerr << "Error: Macro filename is required.\n";
    print_usage();
    return EXIT_FAILURE; // Exit the program
  }

  G4Random::setTheEngine(new CLHEP::MTwistEngine);
  G4Random::setTheSeed(randSeed);
    //  G4Random::showEngineStatus(); 
    // version dependent function call
#if G4VERSION_NUMBER == 1100
    G4int precision = 4;
    G4SteppingVerbose::UseBestUnit(precision);
#endif
    
    // Construct the default run manager
#ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(10); //(2*(G4Threading::G4GetNumberOfCores()));
    G4cout << "Multithreaded" << G4endl;
#else
    G4RunManager* runManager = new G4RunManager;
    G4cout << "Single threaded" << G4endl;
#endif
    // Set mandatory initialization classes
    // Detector construction
    runManager->SetUserInitialization(new DetectorConstruction());
    
    // Physics list
    G4VModularPhysicsList* physicsList = new FTFP_BERT;
    physicsList->SetVerboseLevel(1);
    runManager->SetUserInitialization(physicsList);

    if(!dataFilename.empty()) {
      runManager->SetUserInitialization(new ActionInitialization(dataFilename_ptr));
          }
    else {
      runManager->SetUserInitialization(new ActionInitialization());
    }
    
    // Initialize visualization
    G4VisManager* visManager = new G4VisExecutive;
    // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
    // G4VisManager* visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();
    
    G4cout << "Version: " << G4VERSION_NUMBER << G4endl;
    // Detect interactive mode (if no arguments) and define UI session
    // Get the pointer to the User Interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    
    if ( ! ui ) {
    // batch mode
         G4String command = "/control/execute ";
       //  G4String fileName = argv[1];
         UImanager->ApplyCommand(command+macroFilename);
    }
    else {
        //interactive mode
        ui = new G4UIExecutive(argc, argv);
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    }
    delete visManager;
    delete runManager;
}

