#ifndef FastPlasticTrackingAction_h
#define FastPlasticTrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"


class FastPlasticTrackingAction : public G4UserTrackingAction {

public:
	FastPlasticTrackingAction();
	~FastPlasticTrackingAction() {};

	void PreUserTrackingAction(const G4Track*);
	void PostUserTrackingAction(const G4Track*);

};

#endif
