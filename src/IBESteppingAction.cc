

#include "IBESteppingAction.hh"

#include "IBEDetectorConstruction.hh"
#include "IBEEventAction.hh"

#include "G4Step.hh"
#include "G4Track.hh"

////#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IBESteppingAction::IBESteppingAction(IBEDetectorConstruction* det,
                                         IBEEventAction* evt)
:detector(det), eventaction(evt)					 
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IBESteppingAction::~IBESteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IBESteppingAction::UserSteppingAction(const G4Step* aStep)
{
  // get volume of the current step
  G4VPhysicalVolume* volume 
    = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

  G4Track* track
    =aStep->GetTrack();  
  // collect energy and track length step by step
  G4double edep = aStep->GetTotalEnergyDeposit();
  
  G4double stepl = 0.;
  if (aStep->GetTrack()->GetDefinition()->GetPDGCharge() != 0.)
    stepl = aStep->GetStepLength();
      
  if (volume == detector->Getplastic_phys()){
    if(track->GetDefinition()->GetPDGCharge() != 0. && track->GetParentID()<=1)
      eventaction->AddPlasticBeta(edep);
    else  if(track->GetParentID()>1)
      eventaction->AddPlasticGamma(edep);
  }
  else if(volume ==detector->GetGermanium_phys()){
        if(track->GetDefinition()->GetPDGCharge() !=0. && track->GetParentID()>1)
            eventaction->AddGermaniumGamma(edep);
        else if(track->GetDefinition()->GetPDGCharge() ==0)
           eventaction->AddGermaniumGamma(edep); 
  }
  
  //example of saving random number seed of this event, under condition
  //// if (condition) G4RunManager::GetRunManager()->rndmSaveThisEvent(); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
