#ifndef CloverSingleBuchTrackingAction_h
#define CloverSingleBuchTrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"


class CloverSingleBuchTrackingAction : public G4UserTrackingAction {

public:
	CloverSingleBuchTrackingAction();
	~CloverSingleBuchTrackingAction() {};

	void PreUserTrackingAction(const G4Track*);
	void PostUserTrackingAction(const G4Track*);

};

#endif
