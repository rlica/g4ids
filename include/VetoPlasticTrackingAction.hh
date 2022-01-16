#ifndef VetoPlasticTrackingAction_h
#define VetoPlasticTrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"


class VetoPlasticTrackingAction : public G4UserTrackingAction {

public:
	VetoPlasticTrackingAction();
	~VetoPlasticTrackingAction() {};

	void PreUserTrackingAction(const G4Track*);
	void PostUserTrackingAction(const G4Track*);

};

#endif
