#ifndef _TREE_DATA__H_
#define _TREE_DATA__H_
#include <vector>
#include <TROOT.h>
#include <TLorentzVector.h>

struct EventData {
  short run_id;
  int   spill_id;
  int   event_id;
  short fpga_bits;
  short nim_bits;
  short D1;
  short D2;
  short D3p;
  short D3m;

  EventData();
  virtual ~EventData() {;}
  ClassDef(EventData, 1);
};

struct DimuonData {
  TVector3       pos;
  TLorentzVector mom;
  short          n_hits_pos;
  double         chisq_pos ;
  TVector3       pos_pos   ;
  TLorentzVector mom_pos   ;
  short          n_hits_neg;
  double         chisq_neg ;
  TVector3       pos_neg   ;
  TLorentzVector mom_neg   ;
  
  DimuonData();
  virtual ~DimuonData() {;}
  ClassDef(DimuonData, 1);
};

typedef std::vector<DimuonData> DimuonList;

#endif // _TREE_DATA__H_
