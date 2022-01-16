#ifndef CloverSingleTrackingAction_h
#define CloverSingleTrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"


class CloverSingleTrackingAction : public G4UserTrackingAction {

public:
	CloverSingleTrackingAction();
	~CloverSingleTrackingAction() {};

	void PreUserTrackingAction(const G4Track*);
	void PostUserTrackingAction(const G4Track*);

};

#endif
