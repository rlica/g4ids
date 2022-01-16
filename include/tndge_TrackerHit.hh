
#ifndef tndge_TrackerHit_h
#define tndge_TrackerHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ios.hh"

class tndge_TrackerHit : public G4VHit
{
  public:
      tndge_TrackerHit();
      ~tndge_TrackerHit();
      tndge_TrackerHit(const tndge_TrackerHit &right);
      const tndge_TrackerHit& operator=(const tndge_TrackerHit &right);
      G4int operator==(const tndge_TrackerHit &right) const;

      inline void *operator new(size_t);
      inline void operator delete(void *aHit);

      void Draw();
      void Print();


  private:
      G4double 			KinEn;
      G4double 			edep;
      G4ThreeVector 		pos;
      const G4VPhysicalVolume* 	physVol;
      const G4LogicalVolume* 	pLogV;
      G4int 			trackID;
      G4String 			particleName;
      G4String 			volName;
      G4int 			replica_nb0, replica_nb1, replica_nb3; 


//	all this U define yourself in the ....SD.cc ( tndge_TrackerSD.cc in this case...) 
//	and then attach all this functions to your own trackerCollection 

  public:
      void 			SetKinEn(G4double kineticEnergy){ KinEn = kineticEnergy; }
      inline G4double 		GetKinEn()			{ return KinEn; }
      void 			SetEdep(G4double de)		{ edep = de; }
      void 			AddEdep(G4double de)		{ edep += de; }
      inline G4double 		GetEdep()			{ return edep; }
      void 			SetPos(G4ThreeVector xyz)	{ pos = xyz; }
      inline G4ThreeVector 	GetPos()			{ return pos; }

      void 			SetPartName(G4String name)	{ particleName = name; }
      inline G4String 		GetPartName()			{ return particleName; }

      inline const G4LogicalVolume* 	GetLogV()		{ return pLogV; }
      void 				SetVname(G4String name)	{ volName = name; }
      inline G4String 			GetVname()		{ return volName; }
      void 				SetTrackID(G4int value)	{ trackID=value; }
      inline const G4int 		GetTrackID()		{ return trackID; }

      void SetReplicaNb0(int nr){ replica_nb0 = nr; }
      inline G4int GetReplicaNumber0(){ return replica_nb0; }
      void SetReplicaNb1(int nr){ replica_nb1 = nr; }
      inline G4int GetReplicaNumber1(){ return replica_nb1; }
      void SetReplicaNb3(int nr){ replica_nb3 = nr; }
      inline G4int GetReplicaNumber3(){ return replica_nb3; }

};

typedef G4THitsCollection<tndge_TrackerHit> tndge_TrackerHitsCollection;

extern G4Allocator<tndge_TrackerHit> tndge_TrackerHitAllocator;

inline void* tndge_TrackerHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) tndge_TrackerHitAllocator.MallocSingle();
  return aHit;
}

inline void tndge_TrackerHit::operator delete(void *aHit)
{
  tndge_TrackerHitAllocator.FreeSingle((tndge_TrackerHit*) aHit);
}

#endif
