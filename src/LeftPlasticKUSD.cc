/*********************************************************************** 
 *
 *     Sensitive detector for detector read-out of LeftPlasticKU detector
 *
 ***********************************************************************/

#include "LeftPlasticKUSD.hh"
#include "LeftPlasticKUDetector.hh"
#include "G4IDSDetectorConstruction.hh"

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4AffineTransform.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4VProcess.hh"

#include <string>
#include <strstream>
#include <sstream>

using namespace std;

template<typename T>
std::string to_string( const T & Value )
{
    // utiliser un flux de sortie pour créer la chaîne
    std::ostringstream oss;
    // écrire la valeur dans le flux
    oss << Value;
    // renvoyer une string
    return oss.str();
}


LeftPlasticKUSD::LeftPlasticKUSD(G4String name)
  :G4VSensitiveDetector(name), detectorID(-1), HCID(-1)
{
  HC_name = "LeftPlasticKU";
  collectionName.insert(HC_name);
//  detectorID = AddLeftPlasticKUDetector(name);
}
                                                                                                                                                                                                                         
LeftPlasticKUSD::~LeftPlasticKUSD()
{;}

void LeftPlasticKUSD::Initialize(G4HCofThisEvent* evnt)
{
  hitsCollection = new LeftPlasticKUHitsCollection(SensitiveDetectorName, HC_name);

//  static G4int HCID = -1;
  if(HCID<0)
    {
      G4String full_name = SensitiveDetectorName;
//      full_name+= "/" + to_string(detectorID) +"/" + HC_name;
      full_name+= "/" + HC_name;
      HCID = G4SDManager::GetSDMpointer()->GetCollectionID(full_name);
      G4cout	<< "RR full_name = "	<< full_name	<< flush << G4endl
		<< "MM HCID ="		<< HCID 	<< flush << G4endl;
    }

  evnt->AddHitsCollection(HCID, hitsCollection);
}

G4bool LeftPlasticKUSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  G4double edep 		= aStep->GetTotalEnergyDeposit();
  G4double kineticEnergy 	= aStep->GetPreStepPoint()->GetKineticEnergy();
  G4double local_time 		= aStep->GetTrack()->GetLocalTime();	// Time since the current track is created. 
  G4double global_time 		= aStep->GetTrack()->GetGlobalTime();	// Time since the event in which the track belongs is created. 
  G4int trackID 		= aStep->GetTrack()->GetTrackID();
  G4int parentID 		= aStep->GetTrack()->GetParentID();
  G4String partName		= aStep->GetTrack()->GetDynamicParticle()->GetParticleDefinition()->GetParticleName();
  G4String volName 		= aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName();
  G4ThreeVector position 	= aStep->GetPostStepPoint()->GetPosition();
/*  G4int replica_nb0 		= aStep->GetPreStepPoint()->GetTouchable()->GetReplicaNumber(0); 
  G4int replica_nb1 		= aStep->GetPreStepPoint()->GetTouchable()->GetReplicaNumber(1); 
  G4int replica_nb3 		= aStep->GetPreStepPoint()->GetTouchable()->GetReplicaNumber(3); 
*/
  if(edep == 0.) return false;

  LeftPlasticKUHit* newHit = new LeftPlasticKUHit();

  newHit -> SetKinEn    (kineticEnergy);
  newHit -> SetTrackID  (trackID);
  newHit -> SetEdep     (edep);
  newHit -> SetPos      (aStep->GetPostStepPoint()->GetPosition());
  newHit -> SetPartName (partName);
  newHit -> SetVname    (volName);
  newHit -> SetPos	(position);
/*  newHit->SetReplicaNb0 (replica_nb0); 
  newHit->SetReplicaNb1 (replica_nb1); 
  newHit->SetReplicaNb3 (replica_nb3); 
*/

  hitsCollection->insert(newHit);

  return true;
}

void LeftPlasticKUSD::EndOfEvent(G4HCofThisEvent*)
{;}
               
/*
G4int LeftPlasticKUSD::AddLeftPlasticKUDetector(G4String name){
  Detectorization* new_detector = new Detectorization(name);
  G4int det_id = detectors.size();
  detectors.push_back(new_detector);
  detectorID=det=id;
  return det_id;
}

G4int LeftPlasticKUSD::AddLeftPlasticKUDetector(){
  G4int det_id = detectors.size();
  ostringstream id_strm;
  id_strm.clear();
  id_strm << det_id;
  return( AddLeftPlasticKUDetector("detLeftPlasticKU" + id_strm.str()) );
}
*/






