#include "G4Trajectory.hh"
#include "FastPlasticTrackingAction.hh"
#include "G4VUserTrackInformation.hh"

#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "G4ParticleTypes.hh"

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
FastPlasticTrackingAction::FastPlasticTrackingAction()
{}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void FastPlasticTrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
	//Use custom trajectory class
	fpTrackingManager->SetTrajectory(new G4Trajectory(aTrack));
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void FastPlasticTrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
}
