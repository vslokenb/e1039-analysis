R__LOAD_LIBRARY(AnaRealDst)

/// Fun4All macro to analyze spill-by-spill DST files of multiple runs.
int Fun4AllRunSpillDST(const char* fn_list="list_run.txt", const int nevent=0)
{
  Fun4AllServer* se = Fun4AllServer::instance();
  se->setRun(run_id);
  //se->Verbosity(1);

  Fun4AllInputManager *in = new Fun4AllDstInputManager("DST");
  se->registerInputManager(in);

  //se->registerSubsystem(new AnaHodoHit());
  //se->registerSubsystem(new AnaTriggerHit());
  se->registerSubsystem(new AnaTrigSignal());
  //se->registerSubsystem(new AnaRealDst());
  //se->registerSubsystem(new AnaEffHodo());
  //se->registerSubsystem(new AnaEffCham(AnaEffCham::D3p));
  //se->registerSubsystem(new AnaHardEvent());

  ifstream ifs(fn_list);
  int run_id;
  while (ifs >> run_id) {
    cout << "Run " << run_id << endl;
    auto list_dst = UtilMine::GetListOfSpillDSTs(run_id);
    for (auto it = list_dst.begin(); it != list_dst.end(); it++) {
      string fn_in = *it;
      cout << "  DST file = " << fn_in << endl;
      in->fileopen(fn_in);
      se->run(nevent);
    }
  }
  se->End();
  delete se;
  exit(0); //return 0;
}
