/***********************************************************************
 *
 *    Sensitive detector for detector read-out of FrontPlasticKU detector
 *
 ************************************************************************/

#ifndef FrontPlasticKUSD_h
#define FrontPlasticKUSD_h 1

#include "G4VSensitiveDetector.hh"
#include "FrontPlasticKUHit.hh"

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
      G4int DetectorHitsCollectionID_FrontPlasticKU;
};
*/


class FrontPlasticKUSD : public G4VSensitiveDetector
{
  public:
      FrontPlasticKUSD(G4String name);
     ~FrontPlasticKUSD();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);

      inline G4int GetFrontPlasticKUDetectorID() {return detectorID;};
      inline G4int SetFrontPlasticKUDetectorID(G4int det_id) {detectorID=det_id;};
      //G4int AddFrontPlasticKUDetector(G4String name);
      //G4int AddFrontPlasticKUDetector();

      //G4int GetNbOfFrontPlasticKUDetectors();


  private:
      G4String HC_name;
      FrontPlasticKUHitsCollection* hitsCollection; 

      G4int detectorID;
//      G4int tracecounter;
      G4int HCID;


//  protected:
//      vector<Detectorization*> detectors;
};

#endif

