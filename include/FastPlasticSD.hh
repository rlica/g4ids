/***********************************************************************
 *
 *    Sensitive detector for detector read-out of FastPlastic detector
 *
 ************************************************************************/

#ifndef FastPlasticSD_h
#define FastPlasticSD_h 1

#include "G4VSensitiveDetector.hh"
#include "FastPlasticHit.hh"

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
      G4int DetectorHitsCollectionID_FastPlastic;
};
*/


class FastPlasticSD : public G4VSensitiveDetector
{
  public:
      FastPlasticSD(G4String name);
     ~FastPlasticSD();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);

      inline G4int GetFastPlasticDetectorID() {return detectorID;};
      inline G4int SetFastPlasticDetectorID(G4int det_id) {detectorID=det_id;};
      //G4int AddFastPlasticDetector(G4String name);
      //G4int AddFastPlasticDetector();

      //G4int GetNbOfFastPlasticDetectors();


  private:
      G4String HC_name;
      FastPlasticHitsCollection* hitsCollection; 

      G4int detectorID;
//      G4int tracecounter;
      G4int HCID;


//  protected:
//      vector<Detectorization*> detectors;
};

#endif

