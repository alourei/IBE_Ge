//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: IBEDetectorConstruction.hh,v 1.6 2006-06-29 17:47:13 gunter Exp $
// GEANT4 tag $Name: geant4-09-04-patch-02 $
//

#ifndef IBEDetectorConstruction_H
#define IBEDetectorConstruction_H 1

class G4LogicalVolume;
class G4VPhysicalVolume;

#include "G4VUserDetectorConstruction.hh"

class IBEDetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    IBEDetectorConstruction();
    ~IBEDetectorConstruction();


  G4VPhysicalVolume* Construct();
  G4VPhysicalVolume* Getplastic_phys(){return  plastic_phys;}
  G4VPhysicalVolume* GetGermanium_phys(){return  Germanium_phys;}
 
  private:
    
    // Logical volumes
    //
    G4LogicalVolume* experimentalHall_log;
    G4LogicalVolume* plastic_log;
    G4LogicalVolume* AluBox_L_log;
    G4LogicalVolume* AluBox_R_log;
    G4LogicalVolume* pet_tape_log;
    G4LogicalVolume* Ag_tape_log;
    
    //CENBG Germanium
    G4LogicalVolume* Germanium_Al_log;
    G4LogicalVolume* Germanium_log;

    // Physical volumes
    //
    G4VPhysicalVolume* experimentalHall_phys;
    G4VPhysicalVolume* plastic_phys;
    G4VPhysicalVolume* AluBox_L_phys;
    G4VPhysicalVolume* AluBox_R_phys;
    G4VPhysicalVolume* pet_tape_phys;
    G4VPhysicalVolume* Ag_tape_phys;
    
    //CENBG Germanium
    G4VPhysicalVolume* Germanium_Al_phys;
    G4VPhysicalVolume* Germanium_phys;
};
#endif

