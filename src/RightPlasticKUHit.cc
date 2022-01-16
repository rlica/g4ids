/************************************************************************* 
 *
 *    Hit in the RightPlasticKU detector
 * 
 *************************************************************************/

#include "RightPlasticKUHit.hh"

#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator<RightPlasticKUHit> RightPlasticKUHitAllocator;


RightPlasticKUHit::RightPlasticKUHit()
  :trackID(0), detectorID(-1), edep(0), pos(0)
{;}

RightPlasticKUHit::~RightPlasticKUHit()
{;}

RightPlasticKUHit::RightPlasticKUHit(const RightPlasticKUHit& right)
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

const RightPlasticKUHit& RightPlasticKUHit::operator=(const RightPlasticKUHit& right)
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


G4int RightPlasticKUHit::operator==(const RightPlasticKUHit &right) const
{
  return (this==&right) ? 1 : 0;
  //return 0;
}

void RightPlasticKUHit::Draw()
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

void RightPlasticKUHit::Print()
{
  G4cout << " RightPlasticKU: " 	<< G4endl;
  G4cout << "  trackID: " 	<< trackID 			<< G4endl
         << "  energy deposit: "<< G4BestUnit(edep,"Energy")	<< G4endl
         << "  position: " 	<< G4BestUnit(pos,"Length") 	<< G4endl
         << "  Kinetic Energy: "<< G4BestUnit(KinEn,"Energy")	<< G4endl
         << "  Volume Name: "	<< volName			<< G4endl
         << "  Particle Name: "	<< particleName			<< G4endl;
}  




