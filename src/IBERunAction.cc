#include "IBERunAction.hh"

#include <iostream>
#include <fstream>
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IBERunAction::IBERunAction()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IBERunAction::~IBERunAction()
{//delete outFile;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IBERunAction::BeginOfRunAction(const G4Run* aRun)
{ 
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
  outFile=new ofstream("IBE_out_new.dat");
  G4cout << "OutFile Opened"<< G4endl;
  *outFile<<"Event #  index        E_beta [MeV] E_beta_plastic [keV] E_gamma_plastic [keV]  E_germanium [keV]"<< endl;
  *outFile<<"-----------------------------------------------------------------------------"<< endl;


  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(true);
    
  //initialize cumulative quantities
  //
  sumEAbs = sum2EAbs =sumEGap = sum2EGap = 0.;
  sumLAbs = sum2LAbs =sumLGap = sum2LGap = 0.; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IBERunAction::fillPerEvent(G4double EAbs, G4double EGap,
                                  G4double LAbs, G4double LGap)
{
  //accumulate statistic
  //
  sumEAbs += EAbs;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IBERunAction::EndOfRunAction(const G4Run* aRun)
{
  G4int NbOfEvents = aRun->GetNumberOfEvent();
  //*outFile<<"Para ti"<<endl;
  if (NbOfEvents == 0) return;
  
  
}
