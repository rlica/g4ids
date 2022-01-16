/***********************************************************************
 *
 *    Sensitive detector for detector read-out of VetoPlastic detector
 *
 ************************************************************************/

#ifndef VetoPlasticSD_h
#define VetoPlasticSD_h 1

#include "G4VSensitiveDetector.hh"
#include "VetoPlasticHit.hh"

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
      G4int DetectorHitsCollectionID_VetoPlastic;
};
*/


class VetoPlasticSD : public G4VSensitiveDetector
{
  public:
      VetoPlasticSD(G4String name);
     ~VetoPlasticSD();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);

      inline G4int GetVetoPlasticDetectorID() {return detectorID;};
      inline G4int SetVetoPlasticDetectorID(G4int det_id) {detectorID=det_id;};
      //G4int AddVetoPlasticDetector(G4String name);
      //G4int AddVetoPlasticDetector();

      //G4int GetNbOfVetoPlasticDetectors();


  private:
      G4String HC_name;
      VetoPlasticHitsCollection* hitsCollection; 

      G4int detectorID;
//      G4int tracecounter;
      G4int HCID;


//  protected:
//      vector<Detectorization*> detectors;
};

#endif

