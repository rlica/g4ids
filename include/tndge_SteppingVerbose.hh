class tndge_SteppingVerbose;

#ifndef tndge_SteppingVerbose_h
#define tndge_SteppingVerbose_h 1

#include "G4SteppingVerbose.hh"
#include "G4UnitsTable.hh"


class tndge_SteppingVerbose : public G4SteppingVerbose
{
public:

	tndge_SteppingVerbose();
	~tndge_SteppingVerbose();

	void 	StepInfo();
	void 	TrackingStarted();
//	const G4String GetVolName();
	void	GetVolName();
	void	GetKineticEn();

};

#endif

