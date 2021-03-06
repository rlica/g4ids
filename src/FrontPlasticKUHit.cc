/************************************************************************* 
 *
 *    Hit in the FrontPlasticKU detector
 * 
 *************************************************************************/

#include "FrontPlasticKUHit.hh"

#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator<FrontPlasticKUHit> FrontPlasticKUHitAllocator;


FrontPlasticKUHit::FrontPlasticKUHit()
  :trackID(0), detectorID(-1), edep(0), pos(0)
{;}

FrontPlasticKUHit::~FrontPlasticKUHit()
{;}

FrontPlasticKUHit::FrontPlasticKUHit(const FrontPlasticKUHit& right)
  : G4VHit()
{
  KinEn		= right.KinEn;
  trackID	= right.trackID;
  detectorID	= right.detectorID;
  edep		= right.edep;
  pos		= right.pos;
  physVol	= right.physVol;	   
  particleName	= right.particleName;	  
  pLogV		= right.pLogV;		  
  volName	= right.volName;
}

const FrontPlasticKUHit& FrontPlasticKUHit::operator=(const FrontPlasticKUHit& right)
{
  KinEn		= right.KinEn;
  trackID	= right.trackID;
  detectorID	= right.detectorID;
  edep		= right.edep;
  pos		= right.pos;
  physVol	= right.physVol;	   
  particleName	= right.particleName;	  
  pLogV		= right.pLogV;		  
  volName	= right.volName;
  return *this;
}


G4int FrontPlasticKUHit::operator==(const FrontPlasticKUHit &right) const
{
  return (this==&right) ? 1 : 0;
  //return 0;
}

void FrontPlasticKUHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
    if(pVVisManager)
      {
        G4Circle circle(pos);
        circle.SetScreenSize(0.04);
        circle.SetFillStyle(G4Circle::filled);
        G4Colour colour(1.,0.,0.);
        G4VisAttributes attribs(colour);
        circle.SetVisAttributes(attribs);
        pVVisManager->Draw(circle);
      }
}

void FrontPlasticKUHit::Print()
{
  G4cout << " FrontPlasticKU: " 	<< G4endl;
  G4cout << "  trackID: " 	<< trackID 			<< G4endl
         << "  energy deposit: "<< G4BestUnit(edep,"Energy")	<< G4endl
         << "  position: " 	<< G4BestUnit(pos,"Length") 	<< G4endl
         << "  Kinetic Energy: "<< G4BestUnit(KinEn,"Energy")	<< G4endl
         << "  Volume Name: "	<< volName			<< G4endl
         << "  Particle Name: "	<< particleName			<< G4endl;
}  




