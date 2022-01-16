
#ifndef tndge_TrackerSD_h
#define tndge_TrackerSD_h 1

#include "globals.hh"
#include "G4VSensitiveDetector.hh"
#include "tndge_TrackerHit.hh"
#include "G4ios.hh"

class G4Step;
class G4HCofThisEvent;


class tndge_TrackerSD : public G4VSensitiveDetector
{
  public:
      tndge_TrackerSD(G4String);
     ~tndge_TrackerSD();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);

  private:
      tndge_TrackerHitsCollection* trackerCollection;

};


#endif
