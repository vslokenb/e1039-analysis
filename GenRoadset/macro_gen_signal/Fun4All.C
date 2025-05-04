#include <top/G4_Beamline.C>
#include <top/G4_Target.C>
#include <top/G4_InsensitiveVolumes.C>
#include <top/G4_SensitiveDetectors.C>
R__LOAD_LIBRARY(libfun4all)
R__LOAD_LIBRARY(libg4detectors)
R__LOAD_LIBRARY(libg4testbench)
R__LOAD_LIBRARY(libg4eval)
R__LOAD_LIBRARY(libg4dst)
R__LOAD_LIBRARY(libSQPrimaryGen)
R__LOAD_LIBRARY(libGenRoadset)
using namespace std;

int Fun4All(const int n_evt=0, double st3_pos_dif=0.,const int KMag_polarity=+1, const double KMag_scale=1.0)
{
  recoConsts *rc = recoConsts::instance();
  const int run_id = 5433;//5433; // To select the plane geometry.
  double FMAGSTR = -1.044; // -1.054; F&KMAGSTR were changed on 2024-06-28
  double KMAGSTR = -1.025 * KMag_scale * KMag_polarity; // -0.951
  std::cout << st3_pos_dif << std::endl;
  rc->set_IntFlag("RUNNUMBER", run_id);
  rc->set_DoubleFlag("FMAGSTR", FMAGSTR);
  rc->set_DoubleFlag("KMAGSTR", KMAGSTR);
  rc->set_CharFlag("VTX_GEN_MATERIAL_MODE", "Target");
  rc->set_DoubleFlag("Z_ST3",1910+st3_pos_dif);
  if (st3_pos_dif > -75){
	    rc->set_DoubleFlag("ST3_HM_scaling_factor", 1.0);
    }
  if (st3_pos_dif<=-75 && st3_pos_dif>-125){
    rc->set_DoubleFlag("ST3_HM_scaling_factor", 1.5);
    }
  if (st3_pos_dif<=-125 && st3_pos_dif>-225){
    rc->set_DoubleFlag("ST3_HM_scaling_factor", 2.0);
    }
  //GeomSvc::UseDbSvc(true);
  GeomSvc *geom_svc = GeomSvc::instance();
  /*
  std::cout << "print geometry information" << std::endl;
  geom_svc->printWirePosition();
  std::cout << " align printing " << std::endl;
  geom_svc->printAlignPar();
  std::cout << " table printing" << std::endl;
  geom_svc->printTable();
  std::cout << "done geometry printing" << std::endl;
  */
  std::vector<std::string> St3detectors={"D3mU","D3mUp","D3mX","D3mXp","D3mV","D3mVp","D3pU","D3pUp","D3pX","D3pXp","D3pV","D3pVp","H3B","H3T"};
  for (auto det : St3detectors){
    geom_svc->setDetectorZ0(det, geom_svc->getDetectorZ0(det)+st3_pos_dif);
    int id=geom_svc->getDetectorID(det);
    if (id <= 0) {
      cout << "Detector not found: " << det << endl;
      continue;
    }
    double z0 = geom_svc->getDetectorZ0(det);
    int nelements = geom_svc->getPlaneNElements(id);

    cout << "  " << det
         << " | ID: " << id
         << " | Z0: " << fixed << setprecision(2) << z0
         << " | N_elements: " << nelements
         << endl;
    cout << "=============================" << endl;
    //geom_svc->getPlane(id).z0=geom_svc->getDetectorZ0(det)+st3_pos_dif;
    //geom_svc->initWireLUT();
    //std::cout<<"detector: "<<det<<" ID: "<<geom_svc->getDetectorID(det)<<" Z0: "<<geom_svc->getDetectorZ0(det)<<std::endl;
  } 
  
  // I THINK THIS RECO CONSTS WILL HANDLE IT ALL :), need to update
  Fun4AllServer *se = Fun4AllServer::instance();

  
  se->Verbosity(1);

  ///
  /// Global parameters
  ///

  

  ///
  /// Event generator
  ///
  const int gen_switch = 1;
  SQPrimaryParticleGen* sq_gen = new SQPrimaryParticleGen();
  switch (gen_switch) {
  case 1: // Drell-Yan: 500 events = 1 hour
    sq_gen->set_massRange(0.5, 9.0);
    sq_gen->set_xfRange(0.00, 0.95);
    sq_gen->enableDrellYanGen();
    break;
  case 2: // J/psi: 500 events = 2 hours
    sq_gen->set_xfRange(0.2, 1.0);
    sq_gen->enableJPsiGen();
    break;
  case 3: // psi'
    sq_gen->set_xfRange(0.2, 1.0); // Not tuned yet
    sq_gen->enablePsipGen();
    break;
  }
  se->registerSubsystem(sq_gen);

  ///
  /// Detector setting
  ///
  PHG4Reco *g4Reco = new PHG4Reco();
  g4Reco->set_field_map(
      rc->get_CharFlag("fMagFile")+" "+
      rc->get_CharFlag("kMagFile")+" "+
      Form("%f",FMAGSTR) + " " +
      Form("%f",KMAGSTR) + " " +
      "5.0",
      PHFieldConfig::RegionalConst);
  g4Reco->SetWorldSizeX(1000);
  g4Reco->SetWorldSizeY(1000);
  g4Reco->SetWorldSizeZ(5000);
  g4Reco->SetWorldShape("G4BOX");
  g4Reco->SetWorldMaterial("G4_AIR"); //G4_Galactic, G4_AIR
  g4Reco->SetPhysicsList("FTFP_BERT");

  g4Reco->Print("ALL"); //DEBUG PRINT

  SetupInsensitiveVolumes(g4Reco);
  SetupBeamline(g4Reco);
  SetupTarget(g4Reco);
  SetupSensitiveDetectors(g4Reco,true,false,"SQ_ArCO2","SQ_Scintillator",2);

  se->registerSubsystem(g4Reco);

  PHG4TruthSubsystem *truth = new PHG4TruthSubsystem();
  g4Reco->registerSubsystem(truth);

  /// digitizer
  SQDigitizer *digitizer = new SQDigitizer("DPDigitizer", 0);
  digitizer->set_enable_st1dc(false);
  digitizer->set_enable_dphodo(false); 
  se->registerSubsystem(digitizer);

  /// Save only events that are in the geometric acceptance.
  SQGeomAcc* geom_acc = new SQGeomAcc();
  geom_acc->SetMuonMode(SQGeomAcc::PAIR);
  geom_acc->SetPlaneMode(SQGeomAcc::HODO_CHAM);
  geom_acc->SetNumOfH1EdgeElementsExcluded(4);
  se->registerSubsystem(geom_acc);
  
  // Make SQ nodes for truth info
  TruthNodeMaker* tnm = new TruthNodeMaker();
  se->registerSubsystem(tnm);

  SubsysRecoSignal* sr_sig = new SubsysRecoSignal();
  se->registerSubsystem(sr_sig);

  ///
  /// Input, output and execution
  ///
  Fun4AllInputManager* man_in = new Fun4AllDummyInputManager("DUMMY");
  se->registerInputManager(man_in);

  const bool count_only_good_events = true;
  se->run(n_evt, count_only_good_events);
  
  se->End();
  se->PrintTimer();
  rc->WriteToFile("recoConsts.tsv");
  std::cout << "All done" << std::endl;
  delete se;
  gSystem->Exit(0);
  return 0;
}
