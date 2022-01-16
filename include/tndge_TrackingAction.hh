#ifndef tndge_TrackingAction_h
#define tndge_TrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"


class tndge_TrackingAction : public G4UserTrackingAction {

public:
	tndge_TrackingAction();
	~tndge_TrackingAction() {};

	void PreUserTrackingAction(const G4Track*);
	void PostUserTrackingAction(const G4Track*);

};

#endif
