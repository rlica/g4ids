/////////////////////////////////////////////////////////////////////////////
/*
 *  \brief  IDS Detector Construction
 *  \author Christophe Sotty : csotty@gmail.com
 *  			       Christophe.Sotty@fys.kuleuve.be
 */
///////////////////////////////////////////////////////////////////////////////


#ifndef G4IDSDetectorConstruction_H
#define G4IDSDetectorConstruction_H 1

#include "G4VUserDetectorConstruction.hh"
//#include "LaBr3Detector.hh"
//#include "tndge_DetectorConstruction.hh"
#include "globals.hh"
#include "G4VPhysicalVolume.hh"
#include "G4RotationMatrix.hh"


// Arrangement of the IDS detectors
//
class G4IDSDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    // Constructor
    G4IDSDetectorConstruction();
    // Destructor
    ~G4IDSDetectorConstruction();

    // Routines
    G4VPhysicalVolume* Construct();
    void Print();

   // Set number of detectors
   void SetNbLaBr3(G4int value)	{ NB_LABR3=value;};
   G4int  GetNbLaBr3()		{ return NB_LABR3;};
   void SetNbClKU(int value)	{ NB_CLKU=value;};
   G4int  GetNbClKU()		{ return NB_CLKU;};
   void SetNbClBuch(int value)	{ NB_CLBUCH=value;};
   G4int  GetNbClBuch()		{ return NB_CLBUCH;};
   void SetNbVetoPlastic(G4int value)	{ NB_VetoPlastic=value;};
   G4int  GetNbVetoPlastic()		{ return NB_VetoPlastic;};
  private:
    G4VPhysicalVolume* mother;
    G4int NB_LABR3;
    G4int NB_CLKU;
    G4int NB_CLBUCH;
    G4int NB_VetoPlastic;
};
#endif
