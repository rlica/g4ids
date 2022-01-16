

#include <time.h>
#include <cstdio>

#include "global.hh"
#include "read_config.hh"

#include "G4IDSDetectorConstruction.hh"
#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"
#include "PhysicsList.hh"
#include "PhysicsListMessenger.hh"
#include "G4IDSEventAction.hh"
#include "G4IDSPrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "G4ios.hh"
#include <time.h>





using namespace std;


void PrintUsage() {
    G4cerr << " Usage: " << G4endl;
    G4cerr << " exampleB4d [-m macro ] [-u UIsession] [-t nThreads] [-c configfile] [-f OutputFileName]" << G4endl;
    G4cerr << "   note: -t option is available only for multi-threaded mode. (not available)"
           << G4endl;
  }

int main(int argc,char** argv)
{

  clock_t t1,t2;
  t1=clock();

  // Evaluate arguments
  //
   if ( argc > 7 ) {
    PrintUsage();
    return 1;
  }
  
  G4String macro;
  G4String session;
  G4String fFileName = "../../rootfiles/test.root"; //R.Lica - rootfiles outside the G4IDS folder
  G4String cFileName = "../configfiles/config.dat";

  for ( G4int i=1; i<argc; i=i+2 ) {
    if      ( G4String(argv[i]) == "-m" ) macro		= argv[i+1];
    else if ( G4String(argv[i]) == "-u" ) session	= argv[i+1];
    else if ( G4String(argv[i]) == "-f" ) fFileName	= "../../rootfiles/" + (G4String)argv[i+1];
    else if ( G4String(argv[i]) == "-c" ) cFileName	= "../configfiles/" + (G4String)argv[i+1];
    else {
      PrintUsage();
      return 1;
    }
  }  
  
  read_config(cFileName);
  
  // Construct the run manager
  G4RunManager * runManager = new G4RunManager;

// set mandatory initialization classes


// -->> here's your detector......
  G4VUserDetectorConstruction* detector = new G4IDSDetectorConstruction;
  runManager->SetUserInitialization(detector);
  G4cout << "\n\t Detectors DONE.....\n" << flush; 

// -->> here's your physics
  G4PhysListFactory factory;
  G4VModularPhysicsList* phys = 0;
  PhysicsListMessenger* mess = 0;
  G4String physName = "";

  // Physics List name defined via 2nd argument
  if (argc==3) { physName = argv[2]; }

  // Physics List name defined via environment variable
  char* path = getenv("PHYSLIST");
  if (path) { physName = G4String(path); }

  // reference PhysicsList via its name
  if(factory.IsReferencePhysList(physName)) {
    phys = factory.GetReferencePhysList(physName);
    mess = new PhysicsListMessenger();
  } 

  // local Physics List
  if(!phys) { phys = new PhysicsList(); }

  // define physics
  runManager->SetUserInitialization(phys);
  G4cout << "\n\t\t Physics DONE.....\n" << flush; 

  G4VUserPrimaryGeneratorAction* gen_action = new G4IDSPrimaryGeneratorAction(fFileName);
  runManager->SetUserAction(gen_action);
  runManager->SetUserAction(new G4IDSEventAction((G4IDSDetectorConstruction*)detector, fFileName));
	
//-----aken from Geant4.10 example B4 (R.Lica)
//Initialize G4 kernel
    runManager->Initialize();
    G4cout << "\n\t\t\t RunManager launched.....\n" << flush; 

#ifdef G4VIS_USE
  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();
#endif

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if ( macro.size() ) {
    // batch mode
    G4String command = "/control/execute ";
    UImanager->ApplyCommand(command+macro);
  }
  else  {  
    // interactive mode : define UI session
#ifdef G4UI_USE
    G4UIExecutive* ui = new G4UIExecutive(argc, argv, session);
#ifdef G4VIS_USE
    UImanager->ApplyCommand("/control/execute init_vis.mac"); 
#else
    UImanager->ApplyCommand("/control/execute init.mac"); 
#endif
    if (ui->IsGUI())
      UImanager->ApplyCommand("/control/execute gui.mac");
    ui->SessionStart();
    delete ui;
#endif
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !

#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;

  //t2=clock();
  //float runningTime ((float)t2-(float)t1);
  //G4cout<<"\nRunning Time: "<<runningTime<<" s\n" <<G4endl;

  return 0;
}

