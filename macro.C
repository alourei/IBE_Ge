{
  ifstream *in=new ifstream("IBE_out_new.dat");
  TH1F *h[3];
  Char_t dummy[256];
  Char_t histoname[256];
  Int_t evnumber,index;
  Double_t Ebeta,Epla,Egamma,Egermanium;
  Int_t coincidence=0;
  Int_t ngamma=0;
  Int_t nbeta=0;
  Int_t nevts=0;
  TTree *T=new TTree("t"," The IBE Tree");
  T->Branch("index",&index,"index/I");
  T->Branch("Ebeta",&Ebeta,"Ebeta/D");
  T->Branch("Epla",&Epla,"Epla/D");
  T->Branch("Egamma",&Egamma,"Egamma/D");
  T->Branch("Egermanium",&Egermanium,"Egermanium/D");
  for(Int_t k=0;k<3;k++){
    sprintf(histoname,"h%d",k);
    cout<<histoname<<endl;
    h[k]=new TH1F(histoname,"Energy in Ge detector;E [keV]",2000,1,2000);
    h[k]->SetLineColor(k+1);
  }
  in->getline(dummy,256);
  cout<<dummy<<endl;
  in->getline(dummy,256);
  cout<<dummy<<endl;
  while(*in>>evnumber>>index>>Ebeta>>Epla>>Egamma>>Egermanium){
    nevts++;
    if(Epla!=0 && Egermanium !=0)
      coincidence++;
    if(Epla!=0)
      nbeta++;
    if(Egermanium !=0){
      ngamma++;
      h[index]->Fill(Egermanium);
    }
    T->Fill();
  }
  cout<<"Total Events-> "<<nevts<<" beta events-> "<<nbeta<<" Efficiency-> "<<(Float_t)nbeta/nevts*100<<"%"<<endl;
  cout<<"Total Events-> "<<nevts<<" gamma events-> "<<ngamma<<" Efficiency-> "<<(Float_t)ngamma/nevts*100<<"%"<<endl;
  cout<<"Total Events-> "<<nevts<<" beta-gamma coicidences-> "<<coincidence<<" Efficiency-> "<<(Float_t)coincidence/nevts*100<<"%"<<endl;
  h[0]->Draw("");
  h[1]->Draw("same");
  h[2]->Draw("same");
}

