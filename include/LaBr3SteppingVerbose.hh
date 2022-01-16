class LaBr3SteppingVerbose;

#ifndef LaBr3SteppingVerbose_h
#define LaBr3SteppingVerbose_h 1

#include "G4SteppingVerbose.hh"
#include "G4UnitsTable.hh"


class LaBr3SteppingVerbose : public G4SteppingVerbose
{
public:

	LaBr3SteppingVerbose();
	~LaBr3SteppingVerbose();

	void 	StepInfo();
	void 	TrackingStarted();
//	const G4String GetVolName();
	void	GetVolName();
	void	GetKineticEn();

};

#endif

