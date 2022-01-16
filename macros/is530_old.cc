
#include "G4RunManager.hh"
//#include "G4UImanager.hh"

#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"
#include "PhysicsList.hh"
#include "PhysicsListMessenger.hh"
#include "tndge_DetectorConstruction.hh"
#include "tndge_EventAction.hh"
#include "tndge_PrimaryGeneratorAction.hh"
#include "tndge_TrackerHit.hh"
#include "tndge_TrackerSD.hh"

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
using namespace std;

int main(int argc,char** argv)
{
  // Construct the default run manager
  //

	G4RunManager* runManager = new G4RunManager;

// set mandatory initialization classes


// -->> here's your detector......
  G4VUserDetectorConstruction* detector = new tndge_DetectorConstruction;
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

//  G4cout<<"\n\n HERE I AM !!!!!!!\n\n\n"<<flush;

  G4VUserPrimaryGeneratorAction* gen_action = new tndge_PrimaryGeneratorAction();
    runManager->SetUserAction(gen_action);
 	runManager->SetUserAction(new tndge_EventAction());

// Initialize G4 kernel
//    runManager->Initialize();
    G4cout << "\n\t\t\t RunManager launched.....\n" << flush; 


#ifdef G4VIS_USE
// Visualization, if you choose to have it!
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();
#endif


  G4UImanager * UI = G4UImanager::GetUIpointer();  

  if(argc==1)  // Define (G)UI terminal for interactive mode
  { 
    // G4UIterminal is a (dumb) terminal
    //
    G4UIsession * session = 0;
#ifdef G4UI_USE_TCSH
      session = new G4UIterminal(new G4UItcsh);      
#else
      session = new G4UIterminal();
#endif
//    UI->ApplyCommand("/control/execute vis.mac");

//    UI->ApplyCommand("/control/execute vrml.mac"); 

    session->SessionStart();
    delete session;
  }
  else   // Batch mode
  { 
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UI->ApplyCommand(command+fileName);
  }
//  ____________________________________________________________________

#ifdef G4VIS_USE
	delete visManager;
#endif
	delete runManager;
  return 0;
  
}
