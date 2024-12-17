#ifndef Fun4AllVectEventInputManager_H_
#define Fun4AllVectEventInputManager_H_
#include <fun4all/Fun4AllInputManager.h>
#include <string>
#include <vector>
#include <map>

class PHCompositeNode;
class SyncObject;

class TFile;
class TTree;
class SQRun;
class SQSpillMap;
class SQEvent;
class SQHitVector;

class Fun4AllVectEventInputManager : public Fun4AllInputManager {
public:
    Fun4AllVectEventInputManager(const std::string &name = "DUMMY", const std::string &topnodename = "TOP");
    virtual ~Fun4AllVectEventInputManager();

    int fileopen(const std::string &filename);
    int fileclose();
    int run(const int nevents = 0);
    int isOpen() { return isopen; }

    void Print(const std::string &what = "ALL") const;
    int ResetEvent();
    int PushBackEvents(const int i);
    int GetSyncObject(SyncObject **mastersync);
    int SyncIt(const SyncObject *mastersync);

    const std::string& get_branch_name() const { return _branch_name; }
    void set_branch_name(const std::string& branchName) { _branch_name = branchName; }

    const std::string& get_tree_name() const { return _tree_name; }
    void set_tree_name(const std::string& treeName) { _tree_name = treeName; }

protected:
    int OpenNextFile();
    void VectToE1039();
    int segment;
    int isopen;
    int events_total;
    int events_thisfile;
    std::string topNodeName;
    PHCompositeNode *topNode;
    SyncObject* syncobject;

    std::string _tree_name;
    std::string _branch_name;

    TFile* _fin;
    TTree* _tin;

    // Data vectors for ROOT file branches
    int EventID;
    int SpillID;
    int RunID;
    
    std::vector<int>* DetectorID = nullptr;
    std::vector<int>* ElementID = nullptr;
    std::vector<double>* DriftDistance = nullptr;
    std::vector<double>* TdcTime = nullptr;
    std::vector<bool>* hit_in_time=nullptr;

    std::vector<int>* Trig_DetectorID = nullptr;
    std::vector<int>* Trig_ElementID = nullptr;
    std::vector<double>* Trig_TdcTime = nullptr;
    std::vector<int>* Trig_DriftDistance = nullptr;
    std::vector<bool>* Trig_hit_in_time=nullptr;

    int fpga_triggers[5] = {0};
    int nim_triggers[5] = {0};
    int Intensity[33] = {0};

   SQRun*       run_header;
   SQSpillMap*  spill_map;
   SQEvent*     event_header;
   SQHitVector* hit_vec;
   SQHitVector* trig_hit_vec;
};

#endif /* __Fun4AllVectEventInputManager_H_ */
