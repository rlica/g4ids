#include "G4Trajectory.hh"
#include "FrontPlasticKUTrackingAction.hh"
#include "G4VUserTrackInformation.hh"

#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "G4ParticleTypes.hh"

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
FrontPlasticKUTrackingAction::FrontPlasticKUTrackingAction()
{}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void FrontPlasticKUTrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
	//Use custom trajectory class
	fpTrackingManager->SetTrajectory(new G4Trajectory(aTrack));
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void FrontPlasticKUTrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
}
