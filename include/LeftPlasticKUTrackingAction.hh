#ifndef LeftPlasticKUTrackingAction_h
#define LeftPlasticKUTrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"


class LeftPlasticKUTrackingAction : public G4UserTrackingAction {

public:
	LeftPlasticKUTrackingAction();
	~LeftPlasticKUTrackingAction() {};

	void PreUserTrackingAction(const G4Track*);
	void PostUserTrackingAction(const G4Track*);

};

#endif
