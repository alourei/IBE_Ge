

#ifndef IBESteppingAction_h
#define IBESteppingAction_h 1

#include "G4UserSteppingAction.hh"

class IBEDetectorConstruction;
class IBEEventAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class IBESteppingAction : public G4UserSteppingAction
{
public:
  IBESteppingAction(IBEDetectorConstruction*, IBEEventAction*);
  virtual ~IBESteppingAction();

  void UserSteppingAction(const G4Step*);
    
private:
  IBEDetectorConstruction* detector;
  IBEEventAction*          eventaction;  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
