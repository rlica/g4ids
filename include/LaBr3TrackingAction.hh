#ifndef LaBr3TrackingAction_h
#define LaBr3TrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"


class LaBr3TrackingAction : public G4UserTrackingAction {

public:
	LaBr3TrackingAction();
	~LaBr3TrackingAction() {};

	void PreUserTrackingAction(const G4Track*);
	void PostUserTrackingAction(const G4Track*);

};

#endif
