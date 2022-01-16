#ifndef G4IDSEventAction_h
#define G4IDSEventAction_h 1



class G4IDSCounter
{
public:
	G4IDSCounter();
	~G4IDSCounter();

	void InitialiseCounter(int value);
	void IncrementCounter();
	int  GetCounterValue();
	
	int MyCounter;

};

#endif
