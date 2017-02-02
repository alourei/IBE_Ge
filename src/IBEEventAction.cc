




#include "IBEEventAction.hh"

#include "IBERunAction.hh"
#include "IBEPrimaryGeneratorAction.hh"
//#include "EventActionMessenger.hh"

#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>
#include <iostream>
#include <fstream>
using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IBEEventAction::IBEEventAction(IBERunAction* run,IBEPrimaryGeneratorAction *prim)
  :runAct(run),primGenAct(prim),printModulo(1000)
{
  ;  //eventMessenger = new EventActionMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IBEEventAction::~IBEEventAction()
{
  ;//  delete eventMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IBEEventAction::BeginOfEventAction(const G4Event* evt)
{  
  G4int evtNb = evt->GetEventID();
  if (evtNb%printModulo == 0) { 
    G4cout << "\n---> Begin of event: " << evtNb << G4endl;
    //CLHEP::HepRandom::showEngineStatus();
}
 
 // initialisation per event
 EnergyBeta = EnergyGamma = EnergyGermanium =0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IBEEventAction::EndOfEventAction(const G4Event* evt)
{
  //accumulates statistic
  //
  //runAct->fillPerEvent(EnergyAbs, EnergyGap, TrackLAbs, TrackLGap);
  
  //print per event (modulo n)
  //
  G4int evtNb = evt->GetEventID();
  if (evtNb%printModulo == 0) {
    G4cout << "---> End of event: " << evtNb << G4endl;	

    /*    G4cout<< evtNb<<"   "
	  << "   Beta: total energy: " << std::setw(7)
	  << G4BestUnit(EnergyBeta,"Energy")
	  << G4endl
	  << "        Gamma: total energy: " << std::setw(7)
	  << G4BestUnit(EnergyGamma,"Energy")
	  << G4endl;
    */
}
	  ofstream *out=runAct->GetOutFilePtr();
    G4double totalenergy=primGenAct->GetEnergyBeta();
    G4int index=primGenAct->GetBRindex();
    *out<< evtNb<<"   "
	<< std::setw(7)<<index<<"\t\t"<<totalenergy/MeV<<"\t\t"
	<<EnergyBeta/keV<<"\t\t"
	<<EnergyGamma/keV<<"\t\t"
    <<EnergyGermanium/keV
	<< endl;

	  
  
}  
