#include <iostream>
#include <ctime>
#include <TSystem.h>


#include "AnaModule.h"
#include <fun4all/Fun4AllServer.h>
#include <fun4all/Fun4AllDstInputManager.h>
#include <fun4all/Fun4AllDstOutputManager.h>
#include <calibrator/CalibHitElementPos.h>
#include <calibrator/CalibDriftDist.h>
#include <ktracker/SQReco.h>
#include <ktracker/VertexFit.h>
#include <phool/recoConsts.h>


R__LOAD_LIBRARY(libinterface_main)
R__LOAD_LIBRARY(libfun4all)
R__LOAD_LIBRARY(libg4detectors)
R__LOAD_LIBRARY(libg4eval)
R__LOAD_LIBRARY(libcalibrator)
R__LOAD_LIBRARY(libktracker)
R__LOAD_LIBRARY(libanamodule)

int Fun4All(const int run_id, const int spill_id, const string DST_in, const string DST_out, const int n_evt=0, const bool do_displaced_tracking=true)
{

  cout << "E1039_RESOURCE = " << (gSystem->Getenv("E1039_RESOURCE") ? gSystem->Getenv("E1039_RESOURCE") : "NULL") << endl;
  cout << "E1039_CORE     = " << (gSystem->Getenv("E1039_CORE")     ? gSystem->Getenv("E1039_CORE")     : "NULL") << endl;
  cout << "E1039_SHARE    = " << (gSystem->Getenv("E1039_SHARE")    ? gSystem->Getenv("E1039_SHARE")    : "NULL") << endl;
  cout << "DST_in         = " << DST_in << endl;
  cout << "DST_out        = " << DST_out << endl;

  cout << "testing reco consts -1 "<<  endl;
  recoConsts* rc = recoConsts::instance();
  cout << "testing reco consts "<<  endl;
  rc->set_IntFlag("RUNNUMBER", run_id);
  rc->set_DoubleFlag("FMAGSTR", -1.044);
  rc->set_DoubleFlag("KMAGSTR", -1.025);
  rc->set_BoolFlag("COARSE_MODE", false);
  rc->set_BoolFlag("REQUIRE_MUID", false);
  rc->set_CharFlag("HIT_MASK_MODE", "X");
  cout << "testing reco consts 1.5 " << endl;
  rc->set_CharFlag("AlignmentMille", "config/align_mille_v10_a.txt");
  cout << "testing reco consts 1.5 " << endl;
  rc->set_CharFlag("AlignmentHodo", "");
  rc->set_CharFlag("AlignmentProp", "");
  rc->set_CharFlag("Calibration", "");
  cout << "testing reco consts 1.6 " << endl;
  rc->set_IntFlag ("MaxHitsDC0" , int(350)); // /3.0
  rc->set_IntFlag ("MaxHitsDC1" , int(350)); // /3.0
  rc->set_IntFlag ("MaxHitsDC2" , int(170)); // /3.0
  rc->set_IntFlag ("MaxHitsDC3p", int(140)); // /3.0
  rc->set_IntFlag ("MaxHitsDC3m", int(140)); // /3.0
  rc->set_DoubleFlag("RejectWinDC0" , 0.3);
  rc->set_DoubleFlag("RejectWinDC1" , 0.5);
  rc->set_DoubleFlag("RejectWinDC2" , 0.35);
  rc->set_DoubleFlag("RejectWinDC3p", 0.24);
  rc->set_DoubleFlag("RejectWinDC3m", 0.24);
  cout << "testing reco consts 2 " << endl;
  if (do_displaced_tracking)  
  {     
    rc->set_BoolFlag("TRACK_ELECTRONS", do_displaced_tracking);  
    rc->set_BoolFlag("TRACK_DISPLACED", do_displaced_tracking);   
  }
  cout << "testing reco consts 3" << endl;
  Fun4AllServer* se = Fun4AllServer::instance();
  // se->setRun(run_id);
  //se->Verbosity(1);

  CalibHitElementPos* cal_ele_pos = new CalibHitElementPos();
  cal_ele_pos->CalibTriggerHit(false);
  se->registerSubsystem(cal_ele_pos);
  cout << "testing post calib hit" << endl;
  //CalibHodoInTime* cal_hodo = new CalibHodoInTime();
  //cal_hodo->SkipCalibration();
  //cal_hodo->DeleteOutTimeHit();
  //se->registerSubsystem(cal_hodo);
  
  CalibDriftDist* cal_dd = new CalibDriftDist();
  //cal_dd->Verbosity(999);
  //cal_dd->DeleteOutTimeHit();
  se->registerSubsystem(cal_dd);
  cout << "testing sqreco" << endl;  
  SQReco* reco = new SQReco();
  //reco->Verbosity(99);
  reco->set_legacy_rec_container(true); // default = true
  reco->set_geom_file_name((string)gSystem->Getenv("E1039_RESOURCE") + "/geometry/geom_run005433.root");
  reco->set_enable_KF(true);
  reco->setInputTy(SQReco::E1039);
  reco->setFitterTy(SQReco::KFREF);
  reco->set_evt_reducer_opt("none"); // "ahs"
  reco->set_enable_eval_dst(true);
  cout << "testing for loop  "<<  endl;
  for (int ii = 0; ii <= 3; ii++) reco->add_eval_list(ii);
  reco->set_enable_eval(true);
  reco->set_eval_file_name("eval.root");
  se->registerSubsystem(reco);

  // SQVertexing* vtx = new SQVertexing();
  //vtx->Verbosity(99);
  //vtx->set_legacy_rec_container(true); // default = false
  //vtx->set_single_retracking(true);

  // se->registerSubsystem(vtx);

  // se->registerSubsystem(new SQVertexing("vtx_pm", +1, +1));
  // se->registerSubsystem(new SQVertexing("vtx_mm", -1, -1));
  cout << "testing vtx fit "<<  endl;
  VertexFit* vtx_fit = new VertexFit();
  vtx_fit->Verbosity(3);
  vtx_fit->set_eval_file_name("vtx_eval.root");
  se->registerSubsystem(vtx_fit);

  // se->registerSubsystem(new AnaDimuon());
  // se->registerSubsystem(new AnaDimuonLikeSign("AnaDimuonPP", "PP"));
  // se->registerSubsystem(new AnaDimuonLikeSign("AnaDimuonMM", "MM"));

  cout << "testing anamodule " <<  endl;
  AnaModule *ana = new AnaModule();
  ana->set_output_filename("outfile.root");
  ana->set_reco(true);
  // ana->set_additional_information(infile);
  se->registerSubsystem(ana);
  cout << "testing dst "<<  endl;
  Fun4AllDstInputManager* in = new Fun4AllDstInputManager("DSTIN");
  se->registerInputManager(in);
  in->fileopen(DST_in);

  Fun4AllDstOutputManager* out = new Fun4AllDstOutputManager("DSTOUT");
  se->registerOutputManager(static_cast<Fun4AllOutputManager*>(out));
  cout << "testing run "<<  endl;
  se->run(n_evt);
  se->End();
  //rc->WriteToFile("recoConsts.tsv");
  delete se;
  exit(0); //return 0;
}