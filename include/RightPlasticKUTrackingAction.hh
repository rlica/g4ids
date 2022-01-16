#ifndef RightPlasticKUTrackingAction_h
#define RightPlasticKUTrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"


class RightPlasticKUTrackingAction : public G4UserTrackingAction {

public:
	RightPlasticKUTrackingAction();
	~RightPlasticKUTrackingAction() {};

	void PreUserTrackingAction(const G4Track*);
	void PostUserTrackingAction(const G4Track*);

};

#endif
