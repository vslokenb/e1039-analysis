#include <iomanip>
#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <interface_main/SQRun.h>
#include <interface_main/SQHitVector.h>
#include <interface_main/SQEvent.h>
#include <ktracker/SRecEvent.h>
#include <fun4all/Fun4AllReturnCodes.h>
#include <phool/PHNodeIterator.h>
#include <phool/PHIODataNode.h>
#include <phool/getClass.h>
#include <geom_svc/GeomSvc.h>
//#include <UtilAna/UtilHist.h>
#include "AnaDimuon.h"
using namespace std;

AnaDimuon::AnaDimuon(const std::string& name)
  : SubsysReco  (name)
  , m_sq_evt    (0)
  , m_sq_hit_vec(0)
  , m_srec      (0)
  , m_file_name ("output.root")
  , m_file      (0)
  , m_tree      (0)
{
  ;
}

AnaDimuon::~AnaDimuon()
{
  ;
}

int AnaDimuon::Init(PHCompositeNode* topNode)
{
  return Fun4AllReturnCodes::EVENT_OK;
}

int AnaDimuon::InitRun(PHCompositeNode* topNode)
{
  m_sq_evt     = findNode::getClass<SQEvent    >(topNode, "SQEvent");
  m_sq_hit_vec = findNode::getClass<SQHitVector>(topNode, "SQHitVector");
  m_srec       = findNode::getClass<SRecEvent  >(topNode, "SRecEvent");
  if (!m_sq_evt || !m_sq_hit_vec || !m_srec) return Fun4AllReturnCodes::ABORTEVENT;

  m_file = new TFile(m_file_name.c_str(), "RECREATE");
  m_tree = new TTree("tree", "Created by AnaDimuon");
  m_tree->Branch("event"      , &m_evt);
  m_tree->Branch("dimuon_list", &m_dim_list);

  SQRun* sq_run = findNode::getClass<SQRun>(topNode, "SQRun");
  if (!sq_run) return Fun4AllReturnCodes::ABORTEVENT;
  int LBtop = sq_run->get_v1495_id(2);
  int LBbot = sq_run->get_v1495_id(3);
  int ret = m_rs.LoadConfig(LBtop, LBbot);
  if (ret != 0) {
    cout << "!!WARNING!!  OnlMonTrigEP::InitRunOnlMon():  roadset.LoadConfig returned " << ret << ".\n";
  }
  cout <<"Roadset " << m_rs.str(1) << endl;

  return Fun4AllReturnCodes::EVENT_OK;
}

int AnaDimuon::process_event(PHCompositeNode* topNode)
{
  //if (! m_sq_evt->get_trigger(SQEvent::MATRIX1)) {
  //  return Fun4AllReturnCodes::EVENT_OK;
  //}

  m_evt.run_id    = m_sq_evt->get_run_id();
  m_evt.spill_id  = m_sq_evt->get_spill_id();
  m_evt.event_id  = m_sq_evt->get_event_id();
  m_evt.fpga_bits = (m_sq_evt->get_trigger() >> SQEvent::MATRIX1) & 0x1f;
  m_evt.nim_bits  = (m_sq_evt->get_trigger() >> SQEvent::NIM1   ) & 0x1f;

  m_evt.D1 = m_evt.D2 = m_evt.D3p = m_evt.D3m = 0;
  for (SQHitVector::Iter it = m_sq_hit_vec->begin(); it != m_sq_hit_vec->end(); it++) {
    SQHit* hit = *it;
    int det_id = hit->get_detector_id();
    if      ( 0 < det_id && det_id <=  6) m_evt.D1++;
    else if (12 < det_id && det_id <= 18) m_evt.D2++;
    else if (18 < det_id && det_id <= 24) m_evt.D3p++;
    else if (24 < det_id && det_id <= 30) m_evt.D3m++;
  }
  
  m_dim_list.clear();
  int n_dim = m_srec->getNDimuons();
  for (int i_dim = 0; i_dim < n_dim; i_dim++) {
    SRecDimuon sdim = m_srec->getDimuon(i_dim);
    SRecTrack trk_pos = m_srec->getTrack(sdim.get_track_id_pos());
    SRecTrack trk_neg = m_srec->getTrack(sdim.get_track_id_neg());

    int road_pos = trk_pos.getTriggerRoad();
    int road_neg = trk_neg.getTriggerRoad();
    bool pos_top = m_rs.PosTop()->FindRoad(road_pos);
    bool pos_bot = m_rs.PosBot()->FindRoad(road_pos);
    bool neg_top = m_rs.NegTop()->FindRoad(road_neg);
    bool neg_bot = m_rs.NegBot()->FindRoad(road_neg);
    //cout << "T " << road_pos << " " << road_neg << " " << pos_top << pos_bot << neg_top << neg_bot << endl;

    DimuonData dd;
    dd.road_pos   = road_pos;
    dd.road_neg   = road_neg;
    dd.pos_top    = pos_top;
    dd.pos_bot    = pos_bot;
    dd.neg_top    = neg_top;
    dd.neg_bot    = neg_bot;
    dd.pos        = sdim.get_pos();
    dd.mom        = sdim.get_mom();
    dd.n_hits_pos = trk_pos.get_num_hits();
    dd.chisq_pos  = trk_pos.get_chisq();
    dd.pos_pos    = trk_pos.get_pos_vtx();
    dd.mom_pos    = trk_pos.get_mom_vtx();
    dd.n_hits_neg = trk_neg.get_num_hits();
    dd.chisq_neg  = trk_neg.get_chisq();
    dd.pos_neg    = trk_neg.get_pos_vtx();
    dd.mom_neg    = trk_neg.get_mom_vtx();
    
    m_dim_list.push_back(dd);
  }
  
  //GeomSvc* geom = GeomSvc::instance();

  m_tree->Fill();
  return Fun4AllReturnCodes::EVENT_OK;
}

