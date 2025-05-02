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

int Fun4All(const int n_evt=0, const int KMag_polarity=+1, const double KMag_scale=1.0, double st3_pos_dif=0 )
{
  recoConsts *rc = recoConsts::instance();
  GeomSvc::UseDbSvc(true);
  GeomSvc *geom_svc = GeomSvc::instance();
  std::vector<std::string> St3detectors={"D3mU","D3mUp","D3mX","D3mXp","D3mV","D3mVp","D3pU","D3pUp","D3pX","D3pXp","D3pV","D3pVp","H3B","H3T"};
  for (auto det : St3detectors){
    geom_svc->setDetectorZ0(det, geom_svc->getDetectorZ0(det)+st3_pos_dif);
    //int id=geom_svc->getDetectorID(det);
    //geom_svc->getPlane(id).z0=geom_svc->getDetectorZ0(det)+st3_pos_dif;
    //geom_svc->initWireLUT();
    std::cout<<"detector: "<<det<<" ID: "<<geom_svc->getDetectorID(det)<<" Z0: "<<geom_svc->getDetectorZ0(det)<<std::endl;
  }

  // I THINK THIS RECO CONSTS WILL HANDLE IT ALL :), need to update
  Fun4AllServer *se = Fun4AllServer::instance();

  ///
  /// Global parameters
  ///
  const int run_id = 5433; // To select the plane geometry.
  double FMAGSTR = -1.044; // -1.054; F&KMAGSTR were changed on 2024-06-28
  double KMAGSTR = -1.025 * KMag_scale * KMag_polarity; // -0.951
  rc->set_IntFlag   ("RUNNUMBER", run_id);

  if (st3_pos_dif > -75)
    {
	    rc->set_DoubleFlag("ST3_HM_scaling_factor", 1.0);
	    
	    rc->set_DoubleFlag("SAGITTA_TARGET_CENTER_X_DC3p", 1.93);
	    rc->set_DoubleFlag("SAGITTA_TARGET_CENTER_U_DC3p", 2.04);
	    rc->set_DoubleFlag("SAGITTA_TARGET_CENTER_V_DC3p", 1.82);
	    rc->set_DoubleFlag("SAGITTA_TARGET_CENTER_X_DC3m", 1.99);
	    rc->set_DoubleFlag("SAGITTA_TARGET_CENTER_U_DC3m", 2.11);
	    rc->set_DoubleFlag("SAGITTA_TARGET_CENTER_V_DC3m", 1.89);
	    rc->set_DoubleFlag("SAGITTA_DUMP_CENTER_X_DC3p", 1.70);
	    rc->set_DoubleFlag("SAGITTA_DUMP_CENTER_U_DC3p", 1.78);
	    rc->set_DoubleFlag("SAGITTA_DUMP_CENTER_V_DC3p", 1.62);
	    rc->set_DoubleFlag("SAGITTA_DUMP_CENTER_X_DC3m", 1.75);
	    rc->set_DoubleFlag("SAGITTA_DUMP_CENTER_U_DC3m", 1.84);
	    rc->set_DoubleFlag("SAGITTA_DUMP_CENTER_V_DC3m", 1.66);
	    
	    rc->set_DoubleFlag("SAGITTA_TARGET_WIDTH_X_DC3p", 0.25);
	    rc->set_DoubleFlag("SAGITTA_TARGET_WIDTH_U_DC3p", 0.25);
	    rc->set_DoubleFlag("SAGITTA_TARGET_WIDTH_V_DC3p", 0.25);
	    rc->set_DoubleFlag("SAGITTA_TARGET_WIDTH_X_DC3m", 0.25);
	    rc->set_DoubleFlag("SAGITTA_TARGET_WIDTH_U_DC3m", 0.25);
	    rc->set_DoubleFlag("SAGITTA_TARGET_WIDTH_V_DC3m", 0.25);
	    rc->set_DoubleFlag("SAGITTA_DUMP_WIDTH_X_DC3p", 0.3);
	    rc->set_DoubleFlag("SAGITTA_DUMP_WIDTH_U_DC3p", 0.3);
	    rc->set_DoubleFlag("SAGITTA_DUMP_WIDTH_V_DC3p", 0.3);
	    rc->set_DoubleFlag("SAGITTA_DUMP_WIDTH_X_DC3m", 0.3);
	    rc->set_DoubleFlag("SAGITTA_DUMP_WIDTH_U_DC3m", 0.3);
	    rc->set_DoubleFlag("SAGITTA_DUMP_WIDTH_V_DC3m", 0.3);
	    
    }
    if (st3_pos_dif<=-75 && st3_pos_dif>-125){
	    rc->set_DoubleFlag("ST3_HM_scaling_factor", 1.5);
	    
	    rc->set_DoubleFlag("SAGITTA_TARGET_CENTER_X_DC3p", 2.14);
	    rc->set_DoubleFlag("SAGITTA_TARGET_CENTER_U_DC3p", 2.28);
	    rc->set_DoubleFlag("SAGITTA_TARGET_CENTER_V_DC3p", 2.00);
	    rc->set_DoubleFlag("SAGITTA_TARGET_CENTER_X_DC3m", 2.24);
	    rc->set_DoubleFlag("SAGITTA_TARGET_CENTER_U_DC3m", 2.40);
	    rc->set_DoubleFlag("SAGITTA_TARGET_CENTER_V_DC3m", 2.09);
	    rc->set_DoubleFlag("SAGITTA_DUMP_CENTER_X_DC3p", 1.87);
	    rc->set_DoubleFlag("SAGITTA_DUMP_CENTER_U_DC3p", 1.97);
	    rc->set_DoubleFlag("SAGITTA_DUMP_CENTER_V_DC3p", 1.76);
	    rc->set_DoubleFlag("SAGITTA_DUMP_CENTER_X_DC3m", 1.95);
	    rc->set_DoubleFlag("SAGITTA_DUMP_CENTER_U_DC3m", 2.08);
	    rc->set_DoubleFlag("SAGITTA_DUMP_CENTER_V_DC3m", 1.84);
	    
	    rc->set_DoubleFlag("SAGITTA_TARGET_WIDTH_X_DC3p", 0.25);
	    rc->set_DoubleFlag("SAGITTA_TARGET_WIDTH_U_DC3p", 0.25);
	    rc->set_DoubleFlag("SAGITTA_TARGET_WIDTH_V_DC3p", 0.25);
	    rc->set_DoubleFlag("SAGITTA_TARGET_WIDTH_X_DC3m", 0.25);
	    rc->set_DoubleFlag("SAGITTA_TARGET_WIDTH_U_DC3m", 0.25);
	    rc->set_DoubleFlag("SAGITTA_TARGET_WIDTH_V_DC3m", 0.25);
	    rc->set_DoubleFlag("SAGITTA_DUMP_WIDTH_X_DC3p", 0.3);
	    rc->set_DoubleFlag("SAGITTA_DUMP_WIDTH_U_DC3p", 0.3);
	    rc->set_DoubleFlag("SAGITTA_DUMP_WIDTH_V_DC3p", 0.3);
	    rc->set_DoubleFlag("SAGITTA_DUMP_WIDTH_X_DC3m", 0.3);
	    rc->set_DoubleFlag("SAGITTA_DUMP_WIDTH_U_DC3m", 0.3);
	    rc->set_DoubleFlag("SAGITTA_DUMP_WIDTH_V_DC3m", 0.3);
	    
	    rc->set_DoubleFlag("SAGITTA_TARGET_CENTER", 2.18);
	    rc->set_DoubleFlag("SAGITTA_DUMP_CENTER", 1.91);
    }
    if (st3_pos_dif<=-125 && st3_pos_dif>-225){
	    rc->set_DoubleFlag("ST3_HM_scaling_factor", 2.0);
	    
	    rc->set_DoubleFlag("SAGITTA_TARGET_CENTER_X_DC3p", 2.45);
	    rc->set_DoubleFlag("SAGITTA_TARGET_CENTER_U_DC3p", 2.65);
	    rc->set_DoubleFlag("SAGITTA_TARGET_CENTER_V_DC3p", 2.27);
	    rc->set_DoubleFlag("SAGITTA_TARGET_CENTER_X_DC3m", 2.61);
	    rc->set_DoubleFlag("SAGITTA_TARGET_CENTER_U_DC3m", 2.84);
	    rc->set_DoubleFlag("SAGITTA_TARGET_CENTER_V_DC3m", 2.40);
	    rc->set_DoubleFlag("SAGITTA_DUMP_CENTER_X_DC3p", 2.13);
	    rc->set_DoubleFlag("SAGITTA_DUMP_CENTER_U_DC3p", 2.30);
	    rc->set_DoubleFlag("SAGITTA_DUMP_CENTER_V_DC3p", 1.99);
	    rc->set_DoubleFlag("SAGITTA_DUMP_CENTER_X_DC3m", 2.27);
	    rc->set_DoubleFlag("SAGITTA_DUMP_CENTER_U_DC3m", 2.47);
	    rc->set_DoubleFlag("SAGITTA_DUMP_CENTER_V_DC3m", 2.10);
	    
	    rc->set_DoubleFlag("SAGITTA_TARGET_WIDTH_X_DC3p", 0.25);
	    rc->set_DoubleFlag("SAGITTA_TARGET_WIDTH_U_DC3p", 0.25);
	    rc->set_DoubleFlag("SAGITTA_TARGET_WIDTH_V_DC3p", 0.25);
	    rc->set_DoubleFlag("SAGITTA_TARGET_WIDTH_X_DC3m", 0.25);
	    rc->set_DoubleFlag("SAGITTA_TARGET_WIDTH_U_DC3m", 0.25);
	    rc->set_DoubleFlag("SAGITTA_TARGET_WIDTH_V_DC3m", 0.25);
	    rc->set_DoubleFlag("SAGITTA_DUMP_WIDTH_X_DC3p", 0.3);
	    rc->set_DoubleFlag("SAGITTA_DUMP_WIDTH_U_DC3p", 0.3);
	    rc->set_DoubleFlag("SAGITTA_DUMP_WIDTH_V_DC3p", 0.3);
	    rc->set_DoubleFlag("SAGITTA_DUMP_WIDTH_X_DC3m", 0.3);
	    rc->set_DoubleFlag("SAGITTA_DUMP_WIDTH_U_DC3m", 0.3);
	    rc->set_DoubleFlag("SAGITTA_DUMP_WIDTH_V_DC3m", 0.3);
	    
	    rc->set_DoubleFlag("SAGITTA_TARGET_CENTER", 2.54);
	    rc->set_DoubleFlag("SAGITTA_DUMP_CENTER", 2.21);
    }
  rc->set_DoubleFlag("FMAGSTR", FMAGSTR);
  rc->set_DoubleFlag("KMAGSTR", KMAGSTR);
  rc->set_CharFlag("VTX_GEN_MATERIAL_MODE", "Target");

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

  SetupInsensitiveVolumes(g4Reco);
  SetupBeamline(g4Reco);
  SetupTarget(g4Reco);
  SetupSensitiveDetectors(g4Reco);

  se->registerSubsystem(g4Reco);

  PHG4TruthSubsystem *truth = new PHG4TruthSubsystem();
  g4Reco->registerSubsystem(truth);

  /// digitizer
  SQDigitizer *digitizer = new SQDigitizer("DPDigitizer", 0);
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
