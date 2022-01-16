
#include "G4IDSCounter.hh"



G4IDSCounter::G4IDSCounter()
	{	MyCounter = 0;	}
	
G4IDSCounter::~G4IDSCounter()
	{	}



void G4IDSCounter::InitialiseCounter(int value)  
	{	MyCounter = value;	}


void G4IDSCounter::IncrementCounter()  
	{	MyCounter++;	}


int G4IDSCounter::GetCounterValue()  
	{	return (MyCounter);	}

