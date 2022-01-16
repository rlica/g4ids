/***********************************************************************
 *
 *    sensitive detector for detector read-out of LaBr3 detector
 *
 ************************************************************************/

#ifndef LaBr3SensitiveDetector_h
#define LaBr3SensitiveDetector_h 1

#include "G4VSensitiveDetector.hh"
#include "LaBr3Hit.hh"

class G4Step;
class G4HCofThisEvent;
//class IDS_DetClass17HistoManager;
class G4VPhysicalVolume;
class G4AffineTransform;

#include <vector>

/*
class Detectorization{
  public:
      Detectorization(G4String);
      ~Detectorization();

      G4String DetectorName;
      G4int DetectorHitsCollectionID_LaBr3;
};
*/


class LaBr3SensitiveDetector : public G4VSensitiveDetector
{
  public:
      LaBr3SensitiveDetector(G4String name);
     ~LaBr3SensitiveDetector();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);

      inline G4int GetLaBr3DetectorID() {return detectorID;};
      inline G4int SetLaBr3DetectorID(G4int det_id) {detectorID=det_id;};
      //G4int AddLaBr3Detector(G4String name);
      //G4int AddLaBr3Detector();

      //G4int GetNbOfLaBr3Detectors();


  private:
      G4String HC_name;
      LaBr3HitsCollection* hitsCollection; 

      G4int detectorID;
//      G4int tracecounter;
      G4int HCID;


//  protected:
//      vector<Detectorization*> detectors;
};

#endif

