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
// $Id: IBEDetectorConstruction.cc,v 1.9 2006-06-29 17:47:19 gunter Exp $
// GEANT4 tag $Name: geant4-09-04-patch-02 $
//

#include "IBEDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "globals.hh"

IBEDetectorConstruction::IBEDetectorConstruction()
 :  experimentalHall_log(0), plastic_log(0),
    AluBox_L_log(0), AluBox_R_log(0),
    experimentalHall_phys(0), plastic_phys(0),
    AluBox_L_phys(0), AluBox_R_phys(0)
{;}

IBEDetectorConstruction::~IBEDetectorConstruction()
{
}

G4VPhysicalVolume* IBEDetectorConstruction::Construct()
{

  //------------------------------------------------------ materials

  G4double a;  // atomic mass
  G4double z;  // atomic number
  G4double density;
  G4int ncomponents, natoms;
  G4double fractionmass;

  G4Material* Vacuum =
    new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
		   kStateGas, 3.e-18*pascal, 2.73*kelvin);
  Vacuum->SetChemicalFormula("NOMATTER");

  G4Element* N  = new G4Element("Nitrogen" ,"N" , z= 7., a=  14.00674*g/mole);
  G4Element* O  = new G4Element("Oxygen"   ,"O" , z= 8., a=   15.9994*g/mole);

  density = 1.290*g/cm3;
  G4Material* Air =
  new G4Material("Air", density, ncomponents=2);
  Air->AddElement(N, fractionmass=70.*perCent);
  Air->AddElement(O, fractionmass=30.*perCent);

    
    
    G4Material* Al = 
  new G4Material("Aluminum", z= 13., a= 26.98*g/mole, density= 2.7*g/cm3);

  G4Material* Ag = 
  new G4Material("Silver", z= 47., a= 107.8682*g/mole, density=10.49*g/cm3);

  G4Material* Ge =
    new G4Material("Germanium", z= 32., a= 72.63*g/mole, density= 5.323*g/cm3);
    
  //Define BC400
  G4Element* elC  = new G4Element("Carbon","C" , z= 6., a=12.01*g/mole);
  G4Element* elH  = new G4Element("Hydrogen","H" , z= 1., a=1.008*g/mole);

  G4Material* Scint = new G4Material("Scint",density=1.02*g/cm3,ncomponents=2);
  Scint->AddElement(elC, fractionmass=91.53*perCent);
  Scint->AddElement(elH, fractionmass=8.47*perCent);

  //Define PET
  G4Element* elO  = new G4Element("Oxygen","O" , z= 8., a=15.9994*g/mole);

  G4Material *PET=new G4Material("PET",density=1.4*g/cm3,ncomponents=3);
  PET->AddElement(elC,fractionmass=62.5*perCent);
  PET->AddElement(elH,fractionmass=4.2*perCent);
  PET->AddElement(elO,fractionmass=33.3*perCent);
    

  //------------------------------------------------------ volumes

  //------------------------------ experimental hall (world volume)
  //------------------------------ beam line along x axis

  G4double expHall_x = 1.25*m;
  G4double expHall_y = 1.25*m;
  G4double expHall_z = 1.25*m;
  G4Box* experimentalHall_box
    = new G4Box("expHall_box",expHall_x,expHall_y,expHall_z);
  
  //experimentalHall_log = new G4LogicalVolume(experimentalHall_box,
  //Vacuum,"expHall_log",0,0,0);
  
  experimentalHall_log = new G4LogicalVolume(experimentalHall_box,
                                               Air,"expHall_log",0,0,0);
  experimentalHall_log ->SetVisAttributes (G4VisAttributes::Invisible);
  experimentalHall_phys = new G4PVPlacement(0,G4ThreeVector(),
					    experimentalHall_log,"expHall",0,false,0);
  

  //------------------------------ the Aluminium box
  G4double box_x = 51*mm;
  G4double box_y = 155*mm;
  G4double box_z = 60*mm;

  G4Box *Alu_box = new G4Box("Alu_box",box_x,box_y,box_z);
  G4VisAttributes* AluBoxVisAtt = new G4VisAttributes(G4Colour(160.0,160.0,160.0));
  AluBoxVisAtt->SetVisibility(true);
  
  G4LogicalVolume *Alu_box_log = new G4LogicalVolume(Alu_box,Al,"AluBox_log",0,0,0);
    
  G4double box_PosX =0.*mm; 
  G4double box_PosY =0.*mm;
  G4double box_PosZ =0.*mm;
    
  G4VPhysicalVolume *Alu_box_phys = new G4PVPlacement(0,G4ThreeVector(box_PosX,box_PosY,box_PosZ),Alu_box_log,"Alu_Box_phys",experimentalHall_log,false,0);

 
 
    
  //------------------------------ the vacuum inside the box  
  G4double vac_box_x = 34.5*mm;
  G4double vac_box_y = 138.5*mm;
  G4double vac_box_z = 43.5*mm;
    
  G4Box *Vac_box = new G4Box("Vac_box",vac_box_x,vac_box_y,vac_box_z);
  G4VisAttributes* VacBoxVisAtt = new G4VisAttributes(G4Colour(2.0,1.0,1.0));
  VacBoxVisAtt->SetVisibility(true);
    
  G4LogicalVolume *Vac_box_log = new G4LogicalVolume(Vac_box,Vacuum,"VacBox_log",0,0,0);
    
  G4double vac_box_PosX =0.*mm; 
  G4double vac_box_PosY =0.*mm;
  G4double vac_box_PosZ =0.*mm;
 
  G4VPhysicalVolume *Vac_box_phys = new G4PVPlacement(0,G4ThreeVector(vac_box_PosX,vac_box_PosY,vac_box_PosZ),Vac_box_log,"Vac_Box_phys",Alu_box_log,false,0);


  //------------------------------ the Flange
    
  G4double flange_outer_radius = 50*mm;
  G4double flange_inner_radius = 0*mm;
  G4double flange_length = 7.75*mm;
  G4double startAngle = 0.*deg;
  G4double spanningAngle = 360.*deg;
    
  G4Tubs *flange = new G4Tubs("Flange",flange_inner_radius,flange_outer_radius,flange_length,startAngle,spanningAngle);
    G4VisAttributes* flangeVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    flangeVisAtt->SetVisibility(true);
    
    G4LogicalVolume* flange_log = new G4LogicalVolume(flange,Air,"flange_log",0,0,0);
    
    flange_log->SetVisAttributes(flangeVisAtt);
    
    G4double flangePosZ=0*cm;
    G4double flangePosY=0*cm;
    G4double flangePosX=-43.40*mm;
  
    G4RotationMatrix *rot=0;
    rot=new G4RotationMatrix(90*deg,90.*deg,0.);

    G4VPhysicalVolume* flange_phys=new G4PVPlacement(rot,G4ThreeVector(flangePosX,flangePosY,flangePosZ),flange_log,"Flange",Alu_box_log,false,0);

    
    
  //------------------------------ the aliminium plates
    
  G4double block_x = 0.5*mm;
  G4double block_y = 50*mm;
  G4double block_z = 50*mm;
  G4Box* Alu_box_L = new G4Box("Alu_box_L",block_x,
			       block_y,block_z);
  AluBox_L_log = new G4LogicalVolume(Alu_box_L,
				     Al,"AluBox_L_log",0,0,0);
  AluBox_L_log->SetVisAttributes(AluBoxVisAtt);
  G4double blockPos_x = -21.*mm;
  G4double blockPos_y = 0.0*mm;
  G4double blockPos_z = 0.0*mm;
  //AluBox_L_phys = new G4PVPlacement(0,
  //           G4ThreeVector(blockPos_x,blockPos_y,blockPos_z),
  //           AluBox_L_log,"AluBox_LB",experimentalHall_log,false,0);

 
  G4Box* Alu_box_R = new G4Box("Alu_box_R",block_x,
                                          block_y,block_z);
  AluBox_R_log = new G4LogicalVolume(Alu_box_R,
                                             Al,"AluBox_R_log",0,0,0);
  AluBox_R_log->SetVisAttributes(AluBoxVisAtt);
 
 blockPos_x = 21.*mm;
  
  //AluBox_R_phys = new G4PVPlacement(0,
  //           G4ThreeVector(blockPos_x,blockPos_y,blockPos_z),
  //           AluBox_R_log,"AluBox_RB",experimentalHall_log,false,0);


  //------------------------------ plastic Scintillator

  G4double sci_x = 1.5*mm;
  G4double sci_y = 2.*cm;
  G4double sci_z = 2.*cm;
  G4Box* scint_box = new G4Box("plastic",
			       sci_x,sci_y,sci_z);

  G4VisAttributes* SciVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));
  SciVisAtt->SetVisibility(true);
  plastic_log = new G4LogicalVolume(scint_box,
                                             Scint,"sci_log",0,0,0);
  plastic_log->SetVisAttributes(SciVisAtt);


  G4double sciPos_x = 0.0*cm;
  G4double sciPos_y = 0.0*m;
  G4double sciPos_z = 0.0*m;
  plastic_phys = new G4PVPlacement(0,
				   G4ThreeVector(sciPos_x,sciPos_y,sciPos_z),
				   plastic_log,"Plastic",Vac_box_log,false,0);

  //---------------------------------the tape
  G4double pet_x=18.0*um;
  G4double pet_y=138.5*mm;
  G4double pet_z=7.5*mm;

  G4Box *pet_tape=new G4Box("tape",pet_x,pet_y,pet_z);
  G4VisAttributes* TapeVisAtt= new G4VisAttributes(G4Colour(1.0,0.0,1.0));
  TapeVisAtt->SetVisibility(true);

  pet_tape_log=new G4LogicalVolume(pet_tape,PET,"tape_log",0,0,0);

  pet_tape_log->SetVisAttributes(TapeVisAtt);

  G4double tapePos_x = -6*mm;
  G4double tapePos_y = 0.0*m;
  G4double tapePos_z = 0.0*m;
  pet_tape_phys=new G4PVPlacement(0,
  				   G4ThreeVector(tapePos_x,tapePos_y,tapePos_z),
  				   pet_tape_log,"PET_TAPE",Vac_box_log,false,0);

  //---------------------------------the silver tape (Al)
  G4double Ag_x=0.5*um;
  G4double Ag_y=138.5*mm;
  G4double Ag_z=7.5*mm;

  G4Box *Ag_tape=new G4Box("Ag_tape",Ag_x,Ag_y,Ag_z);
  G4VisAttributes* AgVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,1.0));
  AgVisAtt->SetVisibility(true);

  Ag_tape_log=new G4LogicalVolume(Ag_tape,Al,"Agtape_log",0,0,0);

  Ag_tape_log->SetVisAttributes(AgVisAtt);

  G4double AgtapePos_x = -6*mm-18*um-0.5*um;
  G4double AgtapePos_y = 0.0*m;
  G4double AgtapePos_z = 0.0*m;
  Ag_tape_phys=new G4PVPlacement(0,
				   G4ThreeVector(AgtapePos_x,AgtapePos_y,AgtapePos_z),
				   Ag_tape_log,"Ag_TAPE",Vac_box_log,false,0);

  //---------------------------------the CENBG Germanium (Al)
  G4double Ge_al_outer_radius = 40*mm;
  G4double Ge_al_inner_radius = 0*mm;
  G4double Ge_al_length = 5*cm; 
  //G4double startAngle = 0.*deg;
  //G4double spanningAngle = 360.*deg;

  G4Tubs *Ge_al_cover=new G4Tubs("Ge_Al_cover",Ge_al_inner_radius,Ge_al_outer_radius,Ge_al_length,startAngle,spanningAngle);
  G4VisAttributes* Ge_alVisAtt= new G4VisAttributes(G4Colour(0.0,0.5,1.0));
  Ge_alVisAtt->SetVisibility(true);
   
  Germanium_Al_log=new G4LogicalVolume(Ge_al_cover,Al,"Ge_al_log",0,0,0);
  
  Germanium_Al_log->SetVisAttributes(Ge_alVisAtt); 

  G4double Ge_alPosX=-25*cm;
  G4double Ge_alPosY=0*cm;
  G4double Ge_alPosZ=0.*cm;
    
                    
  Germanium_Al_phys=new G4PVPlacement(rot,G4ThreeVector(Ge_alPosX,Ge_alPosY,Ge_alPosZ),Germanium_Al_log,"Ge_COVER",experimentalHall_log,false,0);
  
  //---------------------------------the CENBG Germanium (Vacuum)
    
  G4double Ge_vacuum_outer_radius = 38*mm;
  G4double Ge_vacuum_inner_radius = 0*mm;
  G4double Ge_vacuum_length = 4.45*cm;
  
  G4Tubs *Ge_vacuum = new G4Tubs("Ge_vacuum",Ge_vacuum_inner_radius,Ge_vacuum_outer_radius,Ge_vacuum_length,startAngle,spanningAngle);
  G4VisAttributes* Ge_vacVisAtt= new G4VisAttributes(G4Colour(0.5,1.0,1.0));
  Ge_vacVisAtt->SetVisibility(true);
  
  G4LogicalVolume* Ge_vacuum_log = new G4LogicalVolume(Ge_vacuum,Vacuum,"Ge_vacuum_log",0,0,0);
    
  Ge_vacuum_log->SetVisAttributes(Ge_vacVisAtt);
 
  G4double Ge_vacPosX=0*cm;
  G4double Ge_vacPosY=0*cm;
  G4double Ge_vacPosZ=0.*cm;

  G4VPhysicalVolume* Ge_vac_phys=new G4PVPlacement(0,G4ThreeVector(Ge_vacPosX,Ge_vacPosY,Ge_vacPosZ),Ge_vacuum_log,"Ge_vacuum",Germanium_Al_log,false,0);
    
  //---------------------------------the CENBG Germanium (Detector)
  
  G4double Ge_detector_inner_radius = 0.*mm;   
  G4double Ge_detector_outer_radius = 35.*mm;   
  G4double Ge_detector_lenth = 3.9*cm;   
   
  G4Tubs *Ge_detector=new G4Tubs("Ge_detector",Ge_detector_inner_radius,Ge_detector_outer_radius,Ge_detector_lenth,startAngle,spanningAngle);
  G4VisAttributes* Ge_detVisAtt= new G4VisAttributes(G4Colour(1.0,0.,0.));
  Ge_detVisAtt->SetVisibility(true);
  
  Germanium_log=new G4LogicalVolume(Ge_detector,Ge,"Ge_detector_log",0,0,0);
 
  Germanium_log->SetVisAttributes(Ge_detVisAtt);
  
  G4double Ge_detPosX = 0.*cm;
  G4double Ge_detPosY = 0.*cm;
  G4double Ge_detPosZ = 1.*cm;
  
  Germanium_phys=new G4PVPlacement(0,G4ThreeVector(Ge_detPosX,Ge_detPosY,Ge_detPosZ),Germanium_log,"Ge_detector",Ge_vacuum_log,false,0);
    
    return experimentalHall_phys;
}

