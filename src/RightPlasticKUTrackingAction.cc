#include "G4Trajectory.hh"
#include "RightPlasticKUTrackingAction.hh"
#include "G4VUserTrackInformation.hh"

#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "G4ParticleTypes.hh"

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
RightPlasticKUTrackingAction::RightPlasticKUTrackingAction()
{}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void RightPlasticKUTrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
	//Use custom trajectory class
	fpTrackingManager->SetTrajectory(new G4Trajectory(aTrack));
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void RightPlasticKUTrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
}