int AnaDimuon::End(PHCompositeNode* topNode)
{
  m_file->cd();
  m_file->Write();
  m_file->Close();  
  return Fun4AllReturnCodes::EVENT_OK;
}

void AnaDimuon::AnalyzeTree(TChain* tree)
{
  cout << "N of trees = " << tree->GetNtrees() << endl;

  TH1* h1_D1  = new TH1D("h1_D1" ,  ";D1 occupancy;N of events", 500, -0.5, 499.5);
  TH1* h1_D2  = new TH1D("h1_D2" ,  ";D2 occupancy;N of events", 300, -0.5, 299.5);
  TH1* h1_D3p = new TH1D("h1_D3p", ";D3p occupancy;N of events", 300, -0.5, 299.5);
  TH1* h1_D3m = new TH1D("h1_D3m", ";D3m occupancy;N of events", 300, -0.5, 299.5);
  
  TH1* h1_nhit_pos = new TH1D("h1_nhit_pos", "#mu^{+};N of hits/track;", 6, 12.5, 18.5);
  TH1* h1_chi2_pos = new TH1D("h1_chi2_pos", "#mu^{+};Track #chi^{2};", 100, 0, 2);
  TH1* h1_z_pos    = new TH1D("h1_z_pos"   , "#mu^{+};Track z (cm);"  , 100, -500, 500);
  TH1* h1_pz_pos   = new TH1D("h1_pz_pos"  , "#mu^{+};Track p_{z} (GeV);", 100, 0, 100);

  TH1* h1_nhit_neg = new TH1D("h1_nhit_neg", "#mu^{+};N of hits/track;", 6, 12.5, 18.5);
  TH1* h1_chi2_neg = new TH1D("h1_chi2_neg", "#mu^{+};Track #chi^{2};", 100, 0, 2);
  TH1* h1_z_neg    = new TH1D("h1_z_neg"   , "#mu^{+};Track z (cm);", 100, -500, 500);
  TH1* h1_pz_neg   = new TH1D("h1_pz_neg"  , "#mu^{+};Track p_{z} (GeV);", 100, 0, 100);

  TH1* h1_dx  = new TH1D("h1_dx" , ";Dimuon x (cm);", 100, -1, 1);
  TH1* h1_dy  = new TH1D("h1_dy" , ";Dimuon y (cm);", 100, -1, 1);
  TH1* h1_dz  = new TH1D("h1_dz" , ";Dimuon z (cm);", 100, -500, 500);
  TH1* h1_dpx = new TH1D("h1_dpx", ";Dimuon p_{x} (GeV);", 100, -5, 5);
  TH1* h1_dpy = new TH1D("h1_dpy", ";Dimuon p_{y} (GeV);", 100, -5, 5);
  TH1* h1_dpz = new TH1D("h1_dpz", ";Dimuon p_{z} (GeV);", 100, 30, 130);
  TH1* h1_m   = new TH1D("h1_m"  , ";Dimuon mass (GeV);", 100, 0, 10);

  //GeomSvc* geom = GeomSvc::instance();
  ostringstream oss;
  
  EventData* evt = 0;
  DimuonList* dim_list = 0;
  tree->SetBranchAddress("event"      , &evt);
  tree->SetBranchAddress("dimuon_list", &dim_list);

  int n_ent = tree->GetEntries();
  cout << "N of entries = " << n_ent << endl;
  for (int i_ent = 0; i_ent < n_ent; i_ent++) {
    if ((i_ent+1) % (n_ent/10) == 0) cout << "  " << 10*(i_ent+1)/(n_ent/10) << "%" << flush;
    tree->GetEntry(i_ent);

    if (! (evt->fpga_bits & 0x1)) continue;
    //if (! (evt->nim_bits & 0x4)) continue;

    h1_D1 ->Fill(evt->D1 );
    h1_D2 ->Fill(evt->D2 );
    h1_D3p->Fill(evt->D3p);
    h1_D3m->Fill(evt->D3m);
    //if (evt->D1 > 120 || evt->D2 > 60 || evt->D3p > 50 || evt->D3m > 50) continue;
    
    for (auto it = dim_list->begin(); it != dim_list->end(); it++) {
      DimuonData* dd = &(*it);
      //bool top_bot = dd->pos_top && dd->neg_bot;
      //bool bot_top = dd->pos_bot && dd->neg_top;
      ////cout << "d " << top_bot << bot_top << endl;
      //if (!top_bot && !bot_top) continue;

      //cout << evt->run_id << " " << evt->spill_id << " " << evt->event_id << " "
      //     << evt-> D1 << " " << evt-> D2 << " " << evt-> D3p << " " << evt-> D3m << " "
      //     << dd->pos.Z() << " " << dd->mom.M() << endl;
      
      h1_nhit_pos->Fill(dd->n_hits_pos);
      h1_chi2_pos->Fill(dd->chisq_pos);
      h1_z_pos   ->Fill(dd->pos_pos.Z());
      h1_pz_pos  ->Fill(dd->mom_pos.Z());

      h1_nhit_neg->Fill(dd->n_hits_neg);
      h1_chi2_neg->Fill(dd->chisq_neg);
      h1_z_neg   ->Fill(dd->pos_neg.Z());
      h1_pz_neg  ->Fill(dd->mom_neg.Z());

      if (dd->n_hits_pos < 15 || dd->pos_pos.Z() < -490 ||
          dd->n_hits_neg < 15 || dd->pos_neg.Z() < -490   ) continue;

      h1_dx ->Fill(dd->pos.X());
      h1_dy ->Fill(dd->pos.Y());
      h1_dz ->Fill(dd->pos.Z());
      h1_dpx->Fill(dd->mom.X());
      h1_dpy->Fill(dd->mom.Y());
      h1_dpz->Fill(dd->mom.Z());
      h1_m  ->Fill(dd->mom.M());
    }
  }
  
  gSystem->mkdir("result", true);
  TCanvas* c1 = new TCanvas("c1", "");
  c1->SetGrid();
  //c1->SetLogy(true);

  h1_D1->Draw();
  c1->SaveAs("result/h1_D1.png");
  h1_D2->Draw();
  c1->SaveAs("result/h1_D2.png");
  h1_D3p->Draw();
  c1->SaveAs("result/h1_D3p.png");
  h1_D3m->Draw();
  c1->SaveAs("result/h1_D3m.png");
  
  h1_nhit_pos->Draw();
  c1->SaveAs("result/h1_nhit_pos.png");  
  h1_chi2_pos->Draw();
  c1->SaveAs("result/h1_chi2_pos.png");  
  h1_z_pos   ->Draw();;
  c1->SaveAs("result/h1_z_pos.png");  
  h1_pz_pos  ->Draw();
  c1->SaveAs("result/h1_pz_pos.png");  

  h1_nhit_neg->Draw();
  c1->SaveAs("result/h1_nhit_neg.png");  
  h1_chi2_neg->Draw();
  c1->SaveAs("result/h1_chi2_neg.png");  
  h1_z_neg   ->Draw();;
  c1->SaveAs("result/h1_z_neg.png");  
  h1_pz_neg  ->Draw();
  c1->SaveAs("result/h1_pz_neg.png");  

  h1_dx ->Draw();
  c1->SaveAs("result/h1_dx.png");
  h1_dy ->Draw();
  c1->SaveAs("result/h1_dy.png");
  h1_dz ->Draw();
  c1->SaveAs("result/h1_dz.png");
  h1_dpx->Draw();
  c1->SaveAs("result/h1_dpx.png");
  h1_dpy->Draw();
  c1->SaveAs("result/h1_dpy.png");
  h1_dpz->Draw();
  c1->SaveAs("result/h1_dpz.png");
  h1_m->Draw();
  c1->SaveAs("result/h1_m.png");

  delete c1;
}

