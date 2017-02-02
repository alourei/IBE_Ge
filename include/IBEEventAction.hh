

#ifndef IBEEventAction_h
#define IBEEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class IBERunAction;
class IBEPrimaryGeneratorAction;
//class EventActionMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class IBEEventAction : public G4UserEventAction
{
public:
  IBEEventAction(IBERunAction*,IBEPrimaryGeneratorAction*);
  virtual ~IBEEventAction();

  void  BeginOfEventAction(const G4Event*);
  void    EndOfEventAction(const G4Event*);
    
  void AddPlasticBeta(G4double de) {EnergyBeta += de;};
  void AddPlasticGamma(G4double de) {EnergyGamma += de;};
  void AddGermaniumGamma(G4double de) {EnergyGermanium += de;};
                       
  void SetPrintModulo(G4int    val)  {printModulo = val;};
    
private:
  IBERunAction*  runAct;
  IBEPrimaryGeneratorAction *primGenAct;
   
  G4double  EnergyBeta,EnergyGamma,EnergyGermanium;
  
  G4int     printModulo;
                             
  //EventActionMessenger*  eventMessenger;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
