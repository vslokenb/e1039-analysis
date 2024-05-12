#ifndef _MULTI_THREAD_RECO__H_
#define _MULTI_THREAD_RECO__H_
#include <fun4all/SubsysReco.h>
#include <ktracker/SQReco.h>
class TFile;
class TTree;
class KScheduler;
//class SQRun;
//class SQSpillMap;
//class SQEvent;
//class SQHitVector;
//class SRecEvent;

class MultiThreadReco: public SQReco {
  std::string m_out_file_name;
  bool m_save_raw_evt;

  KScheduler* m_ksc;

  // SQReco
  //SQRun*       _run_header;
  //SQSpillMap*  _spill_map;
  //SQEvent*     _event_header;
  //SQHitVector* _hit_vector;
  //SQHitVector* _triggerhit_vector;

  TFile* m_file;
  TTree* m_tree;
  SRecEvent* m_srec;

 public:
  MultiThreadReco(const std::string& name="MultiThreadReco");
  virtual ~MultiThreadReco();

  void SetOutputFileName(const std::string name) { m_out_file_name = name; }
  void SaveRawEvent(const bool save) { m_save_raw_evt = save; }

  int Init(PHCompositeNode *topNode);
  int InitRun(PHCompositeNode *topNode);
  int process_event(PHCompositeNode *topNode);
  int End(PHCompositeNode *topNode);
};

#endif // _MULTI_THREAD_RECO__H_
