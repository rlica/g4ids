#ifndef FrontPlasticKUTrackingAction_h
#define FrontPlasticKUTrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"


class FrontPlasticKUTrackingAction : public G4UserTrackingAction {

public:
	FrontPlasticKUTrackingAction();
	~FrontPlasticKUTrackingAction() {};

	void PreUserTrackingAction(const G4Track*);
	void PostUserTrackingAction(const G4Track*);

};

#endif
