//Run action class for the IBE simulation
//D. Perez-Loureiro Jan2012
//Based on Exn03

#ifndef IBERunAction_h
#define IBERunAction_h 1
#include <iostream>
#include <fstream>
#include "G4UserRunAction.hh"
#include "globals.hh"
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//class ofstream;
class G4Run;

class IBERunAction : public G4UserRunAction
{
public:
  IBERunAction();
  virtual ~IBERunAction();

  void BeginOfRunAction(const G4Run*);
  void   EndOfRunAction(const G4Run*);
    
  void fillPerEvent(G4double, G4double, G4double, G4double); 
  ofstream *GetOutFilePtr(){return outFile;};

private:
  ofstream *outFile;
  G4double sumEAbs, sum2EAbs;
  G4double sumEGap, sum2EGap;
    
  G4double sumLAbs, sum2LAbs;
  G4double sumLGap, sum2LGap;    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
