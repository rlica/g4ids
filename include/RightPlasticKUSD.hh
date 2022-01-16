/***********************************************************************
 *
 *    Sensitive detector for detector read-out of RightPlasticKU detector
 *
 ************************************************************************/

#ifndef RightPlasticKUSD_h
#define RightPlasticKUSD_h 1

#include "G4VSensitiveDetector.hh"
#include "RightPlasticKUHit.hh"

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
      G4int DetectorHitsCollectionID_RightPlasticKU;
};
*/


class RightPlasticKUSD : public G4VSensitiveDetector
{
  public:
      RightPlasticKUSD(G4String name);
     ~RightPlasticKUSD();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);

      inline G4int GetRightPlasticKUDetectorID() {return detectorID;};
      inline G4int SetRightPlasticKUDetectorID(G4int det_id) {detectorID=det_id;};
      //G4int AddRightPlasticKUDetector(G4String name);
      //G4int AddRightPlasticKUDetector();

      //G4int GetNbOfRightPlasticKUDetectors();


  private:
      G4String HC_name;
      RightPlasticKUHitsCollection* hitsCollection; 

      G4int detectorID;
//      G4int tracecounter;
      G4int HCID;


//  protected:
//      vector<Detectorization*> detectors;
};

#endif

