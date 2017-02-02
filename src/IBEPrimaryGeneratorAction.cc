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
// $Id: IBEPrimaryGeneratorAction.cc,v 1.6 2006-06-29 17:47:23 gunter Exp $
// GEANT4 tag $Name: geant4-09-04-patch-02 $
//
#include <fstream>

#include "IBEPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "globals.hh"
using namespace std;
IBEPrimaryGeneratorAction::IBEPrimaryGeneratorAction()
{
  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e+"));
  //particleGun->SetParticleEnergy(2*MeV);
  //particleGun->SetParticlePosition(G4ThreeVector(-6.0*mm-12.5*um, 0.0, 0.0));
  //Setting random Position inside the gas box
  G4double X0=-34.5+69*G4UniformRand();
  G4double Y0=-138.5+177*G4UniformRand();
  G4double Z0=-43.5+87*G4UniformRand();
  particleGun->SetParticlePosition(G4ThreeVector(X0*mm,Y0*mm,Z0*mm));

}

IBEPrimaryGeneratorAction::~IBEPrimaryGeneratorAction()
{
  delete particleGun;
}

void IBEPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4double cosTheta;
  G4double phi = twopi*G4UniformRand();
  G4double sinTheta;
  G4int index=0;
  cosTheta = -1.0 + 2.0*G4UniformRand();
  sinTheta = sqrt(1 - cosTheta*cosTheta);

  G4double cosTheta2;
  G4double phi2 = twopi*G4UniformRand();
  G4double sinTheta2;
  cosTheta2 = -1.0 + 2.0*G4UniformRand();
  sinTheta2 = sqrt(1 - cosTheta2*cosTheta2);
  //these are the cosines for an isotropic direction
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e+"));
  EnergyBeta=BetaSpec(&index,"ne18.inp")*MeV;
  //EnergyBeta=BetaSpec(&index,"geoff.inp")*MeV;
  BRindex=index;
  particleGun->SetParticleEnergy(EnergyBeta);
  particleGun -> SetParticleMomentumDirection(G4ThreeVector(sinTheta*cos(phi),sinTheta*sin(phi),cosTheta));
  particleGun->GeneratePrimaryVertex(anEvent);
  if(index>0){
  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
  particleGun -> SetParticleMomentumDirection(G4ThreeVector(sinTheta2*cos(phi2),sinTheta2*sin(phi2),cosTheta2));
  if(index==1)
    particleGun->SetParticleEnergy(1.0415*MeV);
  else
    particleGun->SetParticleEnergy(1.7008*MeV);
  particleGun->GeneratePrimaryVertex(anEvent);
  }
 
  
}



G4double IBEPrimaryGeneratorAction::BetaSpec(G4int *index,char *input_file){
  G4double Z,A,Qvalue;
  G4int NBranch=0;
  G4double Ex[32],BR[32],BRsum=0,Nsum[32];
G4double me= 0.511003;
  G4double Q,Te,N[32][10000];
  G4int step=20;
  ifstream *in =new ifstream(input_file);
  //ofstream *out=new ofstream("test.dat");
  
 if(!in){
   //cout<< "Can't access file "<<input_file<<endl;
    return -1;
  }
  *in>>Z>>A>>Qvalue;
  while(*in>>Ex[NBranch]>>BR[NBranch]){
    BRsum+=BR[NBranch];
    NBranch++;
  }
  
  G4double RAN=G4UniformRand()*BRsum;
  //cout<<RAN<<" "<<BRsum<<endl;

for(int j=0;j<NBranch;j++){
  //  *out<<"*******************************************************" <<endl;
  Nsum[j]=0.0; 
  Q=Qvalue-Ex[j];
  G4double MaxE=Q*1000;
  for(G4int i=0;i<=MaxE;i+=step){
    Te=(G4double)i/1000.;
    if(i<10000){
      N[j][i]=sqrt(Te*Te+2*Te*me)*(Q-Te)*(Q-Te)*(Te+me*me);
      Nsum[j]+=N[j][i];
    }
  }
  G4double sum=0;
  for(G4int i=0;i<=MaxE;i+=step)
    if(i<10000){
      Te = (G4double)i/1000.0;
      N[j][i] = N[j][i]/Nsum[j]*BR[j];
      sum+= N[j][i];
      //*out<<Te<<"\t"<<N[j][i]<<"\t"<<sum<<endl;
    }
 }
 G4double sum=0;
 G4double Ebeta;
 //G4int index;
 for(int j=0;j<NBranch;j++){ 
   Q=Qvalue-Ex[j];
  G4double MaxE=Q*1000;  
  for(G4int i=0;i<=MaxE;i+=step)
     if(i<10000){
       Te = (G4double)i/1000.0;
       sum+= N[j][i];
       if(sum>=RAN){
       	 Ebeta = (G4double)(i+step)/1000.0;
	 *index=j;
       	 break;
       }
       //cout<<Te<<"\t"<<N[j][i]<<"\t"<<sum<<endl;
     }
      if(sum>=RAN)break;
 }      
 //G4cout<<"======>"<<*index<<" "<<RAN<<"\t"<<Ebeta<<G4endl;
 delete in;
 return Ebeta;
 }
  


