/************************************************************************* 
 *
 *    Hit in the RightPlasticKU detector
 * 
 **************************************************************************/

#ifndef RightPlasticKUHit_h
#define RightPlasticKUHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ios.hh"


class RightPlasticKUHit : public G4VHit
{
  public:

      RightPlasticKUHit();
     ~RightPlasticKUHit();
      RightPlasticKUHit(const RightPlasticKUHit&);
      const RightPlasticKUHit& operator=(const RightPlasticKUHit&);
      G4int operator==(const RightPlasticKUHit&) const;

      inline void* operator new(size_t);
      inline void  operator delete(void*);

      void Draw();
      void Print();


  private:
      G4double 			KinEn;
      G4double 			edep;
      G4ThreeVector 		pos;
      const G4VPhysicalVolume* 	physVol;
      const G4LogicalVolume* 	pLogV;
      G4int 			trackID;
      G4int 			detectorID;
      G4String 			particleName;
      G4String 			volName;


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
      void 				SetDetectorID(G4int value){ detectorID=value; }
      inline const G4int 		GetTrackID()		{ return trackID; }
      inline const G4int 		GetDetectorID()		{ return detectorID; }

      /*void SetReplicaNb0(int nr){ replica_nb0 = nr; }
      inline G4int GetReplicaNumber0(){ return replica_nb0; }
      void SetReplicaNb1(int nr){ replica_nb1 = nr; }
      inline G4int GetReplicaNumber1(){ return replica_nb1; }
      void SetReplicaNb3(int nr){ replica_nb3 = nr; }
      inline G4int GetReplicaNumber3(){ return replica_nb3; }*/

};

typedef G4THitsCollection<RightPlasticKUHit> RightPlasticKUHitsCollection;

extern G4Allocator<RightPlasticKUHit> RightPlasticKUHitAllocator;

inline void* RightPlasticKUHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) RightPlasticKUHitAllocator.MallocSingle();
  return aHit;
}

inline void RightPlasticKUHit::operator delete(void *aHit)
{
  RightPlasticKUHitAllocator.FreeSingle((RightPlasticKUHit*) aHit);
}

#endif                
