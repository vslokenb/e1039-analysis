#include <iomanip>
#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
//#include <TH1D.h>
//#include <TCanvas.h>
#include <interface_main/SQRun.h>
#include <interface_main/SQEvent.h>
#include <interface_main/SQHitVector.h>
#include <fun4all/Fun4AllReturnCodes.h>
//#include <phool/PHNodeIterator.h>
//#include <phool/PHIODataNode.h>
//#include <phool/getClass.h>
#include <geom_svc/GeomSvc.h>
//#include <UtilAna/UtilSQHit.h>
#include "KJob.h"
#include "KScheduler.h"
#include "MultiThreadReco.h"
using namespace std;

MultiThreadReco::MultiThreadReco(const std::string& name)
  : SQReco(name)
  , m_out_file_name("multi_thread_reco.root")
  , m_save_raw_evt(false)
  , m_ksc(0)
//  , m_run         (0)
//  , m_spill_map   (0)
//  , m_evt         (0)
//  , m_hit_vec     (0)
//  , m_trig_hit_vec(0)
  , m_file(0)
  , m_tree(0)
  , m_srec(0)
{
  ;
}

MultiThreadReco::~MultiThreadReco()
{
  if (m_ksc) delete m_ksc;
}

int MultiThreadReco::Init(PHCompositeNode* topNode)
{
  return Fun4AllReturnCodes::EVENT_OK;
}

int MultiThreadReco::InitRun(PHCompositeNode* topNode)
{
  //if(is_eval_enabled()) {
  //  //InitEvalTree();
  //  //ResetEvalVars();
  //}

  //int ret = MakeNodes(topNode);
  //if(ret != Fun4AllReturnCodes::EVENT_OK) return ret;

  int ret = GetNodes(topNode);
  if (ret != Fun4AllReturnCodes::EVENT_OK) return ret;

  ret = InitField(topNode);
  if(ret != Fun4AllReturnCodes::EVENT_OK) return ret;

  ret = InitGeom(topNode);
  if(ret != Fun4AllReturnCodes::EVENT_OK) return ret;

//  InitFastTracking();

  if (_enable_KF) {
    if (_fitter_type == SQReco::LEGACY) {
      _kfitter = new KalmanFitter(_phfield, _t_geo_manager);
      _kfitter->setControlParameter(50, 0.001);
    } else {
      _gfitter = new SQGenFit::GFFitter();
      if      (_fitter_type == SQReco::KF    ) _gfitter->init(_gfield, "KalmanFitter");
      else if (_fitter_type == SQReco::KFREF ) _gfitter->init(_gfield, "KalmanFitterRefTrack");
      else if (_fitter_type == SQReco::DAF   ) _gfitter->init(_gfield, "DafSimple");
      else if (_fitter_type == SQReco::DAFREF) _gfitter->init(_gfield, "DafRef");
    }
  }

  m_ksc = new KScheduler("", m_out_file_name);
  //m_ksc->UseTrackletReco(true);
  m_ksc->SaveRawEvent(m_save_raw_evt);
  m_ksc->Init(_phfield, _t_geo_manager, _kfitter, _gfitter);

  //m_run       = findNode::getClass<SQRun     >(topNode, "SQRun");
  //m_spill_map = findNode::getClass<SQSpillMap>(topNode, "SQSpillMap");
  //if (!m_run || !m_spill_map) return Fun4AllReturnCodes::ABORTEVENT;
  //
  //m_evt          = findNode::getClass<SQEvent    >(topNode, "SQEvent");
  //m_hit_vec      = findNode::getClass<SQHitVector>(topNode, "SQHitVector");
  //m_trig_hit_vec = findNode::getClass<SQHitVector>(topNode, "SQTriggerHitVector");
  //if (!m_evt || !m_hit_vec || !m_trig_hit_vec) return Fun4AllReturnCodes::ABORTEVENT;

  ///
  /// Output
  ///
  //m_file = new TFile("result/output.root", "RECREATE");
  //m_tree = new TTree("tree", "Created by MultiThreadReco");
  //m_tree->Branch("det_name", &b_det_name, "det_name/C");
  //m_tree->Branch("det"     , &b_det     ,      "det/I");
  //m_tree->Branch("ele"     , &b_ele     ,      "ele/I");
  //m_tree->Branch("time"    , &b_time    ,     "time/D");

  m_ksc->runThreads();

  return Fun4AllReturnCodes::EVENT_OK;
}

int MultiThreadReco::process_event(PHCompositeNode* topNode)
{
  //if(is_eval_enabled()) ResetEvalVars();
  //if(is_eval_dst_enabled()) _tracklet_vector->clear();

  bool copy = true;
  if (_input_type == SQReco::E1039) {
    _rawEvent = BuildSRawEvent();
    copy = false;
  }

  m_ksc->PushEvent(_rawEvent, copy);

  //if(_eventReducer != nullptr) 
  //{
  //  _eventReducer->reduceEvent(_rawEvent);
  //  if(_input_type == SQReco::E1039) updateHitInfo(_rawEvent);
  //}

//  int finderstatus = _fastfinder->setRawEvent(_rawEvent);
//  if(_legacy_rec_container) 
//  {
//    _recEvent->setRawEvent(_rawEvent);
//    _recEvent->setRecStatus(finderstatus);
//  }
//  if(Verbosity() >= Fun4AllBase::VERBOSITY_A_LOT) _fastfinder->printTimers();
//
//  int nTracklets = 0;
//  int nFittedTracks = 0;
//  std::list<Tracklet>& rec_tracklets = _fastfinder->getFinalTracklets();
//  for(auto iter = rec_tracklets.begin(); iter != rec_tracklets.end(); ++iter)
//  {
//    iter->calcChisq();
//    if(Verbosity() > Fun4AllBase::VERBOSITY_A_LOT) iter->print();
//
//    bool fitOK = false;
//    if(_enable_KF)
//    {
//      if(_fitter_type == SQReco::LEGACY)
//        fitOK = fitTrackCand(*iter, _kfitter);
//      else
//        fitOK = fitTrackCand(*iter, _gfitter);
//    }
//
//    if(!fitOK)
//    {
//      SRecTrack recTrack = iter->getSRecTrack(_enable_KF && (_fitter_type == SQReco::LEGACY));
//      recTrack.setKalmanStatus(-1);
//      
//      fillRecTrack(recTrack);
//    }
//    else
//    {
//      ++nFittedTracks;
//    }
//
//    if(is_eval_enabled()) new((*_tracklets)[nTracklets]) Tracklet(*iter);
//    if(is_eval_dst_enabled()) _tracklet_vector->push_back(&(*iter));
//    ++nTracklets;
//  }

  //if(_input_type == SQReco::E1039) {
  //  delete _rawEvent;
  //  _rawEvent = 0;
  //}

  return Fun4AllReturnCodes::EVENT_OK;
}

int MultiThreadReco::End(PHCompositeNode* topNode)
{
  m_ksc->PushPoison();
  m_ksc->endThreads();
  
  return Fun4AllReturnCodes::EVENT_OK;
}
