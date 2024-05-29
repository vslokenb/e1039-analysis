#ifndef _ANA_HARD_EVENT__H_
#define _ANA_HARD_EVENT__H_
#include <fstream>
#include <fun4all/SubsysReco.h>
class TFile;
class TTree;
class TH1;
class TH2;
class SQEvent;
class SQHardEvent;

/// An example class to analyze the hardware-event info.
class AnaHardEvent: public SubsysReco {
  SQEvent* m_evt;
  SQHardEvent* m_hard_evt;

  std::ofstream m_ofs;
  TFile* m_file;
  TTree* m_tree;
  int    b_det;
  int    b_ele;
  double b_time;
  TH1*   m_h1_n_ttdc;

 public:
  AnaHardEvent(const std::string& name="AnaHardEvent");
  virtual ~AnaHardEvent() {;}
  int Init(PHCompositeNode *topNode);
  int InitRun(PHCompositeNode *topNode);
  int process_event(PHCompositeNode *topNode);
  int End(PHCompositeNode *topNode);
};

#endif // _ANA_HARD_EVENT__H_
