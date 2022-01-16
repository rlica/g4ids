/***********************************************************************
 *
 *    Sensitive detector for detector read-out of LeftPlasticKU detector
 *
 ************************************************************************/

#ifndef LeftPlasticKUSD_h
#define LeftPlasticKUSD_h 1

#include "G4VSensitiveDetector.hh"
#include "LeftPlasticKUHit.hh"

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
      G4int DetectorHitsCollectionID_LeftPlasticKU;
};
*/


class LeftPlasticKUSD : public G4VSensitiveDetector
{
  public:
      LeftPlasticKUSD(G4String name);
     ~LeftPlasticKUSD();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);

      inline G4int GetLeftPlasticKUDetectorID() {return detectorID;};
      inline G4int SetLeftPlasticKUDetectorID(G4int det_id) {detectorID=det_id;};
      //G4int AddLeftPlasticKUDetector(G4String name);
      //G4int AddLeftPlasticKUDetector();

      //G4int GetNbOfLeftPlasticKUDetectors();


  private:
      G4String HC_name;
      LeftPlasticKUHitsCollection* hitsCollection; 

      G4int detectorID;
//      G4int tracecounter;
      G4int HCID;


//  protected:
//      vector<Detectorization*> detectors;
};

#endif

