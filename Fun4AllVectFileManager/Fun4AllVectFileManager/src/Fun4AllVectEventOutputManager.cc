#include <cstdlib>
#include <string>
#include <iostream>
#include <iomanip>
#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <phool/phool.h>
#include <phool/getClass.h>
#include <phool/PHNode.h>
#include <phool/PHNodeIOManager.h>
#include <interface_main/SQEvent.h>
#include <interface_main/SQSpillMap.h>
#include <interface_main/SQHitVector.h>
#include <interface_main/SQDimuonVector.h>
#include <ktracker/SRecEvent.h>
#include <fun4all/Fun4AllReturnCodes.h>
#include "Fun4AllVectEventOutputManager.h"
using namespace std;

Fun4AllVectEventOutputManager::Fun4AllVectEventOutputManager(const std::string &myname)
  : Fun4AllOutputManager(myname),
    m_file(0),
    m_tree(0),
    m_tree_name("tree"),
    m_file_name("output.root"),
    m_evt(0),
    m_sp_map(0),
    m_hit_vec(0)
{
 ;
}

Fun4AllVectEventOutputManager::~Fun4AllVectEventOutputManager() {
    CloseFile();
}

int Fun4AllVectEventOutputManager::OpenFile(PHCompositeNode* startNode) {
std::cout << "Fun4AllVectEventOutputManager::OpenFile(): Attempting to open file: " << m_file_name << " with tree: " << m_tree_name << std::endl;
m_file = new TFile(m_file_name.c_str(), "RECREATE");

if (!m_file || m_file->IsZombie()) {
    std::cerr << "Error: Could not create file " << m_file_name << std::endl;
    exit(1);
} else {
    std::cout << "File " << m_file->GetName() << " opened successfully." << std::endl;
}

m_tree = new TTree(m_tree_name.c_str(), "Tree for storing events");
if (!m_tree) {
    std::cerr << "Error: Could not create tree " << m_tree_name << std::endl;
    exit(1);
} else {
    std::cout << "Tree " << m_tree->GetName() << " created successfully." << std::endl;
}
    m_tree->Branch("RunID", &RunID, "RunID/I");
    m_tree->Branch("SpillID", &SpillID, "SpillID/I");
    m_tree->Branch("EventID", &EventID, "EventID/I");
    m_tree->Branch("RFID", &RFID, "RFID/I");
    m_tree->Branch("TurnID", &TurnID, "TurnID/I");
    m_tree->Branch("Intensity", Intensity, "Intensity[33]/I");
    m_tree->Branch("fpga_triggers", fpga_triggers, "fpga_triggers[5]/I");
    m_tree->Branch("nim_triggers", nim_triggers, "nim_triggers[5]/I");

    m_tree->Branch("DetectorID", &DetectorID);
    m_tree->Branch("ElementID", &ElementID);
    m_tree->Branch("TdcTime", &TdcTime);
    m_tree->Branch("DriftDistance", &DriftDistance);
    m_tree->Branch("hit_in_time", &hit_in_time);

    m_tree->Branch("Trig_DetectorID", &Trig_DetectorID);
    m_tree->Branch("Trig_ElementID", &Trig_ElementID);
    m_tree->Branch("Trig_TdcTime", &Trig_TdcTime);
    m_tree->Branch("Trig_DriftDistance", &Trig_DriftDistance);
    m_tree->Branch("Trig_hit_in_time", &Trig_hit_in_time);

    m_evt = findNode::getClass<SQEvent>(startNode, "SQEvent");
    m_hit_vec = findNode::getClass<SQHitVector>(startNode, "SQHitVector");
    m_trig_hit_vec = findNode::getClass<SQHitVector>(startNode, "SQTriggerHitVector");

    if (!m_evt || !m_hit_vec || !m_trig_hit_vec) return Fun4AllReturnCodes::ABORTEVENT;
 return Fun4AllReturnCodes::EVENT_OK;
}
int Fun4AllVectEventOutputManager::Write(PHCompositeNode* startNode) {
	if (!m_file || !m_tree) {
		OpenFile(startNode);
	}
	ResetBranches();
	RunID = m_evt->get_run_id();
	SpillID = m_evt->get_spill_id();
	RFID = m_evt->get_qie_rf_id();
	EventID = m_evt->get_event_id();
	TurnID = m_evt->get_qie_turn_id();

	fpga_triggers[0] = m_evt->get_trigger(SQEvent::MATRIX1);
	fpga_triggers[1] = m_evt->get_trigger(SQEvent::MATRIX2);
	fpga_triggers[2] = m_evt->get_trigger(SQEvent::MATRIX3);
	fpga_triggers[3] = m_evt->get_trigger(SQEvent::MATRIX4);
	fpga_triggers[4] = m_evt->get_trigger(SQEvent::MATRIX5);

	nim_triggers[0] = m_evt->get_trigger(SQEvent::NIM1);
	nim_triggers[1] = m_evt->get_trigger(SQEvent::NIM2);
	nim_triggers[2] = m_evt->get_trigger(SQEvent::NIM3);
	nim_triggers[3] = m_evt->get_trigger(SQEvent::NIM4);
	nim_triggers[4] = m_evt->get_trigger(SQEvent::NIM5);


	for (int i = -16; i < 16; ++i) {

		//cout << "intensity intex: i" << i+16 << endl;
		Intensity[i+16] = m_evt->get_qie_rf_intensity(i);
	}

	if (m_hit_vec) {
		for (int ihit = 0; ihit < m_hit_vec->size(); ++ihit) {
			SQHit* hit = m_hit_vec->at(ihit);
			DetectorID.push_back(hit->get_detector_id());
			ElementID.push_back(hit->get_element_id());
			TdcTime.push_back(hit->get_tdc_time());
			DriftDistance.push_back(hit->get_drift_distance());
			//cout << "get drift distance: "<< hit->get_drift_distance()<<endl;
			hit_in_time.push_back(hit->is_in_time());
		}
	}

	if (m_trig_hit_vec) {
		for (int ihit = 0; ihit < m_trig_hit_vec->size(); ++ihit) {
			SQHit* hit = m_trig_hit_vec->at(ihit);
			Trig_DetectorID.push_back(hit->get_detector_id());
			Trig_ElementID.push_back(hit->get_element_id());
			Trig_TdcTime.push_back(hit->get_tdc_time());
			Trig_DriftDistance.push_back(hit->get_drift_distance());
			Trig_hit_in_time.push_back(hit->is_in_time());
		}   
	}   

	m_tree->Fill();
	return 0;
}

void Fun4AllVectEventOutputManager::CloseFile() {
    if (!m_file) return;
    std::cout << "Fun4AllVectEventOutputManager::CloseFile(): Closing file: " << m_file_name << std::endl;
    m_file->Write();
    m_file->Close();
    delete m_file;
    m_file = nullptr;
}

void Fun4AllVectEventOutputManager::ResetBranches() {
    DetectorID.clear();
    ElementID.clear();
    TdcTime.clear();
    DriftDistance.clear();
    hit_in_time.clear();

    Trig_DetectorID.clear();
    Trig_ElementID.clear();
    Trig_TdcTime.clear();
    Trig_DriftDistance.clear();
    Trig_hit_in_time.clear();
}

